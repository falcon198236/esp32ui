#pragma once
#include "configure.h"

#ifdef USE_OPC
#define OPC_USER "hyrel"
#define OPC_PASSWORD "hyrel"
#define OPC_PORT    4840

#define BASE_IP_EVENT WIFI_EVENT
#define GOT_IP_EVENT IP_EVENT_STA_GOT_IP
#define DISCONNECT_EVENT WIFI_EVENT_STA_DISCONNECTED
#define EXAMPLE_INTERFACE TCPIP_ADAPTER_IF_STA


extern bool OpcPaused;
extern uint32_t OpcHeartBeat;
void InitOPC();
#endif