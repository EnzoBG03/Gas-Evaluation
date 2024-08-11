#include <avr/interrupt.h>

// Broches des capteurs et actionneurs
const int capteurGazPin = A0;  // Modifié pour correspondre au schéma
const int capteurTactilePin = 2;  // Modifié pour correspondre au schéma
const int boutonDemarragePin = 3;  // Modifié pour correspondre au schéma
const int boutonArretPin = 4;  // Modifié pour correspondre au schéma
const int ledVertePin = 5;  // Modifié pour correspondre au schéma
const int ledJaunePin = 6;  // Modifié pour correspondre au schéma
const int ledRougePin = 7;  // Modifié pour correspondre au schéma

// Seuils pour les LED (ajustés pour la résolution 10 bits de l'Arduino Mega)
const int SEUIL_ROUGE = 700;  // Ajusté pour la résolution 10 bits
const int SEUIL_JAUNE = 400;  // Ajusté pour la résolution 10 bits

// État de l'analyse
volatile bool analyseActive = false;

void setup() {
  // Initialisation des broches
  pinMode(capteurGazPin, INPUT);
  pinMode(capteurTactilePin, INPUT_PULLUP);
  pinMode(ledVertePin, OUTPUT);
  pinMode(ledJaunePin, OUTPUT);
  pinMode(ledRougePin, OUTPUT);
  
  // Configuration des interruptions
  pinMode(boutonDemarragePin, INPUT_PULLUP);
  pinMode(boutonArretPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(boutonDemarragePin), demarrerAnalyse, FALLING);
  attachInterrupt(digitalPinToInterrupt(boutonArretPin), arreterAnalyse, FALLING);
  
  // Initialisation de la communication série pour le débogage
  Serial.begin(9600);
}

void loop() {
  if (analyseActive) {
    int valeurGaz = analogRead(capteurGazPin);
    afficherDonnees(valeurGaz);
    mettreAJourLEDs(valeurGaz);
    delay(1000);
  }
}

void demarrerAnalyse() {
  if (!analyseActive && digitalRead(capteurTactilePin) == LOW) {
    analyseActive = true;
    Serial.println("Analyse demarree");
  } else if (!analyseActive) {
    Serial.println("Veuillez toucher le capteur tactile pour demarrer l'analyse");
  }
}

void arreterAnalyse() {
  if (analyseActive) {
    analyseActive = false;
    eteindreLEDs();
    Serial.println("Analyse arretee");
  }
}

void afficherDonnees(int valeur) {
  Serial.println(valeur);
}

void mettreAJourLEDs(int valeur) {
  digitalWrite(ledVertePin, valeur <= SEUIL_JAUNE ? HIGH : LOW);
  digitalWrite(ledJaunePin, valeur > SEUIL_JAUNE && valeur <= SEUIL_ROUGE ? HIGH : LOW);
  digitalWrite(ledRougePin, valeur > SEUIL_ROUGE ? HIGH : LOW);
}

void eteindreLEDs() {
  digitalWrite(ledVertePin, LOW);
  digitalWrite(ledJaunePin, LOW);
  digitalWrite(ledRougePin, LOW);
}
