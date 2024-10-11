#include "NetworkEvent.h"

void NetworkEvent::Broadcast(const PacketData& _packetData)
{
	for (const std::function<void(const PacketData& _packetData)>& _callback : callbacks)
	{
		if (!_callback) continue;
		_callback(_packetData);
	}
}
void NetworkEvent::AddDynamic(std::function<void(const PacketData& _packetData)> _callback)
{
	if (!_callback) return;
	callbacks.push_back(_callback);
}