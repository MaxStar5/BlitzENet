Include "BlitzENet.bb"

ENet_Initialize()
; Parsing 0 both to IP and Port gives back a client host. 
host% = ENet_CreateHost(0, 0, 1, 4)
; ENet_CreateHost & ENet_ConnectHost requires the same amount of channels.
peer% = ENet_ConnectHost(host, "127.0.0.1", 26656, 4, 0)

Repeat
	Delay 300
	While ENet_HostService(host, 0) > 0
		Select ENet_GetEventType()
			Case ENET_EVENT_TYPE_CONNECT
				DebugLog("Connected!")
			Case ENET_EVENT_TYPE_DISCONNECT
				DebugLog("Disconnected!")
			Case ENET_EVENT_TYPE_RECEIVE
				DebugLog("Received!")
				
				DebugLog(ENet_ReadByte())
		End Select

	Wend 

Forever

ENet_DeInitialize()