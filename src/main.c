#include <stdio.h>
#include <string.h>

#include "pokemon.h"
#include "typechart.h"

// TESTING FUNCTIONS
int main() {

    // pokemon types
    PokemonType pikachu_types[MAX_TYPES] = {
        ELECTRIC,
        NONE_TYPE
    };

    // create pokemon
    Pokemon pikachu = create_pokemon(
        "Pikachu",
        pikachu_types,
        'F',
        25,
        18,
        35,
        55,
        40,
        50,
        50,
        90,
        40.0,
        6.0
    );

    // create moves
    Move thunderbolt = create_move(
        "Thunderbolt",
        ELECTRIC,
        SPECIAL,
        90,
        15,
        100.0
    );

    Move quick_attack = create_move(
        "Quick Attack",
        NORMAL,
        PHYSICAL,
        40,
        30,
        100.0
    );

    Move iron_tail = create_move(
        "Iron Tail",
        STEEL,
        PHYSICAL,
        100,
        15,
        75.0
    );

    Move electro_ball = create_move(
        "Electro Ball",
        ELECTRIC,
        SPECIAL,
        80,
        10,
        100.0
    );

    // assign moves to pokemon
    pikachu.moves[0] = thunderbolt;
    pikachu.moves[1] = quick_attack;
    pikachu.moves[2] = iron_tail;
    pikachu.moves[3] = electro_ball;

    // display pokemon
    print_pokemon(&pikachu);

    // display move info
    printf("\n");
    print_move(&pikachu.moves[0]);

    // create second pokemon
    PokemonType charmander_types[MAX_TYPES] = {
        FIRE,
        NONE_TYPE
    };
    Pokemon charmander = create_pokemon(
        "Charmander",
        charmander_types,
        'M',
        4,
        18,
        39,
        52,
        43,
        60,
        50,
        65,
        60.0,
        8.5
    );
    Move ember = create_move("Ember", FIRE, SPECIAL, 40, 25, 100.0);
    charmander.moves[0] = ember;

    // run battle
    init_type_chart();
    run_battle(&pikachu, &charmander);

    return 0;
}