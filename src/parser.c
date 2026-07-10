#define _DEFAULT_SOURCE
#include "parser.h"

#define LINE_SIZE 1024

// converts a type name string (e.g. "ELECTRIC") into its PokemonType enum value
static PokemonType string_to_type(const char *s) {
    if (strcmp(s, "NORMAL") == 0)   return NORMAL;
    if (strcmp(s, "FIRE") == 0)     return FIRE;
    if (strcmp(s, "WATER") == 0)    return WATER;
    if (strcmp(s, "GRASS") == 0)    return GRASS;
    if (strcmp(s, "ELECTRIC") == 0) return ELECTRIC;
    if (strcmp(s, "ICE") == 0)      return ICE;
    if (strcmp(s, "FIGHTING") == 0) return FIGHTING;
    if (strcmp(s, "POISON") == 0)   return POISON;
    if (strcmp(s, "GROUND") == 0)   return GROUND;
    if (strcmp(s, "FLYING") == 0)   return FLYING;
    if (strcmp(s, "PSYCHIC") == 0)  return PSYCHIC;
    if (strcmp(s, "BUG") == 0)      return BUG;
    if (strcmp(s, "ROCK") == 0)     return ROCK;
    if (strcmp(s, "GHOST") == 0)    return GHOST;
    if (strcmp(s, "DRAGON") == 0)   return DRAGON;
    if (strcmp(s, "DARK") == 0)     return DARK;
    if (strcmp(s, "STEEL") == 0)    return STEEL;
    if (strcmp(s, "FAIRY") == 0)    return FAIRY;
    return NONE_TYPE;
}

// converts a category name string (e.g. "PHYSICAL") into its MoveCategory enum value
static MoveCategory string_to_category(const char *s) {
    if (strcmp(s, "PHYSICAL") == 0) return PHYSICAL;
    if (strcmp(s, "SPECIAL") == 0)  return SPECIAL;
    return STATUS;
}

// safely copies a string into a fixed-size buffer, always null-terminating
static void safe_copy(char *dest, const char *src, size_t dest_size) {
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

int parse_pokemons(const char *filename, Pokemon *pokemons, int max, int *count) {
    *count = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nErro: nao foi possivel abrir o arquivo '%s'.\n", filename);
        return -1;
    }

    char line[LINE_SIZE];

    while (*count < max && fgets(line, LINE_SIZE, file) != NULL) {

        // remove trailing newline, if present
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '\0')
            continue; // skip empty lines

        char name_buf[SIZE];
        char type0_buf[SIZE];
        char type1_buf[SIZE];
        int pokedex_code, hp, attack, defense, sp_atk, sp_def, speed;
        double height, weight;

        char *rest = line; // strsep advances 'rest' as it consumes the line
        char *token = strsep(&rest, ";");
        safe_copy(name_buf, token, sizeof(name_buf));

        token = strsep(&rest, ";"); pokedex_code = atoi(token);
        token = strsep(&rest, ";"); hp       = atoi(token);
        token = strsep(&rest, ";"); attack   = atoi(token);
        token = strsep(&rest, ";"); defense  = atoi(token);
        token = strsep(&rest, ";"); sp_atk   = atoi(token);
        token = strsep(&rest, ";"); sp_def   = atoi(token);
        token = strsep(&rest, ";"); speed    = atoi(token);

        token = strsep(&rest, ";"); safe_copy(type0_buf, token, sizeof(type0_buf));
        token = strsep(&rest, ";"); safe_copy(type1_buf, token, sizeof(type1_buf));

        token = strsep(&rest, ";"); height = strtod(token, NULL);
        token = strsep(&rest, ";"); weight = strtod(token, NULL);

        PokemonType types[MAX_TYPES] = {
            string_to_type(type0_buf),
            string_to_type(type1_buf)
        };

        Pokemon p = create_pokemon(
            name_buf, types, 'M', pokedex_code, 1,
            hp, attack, defense, sp_atk, sp_def, speed,
            height, weight
        );

        // moves are embedded 6 fields at a time: name;type;category;power;pp;accuracy
        for (int i = 0; i < MAX_MOVES; i++) {
            char move_name_buf[NAME_SIZE];
            char move_type_buf[SIZE];
            char move_category_buf[SIZE];
            int power, pp;
            float accuracy;

            token = strsep(&rest, ";");
            if (token == NULL) break; // no more moves in this line

            safe_copy(move_name_buf, token, sizeof(move_name_buf));

            token = strsep(&rest, ";"); safe_copy(move_type_buf, token, sizeof(move_type_buf));
            token = strsep(&rest, ";"); safe_copy(move_category_buf, token, sizeof(move_category_buf));
            token = strsep(&rest, ";"); power = atoi(token);
            token = strsep(&rest, ";"); pp = atoi(token);
            token = strsep(&rest, ";"); accuracy = (float)atof(token);

            if (move_name_buf[0] == '\0')
                continue; // empty move placeholder, skip

            p.moves[i] = create_move(
                move_name_buf,
                string_to_type(move_type_buf),
                string_to_category(move_category_buf),
                power, pp, accuracy
            );
        }

        pokemons[*count] = p;
        (*count)++;
    }

    fclose(file);
    return 0;
}