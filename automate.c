#include "automate.h"

void menu(){
        printf("-------------------------------------------------------------------------------\n");
        printf("-----------------Projet Automates d'etats Finis  AEF---------------------------\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("- Que voulez-vous faire ? -----------------------------------------------------\n");
        printf("- 1- Ajouter un AEF------------------------------------------------------------\n");
        printf("- 2- Modifier un AEF-----------------------------------------------------------\n");
        printf("- 3- Supprimer un AEF----------------------------------------------------------\n");
        printf("- 4- Recuprer un AEF depuis un fichier-----------------------------------------\n");
        printf("- 5- Verifier si un mot est reconnu par un AEF---------------------------------\n");
        printf("- 6- Verifier si un automate est complet---------------------------------------\n");
        printf("- 7- Rendre un automate complet------------------------------------------------\n");
        printf("- 8- Verifier si un automate est deterministe----------------------------------\n");
        printf("- 9- Rendre un AEF deterministe------------------------------------------------\n");
        printf("- 10- Realiser des operations (Complement d'un AEF,Miroir d'un AEF,... )-------\n");
        printf("- 11- Extraire une expression reguliere a partir d'un automate donne-----------\n");
        printf("- 12- Trouver le langage reconnu par un automate donne-------------------------\n");
        printf("- 13- Verifier si deux automates sont equivalents------------------------------\n");
        printf("- 14- Rendre un automate emonde------------------------------------------------\n");
        printf("- 15- Rendre un automate minimal-----------------------------------------------\n");
        printf("- 0- Quitter-------------------------------------------------------------------\n");
        printf("-------------------------------------------------------------------------------\n");

}

// Fonction pour initialiser l'automate
void initialiserAutomate(Automate *automate){
    automate->nb_etats = 0;
    automate->nb_etats_finaux = 0;
    automate->nb_symboles = 0;
    automate->nb_transitions = 0;
    automate->etats = NULL;
    automate->etats_finaux = NULL;
    automate->symboles = NULL;
    automate->transitions = NULL;
}

// Fonction pour ajouter un �tat � l'automate
void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final){
    automate->etats = (Etat*)realloc(automate->etats, (automate->nb_etats + 1) * sizeof(Etat));
    Etat nouvel_etat;
    nouvel_etat.etat = etat;
    nouvel_etat.est_initial = est_initial;
    nouvel_etat.est_final = est_final;
    automate->etats[automate->nb_etats] = nouvel_etat;
    automate->nb_etats++;
    if (est_initial) {
        automate->etat_initial = etat;
    }
    if (est_final) {
        automate->etats_finaux = (int*)realloc(automate->etats_finaux, (automate->nb_etats_finaux + 1) * sizeof(int));
        automate->etats_finaux[automate->nb_etats_finaux] = etat;
        automate->nb_etats_finaux++;
    }
}

// Fonction pour ajouter un symbole � l'automate
void ajouterSymbole(Automate *automate, char symbole) {
    automate->symboles = (Symbole*)realloc(automate->symboles, (automate->nb_symboles + 1) * sizeof(Symbole));
    Symbole nouveau_symbole;
    nouveau_symbole.symbole = symbole;
    automate->symboles[automate->nb_symboles] = nouveau_symbole;
    automate->nb_symboles++;
}

// Fonction pour ajouter une transition � l'automate
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers) {
    automate->transitions = (Transition*)realloc(automate->transitions, (automate->nb_transitions + 1) * sizeof(Transition));
    Transition nouvelle_transition;
    nouvelle_transition.etat_depuis = etat_depuis;
    nouvelle_transition.symbole_entree = symbole_entree;
    nouvelle_transition.etat_vers = etat_vers;
    automate->transitions[automate->nb_transitions] = nouvelle_transition;
    automate->nb_transitions++;
}

// Fonction pour v�rifier si un �tat est final
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
    return -1;  // Pas de transition pour le symbole donn�
}

// Fonction pour v�rifier si un mot est accept� par l'automate
int accepterMot(Automate *automate, const char *mot) {
    int etat_actuel = automate->etat_initial;
    printf("\n Etat initial automate : %d", automate->etat_initial);
    printf("\n mot[0] %c", mot[0]);
    for (int i = 0; mot[i] != '\0'; i++) {
        etat_actuel = effectuerTransition(automate, etat_actuel, mot[i]);


        if (etat_actuel == -1) {
            printf("\N WWWWWIIIWWWW");
            return 0;  // Rejet� si aucune transition possible
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

    char ligne[100];
    char *token = NULL; // D�clarez token en dehors de la boucle

    // Lire les �tats
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL) {
        int etat = atoi(token);
        ajouterEtat(&automate, etat, 0, 0);
        token = strtok(NULL, ",");
    }

    // Lire l'�tat initial
    fgets(ligne, sizeof(ligne), fichier);
    int etat_initial = atoi(ligne);
    for (int i = 0; i < automate.nb_etats; i++) {
        if (automate.etats[i].etat == etat_initial) {
            automate.etats[i].est_initial = 1;
            automate.etat_initial = automate.etats[i].etat;
            break;
        }
    }

    // Lire les �tats finaux
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL) {
        int etat_final = atoi(token);
        for (int i = 0; i < automate.nb_etats; i++) {
            if (automate.etats[i].etat == etat_final) {
                automate.etats[i].est_final = 1;
                automate.etats_finaux = (int*)realloc(automate.etats_finaux, (automate.nb_etats_finaux + 1) * sizeof(int));
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


void lectureFichier(char nom_fichier[]) {
    while (1) {
        printf("Entrez le nom du fichier : ");
        scanf("%s", nom_fichier);

        if (access(nom_fichier, F_OK) != -1) {
            break;  // Sortir de la boucle si le fichier existe
        } else {
            printf("Le fichier n'existe pas. Veuillez r�essayer.\n");
        }
    }
}
