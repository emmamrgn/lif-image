# Rapport du Projet de Synthèse (LIFIMAGE)

## Introduction
Ce rapport détaille le projet situé dans le répertoire `LIFIMAGE/gkit3`. Il inclut une description des objectifs, de l'architecture globale, des fonctionnalités implémentées, ainsi que des essais et expérimentations. Ce projet implémente une simulation graphique en utilisant des primitives géométriques (sphères, cubes, plans) et des sources lumineuses pour générer des images réalistes.

---

## Architecture du Projet
Le projet est structuré comme suit :
- **`gkit/`** : Fournit des bibliothèques et outils graphiques nécessaires.
- **`src/`** : Contient les fichiers sources principaux, y compris les fichiers `.h` et `.cpp`.
- **`projet/`** : Contient les fichiers spécifiques ajoutés ou modifiés pour répondre aux besoins de la simulation.
- **`obj/`** : Contient les fichiers `.o` et `.d` nécessaires à la compilation.
- **`bin/`** : Contient les fichiers exécutables du projet, `bin/projet` pour générer l'image de rendu.

---

## Fonctionnalités Bonus Implémentées

### 1. Matières Réfléchissantes
- **Description** : Les objets de la scène (sphères, cubes, plans) peuvent réfléchir ce qui l'entoure, comme un miroir.
- **Implémentation** :
  - La structure `Hit` (dans [`hit.h`](#)) inclut un champ `mirror` représentant le pourcentage de lumière réfléchie.
  - La fonction `affichage` (dans [`projet.cpp`](#)) calcule les réflexions en utilisant la direction miroir et applique le coefficient de réflexion de Fresnel.
- **Résultat** : La sphère à droite est un miroir, mais ne renvoie pas la couleur des objets...


### 2. Flou de Profondeur
- **Description** : Ajout d'un effet de flou pour simuler la profondeur de champ.
- **Implémentation** :
  - Utilisation de plusieurs rayons par pixel (antialiasing) dans la fonction `affichage` (dans [`projet.cpp`](#)).
  - Les rayons sont légèrement décalés aléatoirement pour simuler un flou réaliste.
- **Résultat** : Les objets proches et éloignés apparaissent flous, tandis que les objets au point focal restent nets.

### 3. Une Surprise : Le Cube
- **Description** : Ajout d'une primitive géométrique supplémentaire, le cube, pour enrichir la scène.
- **Implémentation** :
  - La structure `Cube` est définie dans [`cube.h`](#).
  - La fonction `intersect` (dans [`projet.cpp`](#)) gère les intersections entre un rayon et un cube.
- **Résultat** : Les cubes sont correctement intégrés à la scène et interagissent avec la lumière comme les autres objets.

---

## Ce qui n'a pas fonctionné
### 1. Réfraction des Objets
- **Essai** : Implémentation d'une réfraction réaliste pour les objets transparents.
- **Problème** : Les calculs de direction réfractée et les indices de réfraction n'ont pas produit les résultats attendus.
- **Conclusion** : Cette fonctionnalité reste à améliorer dans une version future.

---

## Résultats Visuels
Voici quelques images générées par le projet :

1. **Réflexions** : Une sphère réfléchissante avec un plan en arrière-plan.
   ![Réflexions](img/miroir.png)
   ![Réflexions](img/miroir2.png)

2. **Flou de Profondeur** : Une scène avec plusieurs objets à différentes distances.
   ![Flou de Profondeur](img/flou_profondeur.png)

3. **Surprise - Cube** : 
   ![Cube](img/cube.png)

---

## Conclusion
Ce projet est une implémentation robuste d'une simulation graphique basée sur le lancer de rayons. Les fonctionnalités implémentées, comme les matières réfléchissantes et le flou de profondeur, ajoutent du réalisme à la scène. Bien que certaines expérimentations n'aient pas abouti, elles ouvrent des perspectives pour des améliorations futures.


![Rendu Final](img/rendu_final.png)