const int height = 300;
const int width = 400;
const int statsStartsAt = 65;

const byte columnWidth = 100;
const byte lineHeight = 20;
const byte lineSpacing = 10;
const byte thinSeparator = 2;
const byte thickSeparator = 5;

void addLabel(String text, int *px, int *py) {
    display.setCursor(*px, *py);
    display.println(text);
    *py += lineHeight + lineSpacing;
}

void addValue(float value, int *px, int *py, int min = 0, int max = 0, String suffix = "") {
    display.setCursor(*px, *py);
    if (min && value < min) {
        display.setTextColor(GxEPD_RED);
    } else if (max && value > max) {
        display.setTextColor(GxEPD_RED);
    } else {
        display.setTextColor(GxEPD_BLACK);
    }
    display.print(value, 0);
    if (suffix.length() > 0) {
        display.setFont(smallFont);
        display.println(suffix);
        display.setFont(mediumFont);
    }
    *py += lineHeight + lineSpacing;
}

void showStats() {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    // Header
    display.setFont(bigFont);
    display.setCursor(5, 25);
    /* display.print("Pollution - "); */
    display.print("In: ");
    if (indoorStats.global > 50) {
        display.setTextColor(GxEPD_RED);
    }
    display.print(indoorStats.global, 0);
    display.print("%");

    display.setCursor(width/2 + 10, 25);
    display.setTextColor(GxEPD_BLACK);
    display.print("Out: ");
    if (outdoorStats.global > 150) {
        display.setTextColor(GxEPD_RED);
    } else {
        display.setTextColor(GxEPD_BLACK);
    }
    display.print(outdoorStats.global, 0);

    // Horizontal separator
    for(int i = 0; i < thickSeparator; i++) {
        display.drawLine(0, 40 + i, width, 40 + i, GxEPD_RED);
    }

    // Vertical separators
    for(int j = 1; j < 4; j++) {
        int separator = (j == 2) ? thickSeparator : thinSeparator;
        int verticalStart = (j == 2) ? 0 : 41;
        for(int i = 0; i < separator; i++) {
            display.drawLine(columnWidth * j + i, verticalStart,
                             columnWidth * j + i, height - 20,
                             GxEPD_RED);
        }
    }

    // First column: indoor Stats names
    int x = 5;
    int y = statsStartsAt;
    display.setTextColor(GxEPD_BLACK);
    display.setFont(mediumFont);

    const char* indoorLabels[] = {"Temp", "Hum", "PM2.5", "Co2", "Voc"};
    for (int i = 0; i < 5; i++) {
        addLabel(indoorLabels[i], &x, &y);
    }


    // Second column: indoor stats values
    x = columnWidth + 5;
    y = statsStartsAt;
    addValue(indoorStats.temp, &x, &y, 0, 25, "C");
    addValue(indoorStats.humidity, &x, &y, 40, 60, "%");
    addValue(indoorStats.pm25, &x, &y, 0, 50, "ugm3");
    addValue(indoorStats.co2, &x, &y, 0, 1300, "ppm");
    addValue(indoorStats.voc, &x, &y, 0, 300, "ppb");

    // Third column: outdoor stats names
    x = columnWidth * 2 + 10;
    y = statsStartsAt;
    display.setTextColor(GxEPD_BLACK);

    const char* outdoorLabels[] = {"Temp", "Hum", "PM2.5", "PM10", "CO", "Ozone",
                                   "No2", "So2"};
    for (int i = 0; i < 8; i++) {
        addLabel(outdoorLabels[i], &x, &y);
    }

    // Forth column: outdoor stats values
    x = columnWidth * 3 + 5;
    y = statsStartsAt;
    addValue(outdoorStats.temp, &x, &y, 0, 0, "C");
    addValue(outdoorStats.humidity, &x, &y, 0, 0, "%");
    addValue(outdoorStats.pm25, &x, &y, 0, 0, "ugm3");
    addValue(outdoorStats.pm10, &x, &y, 0, 0, "ugm3");
    addValue(outdoorStats.co, &x, &y);
    addValue(outdoorStats.o3, &x, &y);
    addValue(outdoorStats.no2, &x, &y);
    addValue(outdoorStats.so2, &x, &y);

    // Horizontal separator
    for(int i = 0; i < 5; i++) {
        display.drawLine(0, height - 20 + i, width, height - 20 + i, GxEPD_RED);
    }

    // Footer
    display.setCursor(0, height - 1);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(smallFont);
    display.println(indoorStats.localTime);
}
