#include "automate.h"

void menuPrincipal() {
    printf("--------------------------------------------------------\n");
    printf("         Projet Automates d'etats Finis (AEF)           \n");
    printf("--------------------------------------------------------\n");
    printf("Que voulez-vous faire ?\n");
    printf("1- Manipuler un AEF\n");
    printf("2- Verifier si un mot est reconnu par un AEF\n");
    printf("3- Verifier si un automate est complet\n");
    printf("4- Rendre un automate complet\n");
    printf("5- Verifier si un automate est deterministe\n");
    printf("6- Rendre un AEF deterministe\n");
    printf("7- Operations sur les AEF (complement, miroir, etc.)\n");
    printf("8- Extraire une expression reguliere d'un automate\n");
    printf("9- Trouver le langage reconnu par un automate\n");
    printf("10- Verifier si deux automates sont equivalents\n");
    printf("11- Rendre un automate emonde\n");
    printf("12- Rendre un automate minimal\n");
    printf("0- Quitter\n");
    printf("--------------------------------------------------------\n");
}
void menuManipuler() {
    printf("Vous avez choisi de manipuler un AEF.\n\n");
    printf("Menu :\n");
    printf("1. Saisir un AEF\n");
    printf("2. Importer un AEF a partir d'un fichier\n");
    printf("3. Modifier un AEF\n");
    printf("4. Sauvegarder un AEF dans un fichier\n");
    printf("5. Supprimer un AEF\n");
    printf("6- Quitter\n");
    printf("7- Menu principal\n");
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


// Fonction pour ajouter un etat a l'automate
void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final) {
    // Verifier si l'etat existe deja dans l'automate
    Etat *existant = rechercherEtat(automate, etat);
    if (existant != NULL) {
        printf("L'etat %d existe deja dans l'automate.\n", etat);
        return;
    }

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


// Fonction pour ajouter un symbole e l'automate
void ajouterSymbole(Automate *automate, char symbole) {
    // Verifier si le symbole existe deja dans l'automate
    if (rechercherSymbole(automate, symbole) != NULL) {
        printf("Le symbole '%c' existe deje dans l'automate.\n", symbole);
        return;  // Ne pas ajouter le symbole s'il existe deja
    }

    // Ajouter le symbole s'il n'existe pas
    automate->symboles = (Symbole*)realloc(automate->symboles, (automate->nb_symboles + 1) * sizeof(Symbole));
    Symbole nouveau_symbole;
    nouveau_symbole.symbole = symbole;
    automate->symboles[automate->nb_symboles] = nouveau_symbole;
    automate->nb_symboles++;
}


// Fonction pour ajouter une transition e l'automate
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers) {
    // Verifier si une transition identique existe deja
    if (rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL) {
        printf("La transition existe deja dans l'automate.\n");
        return;  // Ne pas ajouter la transition si elle existe deja
    }

    // Si la transition est unique, l'ajouter a l'automate
    automate->transitions = (Transition*)realloc(automate->transitions, (automate->nb_transitions + 1) * sizeof(Transition));
    Transition nouvelle_transition;
    nouvelle_transition.etat_depuis = etat_depuis;
    nouvelle_transition.symbole_entree = symbole_entree;
    nouvelle_transition.etat_vers = etat_vers;
    automate->transitions[automate->nb_transitions] = nouvelle_transition;
    automate->nb_transitions++;
}


// Fonction pour verifier si un etat est final
int estEtatFinal(Automate *automate, int etat) {
    //printf("\n Nbre etat fin : %d",automate->nb_etats_finaux);
    for (int i = 0; i < automate->nb_etats_finaux; i++) {
            //printf("\n test fin : %d  X  %d", automate->etats_finaux[i],etat);
        if (automate->etats_finaux[i] == etat) {
            //printf("\n AYA BEHY");
            return 1;
        }
    }
    return 0;
}

// Fonction pour effectuer une transition
int effectuerTransition(Automate *automate, int etat_actuel, char symbole_entree) {
    //printf("\n Nbre transition : %d" , automate->nb_transitions);
    for (int i = 0; i < automate->nb_transitions; i++) {
            //printf("\n Transition entre : %d %c \n", etat_actuel, symbole_entree);
            //printf("\n Transition trouve : %d %c %d \n", automate->transitions[i].etat_depuis, automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
        if (automate->transitions[i].etat_depuis == etat_actuel && automate->transitions[i].symbole_entree == symbole_entree) {
            //printf("\n Tres bien vers %d",automate->transitions[i].etat_vers);
            return automate->transitions[i].etat_vers;

        }
    }
    return -1;  // Pas de transition pour le symbole donne
}

