#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "pokemon.h"
#include "typechart.h"

// FUNCTION BODIES:

int attack_pokemon(Pokemon *attacker, Pokemon *defender, Move *move) {

    if(attacker == NULL) {
        printf("\nNo registered attacker.");
        return -1;
    }

    if(defender == NULL) {
        printf("\nNo registered defender.");
        return -1;
    }

    /*TODO: use attacker's move*/
    if(chance_hit(move->precision)) {

        if(move->PP > 0) {
        
            move->PP -= 1;
            int damage;

            if(move->category == PHYSICAL) 
                damage = (move->power * attacker->attack) / defender -> defense;

            else if(move->category == SPECIAL)
                damage = (move->power * attacker->sp_atk) / defender -> sp_def;
            // if it isn't special or physical, it causes no damage
            else
                return 0;
            
            defender->hp -= damage;

            if(defender->hp < 0) 
                defender->hp = 0;

            printf("\n%s used %s!", attacker->name, move->name);

            return 1;
        }
        else {
            printf("\nNo moves left.");
            return -2;
        }

    } else {

        printf("\nThe attack missed!");
        return 0;

    }
}

int chance_hit(float chance) {

    // if there's 0 chance of hitting, it will always return 0
    if(chance <= 0.0f)
        return 0;

    // if there's 100% chance of hitting, it will always return 1
    if(chance >= 1.0f)
        return 1;

    float roll = rand() / (RAND_MAX + 1.0);

    return roll < chance;
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

        case NORMAL:
            printf("Normal");
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