#ifndef __ATMEGA__
#define __MEGA__
#define __ATMEGA__
#endif
#include "ustd_platform.h"
#include "ustd_functional.h"

#ifndef __SOCKET_IO_CLIENT_H__
#define __SOCKET_IO_CLIENT_H__
#include <ArxContainer.h>
#include <Arduino.h>
#include <WebSocketsClient.h>


#ifndef NODEBUG_SOCKETIOCLIENT

   #define SOCKETIOCLIENT_DEBUG(...) Serial.print("Test");
#else
   #define SOCKETIOCLIENT_DEBUG(...)
#endif

#define PING_INTERVAL 10000 //TODO: use socket.io server response

//#define SOCKETIOCLIENT_USE_SSL
#ifdef SOCKETIOCLIENT_USE_SSL
	#define DEFAULT_PORT 443
#else
	#define DEFAULT_PORT 80
#endif
#define DEFAULT_URL "/socket.io/?transport=websocket"
#define DEFAULT_FINGERPRINT ""


class SocketIoClient {
private:
	arx::vector<String> _packets;
	WebSocketsClient _webSocket;
	int _lastPing;
	arx::map<String, ustd::function<void (const char * payload, size_t length)>> _events;

	void trigger(const char* event, const char * payload, size_t length);
	void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
    void initialize();
	bool _disableHeartbeat=false;
public:
	void begin(const char* host, const int port = DEFAULT_PORT, const char* url = DEFAULT_URL);
	void loop();
	void on(const char* event, ustd::function<void (const char * payload, size_t length)>);
	void emit(const char* event, const char * payload = NULL);
	void remove(const char* event);
	void disconnect();
	void configureEIOping(bool disableHeartbeat);
};

#endif