// Fonction pour verifier si un mot est accepte par l'automate
int accepterMot(Automate *automate, const char *mot) {
    int etat_actuel = automate->etat_initial;
    //printf("\n Etat initial automate : %d", automate->etat_initial);
    //printf("\n mot[0] %c", mot[0]);
    for (int i = 0; mot[i] != '\0'; i++) {
        etat_actuel = effectuerTransition(automate, etat_actuel, mot[i]);


        if (etat_actuel == -1) {
            //printf("\n WWWWWIIIWWWW");
            return 0;  // Rejete si aucune transition possible
        }
    }
    //printf("\n Est final ? %d",estEtatFinal(automate, etat_actuel));
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
    char *token = NULL; // Declarez token en dehors de la boucle

    // Lire les etats
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL) {
        int etat = atoi(token);
        ajouterEtat(&automate, etat, 0, 0);
        token = strtok(NULL, ",");
    }

    // Lire l'etat initial
    fgets(ligne, sizeof(ligne), fichier);
    int etat_initial = atoi(ligne);
    for (int i = 0; i < automate.nb_etats; i++) {
        if (automate.etats[i].etat == etat_initial) {
            automate.etats[i].est_initial = 1;
            automate.etat_initial = automate.etats[i].etat;
            break;
        }
    }

    // Lire les etats finaux
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

