#include <SoftwareSerial.h>

// Broches des capteurs et actionneurs
const int capteurGazPin = A0;
const int capteurTactilePin = 2;
const int boutonDemarragePin = 3;
const int boutonArretPin = 4;
const int ledVertePin = 5;
const int ledJaunePin = 6;
const int ledRougePin = 7;

// Seuils pour les LED
const int SEUIL_ROUGE = 700; // Valeur arbitraire à ajuster selon les caractéristiques du capteur
const int SEUIL_JAUNE = 400; // Valeur arbitraire à ajuster selon les caractéristiques du capteur

// État de l'analyse
bool analyseActive = false;

// Initialisation de la communication série pour le module Bluetooth
SoftwareSerial bluetooth(18, 19); // RX, TX

void setup() {
  // Initialisation des broches
  pinMode(capteurGazPin, INPUT);
  pinMode(capteurTactilePin, INPUT);
  pinMode(boutonDemarragePin, INPUT_PULLUP);
  pinMode(boutonArretPin, INPUT_PULLUP);
  pinMode(ledVertePin, OUTPUT);
  pinMode(ledJaunePin, OUTPUT);
  pinMode(ledRougePin, OUTPUT);
  
  // Initialisation de la communication série
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // Lecture des valeurs des capteurs
  int valeurCapteurGaz = analogRead(capteurGazPin);
  int valeurCapteurTactile = digitalRead(capteurTactilePin);
  int boutonDemarrage = digitalRead(boutonDemarragePin);
  int boutonArret = digitalRead(boutonArretPin);
  
  // Si le bouton de démarrage est pressé et l'analyse n'est pas déjà active, démarrer l'analyse
  if (boutonDemarrage == LOW && !analyseActive) {
    // Vérifier si le capteur tactile est également activé
    if (valeurCapteurTactile == HIGH) {
      analyseActive = true;
      bluetooth.println("Analyse demarree");
    } else {
      bluetooth.println("Veuillez toucher le capteur tactile pour demarrer l'analyse");
    }
  }
  
  // Si le bouton d'arrêt est pressé, arrêter l'analyse
  if (boutonArret == LOW && analyseActive) {
    analyseActive = false;
    digitalWrite(ledVertePin, LOW);
    digitalWrite(ledJaunePin, LOW);
    digitalWrite(ledRougePin, LOW);
    bluetooth.println("Analyse arretee");
  }
  
  // Si l'analyse est active, lire la valeur du capteur de gaz et envoyer les données via Bluetooth
  if (analyseActive) {
    int valeurGaz = valeurCapteurGaz;
    bluetooth.println(valeurGaz);
    
    // Mettre à jour les LED en fonction de la valeur du capteur de gaz
    if (valeurGaz > SEUIL_ROUGE) {
      digitalWrite(ledRougePin, HIGH);
      digitalWrite(ledJaunePin, LOW);
      digitalWrite(ledVertePin, LOW);
    } else if (valeurGaz > SEUIL_JAUNE) {
      digitalWrite(ledRougePin, LOW);
      digitalWrite(ledJaunePin, HIGH);
      digitalWrite(ledVertePin, LOW);
    } else {
      digitalWrite(ledRougePin, LOW);
      digitalWrite(ledJaunePin, LOW);
      digitalWrite(ledVertePin, HIGH);
    }
    
    delay(1000); // Attendre une seconde entre chaque lecture
  }
}
