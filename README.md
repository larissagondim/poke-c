# ADT Pokémon

A simple Pokémon Abstract Data Type (ADT) project written in C.

This project simulates Pokémon data structures and battle mechanics using modular programming with `.h` and `.c` files.

---

## Features

* Pokémon and Move structure representation
* Pokémon and Move constructors
* Pokémon and Move information display
* Type effectiveness chart (18 types, full matrix)
* Attack damage adjusted by move category (Physical/Special/Status) and defending Pokémon types
* Speed-based turn priority: the faster Pokémon attacks first
* Fainted Pokémon cannot attack (`is_alive` check)
* Hit chance system based on move accuracy
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
├── main.c             # basic Pokémon/Move creation and display test
├── pokemon.h          # structs, constants, enums, prototypes
├── pokemon.c          # function implementations
├── typechart.h        # type chart prototypes
├── typechart.c        # type chart initialization and multiplier logic
├── test_typechart.c   # battle/test scenarios with type effectiveness and speed priority
├── Makefile           # build rules for all targets
├── .gitignore
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
    MoveCategory category; // PHYSICAL, SPECIAL or STATUS

    int power;
    int PP;
    float precision;
} Move;
```

---

## Available Functions

### `pokemon.h` / `pokemon.c`

| Function | Description |
|---|---|
| `create_pokemon(...)` | Creates and initializes a Pokémon structure |
| `create_move(...)` | Creates and initializes a Move structure |
| `attack_pokemon(attacker, defender, move)` | Executes an attack, applying damage based on category, stats, and type effectiveness |
| `run_turn(a, b, move_a, move_b)` | Simulates a full turn: compares speed to decide attack order, prevents fainted Pokémon from attacking |
| `is_alive(p)` | Checks if a Pokémon still has HP > 0 |
| `chance_hit(chance)` | Returns whether an attack hits based on its accuracy |
| `print_pokemon(p)` | Displays all Pokémon information |
| `print_move(m)` | Displays all Move information |

### `typechart.h` / `typechart.c`

| Function | Description |
|---|---|
| `init_type_chart()` | Initializes the 18×18 type effectiveness matrix |
| `calculate_type_multiplier(attack_type, defender_types)` | Returns the damage multiplier (0.0, 0.5, 1.0, 2.0, 4.0) based on type matchups |

---

## Battle Mechanics

### Damage Calculation

```
Physical:  damage = (move.power × attacker.attack)  / defender.defense
Special:   damage = (move.power × attacker.sp_atk)  / defender.sp_def
Status:    no damage
```

The damage is then multiplied by the type effectiveness multiplier.

### Type Effectiveness

| Multiplier | Message |
|---|---|
| 0.0× | "It had no effect!" |
| 0.5× | "It's not very effective..." |
| 1.0× | *(neutral, no message)* |
| 2.0× | "It's super effective!" |
| 4.0× | "It's super effective!" (dual-type weakness) |

### Speed Priority (`run_turn`)

```
run_turn(&pikachu, &gyarados, &thunderbolt, &waterfall)
       │
       ├─ pikachu.speed (90) > gyarados.speed (81)?  → Pikachu goes first
       │
       ├─ attack_pokemon(&pikachu, &gyarados, &thunderbolt)
       │
       ├─ is_alive(&gyarados)?  → if yes:
       │
       └─ attack_pokemon(&gyarados, &pikachu, &waterfall)
```

Returns `1` if Pokémon A won, `-1` if B won, `0` if neither fainted.

---

## Example Output

### Pokémon Info (`main.c`)

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
Thunderbolt         Quick Attack
Iron Tail           Electro Ball
```

### Speed Priority Battle (`test_typechart.c`)

```txt
Speed: Pikachu=90 | Gyarados=81

Pikachu used Thunderbolt! It's super effective!

Gyarados has fainted!
Resultado final -> Pikachu HP:35 | Gyarados HP:0
Vencedor: Pikachu
```

---

## Compilation

The project includes a `Makefile` to simplify building and running.

| Command | Description |
|---|---|
| `make` | Compiles the main binary (`poke`) |
| `make run` | Compiles and runs the main program |
| `make test` | Compiles and runs the battle test suite |
| `make clean` | Removes all generated binaries |

### Build and run the main program

```bash
make run
```

### Build and run the tests

```bash
make test
```

### Clean up

```bash
make clean
```

> **Manual compilation** (without Make):
> ```bash
> gcc -Wall -Wextra -std=c11 main.c pokemon.c typechart.c -o poke
> gcc -Wall -Wextra -std=c11 test_typechart.c pokemon.c typechart.c -o test_typechart
> ```

---

## Concepts Practiced

* Abstract Data Types (ADT)
* Encapsulation in C
* Struct manipulation
* Function modularization
* Arrays of structs
* String manipulation with `strcpy`
* Pointers and memory access
* Enum usage for types and categories
* Conditional logic for game mechanics
* Clean project organization

---

## Future Improvements

* STAB (Same-Type Attack Bonus)
* Critical hit system
* Status conditions (burn, paralyze, poison, sleep, freeze)
* Stat stages (−6 to +6 modifiers)
* Full battle loop (multiple turns until one side faints)
* Team battles (3v3 or 6v6)
* Trainer structure
* Reading Pokémon data from files
* Pokémon evolution system
* Save/load system

---

## Author
Larissa Vilasboas Gondim | `@larissagondim` on github

Developed for programming and ADT practice in C.
