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
}
NetworkManager::NetworkManager(const unsigned short& _port)
{
	// Server constructor
	address = "";
	port = _port;
	type = ENetworkType::SERVER;
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
			clients.push_back(_client);
			_client = new sf::TcpSocket();
			_amount--;
			std::cout << "[Server] A client has joined! (" << _initialAmount - _amount << "/" << _initialAmount << ")" << std::endl;
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
void NetworkManager::SendData(const std::string& _data)
{
	std::string _dataToSend = "[1][" + _data + "]";
	char _dataArray[] = { *_dataToSend.c_str()};
	for (sf::TcpSocket* _client : clients)
	{
		_client->send(_dataArray, 500);
	}
}

NetworkData& NetworkManager::FetchData()
{
	NetworkData _dataStruct = NetworkData();
	char _data[500];
	std::size_t _received;
	if (socket->receive(_data, 500, _received) == sf::Socket::Done)
	{
		_dataStruct.dataSize = _received;
		_dataStruct.type = static_cast<ENetworkDataType>(_data[1]);
		std::string _dataString = std::string(_data);
		_dataStruct.data = _dataString.substr(4, _received - 1);
	}
	return _dataStruct;
}