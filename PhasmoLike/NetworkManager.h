#pragma once

#include <SFML/Network.hpp>
#include <iostream>

enum class ENetworkDataType
{
	NONE,
	REPLICATE
};

struct NetworkData
{
	std::string data;
	std::size_t dataSize;
	ENetworkDataType type;

public:
	NetworkData()
	{
		data = "";
		dataSize = 0;
		type = ENetworkDataType::NONE;
	}
	NetworkData(const std::string& _data, const std::size_t& _dataSize, const ENetworkDataType& _type)
	{
		data = _data;
		dataSize = _dataSize;
		type = _type;
	}
};

enum class ENetworkType
{
	CLIENT,
	SERVER
};

class NetworkManager
{
	// Network type
	ENetworkType type = ENetworkType::CLIENT;
	// Address
	std::string address = "127.0.0.1";
	// Port
	unsigned short port = 0;
	// Socket for client (Server is also a client)
	sf::TcpSocket* socket;
	// Listener for server
	sf::TcpListener* listener;
	// List of clients connected to the server
	std::vector<sf::TcpSocket*> clients;

public:
	// Default constructor | DO NOT USE
	NetworkManager();
	// Client constructor
	NetworkManager(const std::string& _address, const unsigned short& _port);
	// Server constructor
	NetworkManager(const unsigned short& _port);
	~NetworkManager();

private:
	void ConnectClient();
	void HostServer();
	const bool IsServer();

public:
	void Start();
	void ListenForClients(unsigned int _amount);
	const int GetClientsCount();
	void SendData(const std::string& _data);
	NetworkData& FetchData();
};