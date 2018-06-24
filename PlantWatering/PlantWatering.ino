#include "MoistureSensor.h"
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "HttpServer.h"

#define MOISTURE_PIN 0

const char* ssid = "VGV75196C1C40";
const char* password = "XUbH4LWWtbsu";

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server_addr(192, 168, 2, 8);  // IP of the MySQL *server* here
char* dbUser = "Zwen";              // MySQL user login username
char* dbPass = "3458Erkelens!";        // MySQL user login password

WiFiClient client;
MySQL_Connection conn((Client *)&client);

// 
// Server@port
//
const int PORT = 8080;
WiFiServer wifiServer(PORT);

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

void InsertInto(String value) {
	String insert = "INSERT INTO moisture.moisture (moistureValue) VALUES (" + value +")";

	// Initiate the query class instance
	MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
	// Execute the query
	char query[80];
	insert.toCharArray(query, 80);
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

	//connectToDatabase();

	//
	// Start server
	//
	wifiServer.begin();
	Serial.printf("\n\r>%s: BIEM! connected.\n\r", __FUNCTION__);

	moistureSensor = MoistureSensor::getInst();
	moistureSensor.setPin(MOISTURE_PIN);

	//server = HttpServer();
}

//
// HTTP GET response message
//
String getResponseString() {
	String res = "";
	res += "HTTP/1.1 200 OK\r\n";
	res += "Connection: close\r\n";
	res += "Content-Type: application/json\r\n";
	res += "\r\n";

	String str = "{\"moisture\":";
	str += String(MoistureSensor::getInst().getValue());
	str += "}\r\n";

	res += str;
	res += "\r\n";
	return res;
}

//
// HTTP POST response message
//
String postResponseString() {
	String res = "";
	res += "HTTP/1.1 200 OK\r\n";
	res += "Connection: close\r\n";
	res += "Content-Type: application/json\r\n";
	res += "\r\n";
	res += "{\"msg\":\"Have a nice day\"}\r\n";
	res += "\r\n";
	return res;
}

// the loop function runs over and over again until power down or reset
void loop() {
	WiFiClient client = wifiServer.available();

	if (client) {
		String httpHeader = "";

		while (client.connected()) {

			if (client.available()) {

				String line = client.readStringUntil('\r');
				httpHeader += line;

				if (line.length() == 1 && line[0] == '\n') {

					// Handle GET
					if (HttpServer::GET == HttpServer::parseHeader(httpHeader)) {
						client.println(getResponseString());
						break;
					}

					// Handle POST
					if (HttpServer::POST == HttpServer::parseHeader(httpHeader)) {
						String body = client.readStringUntil('\r');
						client.println(postResponseString());
						Serial.println(body);
						break;
					}
				}
			}
		}
		client.stop();
	}
}
