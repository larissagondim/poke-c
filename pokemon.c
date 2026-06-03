#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "pokemon.h"
#include "typechart.h"

// FUNCTION BODIES:

int attack_pokemon(Pokemon *attacker, Pokemon *defender, Move *move) {

    if (attacker == NULL) {
        printf("\nNo registered attacker.");
        return -1;
    }

    if (defender == NULL) {
        printf("\nNo registered defender.");
        return -1;
    }

    if (move == NULL) {
        printf("\nNo move selected.");
        return -1;
    }

    if (move->PP <= 0) {
        printf("\nNo moves left.");
        return -2;
    }

    if (!chance_hit(move->precision)) {
        printf("\nThe attack missed!");
        move->PP -= 1;
        return 0;
    }

    move->PP -= 1;
    int damage = 0;

    if (move->category == PHYSICAL) 
        damage = (move->power * attacker->attack) / defender->defense;
    else if (move->category == SPECIAL) 
        damage = (move->power * attacker->sp_atk) / defender->sp_def;
    else {
        printf("\n%s used %s!\n", attacker->name, move->name);
        printf("This move has no damage effect.\n");
        return 0;
    }

    float multiplier = calculate_type_multiplier(move->type, defender->types);
    damage = (int)(damage * multiplier + 0.5f);

    defender->hp -= damage;
    if (defender->hp < 0)
        defender->hp = 0;

    printf("\n%s used %s!", attacker->name, move->name);

    if (multiplier == 0.0f) 
        printf(" It had no effect!\n");
    else if (multiplier > 1.0f) 
        printf(" It's super effective!\n");
    else if (multiplier < 1.0f) 
        printf(" It's not very effective...\n");

    return 1;
}

int chance_hit(float chance) {

    // if there's 0 chance of hitting, it will always return 0
    if (chance <= 0.0f)
        return 0;

    // if there's 100% chance of hitting, it will always return 1
    if (chance >= 100.0f)
        return 1;

    float adjusted_chance = chance / 100.0f;
    float roll = rand() / (RAND_MAX + 1.0);

    return roll < adjusted_chance;
}

Move create_move(
    char name[],
    PokemonType type,
    MoveCategory category,
    int power,
    int PP,
    float precision
) {

    Move m;

    strcpy(m.name, name);

    m.type = type;
    m.category = category;

    m.power = power;
    m.PP = PP;
    m.precision = precision;

    return m;
}

Pokemon create_pokemon(
    char name[],
    char types[MAX_TYPES][SIZE],
    char sex,
    int pokedex_code,
    int level,
    int hp,
    int attack,
    int defense,
    int sp_atk,
    int sp_def,
    int speed,
    double height,
    double weight
) {

    Pokemon p;

    strcpy(p.name, name);

    for (int i = 0; i < MAX_TYPES; i++) {
        strcpy(p.types[i], types[i]);
    }

    p.sex = sex;

    p.pokedex_code = pokedex_code;
    p.level = level;

    p.hp = hp;

    p.attack = attack;
    p.defense = defense;

    p.sp_atk = sp_atk;
    p.sp_def = sp_def;

    p.speed = speed;

    p.height = height;
    p.weight = weight;

    // initializes empty moves
    for (int i = 0; i < MAX_MOVES; i++) {
        strcpy(p.moves[i].name, "");
    }

    return p;
}

int is_alive(Pokemon *p) {

    if(p == NULL) {
        printf("\nNo registered Pokemon.");
        return -1;
    }

    if(!(p->hp > 0)) {
        printf("\n%s has fainted!", p->name);
        return 0;
    }

    return 1;
}

void print_move(Move *m) {

    if (m == NULL) {
        printf("\nMove isn't available.\n");
        exit(1);
    }

    printf("\nMOVE INFO: \n");

    printf("\nName: %s", m->name);

    // type
    printf("\nType: ");

    switch (m->type) {

        case NORMAL:
            printf("Normal");
            break;

        case FIRE:
            printf("Fire");
            break;

        case WATER:
            printf("Water");
            break;

        case GRASS:
            printf("Grass");
            break;

        case ELECTRIC:
            printf("Electric");
            break;

        case ICE:
            printf("Ice");
            break;

        case FIGHTING:
            printf("Fighting");
            break;

        case POISON:
            printf("Poison");
            break;

        case GROUND:
            printf("Ground");
            break;

        case FLYING:
            printf("Flying");
            break;

        case PSYCHIC:
            printf("Psychic");
            break;

        case BUG:
            printf("Bug");
            break;

        case ROCK:
            printf("Rock");
            break;

        case GHOST:
            printf("Ghost");
            break;

        case DRAGON:
            printf("Dragon");
            break;

        case DARK:
            printf("Dark");
            break;

        case STEEL:
            printf("Steel");
            break;

        case FAIRY:
            printf("Fairy");
            break;

        default:
            printf("Unknown");
    }

    // category
    printf("\nCategory: ");

    switch (m->category) {

        case PHYSICAL:
            printf("Physical");
            break;

        case SPECIAL:
            printf("Special");
            break;

        case STATUS:
            printf("Status");
            break;

        default:
            printf("Unknown");
    }

    printf("\nPower: %d", m->power);
    printf("\nPP: %d", m->PP);
    printf("\nAccuracy: %.1f%%\n", m->precision);
}

void print_pokemon(Pokemon *p) {

    if(p == NULL) {
        printf("\nPokemon isn't available.");
        exit(1);
    }
    printf("\nNo. %03d | %s ", p->pokedex_code, p->name);
    if(p->sex == 'M')
        printf("(♂)");
    else 
        printf("(♀)");
    
    if(p->types[1][0] == '\0')
        printf("\n\nType: ");
    else 
        printf("\n\nTypes: ");

    for (int i = 0; i < MAX_TYPES; i++) {
        if (p->types[i][0] != '\0') {
            printf("%s ", p->types[i]);
        }
    }

    printf("\n");
    printf("\nHP: %d", p->hp);
    printf("\nAttack: %d", p->attack);
    printf("\nDefense: %d", p->defense);
    printf("\nSp. Attack: %d", p->sp_atk);
    printf("\nSp. Defense: %d", p->sp_def);
    printf("\nSpeed: %d", p->speed);

    printf("\n\nHeight: %.2f cm", p->height);
    printf("\nWeight: %.2f kg", p->weight);

    printf("\n\nMOVES: \n");

    for (int i = 0; i < MAX_MOVES; i++) {

        printf("%-20s", p->moves[i].name);

        if ((i + 1) % 2 == 0)
            printf("\n");
    }
}

int run_turn(Pokemon *a, Pokemon *b, Move *move_a, Move *move_b) {
    Pokemon *first  = (a->speed >= b->speed) ? a : b;
    Pokemon *second = (a->speed >= b->speed) ? b : a;
    Move *move_first  = (a->speed >= b->speed) ? move_a : move_b;
    Move *move_second = (a->speed >= b->speed) ? move_b : move_a;

    attack_pokemon(first, second, move_first);

    if (is_alive(second) > 0)
        attack_pokemon(second, first, move_second);

    if (a->hp <= 0 && b->hp > 0) return -1; 
    if (b->hp <= 0 && a->hp > 0) return  1; 
    return 0; 
}