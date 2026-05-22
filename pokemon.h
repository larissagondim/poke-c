#ifndef POKEMON_H
#define POKEMON_H

// Constants:

// MAX_TYPES: represents the maximum number of types that a pokemón can have
// NUM_ATTACKS: represents the maximum number of attacks that a pokemon can have
// NAME_SIZE: represents the pokemon's name size based on the biggest pokemon name registered (which contains 36 characters)
// SIZE: standard size for other strings

#define MAX_TYPES 2
#define MAX_MOVES 4
#define NAME_SIZE 37
#define SIZE 20


// ENUMS:

// Pokemon move categories
typedef enum {
    PHYSICAL,
    SPECIAL,
    STATUS
} MoveCategory;

// Pokemon elemental types
typedef enum {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY
} PokemonType;

// STRUCTURES: 

// 'Move'
// Structure that simulates which pokemon attack attributes to make battles more interesting
typedef struct {
    PokemonType type;
    MoveCategory category;
    int power; // base damage power of the move
    int PP; // number of times that it can be used
    float precision; // accuracy percentage of the move
} Move;

// 'Pokemon'
// Structure that represents basic pokemon stats that will simulate its battle dynamics
typedef struct {
    char name[NAME_SIZE];
    char types[MAX_TYPES][SIZE]; // pokemon type(s) (e.g. fire and flying)
    Move moves[MAX_MOVES]; // list of moves the pokemon can use
    int pokedex_code; // national pokédex identification number
    int level; // current pokemon level
    int hp; // health points
    int speed; // determines attack order in battle
    int attack; // physical attack stat
    int deffense; // physical defense stat
    int sp_atk; // special attack stat
    int sp_def; // special deffense stat
    double weight;
    double height;
} Pokemon;

// AUXILIAR FUNCTIONS: 

// @brief Simulates an attack from one pokemon to another using a selected move
// @params attacker Pointer to the attacking pokemon
// @params defender Pointer to the defending pokemon
// @params move Move used during the attack
// @return void
void attack_pokemon(Pokemon *attacker, Pokemon *defender, Move move);

// 'create_pokemon'
// @brief Creates and initializes a pokemon structure
// @params void
// @return A fully initialized Pokemon structure
Pokemon create_pokemon(void);

// @brief Checks whether a pokemon is still alive
// @params p Pokemon to be checked
// @return 1 if the pokemon still has HP, otherwise 0
int is_alive(Pokemon *p);

// @brief Displays all relevant pokemon information on screen
// @params p Pokemon to be displayed
// @return void
void print_pokemon(Pokemon *p);

// @brief Displays all relevant move information on screen
// @params m Move to be displayed
// @return void
void print_move(Move *m);

#endif