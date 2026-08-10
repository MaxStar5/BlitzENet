



Include "BlitzENet.bb"

ENet_Initialize()

; 0 as the host IP argument means INADDR_ANY.
host% = ENet_CreateHost(0, 26656, 1, 4)

Repeat
	Delay 300
	While ENet_HostService(host, 0) > 0
		peer% = ENet_GetEventPeer()
		Select ENet_GetEventType()
			Case ENET_EVENT_TYPE_CONNECT
				DebugLog("Connected!")
				ENet_PushByte(25)
				; ENet_SendPacket returns True if the packet was successfully sent.
				ENet_SendPacket(peer, 1, ENET_PACKET_FLAG_UNRELIALE)
				ENet_ClearOutput()
			Case ENET_EVENT_TYPE_DISCONNECT
				DebugLog("Disconnected!")
			Case ENET_EVENT_TYPE_RECEIVE
				DebugLog("Received!")
		End Select
	Wend 

Forever

ENet_DeInitialize()