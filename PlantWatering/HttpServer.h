// HttpServer.h

#ifndef _HTTPSERVER_h
#define _HTTPSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <string>
#include <ESP8266WiFi.h>

using namespace std;

class HttpServer {
public:
	//
	// Types
	//
	typedef enum HTTP_METHOD { METHOD_ERR = 0, GET, POST };

	static HTTP_METHOD parseHeader(String header) {
		if (header.indexOf("GET") >= 0) return GET;
		if (header.indexOf("POST") >= 0) return POST;
		return METHOD_ERR;
	}
};

#endif

