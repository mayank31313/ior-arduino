/*
 Name:		ev3controller.ino
 Created:	4/25/2019 8:53:52 PM
 Author:	Mayank
*/

#include <LinkedList.h>
#include <Ethernet.h>
#include <SPI.h>

#include "IOTClient.h"

#define POT_PIN A1

byte pins[] = { 4,5,6};
byte read_values[] = {0,0,0};
byte read_previous_value[] = {0,0,0};
byte previous_pot_value = 0;

byte n_pins = 3;

const char codes[] = { 'R','U','L'};

#define CODE 789
#define TO 555
#define TOKEN "826f7556-6442-4c09-9e1e-76dbb462542c"

byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

EthernetClient client;
boolean flag = 0;
IOTClient sc(&client, CODE, TO, TOKEN);
void onReceive(const String&);

void setup() {
	Serial.begin(9600);
	int status;
	do{
		Serial.println("Beginning the Ethernet");
		status = Ethernet.begin(mac);		
	} while (status == 0);
	Serial.println("Ethernet Connected");
	pinMode(POT_PIN, INPUT);
	for (byte i = 0; i < n_pins; i++) {
		pinMode(pins[i], INPUT);
	}

	boolean exit = false;
	while (!sc.connect()) {
		Serial.println("Request Failed");
	}
	sc.setOnReceive(&onReceive);
}

// the loop function runs over and over again until power down or reset
LinkedList<SyncData*>* list = new LinkedList<SyncData*>();

void loop() {
	sc.wait4Data();	
	/*
	for (byte i = 0; i < n_pins; i++) {
		read_values[i] = digitalRead(pins[i]);	
		if (read_previous_value[i] != read_values[i]) {
			SyncData *temp = new SyncData();
			temp->key = String(codes[i]);
			if (read_values[i] == HIGH) {
				Serial.print("PIN HIGH ");
				Serial.println(pins[i]);
				temp->value = "1";
			}
			else {
				Serial.print("PIN LOW ");
				Serial.println(pins[i]);
				temp->value = "0";
			}
			flag = 1;
			list->add(temp);
			read_previous_value[i] = read_values[i];
		}
	}
	
	byte pot_value = (byte)map(analogRead(POT_PIN),0,1024,0,100);
	if (pot_value != previous_pot_value) {
		Serial.print("POT VALUE Changed: ");
		Serial.println(pot_value);
		previous_pot_value = pot_value;
		SyncData *temp = new SyncData();
		temp->key = "S";
		temp->value = String(pot_value);
		list->add(temp);
		flag = 1;
	}
	
	if (flag != 0) {
		sc.sendMessage("CONTROL", list);
		flag = 0;
	}
	list->clear();
	*/
}

void onReceive(const String& message) {
	Serial.println(message);
}


