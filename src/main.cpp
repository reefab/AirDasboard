// PagedDisplayExampleForSmallRam : test example for e-Paper displays from Waveshare and from Dalian Good Display Inc.
//                                  shows how the full display screen can be used with Adafruit_GFX on small RAM Arduinos
//                                  runs also on Arduinos with more RAM, e.g. ESP8266, for test
//
// Created by Jean-Marc Zingg based on demo code from Good Display for GDEP015OC1.
//
// The e-paper displays are available from:
//
// https://www.aliexpress.com/store/product/Wholesale-1-54inch-E-Ink-display-module-with-embedded-controller-200x200-Communicate-via-SPI-interface-Supports/216233_32824535312.html
//
// http://www.buy-lcd.com/index.php?route=product/product&path=2897_8363&product_id=35120
// or https://www.aliexpress.com/store/product/E001-1-54-inch-partial-refresh-Small-size-dot-matrix-e-paper-display/600281_32815089163.html
//

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0

// mapping from Waveshare 2.9inch e-Paper to Wemos D1 mini
// BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V

// mapping example for AVR, UNO, NANO etc.
// BUSY -> 7, RST -> 9, DC -> 8, C S-> 10, CLK -> 13, DIN -> 11

// include library, include base class, make path known
#include <GxEPD.h>

//#include <GxGDEP015OC1/GxGDEP015OC1.cpp>    // 1.54" b/w
#include <GxGDEW0154Z04/GxGDEW0154Z04.cpp>  // 1.54" b/w/r
//#include <GxGDE0213B1/GxGDE0213B1.cpp>      // 2.13" b/w
//#include <GxGDEW0213Z16/GxGDEW0213Z16.cpp>  // 2.13" b/w/r
//#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w
//#include <GxGDEW029Z10/GxGDEW029Z10.cpp>    // 2.9" b/w/r
//#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
//#include <GxGDEW042T2/GxGDEW042T2.cpp>      // 4.2" b/w

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

/* #include GxEPD_BitmapExamples */

#if defined(ESP8266)

// generic/common.h
//static const uint8_t SS    = 15;
//static const uint8_t MOSI  = 13;
//static const uint8_t MISO  = 12;
//static const uint8_t SCK   = 14;
// pins_arduino.h
//static const uint8_t D8   = 15;
//static const uint8_t D7   = 13;
//static const uint8_t D6   = 12;
//static const uint8_t D5   = 14;

//GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, D3, D4);
// GxGDEP015OC1(GxIO& io, uint8_t rst = D4, uint8_t busy = D2);
GxEPD_Class display(io);
// my IoT connection, busy on MISO
//GxEPD_Class display(io, D4, D6);

#elif defined(ESP32)

// pins_arduino.h, e.g. LOLIN32
//static const uint8_t SS    = 5;
//static const uint8_t MOSI  = 23;
//static const uint8_t MISO  = 19;
//static const uint8_t SCK   = 18;

GxIO_Class io(SPI, SS, 17, 16);
GxEPD_Class display(io, 16, 4);

#elif defined(ARDUINO_ARCH_SAMD)

// variant.h of MKR1000
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (24u) // should be 4?
// variant.h of MKRZERO
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (4u)

GxIO_Class io(SPI, 4, 7, 6);
GxEPD_Class display(io, 6, 5);

#elif defined(_BOARD_GENERIC_STM32F103C_H_)

// STM32 Boards (STM32duino.com)
// Generic STM32F103C series
// aka BluePill
// board.h
//#define BOARD_SPI1_NSS_PIN        PA4
//#define BOARD_SPI1_MOSI_PIN       PA7
//#define BOARD_SPI1_MISO_PIN       PA6
//#define BOARD_SPI1_SCK_PIN        PA5
//enum {
//    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,PA14,PA15,
//  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,PB14,PB15,
//  PC13, PC14,PC15
//};
// variant.h
//static const uint8_t SS   = BOARD_SPI1_NSS_PIN;
//static const uint8_t SS1  = BOARD_SPI2_NSS_PIN;
//static const uint8_t MOSI = BOARD_SPI1_MOSI_PIN;
//static const uint8_t MISO = BOARD_SPI1_MISO_PIN;
//static const uint8_t SCK  = BOARD_SPI1_SCK_PIN;

//GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, 8, 9);
//  GxGDEP015OC1(GxIO& io, uint8_t rst = 9, uint8_t busy = 7);
GxEPD_Class display(io, 9, 3);

#else

// pins_arduino.h, e.g. AVR
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

GxIO_Class io(SPI, SS, 8, 9);
//GxIO_DESTM32L io;
//GxIO_GreenSTM32F103V io;
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
    unsigned long timestamp;
    String localTime;
    float pm;
    float temp;
    float humidity;
    float co2;
    float voc;
    float global;
} STATS;

STATS stats;

const GFXfont* bigFont = &FreeSansBold12pt7b;
const GFXfont* smallFont = &FreeSansBold9pt7b;

void updateStats() {
    char url[100];
    sprintf(url, "http://api.foobot.io/v2/device/%s/datapoint/3600/last/3600/", foobot_device_id);
    http.begin(url);
    http.addHeader("Accept", " text/csv;charset=UTF-8");
    http.addHeader("X-API-KEY-TOKEN", foobot_api_token);
    int httpCode = http.GET();
    nbRequests++;
    if (httpCode > 0) {
        String payload = http.getString();
        int payloadLength = payload.length() + 1;
        char charbuf[payloadLength];
        payload.toCharArray(charbuf, payloadLength);
        char* header_line = strtok(charbuf, "\n");
        char* stats_line = strtok(NULL, "\n");
        Serial.println(stats_line);
        stats.timestamp = atoi(strtok(stats_line, ","));
        stats.localTime = strtok(NULL, ",");
        stats.pm = atof(strtok(NULL, ","));
        stats.temp = atof(strtok(NULL, ","));
        stats.humidity = atof(strtok(NULL, ","));
        stats.co2 = atof(strtok(NULL, ","));
        stats.voc = atof(strtok(NULL, ","));
        stats.global = atof(strtok(NULL, ","));
    }
    Serial.print("NB request:");
    Serial.println(nbRequests);
    http.end();
}

void showStats() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    // Header
    display.setFont(bigFont);
    display.setCursor(0, 25);
    display.print("Pollution");
    display.setCursor(125, 25);
    if (stats.global > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(stats.global, 0);
    display.println("%");

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, 40 + i, 200, 40 + i, GxEPD_RED);
    }

    // Stats names colunm
    display.setTextColor(GxEPD_BLACK);
    display.setFont(smallFont);
    display.setCursor(0, 60);
    display.println("PM2.5");
    display.println("Temp");
    display.println("Hum");
    display.println("Co2");
    display.println("Voc");

    // Vertical separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(60 + i, 41, 60 + i, 180, GxEPD_RED);
    }

    // First stats column
    display.setCursor(70, 60);
    display.setTextColor(GxEPD_BLACK);
    if (stats.pm > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(stats.pm, 0);

    display.setCursor(70, 80);
    display.setTextColor(GxEPD_BLACK);
    if (stats.temp > 25) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(stats.temp, 0);
    display.println("C");

    display.setCursor(70, 100);
    display.setTextColor(GxEPD_BLACK);
    if (stats.humidity > 60 || stats.humidity < 40) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(stats.humidity, 0);
    display.println("%");

    display.setCursor(70, 120);
    display.setTextColor(GxEPD_BLACK);
    if (stats.co2 > 1300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(stats.co2, 0);

    display.setCursor(70, 140);
    if (stats.voc > 300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(stats.voc, 0);

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, 180 + i, 200, 180 + i, GxEPD_RED);
    }
    // Footer
    display.setCursor(0, 200);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(smallFont);
    display.println(stats.localTime);
}

void updateStatsAndDisplay() {
    updateStats();
    display.drawPaged(showStats);
}

void setup(void) {
  display.init();
  display.setRotation(3);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }

  updateStatsAndDisplay();
  timer.setInterval(600 * 1000, updateStatsAndDisplay);
}

void loop() {
    timer.run();
}

