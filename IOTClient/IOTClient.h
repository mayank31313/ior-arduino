#ifndef IOTClient_h
#define IOTClient_h


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif

#include<Client.h>
#include <LinkedList.h>
//#include <ESP8266WiFi.h>


#pragma once
struct SyncData {
	String key;
	String value;
};

class IOTClient
{
private:
	Client* client;
	//WiFiClient* client;
	//const char* server = "www.iorresearch.ml";
	const char* server = "192.168.1.10";
	const char *token;
	int code,to;
	unsigned long time_delay;

	String readData();
	void (*onReceive)(const String&);
public:
	//void initialise(WiFiClient* c, int,int , const char *);
	boolean connect();
	IOTClient(const Client* c, int, int, const char* t);
	bool sendMessage(const char* c,LinkedList<SyncData*>* s);
	boolean checkConnectivity();
	void wait4Data();
	void setOnReceive(void (*on_rec)(const String&));
};

#endif
