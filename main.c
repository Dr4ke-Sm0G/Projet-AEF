#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>  // Pour la fonction GetFileAttributes

#include "automate.h"

int main() {
    int choice;
    char nom_fichier[100];  // Un tableau pour stocker le nom du fichier

    Automate automate;

    while (1) {
        menu();

        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        if (choice == 0) {
            break; // Quitter la boucle si l'utilisateur choisit 0
        }

        switch (choice) {
            case 1:
                initialiserAutomate(&automate);
                creerAutomate(&automate);
                break;
            case 2:
                afficherAutomate(&automate);
                break;
            case 3:
                modifierAutomate(&automate);
                break;
            case 4:
                supprimerAutomate(&automate);
                break;
            case 5:
                while (1) {
                    lectureFichier(nom_fichier);

                    initialiserAutomate(&automate);

                    automate = initialiserAutomateDepuisFichier(nom_fichier);


                    // Test de l'automate avec un mot
                    char mot[100];
                    printf("\n Entrez un mot : ");
                    scanf("%s", mot);

                    if (accepterMot(&automate, mot) == 1) {
                        printf("\n Le mot est accepté.\n");
                    } else {
                        printf("\n Le mot est rejeté.\n");
                    }

                    printf("Voulez-vous continuer ? (Oui/Non) : ");
                    char reponse[10];
                    scanf("%s", reponse);
                    if (strcmp(reponse, "Non") == 0 || strcmp(reponse, "non") == 0) {
                        break;  // Sortir de la boucle si l'utilisateur veut arrêter
                    }
                }
                break;
            case 6:
                // Code pour l'option 6
                break;
            case 7:
                // Code pour l'option 7
                break;
            case 8:
                // Code pour l'option 8
                break;
            case 9:
                // Code pour l'option 9
                break;
            case 10:
                // Code pour l'option 10
                break;
            case 11:
                // Code pour l'option 11
                break;
            case 12:
                // Code pour l'option 12
                break;
            default:
                printf("Choix non valide\n");
        }
    }

    return 0;
}
