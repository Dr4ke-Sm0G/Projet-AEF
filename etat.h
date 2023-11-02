#ifndef ETAT_H_INCLUDED
#define ETAT_H_INCLUDED

typedef struct {
    int etat;
    int est_initial;
    int est_final;
} Etat;

void initialiserEtat(Etat *etat, int id, int est_initial, int est_final);


#endif // ETAT_H_INCLUDED
