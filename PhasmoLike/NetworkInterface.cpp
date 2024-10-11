#include "NetworkInterface.h"

NetworkInterface::NetworkInterface()
{
	connectEvent = new NetworkEvent();
	disconnectEvent = new NetworkEvent();
	joinServerEvent = new NetworkEvent();
	kickedFromServerEvent = new NetworkEvent();
}

NetworkInterface::~NetworkInterface()
{
	if (connectEvent) delete connectEvent;
	if (disconnectEvent) delete disconnectEvent;
	if (joinServerEvent) delete joinServerEvent;
	if (kickedFromServerEvent) delete kickedFromServerEvent;
	for (const std::pair<std::string, NetworkEvent*>& _pair : customEvents)
	{
		delete _pair.second;
	}
}

void NetworkInterface::TriggerConnectEvent(const PacketData& _packetData)
{
	if (!connectEvent) return;
	connectEvent->Broadcast(_packetData);
}

void NetworkInterface::TriggerDisconnectEvent(const PacketData& _packetData)
{
	if (!disconnectEvent) return;
	disconnectEvent->Broadcast(_packetData);
}

void NetworkInterface::TriggerJoinServerEvent(const PacketData& _packetData)
{
	if (!joinServerEvent) return;
	joinServerEvent->Broadcast(_packetData);
}

void NetworkInterface::TriggerKickedFromServer(const PacketData& _packetData)
{
	if (!kickedFromServerEvent) return;
	kickedFromServerEvent->Broadcast(_packetData);
}

void NetworkInterface::TriggerCustomEvent(const PacketData& _packetData)
{
	if (!ContainsKey(_packetData.title)) return;
	NetworkEvent* _event = customEvents[_packetData.title];
	if (_event) _event->Broadcast(_packetData);
}

bool NetworkInterface::ContainsKey(const std::string _key)
{
	return (customEvents.find(_key) != customEvents.end());
}

void NetworkInterface::HandlePacket(const PacketData& _packetData)
{
	if (_packetData.title == "UserConnected") TriggerConnectEvent(_packetData);
	else if (_packetData.title == "UserDisconnected") TriggerDisconnectEvent(_packetData);
	else if (_packetData.title == "JoinServer") TriggerJoinServerEvent(_packetData);
	else if (_packetData.title == "KickedFromServer") TriggerKickedFromServer(_packetData);
	else TriggerCustomEvent(_packetData);
}

void NetworkInterface::AddCustomEvent(const std::string _packetID, const std::function<void(const PacketData& _packetData)>& _callback)
{
	if (_packetID == "") return;
	if (ContainsKey(_packetID))
	{
		// Add callback to existing event
		customEvents[_packetID]->AddDynamic(_callback);
	}
	else
	{
		// Create new event
		NetworkEvent* _newEvent = new NetworkEvent();
		_newEvent->AddDynamic(_callback);
		customEvents[_packetID] = _newEvent;
	}
}