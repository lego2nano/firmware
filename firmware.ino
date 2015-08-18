#include "DACWriter.h"
#include "DataRecv.h"

/* Pin Definitions */
#define SDI 2;
#define _SCK 3;
#define LOAD 4;
#define LDAC 5;
#define RECVPin A7

DACWriterClass WRITER;
DataRecvClass RECV;

int pixelCount = 8; // Parameter
int detectTimes = 10; // Parameter
int pixelData[pixelCount] = {0};


void interrupt() {
    delay(10);
}

void dataSend(int* array) {
    for (int i = 0; i < pixelCount; ++i) {
        Serial.print(array[i]);
        if (i == pixelCount - 1)
            Serial.print(';');
        else
            Serial.print(',');
    }
}

void initialize() {
}

void startWork() {
    for (int i = 0; i < pixelCount; ++i) {
        /* Call DACWriter Function */
    	
    	/* Call DataRecv Function */
        pixelData[i] = RECV.detectPixel(RECVPin, detectTimes);
    }
    /* Send Data */
    dataSend(pixelData);
}

void setParameter() {
}


void setup() {
    dataSend(pixelData);
    Serial.begin(9600);
    pinMode(RECVPin, INPUT);
    /* Trigger the interrupt when pin 2 changes value*/
    /* See "https://www.arduino.cc/en/Reference/AttachInterrupt" */
    attachInterrupt(0, interrupt, HIGH); 
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil(';');
        if (command == "IN") initialize();
        else if (command == "SW") startWork();
        else if (command == "SP") setParameter();
        delay(1);
    }
}
