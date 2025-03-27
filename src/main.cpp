#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Konfigurasi untuk Push Button, LED, dan Relay
const int ButtonPin = 19;  // GPIO19 -> Tombol
const int LedPin = 18;     // GPIO18 -> LED
const int RelayPin = 23;   // GPIO23 -> Relay

// Konfigurasi untuk Sensor Ultrasonik HC-SR04
const int trigPin = 5;     // Trig Pin
const int echoPin = 18;    // Echo Pin
#define SOUND_SPEED 0.034  // Kecepatan suara dalam cm/μs

long duration;
float distanceCm;

// Konfigurasi Sensor DHT22
#define DHTPIN 27    
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

// Kredensial WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

unsigned long previousMillis = 0;
const long interval = 5000;  // Interval 5 detik (5000 ms)

void setup() {
  Serial.begin(115200);

  // Setup tombol, LED, dan relay
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(LedPin, LOW);
  digitalWrite(RelayPin, LOW);

  // Setup sensor ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Terhubung!");

  dht.begin();
}

void loop() {
  // Membaca status tombol
  int buttonState = digitalRead(ButtonPin);

  // Jika tombol ditekan (LOW karena INPUT_PULLUP)
  if (buttonState == LOW) {
    digitalWrite(LedPin, HIGH);
    digitalWrite(RelayPin, HIGH);
  } else {
    digitalWrite(LedPin, LOW);
    digitalWrite(RelayPin, LOW);
  }

  // **Pengukuran jarak dengan sensor ultrasonik**
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;

  // Menampilkan hasil ke Serial Monitor
  Serial.print("Jarak (cm): ");
  Serial.println(distanceCm);

  // **Kirim data sensor ke server setiap 5 detik**
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float h = round(dht.readHumidity());
    float t = round(dht.readTemperature());

    if (isnan(h) || isnan(t)) {
      Serial.println(F("Gagal membaca sensor DHT!"));
      return;
    }

    // Hitung heat index
    float hic = dht.computeHeatIndex(t, h, false);

    // Kirim data ke server
    HTTPClient http;
    String url = "http://ffcf-36-74-83-245.ngrok-free.app/api/posts"; // Ganti dengan URL ngrok yang benar
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"nama_sensor\":\"Sensor GD\", \"nilai1\":" + String(h) + ", \"nilai2\":" + String(t) + "}";
    Serial.println(payload);

    int httpResponseCode = http.POST(payload);
    Serial.print("Kode respons HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode == 200 || httpResponseCode == 201) {
      String response = http.getString();
      Serial.println("Respons dari server:");
      Serial.println(response);
    } else {
      Serial.println("Gagal mengirim data");
    }

    http.end();
  }

  delay(1000); // Delay 1 detik sebelum membaca ulang
}
