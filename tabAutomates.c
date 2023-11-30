#include "tabAutomates.h"
#include <stdbool.h>

void initialiserTableauAutomates(TableauAutomates *tableau) {
    tableau->automates = NULL;
    tableau->nb_automates = 0;
}

void ajouterAutomateTab(TableauAutomates *tableau, Automate automate) {
    tableau->nb_automates++;
    tableau->automates = realloc(tableau->automates, tableau->nb_automates * sizeof(Automate));
    tableau->automates[tableau->nb_automates - 1] = automate;

}

Automate rechercherAutomate(TableauAutomates *tableau, int id){
    return tableau->automates[id-1];
}

void remplacerAutomate(TableauAutomates *tableau, int index, Automate nouvelleAutomate) {
    if (index < 0 || index >= tableau->nb_automates) {
        printf("Indice d'automate invalide.\n");
        return;
    }

    // Remplacer l'automate existant par la nouvelle automate
    tableau->automates[index] = nouvelleAutomate;
}

void afficherNbrAutomate(TableauAutomates *tableau){

    printf("\nLe nombre d'automates existants est : %d", tableau.nb_automates);
}

void supprimerAutomateTab(TableauAutomates *tableau, int index) {
    if (index < 0 || index >= tableau->nb_automates) {
        printf("Indice d'automate invalide.\n");
        return;
    }

    // Lib�rer la m�moire de l'automate � supprimer
    supprimerAutomate(&tableau->automates[index]);
    free(&tableau->automates[index]);


    // D�calage des automates apr�s l'automate � supprimer
    for (int i = index; i < tableau->nb_automates - 1; i++) {
        tableau->automates[i] = tableau->automates[i + 1];
    }

    // R�duction de la taille de la m�moire allou�e
    tableau->nb_automates--;
    tableau->automates = realloc(tableau->automates, tableau->nb_automates * sizeof(Automate));
}
