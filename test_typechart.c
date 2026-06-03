// effective test file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemon.h"
#include "typechart.h"

static void print_battle_state(Pokemon *attacker, Pokemon *defender, Move *move) {
    printf("\nBATTLE: \n");
    printf("%s (HP: %d) uses %s against %s (HP: %d)\n",
           attacker->name, attacker->hp,
           move->name,
           defender->name, defender->hp);
}

static void run_attack(Pokemon *attacker, Pokemon *defender, Move *move) {
    print_battle_state(attacker, defender, move);
    int result = attack_pokemon(attacker, defender, move);

    if (result == -1) 
        printf("Fail: No registered attacker nor defender.\n");
    else if (result == -2) 
        printf("Fail: no PP left for this move.\n");
    else if (result == 0) 
        printf("No damage applied.\n");
    else 
        printf("Results: %s is now with %d HP\n", defender->name, defender->hp);
}

int main() {
    srand(0);

    char pikachu_types[MAX_TYPES][SIZE] = {"Electric", ""};
    char charmander_types[MAX_TYPES][SIZE] = {"Fire", ""};
    char bulbasaur_types[MAX_TYPES][SIZE] = {"Grass", "Poison"};
    char gyarados_types[MAX_TYPES][SIZE] = {"Water", "Flying"};
    char metagross_types[MAX_TYPES][SIZE] = {"Steel", "Psychic"};
    char snorlax_types[MAX_TYPES][SIZE] = {"Normal", ""};
    char salamence_types[MAX_TYPES][SIZE] = {"Dragon", "Flying"};
    char clefairy_types[MAX_TYPES][SIZE] = {"Fairy", ""};

    Pokemon pikachu = create_pokemon("Pikachu", pikachu_types, 'F', 25, 18, 35, 55, 40, 50, 50, 90, 40.0, 6.0);
    Pokemon charmander = create_pokemon("Charmander", charmander_types, 'M', 4, 12, 39, 52, 43, 60, 50, 65, 60.0, 8.5);
    Pokemon bulbasaur = create_pokemon("Bulbasaur", bulbasaur_types, 'F', 1, 12, 45, 49, 49, 65, 65, 45, 70.0, 6.9);
    Pokemon gyarados = create_pokemon("Gyarados", gyarados_types, 'M', 130, 30, 95, 125, 79, 60, 100, 81, 65.0, 235.0);
    Pokemon metagross = create_pokemon("Metagross", metagross_types, 'M', 376, 50, 80, 135, 130, 95, 90, 70, 1600.0, 550.0);
    Pokemon snorlax = create_pokemon("Snorlax", snorlax_types, 'M', 143, 30, 160, 110, 65, 65, 110, 30, 460.0, 460.0);
    Pokemon salamence = create_pokemon("Salamence", salamence_types, 'M', 373, 50, 95, 135, 80, 110, 105, 100, 1500.0, 102.6);
    Pokemon clefairy = create_pokemon("Clefairy", clefairy_types, 'F', 35, 30, 70, 45, 48, 60, 65, 35, 60.0, 7.5);

    Move ember = create_move("Ember", FIRE, SPECIAL, 40, 25, 100.0);
    Move thunderbolt = create_move("Thunderbolt", ELECTRIC, SPECIAL, 90, 15, 100.0);
    Move shadow_ball = create_move("Shadow Ball", GHOST, SPECIAL, 80, 15, 100.0);
    Move moonblast = create_move("Moonblast", FAIRY, SPECIAL, 95, 10, 100.0);
    Move body_slam = create_move("Body Slam", NORMAL, PHYSICAL, 85, 15, 100.0);
    Move psychic_move = create_move("Psychic", PSYCHIC, SPECIAL, 90, 10, 100.0);
    Move quick_attack = create_move("Quick Attack", NORMAL, PHYSICAL, 40, 30, 100.0);
    Move iron_tail = create_move("Iron Tail", STEEL, PHYSICAL, 100, 15, 75.0);
    Move electro_ball = create_move("Electro Ball", ELECTRIC, SPECIAL, 80, 10, 100.0);

    pikachu.moves[0] = thunderbolt;
    pikachu.moves[1] = quick_attack;
    pikachu.moves[2] = iron_tail;
    pikachu.moves[3] = electro_ball;

    init_type_chart();

    run_attack(&pikachu, &gyarados, &thunderbolt);
    run_attack(&gyarados, &salamence, &thunderbolt);
    run_attack(&clefairy, &salamence, &moonblast);
    run_attack(&snorlax, &metagross, &body_slam);
    run_attack(&clefairy, &metagross, &shadow_ball);
    run_attack(&bulbasaur, &metagross, &psychic_move);

    printf("\n\nRun tests\n");
    
    printf("\n1st test: faster ko before adversary attacks\n");
    Pokemon pk1 = create_pokemon("Pikachu", pikachu_types, 'F', 25, 18, 35, 55, 40, 50, 50, 90, 40.0, 6.0);
    Pokemon gy1 = create_pokemon("Gyarados", gyarados_types, 'M', 130, 30, 95, 125, 79, 60, 100, 81, 65.0, 235.0);
    Move tb1 = create_move("Thunderbolt", ELECTRIC, SPECIAL, 90, 5, 100.0);
    Move wf1 = create_move("Waterfall", WATER, PHYSICAL, 80, 5, 100.0);
    printf("Speed: %s=%d | %s=%d\n", pk1.name, pk1.speed, gy1.name, gy1.speed);
    int res1 = run_turn(&pk1, &gy1, &tb1, &wf1);
    printf("Final results -> %s HP:%d | %s HP:%d\n", pk1.name, pk1.hp, gy1.name, gy1.hp);
    if (res1 == 1)  printf("Winner: %s\n", pk1.name);
    if (res1 == -1) printf("Winner: %s\n", gy1.name);
    if (res1 == 0)  printf("Nenhum desmaiou no turno.\n");

    printf("\n2nd test: tie and both swap attacks\n");
    Pokemon sal2 = create_pokemon("Salamence", salamence_types, 'M', 373, 50, 95, 135, 80, 110, 105, 100, 1500.0, 102.6);
    Pokemon snx2 = create_pokemon("Snorlax", snorlax_types, 'M', 143, 30, 160, 110, 65, 65, 110, 30, 460.0, 460.0);
    Move og2 = create_move("Outrage", DRAGON, PHYSICAL, 120, 10, 100.0);
    Move bs2 = create_move("Body Slam", NORMAL, PHYSICAL, 85, 15, 100.0);
    printf("Speed: %s=%d | %s=%d\n", sal2.name, sal2.speed, snx2.name, snx2.speed);
    int res2 = run_turn(&sal2, &snx2, &og2, &bs2);
    printf("Final results -> %s HP:%d | %s HP:%d\n", sal2.name, sal2.hp, snx2.name, snx2.hp);
    if (res2 == 1)  printf("Winner: %s\n", sal2.name);
    if (res2 == -1) printf("Winner: %s\n", snx2.name);
    if (res2 == 0)  printf("None has fainted in this turn.\n");

    printf("\n3rd test: charmander b4 bulbassaur\n");
    Pokemon ch3 = create_pokemon("Charmander", charmander_types, 'M', 4, 12, 39, 52, 43, 60, 50, 65, 60.0, 8.5);
    Pokemon bul3 = create_pokemon("Bulbasaur", bulbasaur_types, 'F', 1, 12, 45, 49, 49, 65, 65, 45, 70.0, 6.9);
    Move em3 = create_move("Ember", FIRE, SPECIAL, 40, 25, 100.0);
    Move vw3 = create_move("Vine Whip", GRASS, PHYSICAL, 45, 25, 100.0);
    printf("Speed: %s=%d | %s=%d\n", ch3.name, ch3.speed, bul3.name, bul3.speed);
    int res3 = run_turn(&ch3, &bul3, &em3, &vw3);
    printf("Final result -> %s HP:%d | %s HP:%d\n", ch3.name, ch3.hp, bul3.name, bul3.hp);
    if (res3 == 1)  printf("Winner: %s\n", ch3.name);
    if (res3 == -1) printf("Winner: %s\n", bul3.name);
    if (res3 == 0)  printf("None has fainted in this turn.\n");

    return 0;
}
