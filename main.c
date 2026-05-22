#include <stdio.h>
#include <string.h>

#include "pokemon.h"

// TESTING FUNCTIONS
int main() {

    // pokemon types
    char pikachu_types[MAX_TYPES][SIZE] = {
        "Electric",
        ""
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

    return 0;
}