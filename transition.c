#include "transition.h"

void initialiserTransition(Transition *transition, int depuis, char symbole, int vers) {
    transition->etat_depuis = depuis;
    transition->symbole_entree = symbole;
    transition->etat_vers = vers;
}