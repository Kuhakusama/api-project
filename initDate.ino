#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

// WiFi
const char* ssid = "NomeWifi";
const char* password = "SenhaWifi";

// Firebase
const char* firebaseHost = "https://projeto-final-44901-default-rtdb.firebaseio.com";
const char* firebasePath = "/Graficos/DataHora.json";

// Timezone
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -3 * 3600;
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //CONEXAO WIFI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //TIMEZONE
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("WiFi Conectado.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    char datetime[30];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", &timeinfo);

    String json = "{\"dataHora\": \"" + String(datetime) + "\"}";

    HTTPClient http;
    String url = String(firebaseHost) + firebasePath;

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    
    int httpResponseCode = http.POST(json);
    if (httpResponseCode > 0) {
      Serial.print("Dados enviados com sucesso: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Erro ao enviar: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  delay(60000);
}