#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	// Default constructor, should never be used
	throw std::exception("[NetworkManager] Default constructor should never be used");
}
NetworkManager::NetworkManager(const std::string& _address, const unsigned short& _port)
{
	// Client constructor
	address = _address;
	port = _port;
	type = ENetworkType::CLIENT;
	id = -1;
}
NetworkManager::NetworkManager(const unsigned short& _port)
{
	// Server constructor
	address = "";
	port = _port;
	type = ENetworkType::SERVER;
	id = -1;
}
NetworkManager::~NetworkManager()
{
	if (socket)
		delete socket;
	if (listener)
		delete listener;
	for (sf::TcpSocket* _client : clients)
		delete _client;
}

void NetworkManager::Start()
{
	socket = new sf::TcpSocket();
	if (IsServer())
	{
		HostServer();
	}
	else
	{
		ConnectClient();
	}
}
void NetworkManager::ListenForClients(unsigned int _amount)
{
	if (!IsServer())
	{
		std::cerr << "[NetworkManager] Error: Only server can listen for users!" << std::endl;
		return;
	}

	const int _initialAmount = _amount;

	sf::TcpSocket* _client = new sf::TcpSocket();

	std::cout << "[Server] Listening for clients... (" << _initialAmount - _amount << "/" << _initialAmount << ")" << std::endl;

	while (_amount >= 1)
	{
		if (!_client)
			_client = new sf::TcpSocket();
		if (listener->accept(*_client) == sf::Socket::Done)
		{
			const int _id = static_cast<int>(clientsIDMap.size()) + 1; // ID 0 is the server, so skip it
			clients.push_back(_client);
			clientsIDMap[_id] = _client;
			SendData(_client, "NewNetworkID", std::to_string(_id));
			_client = new sf::TcpSocket();
			_amount--;
			std::cout << "[Server] A client has joined! (" << _initialAmount - _amount << "/" << _initialAmount << ") Given id: " << _id << std::endl;
		}
	}
	delete _client;
	std::cout << "[Server] Server is full!" << std::endl;
}
void NetworkManager::ConnectClient()
{
	std::cout << "[NetworkManager] Connecting to server... (" << address << ":" << port << ")" << std::endl;
	sf::Socket::Status _status = socket->connect(address, port);
	if (_status == sf::Socket::Done)
	{
		std::cout << "[NetworkManager] Connected to server!" << std::endl;
		return;
	}
	std::cerr << "[NetworkManager] Error: Server couldn't be reached!" << std::endl;
}
void NetworkManager::HostServer()
{
	id = 0;
	std::cout << "[NetworkManager] Starting server..." << std::endl;
	listener = new sf::TcpListener();
	if (listener->listen(port) == sf::Socket::Done)
	{
		std::cout << "[NetworkManager] Server started! Listening on port " << port << "" << std::endl;
		return;
	}
	std::cerr << "[NetworkManager] Error: Server couldn't be started!" << std::endl;
}
const bool NetworkManager::IsServer()
{
	return type == ENetworkType::SERVER;
}
const int NetworkManager::GetClientsCount()
{
	return static_cast<int>(clients.size());
}
// Public method, used to send info to server or all clients
void NetworkManager::SendData(const std::string& _packetTitle, const std::string& _packetData)
{
	NetworkDataPacket _customPacketData = NetworkDataPacket(id, _packetTitle, _packetData, ENetworkDataType::CUSTOM);
	sf::Packet _packet;
	_packet << _customPacketData.ToString();
	for (sf::TcpSocket* _client : clients)
	{
		_client->send(_packet);
	}
}
// Private method, used only by server in specific cases (Sending client ID)
void NetworkManager::SendData(sf::TcpSocket* _client, const std::string& _packetTitle, const std::string& _packetData)
{
	NetworkDataPacket _customPacketData = NetworkDataPacket(id, _packetTitle, _packetData, ENetworkDataType::CUSTOM);
	sf::Packet _packet;
	_packet << _customPacketData.ToString();
	_client->send(_packet);
}
NetworkDataPacket NetworkManager::FetchData()
{
	NetworkDataPacket _packetData;
	sf::Packet _packet;
	if (socket->receive(_packet) == sf::Socket::Done)
	{
		std::string _dataString;
		_packet >> _dataString;
		_packetData = NetworkDataPacket(_dataString);
	}
	return _packetData;
}
void NetworkManager::CheckForNewIDPacker(const NetworkDataPacket& _packetData)
{
	std::string _message;
	if (_packetData.title == "NewNetworkID")
	{
		const int _id = std::stoi(_packetData.data);
		id = _id;
		std::cout << "[NetworkManager] Got ID: " << std::to_string(id) << "" << std::endl;
	}
}
NetworkDataPacket NetworkManager::Tick()
{
	NetworkDataPacket _packetData = FetchData();
	if (_packetData.IsValid())
	{
		std::cout << "[Incoming Packet] (From: " << _packetData.fromClientID << ")->" << _packetData.title << ": " << _packetData.data << std::endl;
		CheckForNewIDPacker(_packetData);
	}
	return _packetData;
}