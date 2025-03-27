#include <Arduino.h>

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

  // Membaca durasi sinyal pantulan
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak (dalam cm)
  distanceCm = duration * SOUND_SPEED / 2;

  // Menampilkan hasil ke Serial Monitor
  Serial.print("Jarak (cm): ");
  Serial.println(distanceCm);

  delay(1000); // Delay 1 detik sebelum membaca ulang
}
