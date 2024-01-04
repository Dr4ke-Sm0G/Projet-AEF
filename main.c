#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h> // Pour la fonction GetFileAttributes
#include "automate.h"
#include "tabAutomates.h"

int main()
{
    char nomFichierA[100], nomFichierB[100];
    Automate automateA, automateB, produit;
    TableauAutomates tableau;
    int choice;
    char nom_fichier[100];
    char mot[100];
    Automate automate;
    TableauAutomates tab;
    initialiserTableauAutomates(&tab);
    int id;
    char *expression;

    while (1)
    {
        menuPrincipal();
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            menuManipuler();
            printf("Choisissez une option : ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                initialiserAutomate(&automate);
                creerAutomate(&automate);
                ajouterAutomateTab(&tab, automate);

                break;
            case 2:
                lectureFichier(nom_fichier);
                initialiserAutomate(&automate);
                automate = initialiserAutomateDepuisFichier(nom_fichier);
                ajouterAutomateTab(&tab, automate);
                break;
            case 3:
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                modifierAutomate(&automate);
                break;
            case 4:
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                sauvegarderAutomate(&automate);
                break;
            case 5:
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                supprimerAutomate(&automate);
                break;
            case 6:
                printf("Au revoir !\n");
                return 0;

            case 8:
                printf("\n -- Affichage Automate -- \n");
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                afficherAutomate(&automate);
                break;
            default:
                printf("Choix invalide. Veuillez choisir un nombre valide.\n");
                break;
            }
            break;

        case 2:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate ");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            printf("\n -- Verification d'un mot --\n");
            printf("\n Entrez un mot : ");
            scanf("%s", mot);
            if (accepterMot(&automate, mot) == 1)
            {
                printf("\n Le mot est accepte.\n");
            }
            else
            {
                printf("\n Le mot est rejete.\n");
            }
            break;
        
        case 3:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate ");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            printf("\n -- Verification si l'automate est complet --\n");
            if (estAutomateComplet(&automate))
            {
                printf("L'automate est complet.\n");
            }
            else
            {
                printf("L'automate n'est pas complet.\n");
            }
            break;

        case 4:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate ");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            afficherAutomate(&automate);
            printf("\n -- Rendre l'automate complet --\n");
            printf("\n--------------------\n");
            rendreAutomateComplet(&automate);
            remplacerAutomate(&tab, id - 1, automate);
            printf("L'automate est complet.\n");
            break;

        case 5:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate ");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            printf("\n -- Verification si l'automate est deterministe --\n");
            if (estAutomateDeterministe(&automate))
            {
                printf("L'automate est deterministe.\n");
            }
            else
            {
                printf("L'automate n'est pas deterministe.\n");
            }
            break;

        case 6:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate ");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            printf("\n -- Rendre l'automate deterministe --\n");
            rendreAutomateDeterministe(&automate);
            remplacerAutomate(&tab, id - 1, automate);
            break;
        case 7:

            menuOperations();
            printf("Entrez votre choix : ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 0:
                return 0;
            case 1:
                printf("\n -- Choix de l'automate --\n");
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                completerAutomate(&automate);
                printf("Voulez-vous sauvegarder l'automate complemente ? (O/N) : ");
                char reponse[5];
                scanf("%s", reponse);
                if (strcmp(reponse, "O") == 0)
                {
                    sauvegarderAutomate(&automate);
                }
                break;

            case 2:
                printf("\n -- Choix de l'automate --\n");
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automate ");
                scanf("%d", &id);
                automate = rechercherAutomate(&tab, id);
                miroirAutomate(&automate);
                printf("Voulez-vous sauvegarder l'automate complemente ? (O/N) : ");
                scanf("%s", reponse);
                if (strcmp(reponse, "O") == 0)
                {
                    sauvegarderAutomate(&automate);
                }
                break;
            case 3:

                // Demande des noms de fichiers pour les automates A et B
                printf("\n -- Choix de l'automate --\n");
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automateA ");
                scanf("%d", &id);
                automateA = rechercherAutomate(&tab, id);
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automateB ");
                scanf("%d", &id);
                automateB = rechercherAutomate(&tab, id);
                // Créer le produit des automates A et B
                produitAutomates(&automateA, &automateB, &produit);
                printf("Voulez-vous sauvegarder l'automate complemente ? (O/N) : ");

                scanf("%s", reponse);
                if (strcmp(reponse, "O") == 0)
                {
                    sauvegarderAutomate(&produit);
                }
                break;

            case 4:
                printf("\n -- Choix de l'automate --\n");
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automateA ");
                scanf("%d", &id);
                automateA = rechercherAutomate(&tab, id);
                afficherNbrAutomate(&tab);
                printf("\n Donner le numero de l'automateB ");
                scanf("%d", &id);
                automateB = rechercherAutomate(&tab, id);
                initialiserAutomate(&produit);
                // Créer le produit des automates A et B
                concatenerAutomates(&automateA, &automateB, &produit);
                printf("Voulez-vous sauvegarder l'automate complemente ? (O/N) : ");

                scanf("%s", reponse);
                if (strcmp(reponse, "O") == 0)
                {
                    sauvegarderAutomate(&produit);
                }
                break;
            }

            break;
        default:
            printf("Choix invalide. Veuillez choisir un nombre valide.\n");
            break;
        case 8:
            printf("\n -- Choix de l'automate --\n");
            afficherNbrAutomate(&tab);
            printf("\n Donner le numero de l'automate");
            scanf("%d", &id);
            automate = rechercherAutomate(&tab, id);
            extraireExpressionReguliere(&automate);
            break;
        case 12:
            printf("appel-OK\n");
            rendreAutomateMinimal(&automate);
        }
    }

    return 0;
}
