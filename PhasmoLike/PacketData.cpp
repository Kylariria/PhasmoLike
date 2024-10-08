#include "PacketData.h"

#pragma region Constructors

PacketData::PacketData(const std::string& _inPacketData)
{
	// Packet data syntax: [FROM:'0'][TO:'-1'][TITLE:'Title'][DATA:'Random message!']

	isValid = false; // Set packet to corrupted by default
	std::string _data = _inPacketData;
	std::string _copy;

	if (!_data.rfind("[FROM:'", 0) == 0) return; // FROM section not found >> packet is corrupted

	_data = _data.erase(0, 7); // Removing [FROM:'
	_copy = _data;
	fromClientID = std::stoi(_copy.erase(_copy.find("'"), _copy.size() - 1));
	_data = _data.erase(0, _data.find("'") + 2); // Removing everyting until first ' + 2

	// Data remaining: [TO:'-1'][TITLE: 'Title'][DATA: 'Random message!']

	if (!_data.rfind("[TO:'", 0) == 0) return; // TO section not found >> packet is corrupted

	_data = _data.erase(0, 5); // Removing [TO:'
	_copy = _data;
	toClientID = std::stoi(_copy.erase(_copy.find("'"), _copy.size() - 1));
	_data = _data.erase(0, _data.find("'") + 2); // Removing everyting until first ' + 2

	// Data remaining: [TITLE: 'Title'][DATA: 'Random message!']

	if (!_data.rfind("[TITLE:'", 0) == 0) return;// TITLE section not found >> packet is corrupted

	_data = _data.erase(0, 8);
	_copy = _data;
	title = _copy.erase(_copy.find("'"), _copy.size() - 1);
	_data = _data.erase(0, _data.find("'") + 2); // Removing everyting until first ' + 2

	// Data remaining: [DATA: 'Random message!']

	if (!_data.rfind("[DATA:'", 0) == 0) return; // DATA section not found >> packet is corrupted

	_data = _data.erase(0, 7);
	const int _dataSize = static_cast<int>(_data.size());
	data = _data.erase(_dataSize - 2, _dataSize);

	isValid = true; // If everything was set correctly, set packet type to custom (not corrupted)

	RemoveInvalidChars();
}

PacketData::PacketData(const int _fromClientID, const int _toClientID, const std::string& _packetTitle, const std::string& _packetData)
{
	fromClientID = _fromClientID;
	toClientID = _toClientID;
	title = _packetTitle;
	data = _packetData;
	RemoveInvalidChars();
}

#pragma endregion

#pragma region DataConversion

void PacketData::RemoveInvalidChars()
{
	char _invalidChars[] = { '\'' };
	for (int _index = 0; _index < 1; _index++)
	{
		title.erase(std::remove(title.begin(), title.end(), _invalidChars[_index]), title.end());
		data.erase(std::remove(data.begin(), data.end(), _invalidChars[_index]), data.end());
	}
}

#pragma endregion

#pragma region Operators

sf::Packet& operator<<(sf::Packet& packet, const PacketData& _packetData)
{
	const std::string _stringLine = "[FROM:'" + std::to_string(_packetData.fromClientID) + "'][TO:'" + std::to_string(_packetData.toClientID) + "'][TITLE:'" + _packetData.title + "'][DATA:'" + _packetData.data + "']";
	return packet << _stringLine;
}

#pragma endregion