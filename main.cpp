#define DLL(type) extern "C" __declspec(dllexport) type __stdcall

#include <enet.h>
#include <vector>
#include <string>

std::vector<uint8_t> output;
uint8_t* input;
uint16_t inputPos, inputSize;

// save event
ENetPeer* eventPeer;
ENetEventType eventType;
uint32_t eventData;
ENetPacket* eventPacket;


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
	peer = enet_host_connect(host, &address, channels, data);

	return (int)peer;
}

DLL(void) destroyHost(ENetHost* host) {
	enet_host_destroy(host);
}

DLL(void) disconnectPeer(ENetPeer* peer, int data) {
	enet_peer_disconnect(peer, data);
}

DLL(void) disconnectPeerNow(ENetPeer* peer, int data) {
	enet_peer_disconnect_now(peer, data);
}

DLL(int) getPeerIP(ENetPeer* peer) { return peer->address.host; }
DLL(int) getPeerPort(ENetPeer* peer) { return peer->address.port; }

DLL(void) setPeerTimeout(ENetPeer* peer, int timeoutLimit, int timeoutMinimum, int timeoutMaximum) {
	enet_peer_timeout(peer, timeoutLimit, timeoutMinimum, timeoutMaximum);
}

DLL(void) peerReset(ENetPeer* peer) {
	enet_peer_reset(peer);
}

DLL(void) hostFlush(ENetHost* host) {
	enet_host_flush(host);
}

DLL(int) getEventType() { return eventType; }

DLL(int) getEventPeer() { return (int)eventPeer; }

DLL(int) getEventData() { return eventData; }

DLL(int) getPacketAvail() { return (inputSize - inputPos); }

DLL(int) sendPacket(ENetPeer* peer, int channel, int flag) {
	ENetPacket* packet = enet_packet_create(output.data(), output.size(), flag);
	if (!packet) return false;

	if (enet_peer_send(peer, channel, packet) != 0) {
		enet_packet_destroy(packet);
		return false;
	}
	return true;
}

DLL(int) hostService(ENetHost* host, int timeout) {
	ENetEvent event{};
	int i = enet_host_service(host, &event, timeout);

	eventType = event.type;
	eventData = event.data;
	eventPeer = event.peer;
	if (event.type == ENET_EVENT_TYPE_RECEIVE) {
		if (eventPacket) enet_packet_destroy(eventPacket);
		eventPacket = event.packet;
		input = event.packet->data;
		inputSize = event.packet->dataLength;
	}
	else {
		if (eventPacket) enet_packet_destroy(eventPacket);
		eventPacket = nullptr;
		input = nullptr;
		inputSize = 0;
	}
	
	inputPos = 0;
	return i;
}

template<typename T>

T read()
{
	if (inputPos + sizeof(T) > inputSize) {
		return T{};
	}

	T value;
	memcpy(&value, input + inputPos, sizeof(T));
	inputPos += sizeof(T);

	return value;
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
	static std::string result;

	unsigned int start = inputPos;

	while (inputPos < inputSize && input[inputPos] != 0) inputPos++;

	result.assign(reinterpret_cast<const char*>(input + start), inputPos - start);

	if (inputPos < inputSize) inputPos++;

	return result.c_str();
}

DLL(void) readBytes(void** bank, const int offset, const int size) {
	if (!bank || !*bank || offset < 0 || size <= 0) return; 
	if (inputPos + size > inputSize) return;

	uint8_t* dest = (uint8_t*)(*bank) + offset;
	std::memcpy(dest, input + inputPos, size);

	inputPos += size;
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

DLL(void) pushString(const char* s)
{
	const unsigned int length = std::strlen(s);

	output.insert(output.end(), reinterpret_cast<const uint8_t*>(s), reinterpret_cast<const uint8_t*>(s) + length);
}

DLL(void) pushBytes(void** bank, const int offset, const int size) {
	if (!bank || !*bank || offset < 0 || size <= 0) return;

	const uint8_t* data = static_cast<const uint8_t*>(*bank) + offset;

	output.insert(output.end(), data, data + size);
}

DLL(void) clearOutput() {
	output.clear();
}


DLL(void) initialize() { enet_initialize(); }
DLL(void) deInitialize() { enet_deinitialize(); }