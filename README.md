# Projet Automate en C

## Description
Ce projet implémente un système de gestion d'automates en C. Il permet de créer, modifier, sauvegarder et effectuer diverses opérations sur des automates, tels que vérifier leur complétude, les rendre déterministes, et plus encore.

## Fonctionnalités
- Création et initialisation d'automates
- Lecture et sauvegarde d'automates depuis/vers des fichiers
- Manipulation d'automates (complétion, détermination, miroir, concaténation, etc.)
- Vérification de mots par des automates
- Extraction d'expressions régulières
- Opérations sur plusieurs automates (produit, concaténation)

## Dépendances
- `stdio.h`
- `stdlib.h`
- `string.h`
- `unistd.h`
- `windows.h` (pour la fonction `GetFileAttributes`)
- `automate.h`
- `tabAutomates.h`

## Compilation et Exécution
Pour compiler ce projet, utilisez la commande suivante :
```gcc -o main .\automate.c .\automate.h .\etat.c .\etat.h .\main.c .\main.h .\symbole.c .\symbole.h .\tabAutomates.c .\tabAutomates.h .\transition.c .\transition.h ```

Pour exécuter le programme, lancez :

```./main```
## Utilisation
Le programme fonctionne en mode console. Suivez les instructions à l'écran pour choisir différentes opérations sur les automates.

## Auteur

- CHAHID Yassine
- Ahmed MAAOUIA
- Haroun JOUDI
- Aymane Outimjicht
- Naoufal Berquecha

## Remerciements
**
Un grand merci à la professeure Zaouche Djaouida pour nous avoir confié ce projet. Les défis qu'il présentait nous ont permis de mieux maîtriser notre façon de programmer et d'approfondir notre compréhension du langage C. Ce projet a été une opportunité précieuse d'apprentissage et de développement de nos compétences en programmation.
**

