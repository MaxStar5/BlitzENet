.lib "BlitzENet.dll"

ENet_Initialize():"_Initialize@0"
ENet_DeInitialize():"_deInitialize@0"

ENet_ClearOutput():"_clearOutput@0"
ENet_ConnectHost%(host%, ip$, port%, channels%, data%):"_connectHost@20"
ENet_CreateHost%(ip%, port%, maxClients%, channels%):"_createHost@16"
ENet_DisconnectPeer(host%, peer%, event%, data%):"_disconnectPeer@16"
ENet_HostService(host%, timeout%):"_hostService@8"

ENet_PeerReset%(peer%):"_peerReset@4"

ENet_GetEventPeer%(event%):"_getEventPeer%4"
ENet_GetEventType%(event%):"_getEventType@4"

ENet_PushByte(b%):"_pushByte@4"
ENet_PushFloat(f%):"_pushFloat@4"
ENet_PushInt(i%):"_pushInt@4"
ENet_PushShort(s%):"_pushShort@4"
ENet_PushString(s$):"_pushString@4"

ENet_ReadByte%():"_readByte@0"
ENet_ReadFloat%():"_readFloat@0"
ENet_ReadInt%():"_readInt@0"
ENet_ReadShort%():"_readShort@0"
ENet_ReadString$():"_readString@0"

ENet_ReadPacket(event%):"_readPacket@4"
ENet_SendPacket%(peer%, channel%, flag%):"_sendPacket@12"