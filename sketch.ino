
#include <Arduino.h>  // Wajib untuk PlatformIO + ESP32


// Deklarasi pin LED
int merah = 32;
int kuning = 33;
int hijau = 25;


void setup() {
    Serial.begin(115200);  // Inisialisasi komunikasi Serial
    Serial.println("ESP32 Blinking LED");


    // Atur pin sebagai OUTPUT
    pinMode(merah, OUTPUT);
    pinMode(kuning, OUTPUT);
    pinMode(hijau, OUTPUT);
}


void loop() {
    // Nyalakan kedua LED
    digitalWrite(merah, HIGH);
    digitalWrite(kuning, LOW);
    digitalWrite(hijau, LOW);
    Serial.println("LED ON");
    
    delay(5000); // Tunggu 1 detik


    // Matikan kedua LED
    digitalWrite(merah, LOW);
    digitalWrite(kuning, HIGH);
    digitalWrite(hijau, LOW);
    Serial.println("LED OFF");
    
    delay(5000); // Tunggu 1 detik sebelum mengulang

      // Matikan kedua LED
    digitalWrite(merah, LOW);
    digitalWrite(kuning, LOW);
    digitalWrite(hijau, HIGH);
    Serial.println("LED OFF");
    
    delay(5000); // Tunggu 1 detik sebelum mengulang
}
