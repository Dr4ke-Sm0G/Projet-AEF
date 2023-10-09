#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter un état dans l'AEF
struct Etat {
    int numero; // Numéro de l'état
    int estFinal; // 1 si c'est un état final, 0 sinon
};

// Structure pour représenter une transition dans l'AEF
struct Transition {
    int etatSource;
    char symbole;
    int etatDestination;
};

// Structure pour représenter l'AEF
struct Automate {
    int nbEtats;
    int nbTransitions;
    struct Etat *etats;
    struct Transition *transitions;
    int etatInitial;
};

// Fonction pour saisir un AEF
void saisirAEF(struct Automate *aef) {
    printf("Saisie d'un Automate d'Etats Finis (AEF)\n");

    // Saisie du nombre d'états
    printf("Nombre d'etats : ");
    scanf("%d", &aef->nbEtats);

    // Saisie de l'état initial
    printf("Etat initial : ");
    scanf("%d", &aef->etatInitial);

    // Allouer de la mémoire pour les états
    aef->etats = malloc(aef->nbEtats * sizeof(struct Etat));
    
    // Saisie des détails des états
    for (int i = 0; i < aef->nbEtats; i++) {
        printf("Etat %d (Tapez 1 pour etat final, 0 sinon) : ", i);
        scanf("%d", &aef->etats[i].estFinal);
        aef->etats[i].numero = i;
    }

    // Saisie du nombre de transitions
    printf("Nombre de transitions : ");
    scanf("%d", &aef->nbTransitions);

    // Allouer de la mémoire pour les transitions
    aef->transitions = malloc(aef->nbTransitions * sizeof(struct Transition));

    // Saisie des détails des transitions   
    for (int i = 0; i < aef->nbTransitions; i++) {
        printf("Transition %d (etat source, symbole, etat destination) : ", i);
        scanf("%d %c %d", &aef->transitions[i].etatSource, &aef->transitions[i].symbole, &aef->transitions[i].etatDestination);
    }


}


// Fonction pour importer un AEF à partir d'un fichier
void importerAEF(struct Automate *aef, const char *nomFichier)
{
    // Implémentez la logique d'importation depuis le fichier ici
}

// Fonction pour modifier un AEF
void modifierAEF(struct Automate *aef)
{
    // Implémentez la logique de modification ici
}

// Fonction pour sauvegarder un AEF dans un fichier
void sauvegarderAEF(const struct Automate *aef, const char *nomFichier) {

    printf("Veuillez saisir l'AEF que vous souhaiter sauvegarder");
    void saisirAEF(struct Automate &aef);
    FILE *fichier = fopen(nomFichier, "w"); // Ouvrir le fichier en mode écriture

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }
    // Écrire les informations de l'AEF dans le fichier
    fprintf(fichier, "Automate d'États Finis (AEF) :\n");
    fprintf(fichier, "Nombre d'états : %d\n", aef->nbEtats);
    fprintf(fichier, "État initial : %d\n", aef->etatInitial);

    fprintf(fichier, "Détails des états :\n");
    for (int i = 0; i < aef->nbEtats; i++) {
        fprintf(fichier, "État %d (Final : %d)\n", aef->etats[i].numero, aef->etats[i].estFinal);
    }

    fprintf(fichier, "Nombre de transitions : %d\n", aef->nbTransitions);

    fprintf(fichier, "Détails des transitions :\n");
    for (int i = 0; i < aef->nbTransitions; i++) {
        fprintf(fichier, "Transition %d : État Source : %d, Symbole : %c, État Destination : %d\n",
               i, aef->transitions[i].etatSource, aef->transitions[i].symbole, aef->transitions[i].etatDestination);
    }

    fclose(fichier); // Fermer le fichier après avoir écrit les données
}

// Fonction pour supprimer un AEF

void supprimerAEF(struct Automate *aef) {

    // Libérer la mémoire pour les tableaux dynamiques (états et transitions)

    free(aef->etats);
    free(aef->transitions);

    // Remettre les pointeurs à NULL 

    aef->etats = NULL;
    aef->transitions = NULL;

    // Réinitialiser le nombre d'états et de transitions à zéro
    aef->nbEtats = 0;
    aef->nbTransitions = 0;

}
