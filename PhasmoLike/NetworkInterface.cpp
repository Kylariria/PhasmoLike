#include "NetworkInterface.h"

NetworkInterface::NetworkInterface()
{

}

void NetworkInterface::DebugPing(const NetworkDataPacket& _packet)
{
	cout << "[NetworkInterface]>>> Ping received from " << _packet.fromClientID << "!" << endl;
}
void NetworkInterface::Tick()
{
	if (!manager) return;
	NetworkDataPacket _packet = manager->Tick();
	if (_packet.IsValid())
	{
		if (_packet.title == "DebugPing") DebugPing(_packet);
	}
}