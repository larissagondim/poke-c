#ifndef PARSER_H
#define PARSER_H

// interface for a parser to read pokemon data from a file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemon.h"

// 'parse_pokemons'
// @brief Parses a file containing pokemon data (moves embedded in each line)
//        and stores it in an array.
//
// @param filename path to the file containing pokemon data
// @param pokemons pointer to the array that will store the pokemon data
// @param max maximum number of pokemon the 'pokemons' array can hold
// @param count pointer to the variable that will store the number of pokemon parsed
// @return 0 on success, -1 if the file could not be opened
int parse_pokemons(const char *filename, Pokemon *pokemons, int max, int *count);

#endif