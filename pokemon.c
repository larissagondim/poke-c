#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "pokemon.h"
#include "typechart.h"

// Helper for type names
const char* get_type_name(PokemonType type) {
    switch (type) {
        case NORMAL: return "Normal";
        case FIRE: return "Fire";
        case WATER: return "Water";
        case GRASS: return "Grass";
        case ELECTRIC: return "Electric";
        case ICE: return "Ice";
        case FIGHTING: return "Fighting";
        case POISON: return "Poison";
        case GROUND: return "Ground";
        case FLYING: return "Flying";
        case PSYCHIC: return "Psychic";
        case BUG: return "Bug";
        case ROCK: return "Rock";
        case GHOST: return "Ghost";
        case DRAGON: return "Dragon";
        case DARK: return "Dark";
        case STEEL: return "Steel";
        case FAIRY: return "Fairy";
        default: return "";
    }
}

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

    if (attacker->status == STATUS_PARALYSIS) {
        if (rand() % 4 == 0) { // 25% chance
            printf("\n%s is paralyzed! It can't move!\n", attacker->name);
            return 0;
        }
    }

    if (move->category == PHYSICAL) 
        damage = (((2 * attacker->level / 5 + 2) * move->power * attacker->attack / defender->defense) / 50 + 2);
    else if (move->category == SPECIAL) 
        damage = (((2 * attacker->level / 5 + 2) * move->power * attacker->sp_atk / defender->sp_def) / 50 + 2);
    else if (move->category == STATUS) {
        printf("\n%s used %s!", attacker->name, move->name);
        if (defender->status != STATUS_NONE) {
            printf("\nBut it failed!\n");
        } else {
            if (move->type == FIRE) {
                defender->status = STATUS_BURN;
                printf("\n%s was burned!\n", defender->name);
            } else if (move->type == POISON) {
                defender->status = STATUS_POISON;
                printf("\n%s was poisoned!\n", defender->name);
            } else if (move->type == ELECTRIC) {
                defender->status = STATUS_PARALYSIS;
                printf("\n%s is paralyzed! It may be unable to move!\n", defender->name);
            } else {
                printf("\nIt had no effect!\n");
            }
        }
        return 1;
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
    PokemonType types[MAX_TYPES],
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
        p.types[i] = types[i];
    }

    p.sex = sex;

    p.pokedex_code = pokedex_code;
    p.level = level;

    p.hp = hp;
    p.max_hp = hp;
    p.status = STATUS_NONE;

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
        return;
    }

    printf("\nMOVE INFO: \n");

    printf("\nName: %s", m->name);

    // type
    printf("\nType: ");

    printf("%s", get_type_name(m->type));

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
        return;
    }
    printf("\nNo. %03d | %s ", p->pokedex_code, p->name);
    if(p->sex == 'M')
        printf("(♂)");
    else 
        printf("(♀)");
    
    if(p->types[1] == NONE_TYPE)
        printf("\n\nType: ");
    else 
        printf("\n\nTypes: ");

    for (int i = 0; i < MAX_TYPES; i++) {
        if (p->types[i] != NONE_TYPE) {
            printf("%s ", get_type_name(p->types[i]));
        }
    }

    printf("\n");
    if (p->status == STATUS_BURN) printf("\nStatus: BURN");
    else if (p->status == STATUS_POISON) printf("\nStatus: POISON");
    else if (p->status == STATUS_PARALYSIS) printf("\nStatus: PARALYSIS");
    
    printf("\nHP: %d/%d", p->hp, p->max_hp);
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

static void apply_status_effects(Pokemon *p) {
    if (p->hp > 0) {
        if (p->status == STATUS_BURN) {
            int damage = p->max_hp / 16;
            if (damage == 0) damage = 1;
            p->hp -= damage;
            printf("\n%s is hurt by its burn!\n", p->name);
        } else if (p->status == STATUS_POISON) {
            int damage = p->max_hp / 8;
            if (damage == 0) damage = 1;
            p->hp -= damage;
            printf("\n%s is hurt by poison!\n", p->name);
        }
        if (p->hp < 0) p->hp = 0;
        if (p->hp == 0) printf("\n%s has fainted!\n", p->name);
    }
}

int run_turn(Pokemon *a, Pokemon *b, Move *move_a, Move *move_b) {
    Pokemon *first  = (a->speed >= b->speed) ? a : b;
    Pokemon *second = (a->speed >= b->speed) ? b : a;
    Move *move_first  = (a->speed >= b->speed) ? move_a : move_b;
    Move *move_second = (a->speed >= b->speed) ? move_b : move_a;

    if (is_alive(first) > 0)
        attack_pokemon(first, second, move_first);

    if (is_alive(second) > 0)
        attack_pokemon(second, first, move_second);

    apply_status_effects(first);
    apply_status_effects(second);

    if (a->hp <= 0 && b->hp > 0) return -1; 
    if (b->hp <= 0 && a->hp > 0) return  1; 
    return 0; 
}

void run_battle(Pokemon *a, Pokemon *b) {
    printf("\n--- BATTLE START ---");
    printf("\n%s vs %s\n", a->name, b->name);
    int turn = 1;
    while (a->hp > 0 && b->hp > 0) {
        printf("\n--- Turn %d ---\n", turn++);
        
        Move *move_a = &a->moves[rand() % MAX_MOVES];
        while (move_a->name[0] == '\0' || move_a->PP <= 0) {
            move_a = &a->moves[rand() % MAX_MOVES];
        }
        Move *move_b = &b->moves[rand() % MAX_MOVES];
        while (move_b->name[0] == '\0' || move_b->PP <= 0) {
            move_b = &b->moves[rand() % MAX_MOVES];
        }
        
        run_turn(a, b, move_a, move_b);
    }
    printf("\n--- BATTLE END ---\n");
    if (a->hp > 0) {
        printf("\n%s wins!\n", a->name);
    } else if (b->hp > 0) {
        printf("\n%s wins!\n", b->name);
    } else {
        printf("\nIt's a tie!\n");
    }
}