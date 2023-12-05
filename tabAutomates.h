#ifndef TABAUTOMATES_H_INCLUDED
#define TABAUTOMATES_H_INCLUDED

#include "automate.h"
#include <stdbool.h>
// Structure pour representer un tableau d'automates
typedef struct {
    Automate *automates;
    int nb_automates;
} TableauAutomates;

void initialiserTableauAutomates(TableauAutomates *tableau);
void ajouterAutomateTab(TableauAutomates *tableau, Automate automate);
void supprimerAutomateTab(TableauAutomates *tableau, int index);
Automate rechercherAutomate(TableauAutomates *tableau, int id);
void remplacerAutomate(TableauAutomates *tableau, int index, Automate nouvelleAutomate);
void afficherNbrAutomate(TableauAutomates *tableau);

#endif // TABAUTOMATES_H_INCLUDED