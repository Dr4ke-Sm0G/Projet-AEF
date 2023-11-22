#ifndef TABAUTOMATES_H_INCLUDED
#define TABAUTOMATES_H_INCLUDED

// Structure pour représenter un tableau d'automates
typedef struct {
    Automate *automates;
    int nb_automates;
} TableauAutomates;

void ajouterAutomate(TableauAutomates *tableau, Automate automate);
void supprimerAutomate(TableauAutomates *tableau, int index);

#endif // TABAUTOMATES_H_INCLUDED
