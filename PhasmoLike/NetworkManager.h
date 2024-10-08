#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

#include "NetworkInterface.h"

struct PacketData;

enum class EPacketType
{
	TOSERVER,
	TOCLIENT,
	TOALL,
};

enum class ENetworkType
{
	NONE,
	CLIENT,
	SERVER,
};

class NetworkManager
{
	std::thread::id mainThreadID; // ID of the main thread
	ENetworkType type = ENetworkType::NONE; // Network type
	std::string address = ""; // Server's address
	unsigned short port = 0; // Server's port
	sf::TcpSocket* server = nullptr; // Server for clients
	sf::TcpListener* listener = nullptr; // Listener for server
	std::vector<sf::TcpSocket*> clients; // All connected clients
	std::map<int, sf::TcpSocket*> clientsIDMap; // All connected clients with respective ID
	int id = -1; // Own ID (0 For server
	int maxClients = 0; // Max clients connected on the server
	sf::Thread* networkThread = nullptr; // The network thread (to avoid blocking the main thread)
	bool isServerListening = false; // Is the server listening for new clients
	bool isAlive = true; // Should the network loops be running
	bool isServerFull = true; // Is the server full
	int amountOfConnectedClients = 0; // Current amount of connected clients
	NetworkInterface* netInterface = nullptr; // The packet manager interface
	int globalID = 0;

	// Manager Config
	bool debugsMessages = false;
	bool isListenerBlocking = false;

public:
	inline int GetNetworkID() const { return id; }
	inline int GetMaxConnectedClients() const { return maxClients; }
	inline int GetAmountOfConnectedClients() const { return amountOfConnectedClients; }
	inline bool IsServerListening() const { return isServerListening; }
	inline bool IsServerFull() const { return isServerFull; }
	inline void SetConfigDebugsMessages(const bool& _debugsMessages) { debugsMessages = _debugsMessages; }
	inline NetworkInterface* GetNetworkInterface() const { return netInterface; }
	inline bool IsServer() const { return type == ENetworkType::SERVER; }

public:
	NetworkManager();
	~NetworkManager();

private:
	void PrintDebug(const std::string& _message);
	bool IsStarted();
	void NetworkLoop();
	void StartNetworkThread();
	void ServerLoop();
	void ClientLoop();
	void ListenForClients();
	void ServerListenForPackets();
	void ClientListenForPackets();
	bool ComputeServerFull();
	void ResetNetwork();
	void DeleteAll(const bool& _withThread = true);
	void ServerIsFull();
	void ChangeNetworkID(const PacketData& _packetData);
	void AddDefaultEventsCallbacks();
	void SendDataTo(sf::TcpSocket* _client, const PacketData& _packetData);
	void HandlePacket(sf::Packet& _packet);
	void ReplicateData(PacketData _packetData);
	void UserDisconnected(const PacketData& _packetData);
	void DisconnectFromServer(const std::string& _reason = "Client disconnected");
	void SendPacketCloseServer();
	void KickedFromServer(const PacketData& _packetData);
	void Init();

public:
	/// <summary>
	/// Starts the server with the specified port
	/// </summary>
	/// <param name="_port">The port to listen to</param>
	void StartServer(const unsigned short _port);
	/// <summary>
	/// Used to make the server listen for new clients, otherwise clients wont be able to connect
	/// </summary>
	void StartListen();
	/// <summary>
	/// Used to stop the server from listening for new clients
	/// </summary>
	void StopListen();
	/// <summary>
	/// <para>Set the max amount of clients that can be connected to the server</para>
	/// <para>IMPORTANT: This will not kick clients if the limit is set below the current number of clients</para>
	/// </summary>
	/// <param name="_maxClients"></param>
	void SetClientLimit(const int _maxClients);
	/// <summary>
	/// <para>Set to true to avoid a fast loop of new-delete calls, slightly better performance</para>
	/// <para>Set to false to make the server able to receive packets while waiting for clients, slightly lower performance</para>
	/// <para>Performance changes is barely visible</para>
	/// <para>Default is false</para>
	/// </summary>
	/// <param name="_listenerBlocking">New value</param>
	void SetConfigListenerBlocking(const bool& _listenerBlocking);
	/// <summary>
	/// Starts the client and connect to the specified address and port
	/// </summary>
	/// <param name="_address">The address to connect to</param>
	/// <param name="_port">The port to connect to</param>
	void StartClient(const std::string& _address, const unsigned short _port);
	/// <summary>
	/// Send data to network
	/// </summary>
	/// <param name="_packetID">Packet ID to trigger a specific NetworkEvent</param>
	/// <param name="_data">Packet data that will be sent in the NetworkEvent</param>
	/// <param name="_packetType">Packet type</param>
	/// <param name="_toClient">Client id to send the packet to (WILL BE IGNORED IF TYPE IS NOT TOCLIENT)</param>
	void SendData(const std::string& _packetID, const std::string& _data, const EPacketType& _packetType = EPacketType::TOALL, const int& _toClient = -1);
	/// <summary>
	/// Disconnect from the connected server
	/// </summary>
	void Disconnect(const std::string& _reason = "Client disconnected");
	/// <summary>
	/// Close the server
	/// </summary>
	void CloseServer();
	/// <summary>
	/// Disconnect the client from the server if it's running as a client
	/// Close the server if it's running as a server
	/// </summary>
	void Exit();
};