void updateStats() {
    char url[100];
    sprintf(url, "http://api.foobot.io/v2/device/%s/datapoint/3600/last/3600/",
            foobot_device_id);
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
        indoorStats.timestamp = atoi(strtok(stats_line, ","));
        indoorStats.localTime = strtok(NULL, ",");
        indoorStats.pm = atof(strtok(NULL, ","));
        indoorStats.temp = atof(strtok(NULL, ","));
        indoorStats.humidity = atof(strtok(NULL, ","));
        indoorStats.co2 = atof(strtok(NULL, ","));
        indoorStats.voc = atof(strtok(NULL, ","));
        indoorStats.global = atof(strtok(NULL, ","));
    }
    Serial.print("NB request:");
    Serial.println(nbRequests);
    http.end();
}
