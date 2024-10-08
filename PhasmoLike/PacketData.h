#pragma once

#include <SFML/Network/Packet.hpp>
#include <string>

struct PacketData
{
	int fromClientID = -1; // Id of the sender
	int toClientID = -1; // Id of the receiver
	std::string title = ""; // Title of the packet, often a keyword of an action
	std::string data = ""; // The actual data of the packet
	bool isValid = false; // Is the packet corrupted

public:
	/// <summary>
	/// Default constructor, the packet will be invalid by default so do not use it
	/// </summary>
	PacketData() = delete;
	/// <summary>
	/// Constructor to create a packet with a data line received from the network, DO NOT USE MANUALLY
	/// </summary>
	/// <param name="_inPacketData">Data line received</param>
	PacketData(const std::string& _inPacketData);
	/// <summary>
	/// Constructor to create a custom packet
	/// IMPORTANT: Some characters like ' will be removed from the title and data to avoid corruption
	/// </summary>
	/// <param name="_fromClientID">The id of the sender</param>
	/// <param name="_toClientID">The id of the receiver</param>
	/// <param name="_packetTitle">The title of the packet</param>
	/// <param name="_packetData">The data contained in the packet</param>
	PacketData(const int _fromClientID, const int _toClientID, const std::string& _packetTitle, const std::string& _packetData);

private:
	/// <summary>
	/// Removes all invalid characters from a packet title and data to avoid packet corruption
	/// </summary>
	void RemoveInvalidChars();
};

sf::Packet& operator<<(sf::Packet& packet, const PacketData& _packetData);