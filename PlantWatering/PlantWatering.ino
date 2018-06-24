#include "MoistureSensor.h"
#include "MoistureSensor.h"
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <sstream>
#include <string>

#define MOISTURE_PIN 0

const char* ssid = "VGV75196C1C40";
const char* password = "XUbH4LWWtbsu";

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server_addr(192, 168, 2, 8);  // IP of the MySQL *server* here
char* dbUser = "Zwen";              // MySQL user login username
char* dbPass = "3458Erkelens!";        // MySQL user login password

WiFiClient client;
MySQL_Connection conn((Client *)&client);

MoistureSensor moistureSensor;

void connectToDatabase() {
	Serial.println("Connecting...");
	if (conn.connect(server_addr, 3306, dbUser, dbPass)) {
		delay(1000);
		Serial.println("Connected to database.");
	}
	else
		Serial.println("Connection failed.");
}

void InsertInto(std::string value) {
	std::string insert = "INSERT INTO moisture.moisture (moistureValue) VALUES (" + value +")";

	// Initiate the query class instance
	MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
	// Execute the query
	char query[80];
	strcpy(query, insert.c_str);
	cur_mem->execute(query);
	// Note: since there are no results, we do not need to read any data
	// Deleting the cursor also frees up memory used
	delete cur_mem;
}

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

	connectToDatabase();

	moistureSensor = MoistureSensor(0);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int moistureValue = moistureSensor.getValue();
	std::stringstream ss;
	ss << moistureValue;
	InsertInto(ss.str());
	delay(300000);
}
