float h;
float t;
int httpCode;
char buf[128];

//liberias
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

//tipo de pin
#define DHTTYPE DHT11 


//pines
#define DHTPIN 2


#define URL "https://bat-simple-api.vercel.app/data/ruta1"
#ifndef STASSID
#define STASSID "Galaxy A113976"
#define STAPSK "apjj5435"
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println();

  dht.begin();
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
//----------------CODIGO-DHT-------------------------------------------------
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;}

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  
//----------------CODIGO WIFI/HTTPCLIENT---------------------
  
  if ((WiFi.status() == WL_CONNECTED)) {

//    WiFiClient WiFi_Client;
    
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    //client->setFingerprint(fingerprint_sni_cloudflaressl_com);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, URL)) {  // HTTPS
  
      Serial.print("[HTTPS] POST...\n");
      // start connection and send HTTP header
      sprintf(buf, "{\"humedad\": %.2f, \"temperatura\": %.2f, \"x-pos\": 0, \"y-pos\": 0}", h, t);
      https.addHeader("Content-Type", "application/json");
      int httpCode = https.POST(buf);

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
  }
