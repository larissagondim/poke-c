#include <stdio.h>
#include "pokemon.h"
#include "typechart.h"

// function bodies:

int is_alive(Pokemon *p) {
    if(p->hp > 0)
        return 1;
    return 0;
}

void attack_pokemon(Pokemon *attacker, Pokemon *defender, Move move) {
   
}