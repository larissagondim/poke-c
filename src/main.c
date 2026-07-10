#include <stdio.h>
#include "pokemon.h"
#include "typechart.h"
#include "parser.h"

int main() {
    Pokemon pokemons[1000];
    int count = 0;

    if (parse_pokemons("data/pokemon.txt", pokemons, 1000, &count) != 0) {
        printf("Error loading pokemon.txt\n");
        return 1;
    }

    printf("Loaded: %d pokemon(s)\n\n", count);
    // showcasing pokemon
    for (int i = 0; i < count; i++) {
        print_pokemon(&pokemons[i]);
        printf("\n");
    }

    return 0;
}