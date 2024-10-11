#include "NetworkManager.h"
#include "PacketData.h"
#include "NetworkInterface.h"

#pragma region Constructors

NetworkManager::NetworkManager()
{
	mainThreadID = std::this_thread::get_id();
	networkThread = new sf::Thread(&NetworkManager::NetworkLoop, this);
	Init();
}

NetworkManager::~NetworkManager()
{
	isAlive = false; // Stopping all loops from network thread
	if (IsStarted())
	{
		if (!IsServer()) DisconnectFromServer();
		else SendPacketCloseServer();
	}
	DeleteAll();
}

#pragma endregion

void NetworkManager::PrintDebug(const std::string& _message)
{
	if (!debugsMessages) return;
	std::cout << "[NetworkManager]>>> " << _message << std::endl;
}

void NetworkManager::StartServer(const unsigned short _port)
{
	if (IsStarted())
	{
		PrintDebug("NetworkManager is already being used!");
		return;
	}
	PrintDebug("Starting server...");
	type = ENetworkType::SERVER;
	port = _port;
	id = 0;
	listener = new sf::TcpListener();
	listener->setBlocking(isListenerBlocking);
	PrintDebug("Server started!");
	StartNetworkThread();
}

void NetworkManager::StartListen()
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (!IsServer())
	{
		PrintDebug("NetworkManager is not a server!");
		return;
	}
	if (isServerListening)
	{
		PrintDebug("Server is already listening!");
		return;
	}
	if (maxClients == 0) SetClientLimit(1);
	if (listener->listen(port) != sf::Socket::Done)
	{
		PrintDebug("Failed to enable listening mode for the server!");
		ResetNetwork();
		return;
	}
	isServerListening = true;
	PrintDebug("Server is now listening!");
	if (ComputeServerFull()) ServerIsFull();
}

void NetworkManager::StopListen()
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (!IsServer())
	{
		PrintDebug("NetworkManager is not a server!");
		return;
	}
	if (!isServerListening)
	{
		PrintDebug("Server wasn't listening!");
		return;
	}
	PrintDebug("Server is not listening anymore!");
	listener->close();
	isServerListening = false;
}

void NetworkManager::SetClientLimit(const int _maxClients)
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (!IsServer())
	{
		PrintDebug("NetworkManager is not a server!");
		return;
	}
	maxClients = _maxClients;
	PrintDebug("Client limit set to: " + std::to_string(maxClients) + " | Currently: " + std::to_string(amountOfConnectedClients) + "/" + std::to_string(maxClients));
	if (ComputeServerFull()) ServerIsFull();
}

void NetworkManager::SetConfigListenerBlocking(const bool& _listenerBlocking)
{
	isListenerBlocking = _listenerBlocking;
	if (!listener) return;
	listener->setBlocking(isListenerBlocking);
}

void NetworkManager::StartClient(const std::string& _address, const unsigned short _port)
{
	if (IsStarted())
	{
		PrintDebug("NetworkManager is already being used!");
		return;
	}
	PrintDebug("Joining server...");
	type = ENetworkType::CLIENT;
	address = _address;
	port = _port;
	server = new sf::TcpSocket();
	if (server->connect(address, port) != sf::Socket::Done)
	{
		PrintDebug("Failed to connect to server!");
		ResetNetwork();
		return;
	}
	PrintDebug("Server joined!");
	StartNetworkThread();
}

void NetworkManager::SendData(const std::string& _packetID, const std::string& _data, const EPacketType& _packetType, const int& _toClient)
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (_packetID == "")
	{
		PrintDebug("Packet ID can't be empty!");
		return;
	}
	if (_packetType == EPacketType::TOCLIENT && _toClient == -1)
	{
		PrintDebug("Client ID needs to be specified!");
		return;
	}
	if (_packetType == EPacketType::TOSERVER && IsServer())
	{
		PrintDebug("Server cannot send data to server!");
		return;
	}

	const int _toID = _packetType == EPacketType::TOSERVER ? 0 : _packetType == EPacketType::TOCLIENT ? _toClient : -1;

	PacketData _packetData = PacketData(id, _toID, _packetID, _data);

	if (IsServer())
	{
		sf::Packet _packet;
		_packet << _packetData;
		HandlePacket(_packet);
	}
	else
	{
		sf::Packet _packet;
		_packet << _packetData;
		server->send(_packet);
	}
}

