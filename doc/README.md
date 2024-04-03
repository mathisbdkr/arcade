                                    ###
                                      ##
 #####    ## ###    ####   #####      ##   ####
##  ##     ### ##  ##     ##  ##   #####  ##  ##
##  ##     ##  ##  ##     ##  ##  ##  ##  ######
##  ##     ##      ##     ##  ##  ##  ##  ##
 ### ##   ####      ####   ### ##  ### ##  ####

# Documentation Arcade

Cette documentation a pour but de comprendre le fonctionnement du projet et comment intégrer vos jeux et librairies graphiques

# Table des matières

- Core
    - Fonctionnement du core
    - DlLoader

- Interfaces
    -IGameModule
    -IDisplayModule

- Classes
    -

- Librairies
    - Librairies graphiques
        - 
        - NCURSES
        - SFML
        - SDL2

    - Librairies de jeux
        - 
        - Pacman
        - Snake

 ## Classe : Core

Le Coeur du programme est initialisé dans le fichier core.cpp. Il permet le chargement de la librairie graphique indiqué par l’utilisateur et le chargements de toutes les autres librairies graphiques en cas de besoin. Il crée une liste des librairies situé dans un dossier spécifique. Ces librairies seront donc utilisable par le programe.

## Diagramme de classe

<img src="DIAGRAMME/diagramme_classe.jpg" width="400"/>

## Fonctionnement du Core

## DlLoader

La classe `DlLoader` permet de charger les librairies graphiques et les jeux.