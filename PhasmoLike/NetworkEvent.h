#pragma once

#include <functional>
#include <vector>

#include "PacketData.h"

class NetworkEvent
{
	std::vector<std::function<void(const PacketData& _packetData)>> callbacks;

public:
	NetworkEvent() = default;

public:
	/// <summary>
	/// Triggers all callbacks present in the event
	/// </summary>
	/// <param name="_callback">The packet data</param>
	void Broadcast(const PacketData& _packetData);
	/// <summary>
	/// Add a callback to the event
	/// </summary>
	/// <param name="_callback">The callback to add to the event</param>
	void AddDynamic(std::function<void(const PacketData& _packetData)> _callback);
};