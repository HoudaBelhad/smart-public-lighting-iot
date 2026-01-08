# Système d'Éclairage Intelligent IoT

## 📌 Description
Système d'éclairage automatique intelligent utilisant ESP32, capteurs LDR et PIR, avec monitoring via ThingSpeak.

## 🎯 Objectif
Optimiser la consommation énergétique en ajustant automatiquement l'intensité lumineuse selon l'obscurité ambiante et la présence de mouvement.

## 🛠️ Composants
- ESP32 DevKit v4
- Capteur LDR (luminosité)
- Capteur PIR (mouvement)
- LED (orange)

## 📊 Données envoyées à ThingSpeak
- Field 1 : Luminosité (0-4095)
- Field 2 : PWM LED (0-255)
- Field 3 : Détection mouvement (0/1)
- Field 4 : Consommation énergétique estimée (0-100%)

## 🚀 Simulation
Projet simulé sur [Wokwi](https://wokwi.com/)

## 📥 Installation
1. Ouvrir le fichier `code/smart_lighting.ino` dans Arduino IDE
2. Installer la librairie ThingSpeak
3. Modifier les identifiants WiFi et ThingSpeak si nécessaire
4. Téléverser sur ESP32

## 👤 Auteur
Houda Belhad - 2026