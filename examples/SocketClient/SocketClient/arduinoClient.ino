#include <IOTClient.h>
//#include <WiFi.h>

#include <Ethernet.h>
#include <SPI.h>



#define CODE 789
#define TO 555

byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};


EthernetClient client;
//WiFiClient client;

const char *token = "//paste//your//token//here";

//For WiFi Purpose
const char *ssid = "abc", *password = "xyz";

IOTClient sc;

int pin = 8;

void onReceive(const String&);

void setup() {
	Ethernet.begin(mac);
	Serial.begin(9600);
	/*
	delay(2000);
	WiFi.begin(ssid,password);
  
	delay(1000);
	Serial.print("Connecting to ");
	Serial.println(ssid);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}
    Serial.println("");
    Serial.println("WiFi connected");
	Serial.println("connecting...");
	*/

	while (!sc.connect()) {
		Serial.println("Request Failed");
		delay(5000);
	}
	delay(1000);
	sc.setOnReceive(&onReceive);

	pinMode(pin, OUTPUT);
}
int i = 0;
void loop() {
	sc.wait4Data();	
}


void onReceive(const String& message) {
	Serial.println(message);
}