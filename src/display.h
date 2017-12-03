const int height = 300;
const int width = 400;

const byte columnWidth = 90;
const byte lineHeight = 20;
const byte lineSpacing = 10;

void showStats() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    // Header
    display.setFont(bigFont);
    display.setCursor(0, 25);
    display.print("Pollution");
    display.setCursor(180, 25);
    display.print("In: ");
    if (indoorStats.global > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.global, 0);
    display.println("%");

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, 40 + i, width, 40 + i, GxEPD_RED);
    }

    // indoorStats names colunm
    int x = 5;
    int y = 80;
    display.setTextColor(GxEPD_BLACK);
    display.setFont(mediumFont);
    display.setCursor(x, y);
    display.println("Temp");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("Hum");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("PM2.5");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("Co2");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("Voc");

    // Vertical separator
    for(int i = 0; i < 2; i++) {
        display.drawLine(columnWidth + i, 41, columnWidth + i, height - 20,
                         GxEPD_RED);
    }

    // First indoorStats column
    x = columnWidth + 5;
    y = 80;
    display.setCursor(x, y);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.temp > 25) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.temp, 0);
    display.println("C");
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.humidity > 60 || indoorStats.humidity < 40) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.humidity, 0);
    display.println("%");
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.pm25 > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.pm25, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.co2 > 1300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.co2, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    if (indoorStats.voc > 300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.voc, 0);


    // Vertical separator
    for(int i = 0; i < 2; i++) {
        display.drawLine(columnWidth * 2 + i, 41, columnWidth * 2 + i, height - 20,
                         GxEPD_RED);
    }

    // outdoor stats names colunm
    x = columnWidth * 2 + 5;
    y = 80;
    display.setTextColor(GxEPD_BLACK);
    display.setFont(mediumFont);
    display.setCursor(x, y);
    display.println("Temp");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("Hum");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("PM2.5");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("PM1x");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("CO");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("SO2");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("Ozone");
    y += lineHeight + lineSpacing;
    display.setCursor(x, y);
    display.println("NO2");
    y += lineHeight + lineSpacing;

    // Second column: outdoor stats
    x = columnWidth * 3 + 5;
    y = 80;
    display.setCursor(x, y);
    display.setTextColor(GxEPD_BLACK);
    if (outdoorStats.pm25 > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(outdoorStats.pm25, 0);
    y += lineHeight + lineSpacing;

    display.setTextColor(GxEPD_BLACK);

    display.setCursor(x, y);
    display.print(outdoorStats.temp, 0);
    display.println("C");
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.print(outdoorStats.humidity, 0);
    display.println("%");
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.println(outdoorStats.pm10, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.println(outdoorStats.co, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.println(outdoorStats.so2, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.println(outdoorStats.o3, 0);
    y += lineHeight + lineSpacing;

    display.setCursor(x, y);
    display.println(outdoorStats.no2, 0);
    y += lineHeight + lineSpacing;

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, height - 20 + i, width, height - 20 + i, GxEPD_RED);
    }

    // Footer
    display.setCursor(0, height);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(smallFont);
    display.println(indoorStats.localTime);
}
