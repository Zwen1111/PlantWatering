#include "MoistureSensor.h"
#include "MoistureSensor.h"
#include <ESP8266WiFi.h>
#include <sstream>
#include <string>

#define MOISTURE_PIN 0

const char* ssid = "UPC685092";
const char* password = "LSZZYSHV";

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

WiFiClient client;

MoistureSensor moistureSensor;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	delay(10);

	// We start by connecting to a WiFi network

	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	moistureSensor = MoistureSensor(0);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int moistureValue = moistureSensor.getValue();
	std::stringstream ss;
	ss << moistureValue;
	delay(300000);
}
