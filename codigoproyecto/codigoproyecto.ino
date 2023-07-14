float h;
float t;
int httpCode;
char buf[128];
const uint8_t fingerprint[20] = {0x2e, 0x8f, 0x7F, 0xe8, 0x97, 0x10, 0x8b, 0x27, 0xa9, 0x8c, 0x73, 0xab, 0x8c, 0x87, 0x0a, 0x7c, 0x27, 0xb2, 0xe9, 0xc3};

const char IRG_Root_X1 [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIFLTCCBBWgAwIBAgIUFfFE14f81fBk0+frk4gHN2EATw4wDQYJKoZIhvcNAQEL
BQAwgakxCzAJBgNVBAYTAlVTMRMwEQYDVQQIDApDYWxpZm9ybmlhMRIwEAYDVQQH
DAlTdW5ueXZhbGUxETAPBgNVBAoMCEZvcnRpbmV0MR4wHAYDVQQLDBVDZXJ0aWZp
Y2F0ZSBBdXRob3JpdHkxGTAXBgNVBAMMEEZHNUgwRTU4MTk5MDI3NDYxIzAhBgkq
hkiG9w0BCQEWFHN1cHBvcnRAZm9ydGluZXQuY29tMB4XDTIzMDQyNzAwMTMxNloX
DTIzMDcyNjAwMTMxNVowFzEVMBMGA1UEAwwMKi52ZXJjZWwuYXBwMIIBIjANBgkq
hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvT3ruD+Cakvug3v/nZNMHW2HyX62HoT/
gUqwMFgXojxc+l+bkamWAfWlWjYsJinh/vw9hrIwVyu1vQKcOSfV6UZ9jlCUlLKP
VHdK6MLQ3DUQxOUhOfDKMiqXRWzGVCjpeCat5DjVbtsknPe8ZOaPOqYeOps5WU50
Z29DHWB6OGBkYI5oPWFMvA8lU8UkD7ajO2jIeRN9MCQOcJpeZHBuaX5IAFz5Z+PP
v9Rdu4UcNJ7YOekIdtzy2jP8mDBdedVYAJaT197uK6/29+RdTqZ2Nf83Ov9nAJ09
ECXe0j1CMyroO4DCaBf5vJmEI2WHQMX5qJT87/d2uQN8gs9vvGw+aQIDAQABo4IB
3DCCAdgwDgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEF
BQcDAjAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBSkNs2drEC/VL9S49aSJEtYnlRu
cTAjBgNVHREEHDAaggwqLnZlcmNlbC5hcHCCCnZlcmNlbC5hcHAwTAYDVR0gBEUw
QzAIBgZngQwBAgEwNwYLKwYBBAGC3xMBAQEwKDAmBggrBgEFBQcCARYaaHR0cDov
L2Nwcy5sZXRzZW5jcnlwdC5vcmcwggEFBgorBgEEAdZ5AgQCBIH2BIHzAPEAdwB6
MoxU2LcttiDqOOBSHumEFnAyE4VNO9IrwTpXo1LrUgAAAYfARYxNAAAEAwBIMEYC
IQCjMRuh+2sHTjoHXNC9yVgXk8huDOUGqdq0EeBvwfGgEgIhALnLeZDjqQmP5Icv
EBtLGRSOz11cO8EHX9AdRgW3GPSDAHYAtz77JN+cTbp18jnFulj0bF38Qs96nzXE
nh0JgSXttJkAAAGHwEWMZQAABAMARzBFAiBaspctaMf8TbozUDxVh5pvLqRO7czZ
QQKovEvTmhJmowIhAI7V/cN9GJ9ymNp60mc2VZi3MLy36KDVmHZI5A6e8MqRMA0G
CSqGSIb3DQEBCwUAA4IBAQBbgzm1v5axnMLZXd8tgpWyp7Wd+S8uJvyrgJtK9Dli
Mjc989QR9fZMoqrNegvBYoTRy0sMd8a5Ysday4qZWgphddJah1452+0nda9r/Dwv
33mUDx7vv4RYSRnyISdDYKIMgZLXA6zQmrH3SXQAyMdPK35Ie0Et9LDYRoxHUVnV
qjlBmSyDYRwFNJ5U7G5wdfU/WM5jrQE2CZylxYp1y4G2txKdjUJNkbZuBFXgAI8H
zPm+OXUHx6dDtQ9r46vhfM3suH8L61HjI61Y1ZvLlNd9375DbM1KZ78WJlo5k/Vz
hfppaJMfRF2t7AVLlScOlgNlYE23YJXNVCxIIdB9qxZF
-----END CERTIFICATE-----
)CERT";


//liberias
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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
  delay(2000);
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

    WiFiClient client;
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    https.begin(client, URL);  // HTTP
    https.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    sprintf(buf, "{\"humedad\": %.2f, \"temperatura\": %.2f, \"x_pos\": 0, \"y_pos\": 0}", h, t);
    httpCode = https.POST(buf);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    }
    else {
      Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  }
}
