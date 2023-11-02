#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#include "etat.h"
#include "symbole.h"
#include "transition.h"

typedef struct {
    Etat *etats;
    int nb_etats;
    int etat_initial;
    int *etats_finaux;
    int nb_etats_finaux;
    Symbole *symboles;
    int nb_symboles;
    Transition *transitions;
    int nb_transitions;
} Automate;

void menu();

void initialiserAutomate(Automate *automate);

void lectureFichier(char nom_fichier[]);
Automate initialiserAutomateDepuisFichier(const char *nom_fichier);


void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final);
void ajouterSymbole(Automate *automate, char symbole);
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers);

int estEtatFinal(Automate *automate, int etat);
int effectuerTransition(Automate *automate, int etat_actuel, char symbole_entree);
int accepterMot(Automate *automate, const char *mot);

#endif // AUTOMATE_H_INCLUDED
