#ifndef TYPECHART_H
#define TYPECHART_H

#include "pokemon.h"

// macros
// TYPE_COUNT: number of existing types
#define TYPE_COUNT 18

// auxiliar functions

// init_typechart
// @brief initializes typechart
// @params nothing cuz it's void
// @return nothing cuz it's void
void init_type_chart(void);

// calculate_type_multiplier
// @brief calculates the typ advantage damage used in pokemon attacks
// @params attack_type: pokem'ons type
// @params defender_type: the defender type
// @return a float value that represents the damage multiplier
float calculate_type_multiplier(PokemonType attack_type, char defender_types[MAX_TYPES][SIZE]);

#endif
