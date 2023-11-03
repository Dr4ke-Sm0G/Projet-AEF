#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED

typedef struct {
    int etat_depuis;
    char symbole_entree;
    int etat_vers;
} Transition;

void initialiserTransition(Transition *transition, int depuis, char symbole, int vers);


#endif // TRANSITION_H_INCLUDED