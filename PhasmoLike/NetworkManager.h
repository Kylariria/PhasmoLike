#pragma once

#include <SFML/Network.hpp>
#include <iostream>

enum class ENetworkDataType
{
	NONE,
	CUSTOM
};

struct NetworkDataPacket
{
	int fromClientID;
	std::string title;
	std::string data;
	ENetworkDataType type;

public:
	bool IsValid() const
	{
		return type != ENetworkDataType::NONE;
	}
	std::string ToString() const
	{
		return "[FROM:'" + std::to_string(fromClientID) + "'][TITLE:'" + title + "'][DATA:'" + data + "']";
	}

public:
	NetworkDataPacket()
	{
		fromClientID = -1;
		title = "";
		data = "";
		type = ENetworkDataType::NONE;
	}
	NetworkDataPacket(const std::string& _inPacketData)
	{
		// Packet data syntax: [FROM: '0'][TITLE: 'Title'][DATA: 'Random message!']

		type = ENetworkDataType::NONE; // Set packet to corrupted by default
		std::string _data = _inPacketData;
		std::string _copy;

		if (!_data.rfind("[FROM:'", 0) == 0) return; // FROM section not found >> packet is corrupted

		_data = _data.erase(0, 7);
		_copy = _data;
		fromClientID = std::stoi(_copy.erase(1, _copy.size() - 1));
		_data = _data.erase(0, 3);

		// Data remaining: [TITLE: 'Title'][DATA: 'Random message!']

		if (!_data.rfind("[TITLE:'", 0) == 0) return;// TITLE section not found >> packet is corrupted

		_data = _data.erase(0, 8);
		_copy = _data;
		title = _copy.erase(_copy.find("'"), _copy.size() - 1);
		_data = _data.erase(0, title.size() + 2);

		// Data remaining: [DATA: 'Random message!']

		if (!_data.rfind("[DATA:'", 0) == 0) return; // DATA section not found >> packet is corrupted
				
		_data = _data.erase(0, 7);
		const int _dataSize = static_cast<int>(_data.size());
		data = _data.erase(_dataSize - 2, _dataSize);

		type = ENetworkDataType::CUSTOM; // If everything was set correctly, set packet type to custom (not corrupted)

		RemoveInvalidChars();
	}
	NetworkDataPacket(const int _fromClientID, const std::string& _packetTitle, const std::string& _packetData, const ENetworkDataType _type)
	{
		fromClientID = _fromClientID;
		title = _packetTitle;
		data = _packetData;
		type = _type;
		RemoveInvalidChars();
	}

private:
	void RemoveInvalidChars()
	{
		char _invalidChars[] = { ' ', ':', '[', ']', '\'' };
		for (int _index = 0; _index < 5; _index++)
		{
			title.erase(std::remove(title.begin(), title.end(), _invalidChars[_index]), title.end());
			data.erase(std::remove(data.begin(), data.end(), _invalidChars[_index]), data.end());
		}
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
	std::map<int, sf::TcpSocket*> clientsIDMap;
	// Own id
	int id;

public:
	int GetID() const
	{
		return id;
	}

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
	NetworkDataPacket FetchData();
	void SendData(sf::TcpSocket* _client, const std::string& _packetTitle, const std::string& _packetData);
	void CheckForNewIDPacker(const NetworkDataPacket& _packetData);

public:
	void Start();
	void ListenForClients(unsigned int _amount);
	const int GetClientsCount();
	void SendData(const std::string& _packetTitle, const std::string& _packetData);
	NetworkDataPacket Tick();
};