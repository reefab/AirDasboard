#include <ArduinoJson.h>

void updateAqicnStats() {
    char url[150];
    sprintf(url, "http://api.waqi.info/feed/%s/?token=%s",
            aqicn_feed_id, aqicn_token);
    Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == 200) {
        String payload = http.getString();
        Serial.println(payload);
        //StaticJsonBuffer<1200> jsonBuffer;
        const size_t bufferSize = 1200;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(payload);

        // Test if parsing succeeds.
        if (!root.success()) {
            Serial.println("parseObject() failed");
            return;
        }
        outdoorStats.global = root["data"]["aqi"];
        outdoorStats.co = root["data"]["iaqi"]["co"]["v"];
        outdoorStats.humidity = root["data"]["iaqi"]["h"]["v"];
        outdoorStats.temp = root["data"]["iaqi"]["t"]["v"];
        outdoorStats.no2 = root["data"]["iaqi"]["no2"]["v"];
        outdoorStats.o3 = root["data"]["iaqi"]["o3"]["v"];
        outdoorStats.pm10 = root["data"]["iaqi"]["pm10"]["v"];
        outdoorStats.pm25 = root["data"]["iaqi"]["pm25"]["v"];
        outdoorStats.so2 = root["data"]["iaqi"]["so2"]["v"];
    }
    http.end();
}
