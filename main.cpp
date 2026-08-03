#define DLL(type) extern "C" __declspec(dllexport) type __stdcall

#include <enet.h>
#include <vector>


std::vector<uint8_t> output;
uint8_t* input;
uint8_t inputPos;

DLL(int) createHost(int ip, int port, int maxClients, int channels) {
	// if ip and port are 0 return client
	if(!ip && !port) return (int)enet_host_create(nullptr, maxClients, channels, 0, 0);

	ENetAddress address{};
	address.host = ip;
	address.port = port;

	return (int)enet_host_create(&address, maxClients, channels, 0, 0);
}

DLL(int) connectHost(ENetHost* host, const char* ip, int port, int channels, int data) {
	ENetAddress address;

	address.port = port;
	enet_address_set_host(&address, ip);

	ENetPeer* peer;
	if (!output.size()) {
		peer = enet_host_connect(host, &address, channels, data);
	}
	else {
		peer = enet_host_connect(host, &address, channels, data);
	}

	return (int)peer;
}

DLL(void) disconnectPeer(ENetHost* host, ENetPeer* peer, ENetEvent* event, int data) {
	if (!output.size()) {
		enet_peer_disconnect(peer, data);
	}
	else {
		enet_peer_disconnect(peer, data);
	}
	enet_host_service(host, event, 0);

	enet_host_destroy(host);
}

DLL(void) peerReset(ENetPeer* peer) {
	enet_peer_reset(peer);
}
DLL(int) hostService(ENetHost* host, int timeout) {
	ENetEvent event{};

	if (enet_host_service(host, &event, timeout) > 0) {
		return (int)&event;
	}
	return 0;
}

DLL(int) getEventType(ENetEvent* event) {
	return event->type;
}
DLL(int) getEventPeer(ENetEvent* event) {
	return (int)event->peer;
}
DLL(int) sendPacket(ENetPeer* peer, int channel, int flag) {
	ENetPacket* packet = enet_packet_create(output.data(), output.size(), flag);
	if (!packet) return false;

	if (enet_peer_send(peer, channel, packet) != 0) {
		enet_packet_destroy(packet);
		return false;
	}

	return true;
}

DLL(void) readPacket(ENetEvent* event) {
	input = event->packet->data;
	inputPos = 0;

	enet_packet_destroy(event->packet);
	enet_free(event);
}

template<typename T>

T read() {
	T* t = (T*)(input + inputPos);
	inputPos += sizeof(T);
	return *t;
}

DLL(int) readByte() {
	return read<uint8_t>();
}

DLL(int) readShort() {
	return read<int16_t>();
}

DLL(int) readInt() {
	return read<int>();
}

DLL(int) readFloat() {
	return read<float>();
}

DLL(const char*) readString() {
	return read<const char*>();
}

template<typename T>

static void Push(const T& value) {
	const unsigned int oldSize = output.size();
	output.resize(oldSize + sizeof(T));
	
	std::memcpy(output.data() + oldSize, &value, sizeof(T));
}


DLL(void) pushByte(int b) {
	Push((uint8_t)b);
}

DLL(void) pushShort(int s) {
	Push((int16_t)s);
}

DLL(void) pushInt(int i) {
	Push(i);
}

DLL(void) pushFloat(float f) {
	Push(f);
}

DLL(void) pushString(const char* s) {
	Push(s);
}

DLL(void) clearOutput() {
	output.clear();
}


DLL(void) initialize() { enet_initialize(); }
DLL(void) deInitialize() { enet_deinitialize(); }