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

void menuPrincipal();
void menuManipuler();

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



// --------------------------FONTIONS-DE-L'ETAPE-12------------------------------------------------------------

void marquerEtatsAtteignables(Automate *automate, int etat_actuel, int *etatsAtteignables);
void supprimerEtatsInatteignables(Automate *automate);
void identifierEtatsIndistinguables(Automate *automate, int ***groupesRetour, int *nbGroupesRetour);
void fusionnerEtatsIndistinguables(Automate *automate, int **groupes, int nbGroupes);
int groupeDeLEtat(int etat, int **groupes, int nbGroupes, int nbEtats);
void rendreAutomateMinimal(Automate *automate);

#endif // AUTOMATE_H_INCLUDED