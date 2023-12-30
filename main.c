#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h> // Pour la fonction GetFileAttributes
#include "automate.h"

int main()
{
    int choice;
    char nom_fichier[100];
    char mot[100];
    Automate automate;

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
                break;
            case 2:
                
                    lectureFichier(nom_fichier);
                    initialiserAutomate(&automate);
                    
                    automate = initialiserAutomateDepuisFichier(nom_fichier);
                    /*
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
                    printf("Voulez-vous continuer ? (Oui/Non) : ");
                    char reponse[10];
                    scanf("%s", reponse);
                    if (strcmp(reponse, "Non") == 0 || strcmp(reponse, "non") == 0)
                    {
                        break;
                    }*/

             
                break;
            case 3:
                modifierAutomate(&automate);
                break;
            case 4:
                sauvegarderAutomate(&automate);
                break;
            case 5:
                supprimerAutomate(&automate);
                break;
            case 6:
                printf("Au revoir !\n");
                return 0;
            case 7:
                break;
            case 8:
                afficherAutomate(&automate);
                break;
            default:
                printf("Choix invalide. Veuillez choisir un nombre valide.\n");
                break;
            }
            break;

        case 2:
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
        case 12:
            printf("appel-OK\n");
            rendreAutomateMinimal(&automate);
        default:
            printf("Choix invalide. Veuillez choisir un nombre valide.\n");
            break;
        }
    }

    return 0;
}