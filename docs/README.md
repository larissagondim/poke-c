# ADT Pokémon

A Pokémon Abstract Data Type (ADT) project written in C.

This project models Pokémon data structures and battle mechanics using modular programming with `.h` and `.c` files, and loads real Pokémon data from the [PokéAPI](https://pokeapi.co/).

---

## Features

* Pokémon and Move structure representation
* **Data pipeline**: Python script fetches real data from PokéAPI → text file → C parser loads it at runtime
* Pokémon and Move constructors
* Pokémon and Move information display
* Type effectiveness chart (18 types, full matrix)
* Level-based damage formula (inspired by the official Pokémon games)
* Attack damage adjusted by move category (Physical/Special/Status) and defending Pokémon types
* **Status conditions**: Burn (1/16 HP per turn), Poison (1/8 HP per turn), Paralysis (speed halved, 25% chance to skip turn)
* Speed-based turn priority: the faster Pokémon attacks first (paralysis halves speed)
* **Full battle loop** (`run_battle`): continuous turns with random move selection until one Pokémon faints
* Fainted Pokémon cannot attack (`is_alive` check)
* Hit chance system based on move accuracy
* Organized modular architecture using ADTs
* Test suite with `assert()` validations
* Practice with:

  * Structs
  * Enums
  * Pointers
  * Dynamic organization of code
  * Header/source separation
  * File I/O and parsing

---

## Project Structure

```txt
poke-c/
│
├── include/                 # Header files
│   ├── pokemon.h            # structs, constants, enums, prototypes
│   ├── typechart.h          # type chart prototypes
│   └── parser.h             # file parser prototypes
│
├── src/                     # Source files
│   ├── main.c               # loads Pokémon from data file and displays them
│   ├── pokemon.c            # function implementations (battle, display, status effects)
│   ├── typechart.c          # type chart initialization and multiplier logic
│   └── parser.c             # parses pokemon.txt into Pokemon structs
│
├── data/                    # Data files
│   ├── fetch_pokemon.py     # Python script that fetches Pokémon data from PokéAPI
│   └── pokemon.txt          # generated data file (semicolon-delimited, one Pokémon per line)
│
├── test/                    # Test files
│   └── test_typechart.c     # battle/test scenarios with type effectiveness, speed priority, and asserts
│
├── docs/                    # Documentation
│   └── README.md
│
├── Makefile                 # build rules for all targets
└── .gitignore
```

---

## Data Pipeline

### 1. Fetching data (`data/fetch_pokemon.py`)

A Python script that uses the [PokéAPI](https://pokeapi.co/) to fetch real Pokémon data (stats, types, moves) and writes everything into `data/pokemon.txt`.

```bash
cd data
python3 fetch_pokemon.py
```

By default it fetches Pokémon #1 through #901. Each line in `pokemon.txt` is semicolon-delimited:

```
Name;Pokedex;HP;Atk;Def;SpAtk;SpDef;Speed;Type1;Type2;Height;Weight;Move1Name;Move1Type;Move1Cat;Move1Power;Move1PP;Move1Acc;...
```

### 2. Parsing data (`src/parser.c`)

The `parse_pokemons()` function reads `pokemon.txt` at runtime, tokenizes each line, and populates an array of `Pokemon` structs — including up to 4 embedded moves per Pokémon.

### 3. Main program (`src/main.c`)

Loads all Pokémon from the data file and prints their stats:

```c
Pokemon pokemons[1000];
int count = 0;

if (parse_pokemons("data/pokemon.txt", pokemons, 1000, &count) != 0) {
    printf("Error loading pokemon.txt\n");
    return 1;
}

for (int i = 0; i < count; i++) {
    print_pokemon(&pokemons[i]);
}
```

---

## Pokémon Structure

```c
typedef struct {
    char name[SIZE];
    PokemonType types[MAX_TYPES];
    char sex;
    Move moves[MAX_MOVES];
    int pokedex_code;
    int level;
    int current_hp;
    int max_hp;
    StatusCondition status;
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

## Enums

```c
typedef enum {
    PHYSICAL, SPECIAL, STATUS
} MoveCategory;

typedef enum {
    NORMAL, FIRE, WATER, GRASS, ELECTRIC, ICE,
    FIGHTING, POISON, GROUND, FLYING, PSYCHIC, BUG,
    ROCK, GHOST, DRAGON, DARK, STEEL, FAIRY, NONE_TYPE
} PokemonType;

typedef enum {
    STATUS_NONE, STATUS_BURN, STATUS_POISON, STATUS_PARALYSIS
} StatusCondition;
```

---

## Available Functions

### `include/pokemon.h` / `src/pokemon.c`

| Function | Description |
|---|---|
| `create_pokemon(...)` | Creates and initializes a Pokemon structure with all its attributes. |
| `create_move(...)` | Creates and initializes a Move structure. |
| `attack_pokemon(attacker, defender, move)` | Simulates an attack. Handles Physical/Special damage, Status moves (burn/poison/paralysis), type effectiveness, accuracy, and PP. Returns `1` if hit, `0` if missed, `-1` for invalid pointers, `-2` for no PP. |
| `run_turn(a, b, move_a, move_b)` | Runs a single turn: compares speed (halved if paralyzed) to decide attack order, applies status effects at end of turn. Returns `1` if A won, `-1` if B won, `0` for tie/no faints. |
| `run_battle(a, b)` | Runs a continuous battle loop — each turn randomly selects from available moves (PP > 0) until one Pokémon faints or both run out of moves. |
| `is_alive(p)` | Checks if a Pokémon is still alive (`current_hp > 0`). Returns `1` if alive, `0` if fainted, `-1` for invalid pointer. |
| `chance_hit(chance)` | Calculates hit probability based on move accuracy. Returns `1` if the attack hits, otherwise `0`. |
| `print_pokemon(p)` | Displays all Pokémon stats (HP as `current_hp/max_hp`), types, status condition, and moves. |
| `print_move(m)` | Displays all Move information (name, type, category, power, PP, accuracy). |

### `include/parser.h` / `src/parser.c`

| Function | Description |
|---|---|
| `parse_pokemons(filename, pokemons, max, count)` | Parses a semicolon-delimited file into an array of `Pokemon` structs (including up to 4 moves each). Returns `0` on success, `-1` if the file can't be opened. |

### `include/typechart.h` / `src/typechart.c`

| Function | Description |
|---|---|
| `init_type_chart()` | Initializes the 18×18 type effectiveness matrix. |
| `calculate_type_multiplier(attack_type, defender_types)` | Returns the damage multiplier based on the attacker's move type vs. the defender's type(s). Auto-initializes the chart if needed. |

---

## Battle Mechanics

### Damage Calculation

The formula is inspired by the official Pokémon games and uses the attacker's level:

```
Physical:  damage = ((2 × level / 5 + 2) × power × attack  / defense)  / 50 + 2
Special:   damage = ((2 × level / 5 + 2) × power × sp_atk  / sp_def)   / 50 + 2
Status:    no direct damage (applies status conditions instead)
```

The damage is then multiplied by the type effectiveness multiplier.

### Status Moves

Status moves apply conditions based on the move's type:

| Move Type | Effect Applied |
|---|---|
| Fire | Burn — deals 1/16 of `max_hp` per turn |
| Poison | Poison — deals 1/8 of `max_hp` per turn |
| Electric | Paralysis — halves speed, 25% chance to skip turn |

If the defender already has a status condition, the move fails.

### Type Effectiveness

| Multiplier | Message |
|---|---|
| 0.0× | "It had no effect!" |
| 0.5× | "It's not very effective..." |
| 1.0× | *(neutral, no message)* |
| 2.0× | "It's super effective!" |
| 4.0× | "It's super effective!" (dual-type weakness) |

### Speed Priority & Turn Order (`run_turn`)

```
run_turn(&pikachu, &gyarados, &thunderbolt, &waterfall)
       │
       ├─ Effective speed (halved if paralyzed)
       │  pikachu: 90  |  gyarados: 81
       │
       ├─ pikachu.speed > gyarados.speed  → Pikachu goes first
       │
       ├─ attack_pokemon(&pikachu, &gyarados, &thunderbolt)
       │
       ├─ is_alive(&gyarados)?  → if yes:
       │    └─ attack_pokemon(&gyarados, &pikachu, &waterfall)
       │
       ├─ apply_status_effects(&pikachu)   ← burn/poison damage at end of turn
       └─ apply_status_effects(&gyarados)
```

Returns `1` if Pokémon A won, `-1` if B won, `0` if neither fainted.

### Full Battle (`run_battle`)

```
run_battle(&pokemon_a, &pokemon_b)
       │
       ├─ Loop while both are alive:
       │    ├─ Randomly pick a move with PP > 0 for each Pokémon
       │    ├─ If either has no usable moves → break
       │    └─ run_turn(a, b, move_a, move_b)
       │
       └─ Declare winner (or tie)
```

---

## Example Output

### Loading from file (`main.c`)

```txt
Carregados: 481 pokemon(s)

No. 001 | Bulbasaur (♂)

Types: Grass Poison

HP: 45/45
Attack: 49
Defense: 49
Sp. Attack: 65
Sp. Defense: 65
Speed: 45

Height: 0.70 cm
Weight: 6.90 kg

MOVES:
solar-beam          power-whip
worry-seed          synthesis
```

### Speed Priority Battle (`test_typechart.c`)

```txt
Speed: Pikachu=90 | Gyarados=81

Pikachu used Thunderbolt! It's super effective!

Gyarados has fainted!
Final results -> Pikachu HP:35 | Gyarados HP:0
```

---

## Compilation

The project includes a `Makefile` to simplify building and running.

| Command | Description |
|---|---|
| `make` | Compiles the main binary (`pokemon`) |
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
> gcc -Wall -Wextra -Iinclude src/main.c src/pokemon.c src/typechart.c src/parser.c -o pokemon
> gcc -Wall -Wextra -Iinclude test/test_typechart.c src/pokemon.c src/typechart.c -o test_typechart
> ```

---

## Concepts Practiced

* Abstract Data Types (ADT)
* Encapsulation in C
* Struct manipulation
* Function modularization
* Arrays of structs
* String manipulation with `strcpy` and `strncpy`
* Pointers and memory access
* Enum usage for types, categories, and status conditions
* Conditional logic for game mechanics
* File I/O and text parsing (`fopen`, `fgets`, `strtok`)
* API consumption with Python (`requests` + PokéAPI)
* Clean project organization
* Automated tests with `assert()`

---

## Future Improvements

* Critical hit system
* Stat stages (−6 to +6 modifiers)
* Team battles (3v3 or 6v6)
* Trainer structure
* Pokémon evolution system
* Save/load system
* Interactive move selection (player input during battle)
* Frontend (WebAssembly, HTTP server, or JS rewrite)

---

## Author
Larissa Vilasboas Gondim | `@larissagondim` on github

Developed for programming and ADT practice in C.
