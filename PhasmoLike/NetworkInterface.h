#pragma once

#include <functional>
#include <map>
#include <iostream>

#include "NetworkEvent.h"

class NetworkManager;
struct PacketData;

class NetworkInterface
{
	NetworkManager* manager = nullptr; // Reference to the NetworkManager
	NetworkEvent* connectEvent = nullptr; // Connect event (for all clients)
	NetworkEvent* disconnectEvent = nullptr; // Disconnect event (for all clients)
	NetworkEvent* joinServerEvent = nullptr; // Join server event
	NetworkEvent* kickedFromServerEvent = nullptr; // Server closed event
	std::map<std::string, NetworkEvent*> customEvents; // Custom events added manually

public:
	inline void SetManager(NetworkManager* _manager) { manager = _manager; }
	inline NetworkEvent* OnConnectEvent() { return connectEvent; }
	inline NetworkEvent* OnDisconnectEvent() { return disconnectEvent; }
	inline NetworkEvent* OnJoinServer() { return joinServerEvent; }
	inline NetworkEvent* OnKickedFromServer() { return kickedFromServerEvent; }

public:
	NetworkInterface();
	~NetworkInterface();

private:
	void TriggerConnectEvent(const PacketData& _packetData);
	void TriggerDisconnectEvent(const PacketData& _packetData);
	void TriggerJoinServerEvent(const PacketData& _packetData);
	void TriggerKickedFromServer(const PacketData& _packetData);
	void TriggerCustomEvent(const PacketData& _packetData);
	bool ContainsKey(const std::string _key);

public:
	void HandlePacket(const PacketData& _packetData);
	void AddCustomEvent(const std::string _packetID, const std::function<void(const PacketData& _packetData)>& _callback);
};