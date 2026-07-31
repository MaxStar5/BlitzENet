#define DLL(type) extern "C" __declspec(dllexport) type __stdcall

#include <enet.h>
#include <vector>

std::vector<uint8_t> output;
std::vector<uint8_t> input;
unsigned int inputPos;

DLL(int) ENet_createHost(int port, int maxClients, int channels) {
	ENetAddress address{};
	address.host = ENET_HOST_ANY;
	address.port = port;

	ENetHost* host = enet_host_create(&address, maxClients, channels, 0, 0);
	return (intptr_t)host;
}

DLL(int) ENet_hostService(ENetHost* host, int timeout) {
	ENetEvent event{};
	
	if (enet_host_service(host, &event, timeout) > 0) {
		return event.type;
	}
	return 0;
}

DLL(int) ENet_sendPacket(ENetPeer* peer, int channel, int flag) {
	ENetPacket* packet = enet_packet_create(output.data(), output.size(), flag);
	if (!packet) return false;

	if (enet_peer_send(peer, channel, packet) != 0) {
		enet_packet_destroy(packet);
		return false;
	}

	return true;
}

template<typename T>

T Read() {
	if (inputPos + sizeof(T) > input.size()) return 0;
	T value{};

}

static void Push(const T& value) {
	const unsigned int oldSize = output.size();
	output.resize(oldSize + sizeof(T));
	
	std::memcpy(output.data() + oldSize, &value, sizeof(T));
}


DLL(void) ENet_pushByte(int b) {
	Push((uint8_t)b);
}

DLL(void) ENet_pushShort(int s) {
	Push((int16_t)s);
}

DLL(void) ENet_pushInt(int i) {
	Push(i);
}

DLL(void) ENet_pushFloat(float f) {
	Push(f);
}

DLL(void) ENet_Initialize() { enet_initialize(); }
DLL(void) ENet_deInitialize() { enet_deinitialize(); }