void NetworkManager::Disconnect(const std::string& _reason)
{
	DisconnectFromServer(_reason);
	if (server) delete server;
	server = nullptr;
	ResetNetwork();
}

void NetworkManager::CloseServer()
{
	SendPacketCloseServer();
	ResetNetwork();
}

void NetworkManager::DisconnectFromServer(const std::string& _reason)
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (IsServer())
	{
		PrintDebug("Cannot disconnect as the server! Did you meant to use 'CloseServer()' ?");
		return;
	}
	PrintDebug("Disconnecting from server...");
	SendData("UserDisconnected", _reason, EPacketType::TOALL);
	server->disconnect();
	PrintDebug("Disconnected from server!");
}

void NetworkManager::SendPacketCloseServer()
{
	if (!IsStarted())
	{
		PrintDebug("NetworkManager is not started!");
		return;
	}
	if (!IsServer())
	{
		PrintDebug("Cannot close the server as a client! Did you meant to use 'Disconnect()' ?");
		return;
	}
	PrintDebug("Closing server...");
	for (sf::TcpSocket* _client : clients)
	{
		ReplicateData(PacketData(0, -1, "KickedFromServer", "Server closed!"));
		_client->disconnect();
	}
	PrintDebug("Server closed!");
}

void NetworkManager::KickedFromServer(const PacketData& _packetData)
{
	PrintDebug("Kicked from server: " + _packetData.data);
	DisconnectFromServer();
	ResetNetwork();
}

void NetworkManager::Init()
{
	netInterface = new NetworkInterface();
	netInterface->SetManager(this);
	AddDefaultEventsCallbacks();
}

bool NetworkManager::IsStarted()
{
	return type != ENetworkType::NONE;
}

void NetworkManager::NetworkLoop()
{
	if (IsServer()) ServerLoop();
	else ClientLoop();
}

void NetworkManager::StartNetworkThread()
{
	PrintDebug("Starting NetworkThread...");
	isAlive = true;
	networkThread->launch();
	PrintDebug("NetworkThread started!");
}

bool NetworkManager::ComputeServerFull()
{
	PrintDebug("Connected clients: " + std::to_string(amountOfConnectedClients) + "/" + std::to_string(maxClients));
	isServerFull = amountOfConnectedClients >= maxClients;
	return isServerFull;
}

void NetworkManager::ResetNetwork()
{
	PrintDebug("Reinitializing NetworkManager...");
	isAlive = false;
	type = ENetworkType::NONE;
	address = "";
	port = 0;
	if (std::this_thread::get_id() == mainThreadID) networkThread->wait();
	DeleteAll(false);
	server = nullptr;
	listener = nullptr;
	clients.clear();
	clientsIDMap.clear();
	netInterface = nullptr;
	id = -1;
	maxClients = 0;
	isServerListening = false;
	isAlive = true;
	isServerFull = true;
	amountOfConnectedClients = 0;
	globalID = 0;
	Init();
	PrintDebug("NetworkManager reinitialized and ready to be used again!");
}

void NetworkManager::DeleteAll(const bool& _withThread)
{
	if (server) delete server;
	server = nullptr;
	if (listener) delete listener;
	listener = nullptr;
	for (sf::TcpSocket* _client : clients) delete _client;
	if (_withThread && networkThread) delete networkThread;
	if (netInterface) delete netInterface;
	netInterface = nullptr;
}

void NetworkManager::ServerIsFull()
{
	PrintDebug("Server is full!");
	if (isServerListening) StopListen();
}

void NetworkManager::ChangeNetworkID(const PacketData& _packetData)
{
	id = std::stoi(_packetData.data);
	PrintDebug("Network ID changed to: " + std::to_string(id));
}

void NetworkManager::AddDefaultEventsCallbacks()
{
	netInterface->AddCustomEvent("NewNetworkID", [&](const PacketData& _packetData) { ChangeNetworkID(_packetData); });
	netInterface->OnDisconnectEvent()->AddDynamic([&](const PacketData& _packetData) { UserDisconnected(_packetData); });
	netInterface->OnKickedFromServer()->AddDynamic([&](const PacketData& _packetData) { KickedFromServer(_packetData); });
}

