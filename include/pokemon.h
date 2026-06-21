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
    FAIRY,
    NONE_TYPE
} PokemonType;

// Pokemon status conditions
typedef enum {
    STATUS_NONE,
    STATUS_BURN,
    STATUS_POISON,
    STATUS_PARALYSIS
} StatusCondition;

// STRUCTURES: 

// 'Move'
// Structure that simulates which pokemon attack attributes to make battles more interesting
typedef struct {
    char name[NAME_SIZE];
    PokemonType type;
    MoveCategory category;
    int power; // base damage power of the move
    int PP; // number of times that it can be used
    float precision; // accuracy percentage of the move
} Move;

// 'Pokemon'
// Structure that represents basic pokemon stats that will simulate its battle dynamics
typedef struct {
    char name[SIZE];
    PokemonType types[MAX_TYPES]; // pokemon type(s)
    char sex; // F for Female | M for male
    Move moves[MAX_MOVES]; // list of moves the pokemon can use
    int pokedex_code; // national pokédex identification number
    int level; // current pokemon level
    int current_hp; // health points
    int max_hp; // maximum health points
    StatusCondition status; // current status condition
    int speed; // determines attack order in battle
    int attack; // physical attack stat
    int defense; // physical defense stat
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
// @return 0 if it's a special attack or if it misses (no damage)
// @return 1 if the attack hits
// @return -1 if there's no registered attacker or defender
// @return -2 if there are no moves left
int attack_pokemon(Pokemon *attacker, Pokemon *defender, Move *move);

// @brief Returns the chance of attack hit based on its precision
// @param chance Move's precision
// @return 1 if it hits, otherwise 0
int chance_hit(float chance);

// 'create_move'
// @brief Creates and initializes a move structure
// @params Move basic attributes
// @return A fully initialized Move structure
Move create_move(
    char name[],
    PokemonType type,
    MoveCategory category,
    int power,
    int PP,
    float precision
);

// 'create_pokemon'
// @brief Creates and initializes a pokemon structure
// @params Pokemon basic attributes
// @return A fully initialized Pokemon structure
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
);


// @brief Checks whether a pokemon is still alive
// @params p Pokemon to be checked
// @return 1 if the pokemon still has HP, otherwise 0
// @return -1 if the pokemón isn't there
int is_alive(Pokemon *p);

// @brief Displays all relevant move information on screen
// @params m Move to be displayed
// @return void
void print_move(Move *m);

// @brief Displays all relevant pokemon information on screen
// @params p Pokemon to be displayed
// @return void
void print_pokemon(Pokemon *p);

// @brief Runs a turn of battle based on its speed
// @param a 1st pokemon that'll be used
// @param b 2nd pokemon
// @param move_a 1st pokemon's move
// @param move_b 2nd pokemon's move
// @return 1 if the 1st pokemon won, -1 if the 2nd pokemon won, 0 if it's a tie or if no pokemon fainted
int run_turn(Pokemon *a, Pokemon *b, Move *move_a, Move *move_b);

// @brief Runs a battle loop between two pokemons until one faints
// @param a 1st pokemon
// @param b 2nd pokemon
void run_battle(Pokemon *a, Pokemon *b);

#endif