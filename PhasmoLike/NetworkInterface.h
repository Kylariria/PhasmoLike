#pragma once
#include "NetworkManager.h"

#include <iostream>

using namespace std;

class NetworkInterface
{
	NetworkManager* manager = nullptr;

public:
	inline void SetManager(NetworkManager* _manager) { manager = _manager; }

public:
	NetworkInterface();

private:
	void DebugPing(const NetworkDataPacket& _packet);

public:
	void Tick();
};