# Evaluation de Gaz - Arduino

## Description

Ce projet utilise un Arduino Mega 2560 R3 pour analyser la concentration de gaz dans l'atmosphère et afficher les résultats via des LEDs.

## Fonctionnalités

- Mesure de la concentration de gaz en temps réel
- Affichage de l'état via 3 LEDs (vert, jaune, rouge)
- Contrôle de démarrage/arrêt via boutons et capteur tactile
- Affichage des données sur le moniteur série pour le débogage

## Matériel requis

- Arduino Mega 2560
- Capteur de gaz (MQ-2)
- Capteur tactile
- 3 LEDs (verte, jaune, rouge)
- 2 boutons poussoirs
- Résistances appropriées pour les LEDs et les boutons (220 Ω pour les LED et 10K Ω pour les boutons)
- Breadboard et fils de connexion

## Schéma de câblage

Le schéma de câblage est disponible dans le dépôt.

## Installation

1. Connectez les composants selon le schéma de câblage fourni.
2. Téléchargez et installez l'IDE Arduino si ce n'est pas déjà fait.
3. Clonez ce dépôt ou téléchargez le fichier `.ino`.
4. Ouvrez le fichier dans l'IDE Arduino.
5. Sélectionnez le bon type de carte (Arduino Mega) et le port COM approprié.
6. Téléversez le code sur votre Arduino.

## Utilisation

1. Alimentez votre Arduino.
2. Ouvrez le moniteur série de l'IDE Arduino pour voir les données (optionnel).
3. Appuyez sur le bouton de démarrage tout en touchant le capteur tactile pour commencer l'analyse.
4. Les LEDs indiqueront le niveau de gaz détecté :
   - Vert : Niveau faible
   - Jaune : Niveau moyen
   - Rouge : Niveau élevé
5. Les données sont également affichées sur le moniteur série.
6. Appuyez sur le bouton d'arrêt pour terminer l'analyse.

## Configuration

Vous pouvez ajuster les seuils de détection à votre convenance en modifiant les valeurs `SEUIL_JAUNE` et `SEUIL_ROUGE` dans le code.

## Dépannage

- Assurez-vous que toutes les connexions sont correctes et sécurisées.
- Si les LEDs ne s'allument pas correctement, vérifiez les connexions et les résistances.
- Vérifiez que le moniteur série est configuré sur 9600 bauds.

## Versions

- v2.0.0 : Restructuration du code et reconstruction de la connectique
- v1.0.0 : Version initiale

## Contribution

Les contributions à ce projet sont les bienvenues. N'hésitez pas à forker le projet et à soumettre vos pull requests.

## Auteur

Enzo BENOIST-GIMET
