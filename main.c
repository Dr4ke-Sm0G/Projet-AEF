
#include "main.h"

int main()

{
    struct Automate monAEF;
    int choice;
    while (1)
    {
        printf("------------------------------------\n\n");
        printf("Projet Automates d'etats Finis (AEF)\n\n");
        printf("------------------------------------\n\n");
        printf("Que voulez-vous faire ? \n");
        printf("1- Manipuler un AEF\n");
        printf("2- Verifier si un mot est reconnu par un AEF\n");
        printf("3- Verifier si un automate est complet\n");
        printf("4- Rendre un automate complet\n");
        printf("5- Verifier si un automate est deterministe\n");
        printf("6- Rendre un AEF deterministe\n");
        printf("7- Realiser des operations (Complement d'un AEF,Miroir d'un AEF,... )\n");
        printf("8- Extraire une expression reguliere a partir un automate donne\n");
        printf("9- Trouver le langage reconnu par un automate donne\n");
        printf("10- Verifier si deux automates sont equivalents\n");
        printf("11- Rendre un automate emonde\n");
        printf("12- Rendre un automate minimal\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Vous avez choisi de manipuler un AEF.\n");
            printf("Menu :\n");
            printf("1. Saisir un AEF\n");
            printf("2. Importer un AEF a partir d'un fichier\n");
            printf("3. Modifier un AEF\n");
            printf("4. Sauvegarder un AEF dans un fichier\n");
            printf("5. Supprimer un AEF\n");
            printf("6. Quitter\n");
            printf("Choisissez une option : ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                saisirAEF(&monAEF);
                break;
            case 2:
                importerAEF(&monAEF, "Fichier.txt");
                break;
            case 3:
                modifierAEF(&monAEF);
                break;
            case 4:
                sauvegarderAEF(&monAEF, "Fichier.txt");
                break;
            case 5:
                supprimerAEF(&monAEF);
                break;
            case 6:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez choisir un nombre valide.\n");
            }
        }
    }
    // Libérez la mémoire 
   // free(monAEF.etats);
    //free(monAEF.transitions);
}
