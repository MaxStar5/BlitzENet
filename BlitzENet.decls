.lib "BlitzENet.dll"

ENet_Initialize():"_initialize@0"
ENet_DeInitialize():"_deInitialize@0"

ENet_ClearOutput():"_clearOutput@0"
ENet_ConnectHost%(host%, ip$, port%, channels%, data%):"_connectHost@20"
ENet_CreateHost%(ip%, port%, maxClients%, channels%):"_createHost@16"
ENet_HostService%(host%, timeout%):"_hostService@8"
ENet_DestroyHost(host%):"_destroyHost@4"

ENet_DisconnectPeer(peer%, data%):"_disconnectPeer@8"
ENet_DisconnectPeerNow(peer%, data%):"_disconnectPeerNow@8"
ENet_PeerReset%(peer%):"_peerReset@4"
ENet_SetPeerTimeout(peer%, timeoutLimit%, timeoutMinimum%, timeoutMaximum%):"_setPeerTimeout@16"
ENet_GetPeerIP%(peer%):"_getPeerIP@4"
ENet_GetPeerPort%(peer%):"_getPeerPort@4"

ENet_GetEventPeer%():"_getEventPeer@0"
ENet_GetEventType%():"_getEventType@0"
ENet_GetEventData%():"_getEventData@0"

ENet_PushByte(b%):"_pushByte@4"
ENet_PushFloat(f%):"_pushFloat@4"
ENet_PushInt(i%):"_pushInt@4"
ENet_PushShort(s%):"_pushShort@4"
ENet_PushString(s$):"_pushString@4"
ENet_PushBytes(bank*, offset%, size%):"_pushBytes@12"

ENet_ReadByte%():"_readByte@0"
ENet_ReadFloat%():"_readFloat@0"
ENet_ReadInt%():"_readInt@0"
ENet_ReadShort%():"_readShort@0"
ENet_ReadString$():"_readString@0"
ENet_ReadBytes(bank*, offset%, size%):"_readBytes@12"

ENet_PacketFinished%():"_packetFinished@0"
ENet_GetPacketSize%():"_getPacketSize@0"
ENet_SendPacket%(peer%, channel%, flag%):"_sendPacket@12"