void NetworkManager::SendDataTo(sf::TcpSocket* _client, const PacketData& _packetData)
{
	sf::Packet _packet;
	_packet << _packetData;
	_client->send(_packet);
}

void NetworkManager::HandlePacket(sf::Packet& _packet)
{
	std::string _packetDataLine;
	_packet >> _packetDataLine;
	PacketData _packetData = PacketData(_packetDataLine);
	if (!_packetData.isValid) return;
	if (_packetData.toClientID != -1)
	{
		if (_packetData.toClientID == id || _packetData.toClientID == -2)
		{
			PrintDebug("[[[Incoming packet]]] from " + std::to_string(_packetData.fromClientID) + " to " + (_packetData.toClientID == -1 ? "all" : _packetData.toClientID == -2 ? "self" : std::to_string(_packetData.toClientID)) + ": " + _packetData.title);
			netInterface->HandlePacket(_packetData);
		}
	}
	else
	{
		PrintDebug("[[[Incoming packet]]] from " + std::to_string(_packetData.fromClientID) + " to " + (_packetData.toClientID == -1 ? "all" : _packetData.toClientID == -2 ? "self" : std::to_string(_packetData.toClientID)) + ": " + _packetData.title);
		netInterface->HandlePacket(_packetData);
	}
	if (_packetData.toClientID == 0) return;
	if (IsServer()) ReplicateData(_packetData);
}

void NetworkManager::ReplicateData(PacketData _packetData)
{
	if (_packetData.toClientID == -1)
	{
		for (sf::TcpSocket* _client : clients)
		{
			SendDataTo(_client, _packetData);
		}
	}
	else
	{
		if (clientsIDMap.find(_packetData.toClientID) == clientsIDMap.end()) return;
		SendDataTo(clientsIDMap[_packetData.toClientID], _packetData);
	}
}

void NetworkManager::UserDisconnected(const PacketData& _packetData)
{
	if (!IsServer()) return;
	PrintDebug("Client " + std::to_string(_packetData.fromClientID) + " disconnected from the server (Reason: " + _packetData.data + "), removing references...");
	if (clientsIDMap.find(_packetData.fromClientID) != clientsIDMap.end())
	{
		sf::TcpSocket* _client = clientsIDMap[_packetData.fromClientID];
		clientsIDMap.erase(_packetData.fromClientID);
		clients.erase(std::remove(clients.begin(), clients.end(), _client), clients.end());
		delete _client;
	}
	PrintDebug("Removed references!");
	amountOfConnectedClients--;
	PrintDebug("Connected clients: " + std::to_string(amountOfConnectedClients) + "/" + std::to_string(maxClients) + "");
}

void NetworkManager::ServerLoop()
{
	while (isAlive)
	{
		if (!isServerFull && isServerListening) ListenForClients();
		ServerListenForPackets();
	}
}

void NetworkManager::ClientLoop()
{
	while (server)
	{
		ClientListenForPackets();
	}
}

void NetworkManager::ListenForClients()
{
	sf::TcpSocket* _client = new sf::TcpSocket();
	if (listener->accept(*_client) == sf::Socket::Done)
	{
		_client->setBlocking(false);
		amountOfConnectedClients++;
		globalID++;
		PrintDebug("New client joined! Sended ID: " + std::to_string(globalID));
		SendData("UserConnected", std::to_string(globalID), EPacketType::TOALL);
		clients.push_back(_client);
		clientsIDMap[globalID] = _client;
		SendDataTo(_client, PacketData(0, -2, "NewNetworkID", std::to_string(globalID)));
		SendDataTo(_client, PacketData(0, globalID, "JoinServer", ""));
		if (ComputeServerFull()) ServerIsFull();
	}
	else
	{
		delete _client;
	}
}

void NetworkManager::ServerListenForPackets()
{
	for (sf::TcpSocket* _client : clients)
	{
		sf::Packet packet;
		if (_client->receive(packet) == sf::Socket::Done)
		{
			HandlePacket(packet);
		}
	}
}

void NetworkManager::ClientListenForPackets()
{
	sf::Packet packet;
	if (server->receive(packet) == sf::Socket::Done)
	{
		HandlePacket(packet);
	}
}

void NetworkManager::Exit()
{
	if (IsServer()) CloseServer();
	else Disconnect();
}