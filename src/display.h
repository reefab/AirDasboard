void showStats() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    // Header
    display.setFont(bigFont);
    display.setCursor(0, 25);
    display.print("Pollution");
    display.setCursor(125, 25);
    if (indoorStats.global > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.global, 0);
    display.println("%");

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, 40 + i, 400, 40 + i, GxEPD_RED);
    }

    // indoorStats names colunm
    display.setTextColor(GxEPD_BLACK);
    display.setFont(mediumFont);
    display.setCursor(0, 60);
    display.println("PM2.5");
    display.setCursor(0, 80);
    display.println("Temp");
    display.setCursor(0, 100);
    display.println("Hum");
    display.setCursor(0, 120);
    display.println("Co2");
    display.setCursor(0, 140);
    display.println("Voc");

    // Vertical separator
    for(int i = 0; i < 3; i++) {
        display.drawLine(60 + i, 41, 60 + i, 280, GxEPD_RED);
    }

    // First indoorStats column
    display.setCursor(70, 60);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.pm > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.pm, 0);

    display.setCursor(70, 80);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.temp > 25) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.temp, 0);
    display.println("C");

    display.setCursor(70, 100);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.humidity > 60 || indoorStats.humidity < 40) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.humidity, 0);
    display.println("%");

    display.setCursor(70, 120);
    display.setTextColor(GxEPD_BLACK);
    if (indoorStats.co2 > 1300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.co2, 0);

    display.setCursor(70, 140);
    if (indoorStats.voc > 300) {
        display.setTextColor(GxEPD_RED);
    }
    display.println(indoorStats.voc, 0);

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, 280 + i, 400, 280 + i, GxEPD_RED);
    }
    // Footer
    display.setCursor(0, 300);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(smallFont);
    display.println(indoorStats.localTime);
}

