#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>  // Pour la fonction GetFileAttributes

#define MAX_STATES 100
#define MAX_SYMBOLS 100
#define MAX_TRANSITIONS 100

// Structure pour représenter un état de l'automate
typedef struct {
    int etat;
    int est_initial;
    int est_final;
} Etat;

// Structure pour représenter un symbole de l'automate
typedef struct {
    char symbole;
} Symbole;

// Structure pour représenter une transition de l'automate
typedef struct {
    int etat_depuis;
    char symbole_entree;
    int etat_vers;
} Transition;

// Structure pour représenter l'automate
typedef struct {
    Etat etats[MAX_STATES];
    int nb_etats;
    int etat_initial;
    int etats_finaux[MAX_STATES];
    int nb_etats_finaux;
    Symbole symboles[MAX_SYMBOLS];
    int nb_symboles;
    Transition transitions[MAX_TRANSITIONS];
    int nb_transitions;
} Automate;

// Fonction pour initialiser l'automate
void initialiserAutomate(Automate *automate) {
    automate->nb_etats = 0;
    automate->nb_etats_finaux = 0;
    automate->nb_symboles = 0;
    automate->nb_transitions = 0;
}

// Fonction pour ajouter un état à l'automate
void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final) {
    Etat nouvel_etat;
    nouvel_etat.etat = etat;
    nouvel_etat.est_initial = est_initial;
    nouvel_etat.est_final = est_final;
    automate->etats[automate->nb_etats++] = nouvel_etat;
    if (est_initial) {
        automate->etat_initial = etat;
    }
    if (est_final) {
        automate->etats_finaux[automate->nb_etats_finaux++] = etat;
    }
}

// Fonction pour ajouter un symbole à l'automate
void ajouterSymbole(Automate *automate, char symbole) {
    Symbole nouveau_symbole;
    nouveau_symbole.symbole = symbole;
    automate->symboles[automate->nb_symboles++] = nouveau_symbole;
}

// Fonction pour ajouter une transition à l'automate
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers) {
    Transition nouvelle_transition;
    nouvelle_transition.etat_depuis = etat_depuis;
    nouvelle_transition.symbole_entree = symbole_entree;
    nouvelle_transition.etat_vers = etat_vers;
    automate->transitions[automate->nb_transitions++] = nouvelle_transition;
}

// Fonction pour vérifier si un état est final
int estEtatFinal(Automate *automate, int etat) {
    printf("\n Nbre etat fin : %d",automate->nb_etats_finaux);
    for (int i = 0; i < automate->nb_etats_finaux; i++) {
            printf("\n test fin : %d  X  %d", automate->etats_finaux[i],etat);
        if (automate->etats_finaux[i] == etat) {
            printf("\n AYA BEHY");
            return 1;
        }
    }
    return 0;
}

// Fonction pour effectuer une transition
int effectuerTransition(Automate *automate, int etat_actuel, char symbole_entree) {
    printf("\n Nbre transition : %d" , automate->nb_transitions);
    for (int i = 0; i < automate->nb_transitions; i++) {
            printf("\n Transition entre : %d %c \n", etat_actuel, symbole_entree);
            printf("\n Transition trouve : %d %c %d \n", automate->transitions[i].etat_depuis, automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
        if (automate->transitions[i].etat_depuis == etat_actuel && automate->transitions[i].symbole_entree == symbole_entree) {
            printf("\n Tres bien vers %d",automate->transitions[i].etat_vers);
            return automate->transitions[i].etat_vers;

        }
    }
    return -1;  // Pas de transition pour le symbole donné
}

// Fonction pour vérifier si un mot est accepté par l'automate
int accepterMot(Automate *automate, const char *mot) {
    int etat_actuel = automate->etat_initial;
    printf("\n Etat initial automate : %d", automate->etat_initial);
    printf("\n mot[0] %c", mot[0]);
    for (int i = 0; mot[i] != '\0'; i++) {
        etat_actuel = effectuerTransition(automate, etat_actuel, mot[i]);


        if (etat_actuel == -1) {
            printf("\N WWWWWIIIWWWW");
            return 0;  // Rejeté si aucune transition possible
        }
    }
    printf("\n Est final ? %d",estEtatFinal(automate, etat_actuel));
    return estEtatFinal(automate, etat_actuel);
}

Automate initialiserAutomateDepuisFichier(const char *nom_fichier) {
    Automate automate;
    initialiserAutomate(&automate);

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    // Lire les états
    char ligne[100];
    fgets(ligne, sizeof(ligne), fichier);
    char *token = strtok(ligne, ",");
    while (token != NULL) {
        int etat = atoi(token);
        ajouterEtat(&automate, etat, 0, 0);
        token = strtok(NULL, ",");
    }

    // Lire les états initiaux
    fgets(ligne, sizeof(ligne), fichier);
    int etat_initial = atoi(ligne);
    for (int i = 0; i < automate.nb_etats; i++) {
        if (automate.etats[i].etat == etat_initial) {
            automate.etats[i].est_initial = 1;
            automate.etat_initial = automate.etats[i].etat;
            break;
        }
    }

    // Lire les états finaux
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL) {
        int etat_final = atoi(token);
        for (int i = 0; i < automate.nb_etats; i++) {
            if (automate.etats[i].etat == etat_final) {
                automate.etats[i].est_final = 1;
                automate.etats_finaux[automate.nb_etats_finaux] = automate.etats[i].etat;
                automate.nb_etats_finaux += 1;
                break;
            }
        }
        token = strtok(NULL, ",");
    }

    // Lire les symboles
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL) {
        char symbole = token[0];
        ajouterSymbole(&automate, symbole);
        token = strtok(NULL, ",");
    }

    // Lire les transitions
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int etat_depuis, etat_vers;
        char symbole_entree;
        sscanf(ligne, "%d,%c,%d", &etat_depuis, &symbole_entree, &etat_vers);
        ajouterTransition(&automate, etat_depuis, symbole_entree, etat_vers);
    }

    fclose(fichier);

    return automate;
}

void lectureFichier(nom_fichier){
    while (1) {
        printf("Entrez le nom du fichier : ");
        scanf("%s", nom_fichier);

        if (access(nom_fichier, F_OK) != -1) {
            break;  // Sortir de la boucle si le fichier existe
        } else {
            printf("Le fichier n'existe pas. Veuillez reessayer.\n");
        }
    }

}

int main() {


    char nom_fichier[100];  // Un tableau pour stocker le nom du fichier
    lectureFichier(nom_fichier);
    Automate automate = initialiserAutomateDepuisFichier(nom_fichier);

    // Test de l'automate avec un mot
    char mot[100];
    printf("\n Entrez un mot : ");
    scanf("%s", mot);

    if (accepterMot(&automate, mot)==1) {
        printf("\n Le mot est accepté.\n");
    } else {
        printf("\n Le mot est rejeté.\n");
    }

    return 0;
}