void creerAutomate(Automate *automate) {
    int nb_etats, nb_symboles, nb_transitions;
    Etat *existant;
    int aumoinsInitial = 0;

    // Demander le nombre d'etats
    printf("Combien d'etats voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_etats);
    do{
    for (int i = 0; i < nb_etats; i++) {
        int etat, est_initial, est_final;

        if((i==nb_etats-1) && (aumoinsInitial==0))
        {
            printf("\n C'est le dernier a ajouter. Dans un AEF, il faut toujours avoir au moins un etat initial\n");
        }

        do{
        // Demander les details de l'etat
        printf("etat %d : ", i + 1);
        scanf("%d", &etat);
        existant = rechercherEtat(automate, etat);
        if (existant != NULL) {
            printf("L'etat %d existe deja dans l'automate.\n", etat);
        }
        }while (existant != NULL);

        // Demander si c'est un etat initial (1) ou non (0)
        do {
            printf("Est initial (1 : si oui/ 0 : sinon) : ");
            scanf("%d", &est_initial);
            if(est_initial==1){
                aumoinsInitial=1;
            }
        } while (est_initial != 0 && est_initial != 1);

        // Demander si c'est un etat final (1) ou non (0)
        do {
            printf("Est final (1 : si oui/ 0 : sinon) : ");
            scanf("%d", &est_final);
        } while (est_final != 0 && est_final != 1);

        // Ajouter l'etat e l'automate
        ajouterEtat(automate, etat, est_initial, est_final);
    }
    }while(aumoinsInitial==0);

    // Demander le nombre de symboles
    printf("Combien de Symboles voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_symboles);

    for (int i = 0; i < nb_symboles; i++) {
        char symbole;
        do{
        // Demander les details du symbole
        printf("Symbole %d : ", i + 1);
        scanf(" %c", &symbole); // Utilisation d'un espace pour ignorer les espaces ou les sauts de ligne

        if (rechercherSymbole(automate, symbole) != NULL) {
            printf("Le symbole '%c' existe deja dans l'automate.\n", symbole);
        }
        }while(rechercherSymbole(automate, symbole) != NULL);

        // Ajouter le symbole e l'automate
        ajouterSymbole(automate, symbole);
    }

    // Demander le nombre de transitions
    printf("Combien de Transitions voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_transitions);

    for (int i = 0; i < nb_transitions; i++) {
        int etat_depuis, etat_vers;
        char symbole_entree;

        do{
        // Demander les details de la transition
        printf("Transition %d - etat de depart : ", i + 1);
        scanf("%d", &etat_depuis);
        printf("Transition %d - Symbole d'entree : ", i + 1);
        scanf(" %c", &symbole_entree); // Utilisation d'un espace pour ignorer les espaces et les sauts de ligne
        printf("Transition %d - etat d'arrivee : ", i + 1);
        scanf("%d", &etat_vers);

        if (rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL) {
            printf("La transition existe deja dans l'automate.\n");
        }
        }while(rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL);

        // Ajouter la transition e l'automate
        ajouterTransition(automate, etat_depuis, symbole_entree, etat_vers);
    }
}

void afficherAutomate(Automate *automate) {
    printf("Automate :\n");

    printf("etats :\n");
    for (int i = 0; i < automate->nb_etats; i++) {
        printf("etat %d - ID : %d, Initial : %d, Final : %d\n", i + 1, automate->etats[i].etat, automate->etats[i].est_initial, automate->etats[i].est_final);
    }

    printf("Symboles :\n");
    for (int i = 0; i < automate->nb_symboles; i++) {
        printf("Symbole %d - %c\n", i + 1, automate->symboles[i].symbole);
    }

    printf("Transitions :\n");
    for (int i = 0; i < automate->nb_transitions; i++) {
        printf("Transition %d - De : %d, Symbole : %c, Vers : %d\n", i + 1, automate->transitions[i].etat_depuis, automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
    }
}

void supprimerAutomate(Automate *automate) {
    free(automate->etats);
    free(automate->etats_finaux);
    free(automate->symboles);
    free(automate->transitions);
    initialiserAutomate(automate);
}

Etat* rechercherEtat(Automate *automate, int id) {
    for (int i = 0; i < automate->nb_etats; i++) {
        if (automate->etats[i].etat == id) {
            return &(automate->etats[i]);  // Retourne un pointeur vers l'etat trouve
        }
    }
    return NULL;  // L'etat n'a pas ete trouve
}

Symbole* rechercherSymbole(Automate *automate, char symbole_recherche) {
    for (int i = 0; i < automate->nb_symboles; i++) {
        if (automate->symboles[i].symbole == symbole_recherche) {
            return &(automate->symboles[i]);
        }
    }
    return NULL;  // Symbole non trouve
}

Transition* rechercherTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers) {
    for (int i = 0; i < automate->nb_transitions; i++) {
        Transition *transition = &automate->transitions[i];
        if (transition->etat_depuis == etat_depuis && transition->symbole_entree == symbole_entree && transition->etat_vers == etat_vers) {
            return transition;  // Retourner la transition si elle est trouvee
        }
    }
    return NULL;  // Retourner NULL si la transition n'est pas trouvee
}


void modifierEtat(Automate *automate) {
    int id_etat;
    Etat *etat_a_modifier;
    do {
        printf("Entrez le numero de l'etat a modifier : ");
        scanf("%d", &id_etat);
        etat_a_modifier = rechercherEtat(automate, id_etat);
        if (etat_a_modifier == NULL) {
            printf("L'etat avec le numero %d n'existe pas dans l'automate. Veuillez reessayer.\n", id_etat);
        }
    } while (etat_a_modifier == NULL);

    int choix;
    do {
        printf("Que voulez-vous faire avec l'etat %d ?\n", id_etat);
        printf("1- Le rendre non final (s'il est final)\n");
        printf("2- Le rendre final (s'il n'est pas final)\n");
        scanf("%d", &choix);
    } while (choix != 1 && choix != 2);

    // Modifier l'etat en consequence
    if (choix == 1) {
        // Le rendre non final
        if (etat_a_modifier->est_final) {
            etat_a_modifier->est_final = 0;
            printf("L'etat %d a ete rendu non final.\n", id_etat);
        } else {
            printf("L'etat %d n'etait pas final, donc il n'a pas ete modifie.\n", id_etat);
        }
    } else if (choix == 2) {
        // Le rendre final
        if (!etat_a_modifier->est_final) {
            etat_a_modifier->est_final = 1;
            printf("L'etat %d a ete rendu final.\n", id_etat);
        } else {
            printf("L'etat %d etait deja final, donc il n'a pas ete modifie.\n", id_etat);
        }
    }
}

void modifierAutomate(Automate *automate) {
    int choix;

    printf("Que voulez-vous modifier ?\n");
    printf("1- Modifier les etats\n");
    printf("2- Modifier les transitions\n");
    printf("3- Modifier les symboles\n");

    scanf("%d", &choix);

    switch (choix) {
        case 1:
            modifierEtat(automate);
            break;
        case 2:
            // Modifier les transitions
            // Vous pouvez appeler une fonction pour cela
            // Exemple : modifierTransitions(automate);
            break;
        case 3:
            // Modifier les symboles
            // Vous pouvez appeler une fonction pour cela
            // Exemple : modifierSymboles(automate);
            break;
        default:
            printf("Choix invalide.\n");
    }
}



void lectureFichier(char nom_fichier[]) {
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

void sauvegarderAutomate(Automate *automate) {
    char nom_fichier[100];
    printf("Entrez le nom du fichier de sauvegarde : ");
    scanf("%s", nom_fichier);

    FILE *fichier = fopen(nom_fichier, "w");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    // Ecrire les Etats de l'automate
    for (int i = 0; i < automate->nb_etats; i++) {
        fprintf(fichier, "%d", automate->etats[i].etat);
        if (i < automate->nb_etats - 1) {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les Etats initiaux
    fprintf(fichier, "%d\n", automate->etat_initial);

    // Ecrire les Etats finaux

    for (int i = 0; i < automate->nb_etats_finaux; i++) {
        fprintf(fichier, "%d", automate->etats_finaux[i]);
        if (i < automate->nb_etats_finaux - 1) {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les symboles
    for (int i = 0; i < automate->nb_symboles; i++) {
        fprintf(fichier, "%c", automate->symboles[i].symbole);
        if (i < automate->nb_symboles - 1) {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les transitions
    for (int i = 0; i < automate->nb_transitions; i++) {
        fprintf(fichier, "%d,%c,%d\n", automate->transitions[i].etat_depuis,
                automate->symboles[i].symbole, automate->transitions[i].etat_vers);
    }

    fclose(fichier);
}
