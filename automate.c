#include "automate.h"
#include "tabAutomates.h"
#include <stdbool.h>

void menuPrincipal()
{
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
void menuManipuler()
{
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

void menuOperations()
{
    printf("Vous avez choisi de realiser les operations suivantes sur les AEFs\n\n");
    printf("Menu :\n");
    printf("1. Complement d'un AEF\n");
    printf("2. Miroir d'un AEF\n");
    printf("3. Produit de deux AEFs\n");
    printf("4. Concatenation de deux AEFs\n");
    printf("6- Quitter\n");
    printf("7- Menu principal\n");
}

// Fonction pour initialiser l'automate
void initialiserAutomate(Automate *automate)
{
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
void ajouterEtat(Automate *automate, int etat, int est_initial, int est_final)
{
    // Verifier si l'etat existe deja dans l'automate
    Etat *existant = rechercherEtat(automate, etat);
    if (existant != NULL)
    {
        printf("L'etat %d existe deja dans l'automate.\n", etat);
        return;
    }

    automate->etats = (Etat *)realloc(automate->etats, (automate->nb_etats + 1) * sizeof(Etat));
    Etat nouvel_etat;
    nouvel_etat.etat = etat;
    nouvel_etat.est_initial = est_initial;
    nouvel_etat.est_final = est_final;
    automate->etats[automate->nb_etats] = nouvel_etat;
    automate->nb_etats++;
    if (est_initial)
    {
        automate->etat_initial = etat;
    }
    if (est_final)
    {
        automate->etats_finaux = (int *)realloc(automate->etats_finaux, (automate->nb_etats_finaux + 1) * sizeof(int));
        automate->etats_finaux[automate->nb_etats_finaux] = etat;
        automate->nb_etats_finaux++;
    }
}

// Fonction pour ajouter un symbole e l'automate
void ajouterSymbole(Automate *automate, char symbole)
{
    // Verifier si le symbole existe deja dans l'automate
    if (rechercherSymbole(automate, symbole) != NULL)
    {
        printf("Le symbole '%c' existe deje dans l'automate.\n", symbole);
        return; // Ne pas ajouter le symbole s'il existe deja
    }

    // Ajouter le symbole s'il n'existe pas
    automate->symboles = (Symbole *)realloc(automate->symboles, (automate->nb_symboles + 1) * sizeof(Symbole));
    Symbole nouveau_symbole;
    nouveau_symbole.symbole = symbole;
    automate->symboles[automate->nb_symboles] = nouveau_symbole;
    automate->nb_symboles++;
}

// Fonction pour ajouter une transition e l'automate
void ajouterTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers)
{
    // Verifier si une transition identique existe deja
    if (rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL)
    {
        printf("La transition existe deja dans l'automate.\n");
        return; // Ne pas ajouter la transition si elle existe deja
    }

    // Si la transition est unique, l'ajouter a l'automate
    automate->transitions = (Transition *)realloc(automate->transitions, (automate->nb_transitions + 1) * sizeof(Transition));
    Transition nouvelle_transition;
    nouvelle_transition.etat_depuis = etat_depuis;
    nouvelle_transition.symbole_entree = symbole_entree;
    nouvelle_transition.etat_vers = etat_vers;
    automate->transitions[automate->nb_transitions] = nouvelle_transition;
    automate->nb_transitions++;
}

// Fonction pour verifier si un etat est final
int estEtatFinal(Automate *automate, int etat)
{
    // printf("\n Nbre etat fin : %d",automate->nb_etats_finaux);
    for (int i = 0; i < automate->nb_etats_finaux; i++)
    {
        // printf("\n test fin : %d  X  %d", automate->etats_finaux[i],etat);
        if (automate->etats_finaux[i] == etat)
        {
            // printf("\n AYA BEHY");
            return 1;
        }
    }
    return 0;
}

// Fonction pour effectuer une transition
int effectuerTransition(Automate *automate, int etat_actuel, char symbole_entree)
{
    // printf("\n Nbre transition : %d" , automate->nb_transitions);
    for (int i = 0; i < automate->nb_transitions; i++)
    {
        // printf("\n Transition entre : %d %c \n", etat_actuel, symbole_entree);
        // printf("\n Transition trouve : %d %c %d \n", automate->transitions[i].etat_depuis, automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
        if (automate->transitions[i].etat_depuis == etat_actuel && automate->transitions[i].symbole_entree == symbole_entree)
        {
            // printf("\n Tres bien vers %d",automate->transitions[i].etat_vers);
            return automate->transitions[i].etat_vers;
        }
    }
    return -1; // Pas de transition pour le symbole donne
}

// Fonction pour verifier si un mot est accepte par l'automate
int accepterMot(Automate *automate, const char *mot)
{
    int etat_actuel = automate->etat_initial;
    // printf("\n Etat initial automate : %d", automate->etat_initial);
    // printf("\n mot[0] %c", mot[0]);
    for (int i = 0; mot[i] != '\0'; i++)
    {
        etat_actuel = effectuerTransition(automate, etat_actuel, mot[i]);

        if (etat_actuel == -1)
        {
            // printf("\n WWWWWIIIWWWW");
            return 0; // Rejete si aucune transition possible
        }
    }
    // printf("\n Est final ? %d",estEtatFinal(automate, etat_actuel));
    return estEtatFinal(automate, etat_actuel);
}

Automate initialiserAutomateDepuisFichier(const char *nom_fichier)
{
    Automate automate;
    initialiserAutomate(&automate);

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    char ligne[100];
    char *token = NULL; // Declarez token en dehors de la boucle

    // Lire les etats
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL)
    {
        int etat = atoi(token);
        ajouterEtat(&automate, etat, 0, 0);
        token = strtok(NULL, ",");
    }

    // Lire l'etat initial
    fgets(ligne, sizeof(ligne), fichier);
    int etat_initial = atoi(ligne);
    for (int i = 0; i < automate.nb_etats; i++)
    {
        if (automate.etats[i].etat == etat_initial)
        {
            automate.etats[i].est_initial = 1;
            automate.etat_initial = automate.etats[i].etat;
            break;
        }
    }

    // Lire les etats finaux
    fgets(ligne, sizeof(ligne), fichier);
    token = strtok(ligne, ",");
    while (token != NULL)
    {
        int etat_final = atoi(token);
        for (int i = 0; i < automate.nb_etats; i++)
        {
            if (automate.etats[i].etat == etat_final)
            {
                automate.etats[i].est_final = 1;
                automate.etats_finaux = (int *)realloc(automate.etats_finaux, (automate.nb_etats_finaux + 1) * sizeof(int));
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
    while (token != NULL)
    {
        char symbole = token[0];
        ajouterSymbole(&automate, symbole);
        token = strtok(NULL, ",");
    }

    // Lire les transitions
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        int etat_depuis, etat_vers;
        char symbole_entree;
        sscanf(ligne, "%d,%c,%d", &etat_depuis, &symbole_entree, &etat_vers);
        ajouterTransition(&automate, etat_depuis, symbole_entree, etat_vers);
    }

    fclose(fichier);

    return automate;
}

void creerAutomate(Automate *automate)
{
    int nb_etats, nb_symboles, nb_transitions;
    Etat *existant;
    int aumoinsInitial = 0;

    // Demander le nombre d'etats
    printf("Combien d'etats voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_etats);
    do
    {
        for (int i = 0; i < nb_etats; i++)
        {
            int etat, est_initial, est_final;

            if ((i == nb_etats - 1) && (aumoinsInitial == 0))
            {
                printf("\n C'est le dernier a ajouter. Dans un AEF, il faut toujours avoir au moins un etat initial\n");
            }

            printf("\nChoisissez un etat superieur strictement a 0 : etat > 0");
            do
            {
                // Demander les details de l'etat
                printf("\nEtat %d : ", i + 1);
                scanf("%d", &etat);
                existant = rechercherEtat(automate, etat);
                if (existant != NULL)
                {
                    printf("L'etat %d existe deja dans l'automate.\n", etat);
                }
            } while ((existant != NULL) || (etat < 1));

            // Demander si c'est un etat initial (1) ou non (0)
            do
            {
                printf("Est initial (1 : si oui/ 0 : sinon) : ");
                scanf("%d", &est_initial);
                if (est_initial == 1)
                {
                    aumoinsInitial = 1;
                }
            } while (est_initial != 0 && est_initial != 1);

            // Demander si c'est un etat final (1) ou non (0)
            do
            {
                printf("Est final (1 : si oui/ 0 : sinon) : ");
                scanf("%d", &est_final);
            } while (est_final != 0 && est_final != 1);

            // Ajouter l'etat e l'automate
            if (aumoinsInitial == 1)
            {
                ajouterEtat(automate, etat, est_initial, est_final);
            }
        }
    } while (aumoinsInitial == 0);

    // Demander le nombre de symboles
    printf("Combien de Symboles voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_symboles);

    for (int i = 0; i < nb_symboles; i++)
    {
        char symbole;
        do
        {
            // Demander les details du symbole
            printf("Symbole %d : ", i + 1);
            scanf(" %c", &symbole); // Utilisation d'un espace pour ignorer les espaces ou les sauts de ligne

            if (rechercherSymbole(automate, symbole) != NULL)
            {
                printf("Le symbole '%c' existe deja dans l'automate.\n", symbole);
            }
        } while (rechercherSymbole(automate, symbole) != NULL);

        // Ajouter le symbole e l'automate
        ajouterSymbole(automate, symbole);
    }

    // Demander le nombre de transitions
    printf("Combien de Transitions voulez-vous ajouter a l'automate ? : ");
    scanf("%d", &nb_transitions);

    for (int i = 0; i < nb_transitions; i++)
    {
        int etat_depuis, etat_vers;
        char symbole_entree;

        do
        {
            do
            {
                // Demander les details de la transition
                printf("Transition %d - etat de depart : ", i + 1);
                scanf("%d", &etat_depuis);
                if (rechercherEtat(automate, etat_depuis) == NULL)
                {
                    printf("\nEtat de depart non existant!!! \n");
                }
            } while (rechercherEtat(automate, etat_depuis) == NULL);

            do
            {
                printf("Transition %d - Symbole d'entree : ", i + 1);
                scanf(" %c", &symbole_entree); // Utilisation d'un espace pour ignorer les espaces et les sauts de ligne
                if (rechercherSymbole(automate, symbole_entree) == NULL)
                {
                    printf("\nSymbole non existant!!! \n");
                }
            } while (rechercherSymbole(automate, symbole_entree) == NULL);

            do
            {
                printf("Transition %d - etat d'arrivee : ", i + 1);
                scanf("%d", &etat_vers);
                if (rechercherEtat(automate, etat_vers) == NULL)
                {
                    printf("\nEtat d'arrivee non existant!!! \n");
                }
            } while (rechercherEtat(automate, etat_vers) == NULL);

            if (rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL)
            {
                printf("La transition existe deja dans l'automate.\n");
            }
        } while (rechercherTransition(automate, etat_depuis, symbole_entree, etat_vers) != NULL);

        // Ajouter la transition e l'automate
        ajouterTransition(automate, etat_depuis, symbole_entree, etat_vers);
    }
}

void afficherAutomate(Automate *automate)
{
    printf("Automate :\n");

    printf("etats :\n");
    for (int i = 0; i < automate->nb_etats; i++)
    {
        printf("etat %d - ID : %d, Initial : %d, Final : %d\n", i + 1, automate->etats[i].etat, automate->etats[i].est_initial, automate->etats[i].est_final);
    }

    printf("Symboles :\n");
    for (int i = 0; i < automate->nb_symboles; i++)
    {
        printf("Symbole %d - %c\n", i + 1, automate->symboles[i].symbole);
    }

    printf("Transitions :\n");
    for (int i = 0; i < automate->nb_transitions; i++)
    {
        printf("Transition %d - De : %d, Symbole : %c, Vers : %d\n", i + 1, automate->transitions[i].etat_depuis, automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
    }
}

void supprimerAutomate(Automate *automate)
{
    free(automate->etats);
    free(automate->etats_finaux);
    free(automate->symboles);
    free(automate->transitions);
    initialiserAutomate(automate);
}

Etat *rechercherEtat(Automate *automate, int id)
{
    for (int i = 0; i < automate->nb_etats; i++)
    {
        if (automate->etats[i].etat == id)
        {
            return &(automate->etats[i]); // Retourne un pointeur vers l'etat trouve
        }
    }
    return NULL; // L'etat n'a pas ete trouve
}

Symbole *rechercherSymbole(Automate *automate, char symbole_recherche)
{
    for (int i = 0; i < automate->nb_symboles; i++)
    {
        if (automate->symboles[i].symbole == symbole_recherche)
        {
            return &(automate->symboles[i]);
        }
    }
    return NULL; // Symbole non trouve
}

Transition *rechercherTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers)
{
    for (int i = 0; i < automate->nb_transitions; i++)
    {
        Transition *transition = &automate->transitions[i];
        if (transition->etat_depuis == etat_depuis && transition->symbole_entree == symbole_entree && transition->etat_vers == etat_vers)
        {
            return transition; // Retourner la transition si elle est trouvee
        }
    }
    return NULL; // Retourner NULL si la transition n'est pas trouvee
}

void modifierEtat(Automate *automate)
{
    int id_etat;
    Etat *etat_a_modifier;
    do
    {
        printf("Entrez le numero de l'etat a modifier : ");
        scanf("%d", &id_etat);
        etat_a_modifier = rechercherEtat(automate, id_etat);
        if (etat_a_modifier == NULL)
        {
            printf("L'etat avec le numero %d n'existe pas dans l'automate. Veuillez reessayer.\n", id_etat);
        }
    } while (etat_a_modifier == NULL);

    int choix1;
    char choix2;
    do
    {
        printf("Que voulez-vous faire avec l'etat %d ?\n", id_etat);
        printf("1- Le rendre non final (s'il est final)\n");
        printf("2- Le rendre final (s'il n'est pas final)\n");
        scanf("%d", &choix1);
    } while (choix1 != 1 && choix1 != 2);

    // Modifier l'etat en consequence
    if (choix1 == 1)
    {
        // Le rendre non final
        if (etat_a_modifier->est_final)
        {
            etat_a_modifier->est_final = 0;
            printf("L'etat %d a ete rendu non final.\n", id_etat);
        }
        else
        {
            printf("L'etat %d n'etait pas final, donc il n'a pas ete modifie.\n", id_etat);
        }
    }
    else if (choix1 == 2)
    {
        // Le rendre final
        if (!etat_a_modifier->est_final)
        {
            etat_a_modifier->est_final = 1;
            printf("L'etat %d a ete rendu final.\n", id_etat);
        }
        else
        {
            printf("L'etat %d etait deja final, donc il n'a pas ete modifie.\n", id_etat);
        }
    }

    // Demander à l'utilisateur s'il souhaite sauvegarder
    printf("Voulez-vous sauvegarder les modifications ? (O/N) ");
    scanf(" %c", &choix2);

    if (choix2 == 'O')
    {
        // Appeler la fonction de sauvegarde ici
        sauvegarderAutomate(automate);
        printf("Automate sauvegarde avec succes.\n");
    }
    else
        return;
}

void modifierAutomate(Automate *automate)
{
    int choix;

    printf("Que voulez-vous modifier ?\n");
    printf("1- Modifier les etats\n");
    printf("2- Modifier les transitions\n");

    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        modifierEtat(automate);
        break;
    case 2:
        modifierTransition(automate);
        break;
    default:
        printf("Choix invalide.\n");
    }
}

void lectureFichier(char nom_fichier[])
{
    while (1)
    {
        printf("Entrez le nom du fichier : ");
        scanf("%s", nom_fichier);

        if (access(nom_fichier, F_OK) != -1)
        {
            break; // Sortir de la boucle si le fichier existe
        }
        else
        {
            printf("Le fichier n'existe pas. Veuillez reessayer.\n");
        }
    }
}
void sauvegarderAutomate(Automate *automate)
{
    char nom_fichier[100];
    printf("Entrez le nom du fichier de sauvegarde : ");
    scanf("%s", nom_fichier);

    FILE *fichier = fopen(nom_fichier, "w");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    // Ecrire les Etats de l'automate
    for (int i = 0; i < automate->nb_etats; i++)
    {
        fprintf(fichier, "%d", automate->etats[i].etat);
        if (i < automate->nb_etats - 1)
        {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les Etats initiaux
    int premierInitial = 1;
    for (int i = 0; i < automate->nb_etats; i++)
    {
        if (automate->etats[i].est_initial)
        {
            if (!premierInitial)
            {
                // Si ce n'est pas le premier état initial, ajoutez une virgule avant l'identifiant de l'état
                fprintf(fichier, ",");
            }
            fprintf(fichier, "%d", automate->etats[i].etat);
            premierInitial = 0;
        }
    }
    fprintf(fichier, "\n");
    int premierFinal = 1;
    // Ecrire les Etats finaux
    for (int i = 0; i < automate->nb_etats; i++)
    {
        if (automate->etats[i].est_final)
        {
            if (!premierFinal)
            {
                // Si ce n'est pas le premier état initial, ajoutez une virgule avant l'identifiant de l'état
                fprintf(fichier, ",");
            }
            fprintf(fichier, "%d", automate->etats[i].etat);
            premierFinal = 0;
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les symboles
    for (int i = 0; i < automate->nb_symboles; i++)
    {
        fprintf(fichier, "%c", automate->transitions[i].symbole_entree);
        if (i < automate->nb_symboles - 1)
        {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les transitions
    for (int i = 0; i < automate->nb_transitions; i++)
    {
        fprintf(fichier, "%d,%c,%d\n", automate->transitions[i].etat_depuis,
                automate->transitions[i].symbole_entree, automate->transitions[i].etat_vers);
    }

    fclose(fichier);
}

// Fonction pour vérifier si un automate est complet
bool estAutomateComplet(Automate *automate)
{
    // Vérifier chaque état
    for (int i = 0; i < automate->nb_etats; i++)
    {
        // Vérifier chaque symbole
        for (int j = 0; j < automate->nb_symboles; j++)
        {
            // Recherche d'une transition pour l'état actuel et le symbole actuel
            bool transitionTrouvee = false;
            for (int k = 0; k < automate->nb_transitions; k++)
            {
                if (automate->transitions[k].etat_depuis == automate->etats[i].etat &&
                    automate->transitions[k].symbole_entree == automate->symboles[j].symbole)
                {
                    transitionTrouvee = true;
                    break;
                }
            }

            // Si aucune transition n'est trouvée, l'automate n'est pas complet
            if (!transitionTrouvee)
            {
                return false;
            }
        }
    }

    // Si toutes les transitions nécessaires sont trouvées, l'automate est complet
    return true;
}

void rendreAutomateComplet(Automate *automate)
{

    if (estAutomateComplet(automate))
    {
        printf("\nL'automate est deja complet");
    }

    else
    {
        ajouterEtat(automate, 0, 0, 0);
        for (int m = 0; m < automate->nb_symboles; m++)
        {
            ajouterTransition(automate, 0, automate->symboles[m].symbole, 0);
        }
        // Vérifier chaque état
        for (int i = 0; i < automate->nb_etats; i++)
        {
            // Vérifier chaque symbole
            for (int j = 0; j < automate->nb_symboles; j++)
            {
                // Recherche d'une transition pour l'état actuel et le symbole actuel
                bool transitionTrouvee = false;
                for (int k = 0; k < automate->nb_transitions; k++)
                {
                    if (automate->transitions[k].etat_depuis == automate->etats[i].etat &&
                        automate->transitions[k].symbole_entree == automate->symboles[j].symbole)
                    {
                        transitionTrouvee = true;
                        break;
                    }
                }
                if (!transitionTrouvee)
                {
                    ajouterTransition(automate, automate->etats[i].etat, automate->symboles[j].symbole, 0);
                }
            }
        }
    }
}

// Fonction pour vérifier si un automate est déterministe
bool estAutomateDeterministe(Automate *automate)
{
    // Pour chaque état
    for (int i = 0; i < automate->nb_etats; i++)
    {
        // Pour chaque symbole de l'alphabet
        for (int j = 0; j < automate->nb_symboles; j++)
        {
            // Compter le nombre de transitions possibles
            int nombreTransitions = 0;

            // Recherche d'une transition pour l'état actuel et le symbole actuel
            for (int k = 0; k < automate->nb_transitions; k++)
            {
                if (automate->transitions[k].etat_depuis == automate->etats[i].etat &&
                    automate->transitions[k].symbole_entree == automate->symboles[j].symbole)
                {
                    nombreTransitions++;
                }
            }

            // Si plus d'une transition est trouvée, l'automate n'est pas déterministe
            if (nombreTransitions > 1)
            {
                return false;
            }
        }
    }

    // Si aucune violation n'est trouvée, l'automate est déterministe
    return true;
}

void supprimerTransition(Automate *automate, int etat_depuis, char symbole_entree, int etat_vers)
{
    // Recherche de la transition à supprimer
    int indexTransition = -1;
    for (int i = 0; i < automate->nb_transitions; i++)
    {
        if (automate->transitions[i].etat_depuis == etat_depuis &&
            automate->transitions[i].symbole_entree == symbole_entree &&
            automate->transitions[i].etat_vers == etat_vers)
        {
            indexTransition = i;
            break;
        }
    }

    // Si la transition a été trouvée, supprimer-la
    if (indexTransition != -1)
    {
        // Décalage des transitions après la transition à supprimer
        for (int i = indexTransition; i < automate->nb_transitions - 1; i++)
        {
            automate->transitions[i] = automate->transitions[i + 1];
        }

        // Réduction de la taille de la mémoire allouée
        automate->transitions = realloc(automate->transitions, (automate->nb_transitions - 1) * sizeof(Transition));
        automate->nb_transitions--;
    }
}

void rendreAutomateDeterministe(Automate *automate)
{

    if (estAutomateDeterministe(automate))
    {
        printf("\nL'automate est deja deterministe");
    }
    else
    {
        for (int i = 0; i < automate->nb_etats; i++)
        {
            // Pour chaque symbole de l'alphabet
            for (int j = 0; j < automate->nb_symboles; j++)
            {
                // Compter le nombre de transitions possibles
                int nombreTransitions = 0;

                // Recherche d'une transition pour l'état actuel et le symbole actuel
                for (int k = 0; k < automate->nb_transitions; k++)
                {
                    if (automate->transitions[k].etat_depuis == automate->etats[i].etat &&
                        automate->transitions[k].symbole_entree == automate->symboles[j].symbole)
                    {
                        nombreTransitions++;
                        if (nombreTransitions > 1)
                        {
                            supprimerTransition(automate, automate->transitions[k].etat_depuis, automate->transitions[k].symbole_entree, automate->transitions[k].etat_vers);
                            nombreTransitions--;
                        }
                    }
                }
            }
        }
    }
}
// char* mon_strdup(const char* s) {
//     if (s == NULL) {
//         return NULL;
//     }

//     // Allouer de la mémoire pour la nouvelle chaîne
//     char* copie = malloc(strlen(s) + 1); // +1 pour le caractère nul
//     if (copie == NULL) {
//         return NULL; // Échec d'allocation de mémoire
//     }

//     // Copier la chaîne dans la nouvelle mémoire
//     strcpy(copie, s);
//     return copie;
// }

// char* construireExpression(Automate *automate) {
//     if (automate->etats[automate->etat_courant].est_final) {

//         return mon_strdup(automate->expression_actuelle); // Retourner l'expression actuelle si l'état est final
//     }

//     char* expression_complete = mon_strdup(""); // Initialiser une expression vide
//     if (expression_complete == NULL) return NULL;

//     for (int i = 0; i < automate->nb_transitions; ++i) {
//         if (automate->transitions[i].etat_depuis == automate->etat_courant) {
//             char symbole[2] = {automate->symboles[i].symbole, '\0'};

//             // Création de la nouvelle expression avec le symbole ajouté
//             char* nouvelle_expr = (char*)malloc(strlen(automate->expression_actuelle) + strlen(symbole) + 1);
//             if (nouvelle_expr == NULL) {
//                 free(expression_complete);
//                 return NULL;
//             }
//             strcpy(nouvelle_expr, automate->expression_actuelle);
//             strcat(nouvelle_expr, symbole);

//             int temp_etat_courant = automate->etat_courant;
//             automate->expression_actuelle = nouvelle_expr;
//             automate->etat_courant = automate->transitions[i].etat_vers;

//             char* expression_partielle = construireExpression(automate);
//             automate->etat_courant = temp_etat_courant;
//             free(nouvelle_expr);

//             if (expression_partielle != NULL) {
//                 // Concaténation de l'expression partielle à l'expression complète
//                 char* temp = expression_complete;
//                 expression_complete = (char*)malloc(strlen(temp) + strlen(expression_partielle) + 1);
//                 if (expression_complete == NULL) {
//                     free(temp);
//                     free(expression_partielle);
//                     return NULL;
//                 }
//                 strcpy(expression_complete, temp);
//                 strcat(expression_complete, expression_partielle);

//                 free(temp);
//                 free(expression_partielle);
//             }

//             if (expression_complete == NULL) return NULL;
//         }
//     }
//     return expression_complete;
// }

// char* extraireExpressionsRegulieres(Automate* automate) {
//     char* expression = mon_strdup(""); // Initialiser l'expression globale
//     if (expression == NULL) return NULL;

//     for (int i = 0; i < automate->nb_etats; ++i) {
//         if (automate->etats[i].est_initial) {
//             automate->etat_courant = i; // Utiliser l'état initial actuel
//             char* expression_partielle = construireExpression(automate);

//             // Concaténation de l'expression partielle à l'expression globale
//             if (expression_partielle != NULL) {
//                 char* temp = expression;
//                 expression = (char*)malloc(strlen(temp) + strlen(expression_partielle) + 1);
//                 if (expression == NULL) {
//                     free(temp);
//                     free(expression_partielle);
//                     return NULL;
//                 }
//                 strcpy(expression, temp);
//                 strcat(expression, expression_partielle);

//                 free(temp);
//                 free(expression_partielle);
//             }
//         }
//     }
//     return expression;
// }

void completerAutomate(Automate *automate)
{
    for (int i = 0; i < automate->nb_etats; ++i)
    {
        automate->etats[i].est_final = !automate->etats[i].est_final; // Inverse l'état final
    }
}

void miroirAutomate(Automate *automate)
{
    // Echanger les etats initiaux et finaux
    for (int i = 0; i < automate->nb_etats; ++i)
    {
        bool temp = automate->etats[i].est_initial;
        automate->etats[i].est_initial = automate->etats[i].est_final;
        automate->etats[i].est_final = temp;
    }
    // Inverser les directions des transitions
    for (int i = 0; i < automate->nb_transitions; ++i)
    {
        int temp = automate->transitions[i].etat_depuis;
        automate->transitions[i].etat_depuis = automate->transitions[i].etat_vers;
        automate->transitions[i].etat_vers = temp;
    }
}

void produitAutomates(Automate *automateA, Automate *automateB)
{

    char nom_fichier[100];
    printf("Entrez le nom du fichier de sauvegarde : ");
    scanf("%s", nom_fichier);

    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    // Ecrire les Etats de l'automate
    for (int i = 0; i < automateA->nb_etats; ++i)
    {
        for (int j = 0; j < automateB->nb_etats; ++j)
        {

            {
                fprintf(fichier, "(%d,%d)", automateA->etats[i].etat, automateB->etats[j].etat);
                if (i < automateA->nb_etats - 1 && j < automateB->nb_etats - 1)
                {
                    fprintf(fichier, ",");
                }
            }
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les Etats initiaux
    for (int i = 0; i < automateA->nb_etats; ++i)
    {
        for (int j = 0; j < automateB->nb_etats; ++j)
        {
            if (automateA->etats[i].est_initial && automateB->etats[j].est_initial)
            {
                fprintf(fichier, "(%d,%d)", automateA->etats[i].etat, automateB->etats[j].etat);
                if (i < automateA->nb_etats - 1 && j < automateB->nb_etats - 1)
                {
                    fprintf(fichier, ",");
                }
            }
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les Etats finaux
    for (int i = 0; i < automateA->nb_etats; ++i)
    {
        for (int j = 0; j < automateB->nb_etats; ++j)
        {
            if (automateA->etats[i].est_final && automateB->etats[j].est_final)
            {
                fprintf(fichier, "(%d,%d)", automateA->etats[i].etat, automateB->etats[j].etat);
                if (i < automateA->nb_etats - 1 && j < automateB->nb_etats - 1)
                {
                    fprintf(fichier, ",");
                }
            }
        }
    }
    fprintf(fichier, "\n");

    // Ecrire les transitions
    for (int i = 0; i < automateA->nb_transitions; i++)
    {
        for (int j = 0; j < automateB->nb_transitions; j++)
        {
            if (automateA->transitions[i].symbole_entree == automateB->transitions[j].symbole_entree)
            {
                fprintf(fichier, "(%d,%d),%c,(%d,%d)\n",
                        automateA->transitions[i].etat_depuis,
                        automateB->transitions[j].etat_depuis,
                        automateA->transitions[i].symbole_entree,
                        automateA->transitions[i].etat_vers,
                        automateB->transitions[j].etat_vers);
            }
        }
    }

    fclose(fichier);
}
void concatenerAutomates(Automate *automateA, Automate *automateB, Automate *automateC)
{
    // Copier les états et les transitions de l'automate A
    for (int i = 0; i < automateA->nb_etats; ++i)
    {
        ajouterEtat(automateC, automateA->etats[i].etat, automateA->etats[i].est_initial, 0); // Les états finaux de A ne sont pas finaux dans le nouvel automate
    }
    for (int i = 0; i < automateA->nb_transitions; ++i)
    {
        ajouterTransition(automateC, automateA->transitions[i].etat_depuis, automateA->transitions[i].symbole_entree, automateA->transitions[i].etat_vers);
    }


    for (int i = 0; i < automateB->nb_etats; ++i)
    {
        ajouterEtat(automateC, automateB->etats[i].etat, 0, automateB->etats[i].est_final); // Seuls les états finaux de B sont finaux dans le nouvel automate

    }
    for (int i = 0; i < automateB->nb_transitions; ++i)
    {
        ajouterTransition(automateC, automateB->transitions[i].etat_depuis, automateB->transitions[i].symbole_entree, automateB->transitions[i].etat_vers );
    }

    // Ajouter des transitions epsilon des états finaux de A vers l'état initial de B
    for (int i = 0; i < automateA->nb_etats; ++i)
    {
        if (automateA->etats[i].est_final)
        {
            ajouterTransition(automateC, automateA->etats[i].etat, 'ɛ', automateB->etat_initial); // EPSILON représente la transition epsilon
        }
    }
}
// Fonction pour libérer la mémoire allouée pour l'automate
void freeAutomate(Automate *automate)
{
    free(automate->etats);
    free(automate->etats_finaux);
    free(automate->symboles);
    free(automate->transitions);
}