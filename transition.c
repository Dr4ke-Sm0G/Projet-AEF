// #include "transition.h"
#include "automate.h"

void initialiserTransition(Transition *transition, int depuis, char symbole, int vers)
{
    transition->etat_depuis = depuis;
    transition->symbole_entree = symbole;
    transition->etat_vers = vers;
}
void modifierTransition(Automate *automate)
{
    int etat_depart, etat_arrivee;
    char symbole_entree;
    Transition *transition_a_modifier;
    int choix;

    printf("Menu de modification de transition :\n");
    printf("1. Modifier une transition\n");
    printf("2. Ajouter une nouvelle transition\n");
    printf("0. Quitter\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        do
        {
            printf("Entrez l'etat de depart de la transition a modifier : ");
            scanf("%d", &etat_depart);
            printf("Entrez le symbole d'entree de la transition a modifier : ");
            scanf(" %c", &symbole_entree);
            printf("Entrez l'etat d'arrivee de la transition a modifier : ");
            scanf("%d", &etat_arrivee);

            transition_a_modifier = rechercherTransition(automate, etat_depart, symbole_entree, etat_arrivee);

            if (transition_a_modifier == NULL)
            {
                printf("La transition n'a pas ete trouvee dans l'automate. Veuillez reessayer.\n");
            }
        } while (transition_a_modifier == NULL);
        do
        {
            printf("\nQue voulez-vous faire avec la transition (depart : %d, symbole : %c, arrivee : %d) ?\n", etat_depart, symbole_entree, etat_arrivee);
            printf("1- Modifier l'etat de depart\n");
            printf("2- Modifier le symbole d'entree\n");
            printf("3- Modifier l'etat d'arrivee\n");
            printf("4- Supprimer la transition\n");
            printf("5- Quitter\n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix);
        } while (choix < 1 || choix > 5);
        switch (choix)
        {
        case 1:
            printf("Entrez le nouvel etat de depart : ");
            scanf("%d", &transition_a_modifier->etat_depuis);
            break;
        case 2:
            printf("Entrez le nouveau symbole d'entree : ");
            scanf(" %c", &transition_a_modifier->symbole_entree);
            break;
        case 3:
            printf("Entrez le nouvel etat d'arrivee : ");
            scanf("%d", &transition_a_modifier->etat_vers);
            break;
        case 4:
            // Supprimer la transition en la remplacant par la derniere transition de l'automate
            *transition_a_modifier = automate->transitions[automate->nb_transitions - 1];
            automate->nb_transitions--;
            printf("La transition a ete supprimee.\n");
            break;
        case 5:
            break;
        default :
            break;
        }
        break;

    case 2: {
            // Ajouter une nouvelle transition
            int etat_depuis, etat_vers;
            char symbole_entree;

            printf("Entrez l'etat de depart de la nouvelle transition : ");
            scanf("%d", &etat_depuis);
            printf("Entrez le symbole d'entree de la nouvelle transition : ");
            scanf(" %c", &symbole_entree);
            printf("Entrez l'etat d'arrivee de la nouvelle transition : ");
            scanf("%d", &etat_vers);

            ajouterTransition(automate, etat_depuis, symbole_entree, etat_vers);
            printf("Nouvelle transition ajoutee avec succes.\n");
            break;
        }
        case 0:
            break;
        default:
            printf("Choix invalide. Veuillez choisir une option valide.\n");
            break;
    }
     // Demander a l'utilisateur s'il souhaite sauvegarder
    printf("Voulez-vous sauvegarder les modifications ? (O/N) ");
    scanf(" %c", &choix);

    if (choix == 'O') {
        // Appeler la fonction de sauvegarde ici
        sauvegarderAutomate(automate);
        printf("Automate sauvegarde avec succes.\n");
    }
    else return;
}