void ajouterAutomate(TableauAutomates *tableau, Automate automate) {
    tableau->nb_automates++;
    tableau->automates = realloc(tableau->automates, tableau->nb_automates * sizeof(Automate));
    tableau->automates[tableau->nb_automates - 1] = automate;
}

void supprimerAutomate(TableauAutomates *tableau, int index) {
    if (index < 0 || index >= tableau->nb_automates) {
        printf("Indice d'automate invalide.\n");
        return;
    }

    // Lib�rer la m�moire de l'automate � supprimer
    libererAutomate(&tableau->automates[index]);

    // D�calage des automates apr�s l'automate � supprimer
    for (int i = index; i < tableau->nb_automates - 1; i++) {
        tableau->automates[i] = tableau->automates[i + 1];
    }

    // R�duction de la taille de la m�moire allou�e
    tableau->nb_automates--;
    tableau->automates = realloc(tableau->automates, tableau->nb_automates * sizeof(Automate));
}
