#include "etat.h"

void initialiserEtat(Etat *etat, int id, int est_initial, int est_final) {
    etat->etat = id;
    etat->est_initial = est_initial;
    etat->est_final = est_final;
}
