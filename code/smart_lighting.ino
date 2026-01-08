#include <WiFi.h>
#include "ThingSpeak.h"

#define LDR_PIN 36
#define PIR_PIN 15
#define LED_PIN 12

// --- Paramètres LED ---
int seuilNuit = 2000;       // seuil pour détecter nuit
int maxPWM = 255;            // LED pleine puissance
int minPWM = 50;             // LED minimale

// --- Wi-Fi et ThingSpeak ---
const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
const long myChannelNumber = 3222079;
const char* myApiKey = "5VV7JHE5SBOLWLUZ";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("Connexion Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connecté !");
  Serial.println("Local IP: " + String(WiFi.localIP()));

  ThingSpeak.begin(client);
}

void loop() {
  int luminosite = analogRead(LDR_PIN);      // 0 à 4095
  int mouvement = digitalRead(PIR_PIN);      // 0 ou 1

  int ledPWM = 0;                            // PWM à envoyer
  int consoEnergetique = 0;                  // consommation estimée

  // --- Gestion LED graduelle ---
  if (luminosite < seuilNuit) {             // Nuit
    if (mouvement == HIGH) {
      ledPWM = map(seuilNuit - luminosite, 0, seuilNuit, minPWM, maxPWM);
    } else {
      ledPWM = map(seuilNuit - luminosite, 0, seuilNuit, minPWM/2, maxPWM/2);
    }
    ledPWM = constrain(ledPWM, 0, maxPWM);
  } else {
    ledPWM = 0;                             // Jour → LED OFF
  }

  analogWrite(LED_PIN, ledPWM);

  // --- Estimation consommation ---
  consoEnergetique = map(ledPWM, 0, maxPWM, 0, 100);

  // --- Affichage console ---
  Serial.print("Luminosité: "); Serial.print(luminosite);
  Serial.print(" | PIR: "); Serial.print(mouvement);
  Serial.print(" | LED PWM: "); Serial.print(ledPWM);
  Serial.print(" | Conso: "); Serial.println(consoEnergetique);

  // --- Envoi ThingSpeak ---
  ThingSpeak.setField(1, luminosite);
  ThingSpeak.setField(2, ledPWM);           // on envoie PWM réel
  ThingSpeak.setField(3, mouvement);
  ThingSpeak.setField(4, consoEnergetique);

  int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);
  if (x == 200) Serial.println("Données envoyées avec succès !");
  else Serial.println("Erreur envoi: " + String(x));

  delay(2000);
}
