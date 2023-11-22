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

    // Libérer la mémoire de l'automate à supprimer
    libererAutomate(&tableau->automates[index]);

    // Décalage des automates après l'automate à supprimer
    for (int i = index; i < tableau->nb_automates - 1; i++) {
        tableau->automates[i] = tableau->automates[i + 1];
    }

    // Réduction de la taille de la mémoire allouée
    tableau->nb_automates--;
    tableau->automates = realloc(tableau->automates, tableau->nb_automates * sizeof(Automate));
}
