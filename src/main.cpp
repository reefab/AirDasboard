#include <GxEPD.h>

#include <GxGDEW042Z15/GxGDEW042Z15.cpp>      // 4.2" b/w/r

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>

#if defined(ESP8266)
//GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, D3, D4);
// GxGDEP015OC1(GxIO& io, uint8_t rst = D4, uint8_t busy = D2);
GxEPD_Class display(io);
#endif

#include "config.h"

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library
#include <ESP8266HTTPClient.h>

HTTPClient http;

int nbRequests = 0;

#include <SimpleTimer.h>
SimpleTimer timer;

typedef struct {
    unsigned long timestamp = 0;
    String localTime = "Never";
    float pm = 0;
    float temp = 0;
    float humidity = 0;
    float co2 = 0;
    float voc = 0;
    float global = 0;
} FoobotStats;

FoobotStats indoorStats;

#include "foobot.h"

const GFXfont* bigFont = &FreeSansBold18pt7b;
const GFXfont* mediumFont = &FreeSansBold12pt7b;
const GFXfont* smallFont = &FreeSansBold9pt7b;

#include "display.h"

void updateStatsAndDisplay() {
    updateStats();
    display.drawPaged(showStats);
}

void connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting..");
    }
}

void setup(void) {
    display.init();
    display.setRotation(4);
    Serial.begin(9600);

    connect();
    updateStatsAndDisplay();
    /* timer.setInterval(600 * 1000, updateStatsAndDisplay); */
    ESP.deepSleep(600e6);
}

void loop() {
    /* timer.run(); */
}

