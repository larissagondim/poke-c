# ADT Pokémon

A simple Pokémon Abstract Data Type (ADT) project written in C.

This project simulates Pokémon data structures and basic battle-related entities using modular programming with `.h` and `.c` files.

---

## Features

* Pokémon structure representation
* Move structure representation
* Pokémon constructors
* Move constructors
* Pokémon information display
* Move information display
* Type effectiveness calculation using a type chart
* Attack damage adjusted by defending Pokémon types
* Organized modular architecture using ADTs
* Practice with:

  * Structs
  * Enums
  * Pointers
  * Dynamic organization of code
  * Header/source separation

---

## Project Structure

```txt
poke-c/
│
├── main.c          # project testing
├── pokemon.h       # structs, constants, prototypes
├── pokemon.c       # function implementations
├── typechart.h     # type definitions
├── typechart.c     # type chart logic
├── test_typechart.c # battle/test scenarios with type effectiveness
└── README.md
```

---

## Pokémon Structure

```c
typedef struct {
    char name[NAME_SIZE];
    char types[MAX_TYPES][SIZE];
    char sex;

    Move moves[MAX_MOVES];

    int pokedex_code;
    int level;

    int hp;
    int speed;
    int attack;
    int defense;
    int sp_atk;
    int sp_def;

    double weight;
    double height;
} Pokemon;
```

---

## Move Structure

```c
typedef struct {
    char name[NAME_SIZE];
    PokemonType type;
    MoveCategory category;

    int power;
    int PP;
    float precision;
} Move;
```

---

## Example Output

```txt
No. 025 | Pikachu (♀)
Types: Electric

HP: 35
Attack: 55
Defense: 40
Sp. Attack: 50
Sp. Defense: 50
Speed: 90

Height: 40.00 cm
Weight: 6.00 kg

MOVES:

Thunderbolt        Quick Attack
Iron Tail          Electro Ball
```

---

## Compilation

Compile the project using GCC:

```bash
gcc main.c pokemon.c typechart.c -o pokemon
```

Run:

```bash
./pokemon
```

Compile the typechart battle test:

```bash
gcc test_typechart.c pokemon.c typechart.c -o test_typechart
```

Run the battle test:

```bash
./test_typechart
```

---

## Concepts Practiced

* Abstract Data Types (ADT)
* Encapsulation in C
* Struct manipulation
* Function modularization
* Arrays of structs
* String manipulation with `strcpy`
* Pointers and memory access
* Clean project organization

---

## Future Improvements

* Battle system enhancements
* More complete damage formula
* Item effects and status conditions
* Pokémon evolution system
* Random encounters
* Save/load system
* Dynamic move learning

---

## Author
Larissa Vilasboas Gondim | `@larissagondim`on github

Developed for programming and ADT practice in C.
