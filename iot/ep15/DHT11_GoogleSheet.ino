#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "DHT.h" //ไลบารี่ของเซ็นเซอร์ DHT

#define DHTTYPE DHT11   // ระบุรุ่นของเซ็นเซอร์ DHT ในที่นี้ใช้เป็น DHT 11
const int DHTPin = 7; // ระบุขาที่ใช้ต่อกับเซ็นเซอร์ DHT11
DHT dht(DHTPin, DHTTYPE);

WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    delay(10);
    dht.begin(); 
    // We start by connecting to a WiFi network
    WiFiMulti.addAP("TP-Link_D50B", "41624151");

    Serial.println();
    Serial.println();
    Serial.print("ทำการเชื่อมต่อไวไฟ... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop()
{
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        String url = "https://script.google.com/macros/s/AKfycbysJ7hMzeCw28MFogd50a0Ms80BF42IQvxGAIxFfQQuDoqibnYp2jQDEsBZjepbHecNbQ/exec?temp=" + String(t) + "&humi=" + String(h);
        Serial.println("ทำการส่งค่าขึ้นไปยัง Google Sheet...");
        http.begin(url.c_str()); //Specify the URL and certificate
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        int httpCode = http.GET();
        String payload;
        if (httpCode > 0) { //Check for the returning code
          payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }
        else {
          Serial.println("การส่งผิดพลาดและล้มเหลว");
        }
        http.end();
      }


    Serial.println("ทำการรอ 3 วินาทีเพื่อที่จะทำการส่งใหม่...");
    delay(3000); // ตั้งค่าเวลาลูปสำหรับการส่ง โดยกำหนดให้เป็น 5 วินาที
}