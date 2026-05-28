#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "typechart.h"
#include "pokemon.h"

// type effectiveness chart
// [ATTACKING_TYPE][DEFENDING_TYPE]
float type_chart[TYPE_COUNT][TYPE_COUNT];
static int chart_initialized = 0;

static void ensure_chart_initialized(void) {
    if (!chart_initialized) {
        init_type_chart();
    }
}

static int strings_equal_ignore_case(const char *a, const char *b) {
    if (a == NULL || b == NULL) return 0;
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

static int parse_pokemon_type(const char type_name[]) {
    if (type_name == NULL || type_name[0] == '\0')
        return -1;

    if (strings_equal_ignore_case(type_name, "Normal")) return NORMAL;
    if (strings_equal_ignore_case(type_name, "Fire")) return FIRE;
    if (strings_equal_ignore_case(type_name, "Water")) return WATER;
    if (strings_equal_ignore_case(type_name, "Grass")) return GRASS;
    if (strings_equal_ignore_case(type_name, "Electric")) return ELECTRIC;
    if (strings_equal_ignore_case(type_name, "Ice")) return ICE;
    if (strings_equal_ignore_case(type_name, "Fighting")) return FIGHTING;
    if (strings_equal_ignore_case(type_name, "Poison")) return POISON;
    if (strings_equal_ignore_case(type_name, "Ground")) return GROUND;
    if (strings_equal_ignore_case(type_name, "Flying")) return FLYING;
    if (strings_equal_ignore_case(type_name, "Psychic")) return PSYCHIC;
    if (strings_equal_ignore_case(type_name, "Bug")) return BUG;
    if (strings_equal_ignore_case(type_name, "Rock")) return ROCK;
    if (strings_equal_ignore_case(type_name, "Ghost")) return GHOST;
    if (strings_equal_ignore_case(type_name, "Dragon")) return DRAGON;
    if (strings_equal_ignore_case(type_name, "Dark")) return DARK;
    if (strings_equal_ignore_case(type_name, "Steel")) return STEEL;
    if (strings_equal_ignore_case(type_name, "Fairy")) return FAIRY;

    return -1;
}

float calculate_type_multiplier(PokemonType attack_type, char defender_types[MAX_TYPES][SIZE]) {
    ensure_chart_initialized();

    if (attack_type < 0 || attack_type >= TYPE_COUNT)
        return 1.0f;

    float multiplier = 1.0f;

    for (int i = 0; i < MAX_TYPES; i++) {
        if (defender_types[i][0] == '\0')
            continue;

        int defender_type = parse_pokemon_type(defender_types[i]);
        if (defender_type >= 0 && defender_type < TYPE_COUNT)
            multiplier *= type_chart[attack_type][defender_type];
    }

    return multiplier;
}

static void init_type_chart_table(float type_chart[TYPE_COUNT][TYPE_COUNT]) {
    // initializing everything as neutral damage
    for (int i = 0; i < TYPE_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) 
            type_chart[i][j] = 1.0;
    }

    // adding the special cases

    // NORMAL TYPE
    
    type_chart[NORMAL][ROCK] = 0.5;
    type_chart[NORMAL][GHOST] = 0.0;
    type_chart[NORMAL][STEEL] = 0.5;

    // FIRE TYPE

    type_chart[FIRE][GRASS] = 2.0;
    type_chart[FIRE][ICE] = 2.0;
    type_chart[FIRE][BUG] = 2.0;
    type_chart[FIRE][STEEL] = 2.0;

    type_chart[FIRE][FIRE] = 0.5;
    type_chart[FIRE][WATER] = 0.5;
    type_chart[FIRE][ROCK] = 0.5;
    type_chart[FIRE][DRAGON] = 0.5;

    // WATER TYPE

    type_chart[WATER][FIRE] = 2.0;
    type_chart[WATER][GROUND] = 2.0;
    type_chart[WATER][ROCK] = 2.0;

    type_chart[WATER][WATER] = 0.5;
    type_chart[WATER][GRASS] = 0.5;
    type_chart[WATER][DRAGON] = 0.5;

    // GRASS TYPE

    type_chart[GRASS][WATER] = 2.0;
    type_chart[GRASS][GROUND] = 2.0;
    type_chart[GRASS][ROCK] = 2.0;
    type_chart[GRASS][FIRE] = 0.5;
    type_chart[GRASS][GRASS] = 0.5;
    type_chart[GRASS][POISON] = 0.5;
    type_chart[GRASS][FLYING] = 0.5;
    type_chart[GRASS][BUG] = 0.5;
    type_chart[GRASS][DRAGON] = 0.5;
    type_chart[GRASS][STEEL] = 0.5;

    // ELECTRIC TYPE

    type_chart[ELECTRIC][WATER] = 2.0;
    type_chart[ELECTRIC][FLYING] = 2.0;
    type_chart[ELECTRIC][ELECTRIC] = 0.5;
    type_chart[ELECTRIC][GRASS] = 0.5;
    type_chart[ELECTRIC][DRAGON] = 0.5;
    type_chart[ELECTRIC][GROUND] = 0.0;

    // ICE TYPE

    type_chart[ICE][GRASS] = 2.0;
    type_chart[ICE][GROUND] = 2.0;
    type_chart[ICE][FLYING] = 2.0;
    type_chart[ICE][DRAGON] = 2.0;

    type_chart[ICE][FIRE] = 0.5;
    type_chart[ICE][WATER] = 0.5;
    type_chart[ICE][ICE] = 0.5;
    type_chart[ICE][STEEL] = 0.5;

    // FIGHTING TYPE

    type_chart[FIGHTING][NORMAL] = 2.0;
    type_chart[FIGHTING][ICE] = 2.0;
    type_chart[FIGHTING][ROCK] = 2.0;
    type_chart[FIGHTING][DARK] = 2.0;
    type_chart[FIGHTING][STEEL] = 2.0;
    type_chart[FIGHTING][POISON] = 0.5;
    type_chart[FIGHTING][FLYING] = 0.5;
    type_chart[FIGHTING][PSYCHIC] = 0.5;
    type_chart[FIGHTING][BUG] = 0.5;
    type_chart[FIGHTING][FAIRY] = 0.5;
    type_chart[FIGHTING][GHOST] = 0.0;

    // POISON
    
    type_chart[POISON][GRASS] = 2.0;
    type_chart[POISON][FAIRY] = 2.0;
    type_chart[POISON][POISON] = 0.5;
    type_chart[POISON][GROUND] = 0.5;
    type_chart[POISON][ROCK] = 0.5;
    type_chart[POISON][GHOST] = 0.5;
    type_chart[POISON][STEEL] = 0.0;

    // GROUND TYPE

    type_chart[GROUND][FIRE] = 2.0;
    type_chart[GROUND][ELECTRIC] = 2.0;
    type_chart[GROUND][POISON] = 2.0;
    type_chart[GROUND][ROCK] = 2.0;
    type_chart[GROUND][STEEL] = 2.0;
    type_chart[GROUND][GRASS] = 0.5;
    type_chart[GROUND][BUG] = 0.5;
    type_chart[GROUND][FLYING] = 0.0;

    // FLYING TYPE 

    type_chart[FLYING][GRASS] = 2.0;
    type_chart[FLYING][FIGHTING] = 2.0;
    type_chart[FLYING][BUG] = 2.0;
    type_chart[FLYING][ELECTRIC] = 0.5;
    type_chart[FLYING][ROCK] = 0.5;
    type_chart[FLYING][STEEL] = 0.5;

    // PSYCHIC TYPE

    type_chart[PSYCHIC][FIGHTING] = 2.0;
    type_chart[PSYCHIC][POISON] = 2.0;
    type_chart[PSYCHIC][PSYCHIC] = 0.5;
    type_chart[PSYCHIC][STEEL] = 0.5;
    type_chart[PSYCHIC][DARK] = 0.0;

    // BUG TYPE

    type_chart[BUG][GRASS] = 2.0;
    type_chart[BUG][PSYCHIC] = 2.0;
    type_chart[BUG][DARK] = 2.0;

    type_chart[BUG][FIRE] = 0.5;
    type_chart[BUG][FIGHTING] = 0.5;
    type_chart[BUG][POISON] = 0.5;
    type_chart[BUG][FLYING] = 0.5;
    type_chart[BUG][GHOST] = 0.5;
    type_chart[BUG][STEEL] = 0.5;
    type_chart[BUG][FAIRY] = 0.5;

    // ROCK TYPE

    type_chart[ROCK][FIRE] = 2.0;
    type_chart[ROCK][ICE] = 2.0;
    type_chart[ROCK][FLYING] = 2.0;
    type_chart[ROCK][BUG] = 2.0;
    type_chart[ROCK][FIGHTING] = 0.5;
    type_chart[ROCK][GROUND] = 0.5;
    type_chart[ROCK][STEEL] = 0.5;

    // GHOST TYPE

    type_chart[GHOST][PSYCHIC] = 2.0;
    type_chart[GHOST][GHOST] = 2.0;
    type_chart[GHOST][DARK] = 0.5;
    type_chart[GHOST][NORMAL] = 0.0;

    // DRAGON TYPE

    type_chart[DRAGON][DRAGON] = 2.0;
    type_chart[DRAGON][STEEL] = 0.5;
    type_chart[DRAGON][FAIRY] = 0.0;
    
    // DARK TYPE

    type_chart[DARK][PSYCHIC] = 2.0;
    type_chart[DARK][GHOST] = 2.0;
    type_chart[DARK][FIGHTING] = 0.5;
    type_chart[DARK][DARK] = 0.5;
    type_chart[DARK][FAIRY] = 0.5;

    // STEEL TYPE

    type_chart[STEEL][ICE] = 2.0;
    type_chart[STEEL][ROCK] = 2.0;
    type_chart[STEEL][FAIRY] = 2.0;
    type_chart[STEEL][FIRE] = 0.5;
    type_chart[STEEL][WATER] = 0.5;
    type_chart[STEEL][ELECTRIC] = 0.5;
    type_chart[STEEL][STEEL] = 0.5;
    
    // FAIRY TYPE

    type_chart[FAIRY][FIGHTING] = 2.0;
    type_chart[FAIRY][DRAGON] = 2.0;
    type_chart[FAIRY][DARK] = 2.0;
    type_chart[FAIRY][FIRE] = 0.5;
    type_chart[FAIRY][POISON] = 0.5;
    type_chart[FAIRY][STEEL] = 0.5;
}

void init_type_chart(void) {
    init_type_chart_table(type_chart);
    chart_initialized = 1;
}
