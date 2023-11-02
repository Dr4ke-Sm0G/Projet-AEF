#include <stdio.h>
#include <stdlib.h>
#define MAX_ETATS 50
// Structure pour représenter un état dans l'AEF
struct Etat
{
    int numero;   // nom de l'état
    int estFinal; // 1 si c'est un état final, 0 sinon
};

// Structure pour représenter une transition dans l'AEF
struct Transition
{
    char etatSource[10];
    char symbole;
    char etatDestination[10];
};

// Structure pour représenter l'AEF
struct Automate
{
    int nbEtats;
    int nbTransitions; // changer ça par symbole, il faut ajouter l'id d'automate
    struct Etat *etats;
    struct Transition *transitions;
    char etatInitial[10];
};

// Fonction pour saisir un AEF
void saisirAEF(struct Automate *aef)
{
    char nomAutomate[50];
    char choix;
    printf("Saisie d'un Automate d'Etats Finis (AEF)\n");
    // Saisie du nombre d'états
    printf("Nombre d'etats : ");
    scanf("%d", &aef->nbEtats);

    // Saisie de l'état initial
    printf("Etat initial : ");
    scanf("%s", &aef->etatInitial);

    // Allouer de la mémoire pour les états
    aef->etats = (struct Etat *)malloc(aef->nbEtats * sizeof(struct Etat));

    // Saisie des détails des états
    for (int i = 0; i < aef->nbEtats; i++)
    {
        printf("Etat %d (Tapez 1 pour etat final, 0 sinon) : ", i);
        scanf("%d", &aef->etats[i].estFinal);
        aef->etats[i].numero = i;
    }
    // Saisie du nombre de transitions
    printf("Nombre de transitions : ");
    scanf("%d", &aef->nbTransitions);

    // Allouer de la mémoire pour les transitions
    aef->transitions = (struct Transition *)malloc(aef->nbTransitions * sizeof(struct Transition));

    // Saisie des détails des transitions
    for (int i = 0; i < aef->nbTransitions; i++)
    {
        printf("Transition %d (etat source, symbole, etat destination) : ", i);
        scanf("%s %c %s", &aef->transitions[i].etatSource, &aef->transitions[i].symbole, &aef->transitions[i].etatDestination);
    }
    printf("Voulez-vous sauvegarder cet automate ? (O/N)");
    scanf("%s", &choix);
    if (choix == 'O')
    {
        printf("Entrez le nom de l'automate : ");
        scanf("%s", &nomAutomate);
        FILE *fichier = fopen(nomAutomate, "w"); // Ouvrir le fichier en mode écriture

        if (fichier == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
            return;
        }
        // Écrire les informations de l'AEF dans le fichier

        fprintf(fichier, "%d\n", aef->nbEtats);
        fprintf(fichier, "%s\n", aef->etatInitial);
        for (int i = 0; i < aef->nbEtats; i++)
        {
            fprintf(fichier, "q%d%d\n", aef->etats[i].numero, aef->etats[i].estFinal);
        }

        fprintf(fichier, "%d\n", aef->nbTransitions);
        for (int i = 0; i < aef->nbTransitions; i++)
        {
            fprintf(fichier, "%d,%s,%c,%s\n",
                    i, aef->transitions[i].etatSource, aef->transitions[i].symbole, aef->transitions[i].etatDestination);
        }

        fclose(fichier); // Fermer le fichier après avoir écrit les données
    }
    else
    {
        return;
    }
}

// Fonction pour importer un AEF à partir d'un fichier
void importerAEF(struct Automate *aef, const char *nomFichier)
{
    // Implémentez la logique d'importation depuis le fichier ici
}
void modifierAEF(struct Automate *aef, const char *nomAutomate)
{
    int choix;
    struct Etat nouvelEtat;

    while (1)
    {
        printf("Que voulez-vous changer ?\n");
        printf("1- Etats\n");
        printf("2- Transitions\n");
        printf("3- Quitter la modification\n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("1- Ajouter un état\n");
            printf("2- Supprimer un état\n");
            printf("3- Retour au menu précédent\n");
            scanf("%d", &choix);

            switch (choix)
            {
            case 1:
                printf("Entrez le numéro de l'état : ");
                scanf("%d", &nouvelEtat.numero);
                printf("Tapez 1 pour état final, 0 sinon : ");
                scanf("%d", &nouvelEtat.estFinal);

                // Incrémentez le nombre total d'états
                aef->nbEtats++;

                printf("L'état a été ajouté avec succès.\n");

                // Ouvrez le fichier de l'automate en mode écriture
                FILE *fichier = fopen(nomAutomate, "w");

                if (fichier == NULL)
                {
                    printf("Erreur lors de l'ouverture du fichier pour la mise à jour.\n");
                    return;
                }

                // Écrivez les informations de l'AEF dans le fichier
                fprintf(fichier, "%d\n", aef->nbEtats);
                fprintf(fichier, "%s\n", aef->etatInitial);
                for (int i = 0; i < aef->nbEtats; i++)
                {
                    fprintf(fichier, "q%d%d\n", aef->etats[i].numero, aef->etats[i].estFinal);
                }

                fprintf(fichier, "%d\n", aef->nbTransitions);
                for (int i = 0; i < aef->nbTransitions; i++)
                {
                    fprintf(fichier, "%s,%c,%s\n",
                            aef->transitions[i].etatSource, aef->transitions[i].symbole, aef->transitions[i].etatDestination);
                }

                fclose(fichier); // Fermer le fichier après avoir écrit les données
                break;

            case 2:
                // Implémentez la logique pour ajouter, supprimer ou modifier des transitions
                break;

            case 3:
                // Quittez la modification
                return;

            default:
                printf("Choix invalide.\n");
            }
        }
    }
}


// Fonction pour supprimer un AEF

void supprimerAEF(struct Automate *aef)
{

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
