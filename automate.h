#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>

#include "etat.h"
#include "symbole.h"
#include "transition.h"

typedef struct {
    int id;
    Etat *etats;
    int nb_etats;
    int etat_initial;
    int *etats_finaux;
    int nb_etats_finaux;
    Symbole *symboles;
    int nb_symboles;
    Transition *transitions;
    int nb_transitions;
    char* expression_actuelle;
    int etat_courant;
} Automate;

void menuPrincipal();
void menuManipuler();
void menuOperations();

void initialiserAutomate(Automate *automate);

Etat* rechercherEtat(Automate *automate, int id);
Symbole* rechercherSymbole(Automate *automate, char symbole_recherche);
Transition* rechercherTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers);

void lectureFichier(char nom_fichier[]);
Automate initialiserAutomateDepuisFichier(const char *nom_fichier);

void creerAutomate(Automate *automate);
void afficherAutomate(Automate *automate);
void supprimerAutomate(Automate *automate);
void modifierAutomate(Automate *automate);
void sauvegarderAutomate(Automate *automate);

void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final);
void ajouterSymbole(Automate *automate, char symbole);
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers);

int estEtatFinal(Automate *automate, int etat);
int effectuerTransition(Automate *automate, int etat_actuel, char symbole_entree);
int accepterMot(Automate *automate, const char *mot);

void modifierTransition(Automate *automate);

bool estAutomateComplet(Automate *automate);
void rendreAutomateComplet(Automate *automate);

bool estAutomateDeterministe(Automate *automate);
void rendreAutomateDeterministe(Automate *automate);


// char* construireExpression(Automate *automate);
// char* extraireExpressionsRegulieres(Automate *automate);

void completerAutomate(Automate *automate);
void miroirAutomate(Automate *automate);
void produitAutomates(Automate *automateA, Automate *automateB, Automate *produit);


#endif // AUTOMATE_H_INCLUDED