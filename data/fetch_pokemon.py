import requests
import time

def get_pokemon(name_or_id):
    # getting pokemon basic info
    r = requests.get(f'https://pokeapi.co/api/v2/pokemon/{name_or_id}/')
    data = r.json()
    # getting stats and types from the pokemon, adjusting height and weight
    stats = {s['stat']['name']: s['base_stat'] for s in data['stats']}
    types = [t['type']['name'] for t in data['types']]

    return {
        "name": data['name'],
        "pokedex_code": data['id'],
        "hp": stats['hp'],
        "attack": stats['attack'],
        "defense": stats['defense'],
        "sp_atk": stats['special-attack'],
        "sp_def": stats['special-defense'],
        "speed": stats['speed'],
        "types": types,
        "height": data['height'] / 10,
        "weight": data['weight'] / 10,
    }


def get_move(move_name):
    r = requests.get(f'https://pokeapi.co/api/v2/move/{move_name}/')
    data = r.json()

    power = data['power'] if data['power'] is not None else 0
    accuracy = data['accuracy'] if data['accuracy'] is not None else 100  # moves that always hit come as null
    category = data['damage_class']['name']  # "physical" | "special" | "status"

    return {
        "name": data['name'],
        "type": data['type']['name'].upper(),
        "category": category.upper(),
        "power": power,
        "pp": data['pp'],
        "accuracy": accuracy,
    }


def format_types(types):
    # always fills two slots, if not enough types, it will fill with "NONE_TYPE"
    t = [x.upper() for x in types]
    while len(t) < 2:
        t.append("NONE_TYPE")
    return t


def get_top_moves(pokemon_data, limit=4):
    # tries several version_groups until it finds one with level-up data
    version_groups_fallback = ["scarlet-violet", "sword-shield", "sun-moon", "red-blue"]

    candidates = []
    for vg in version_groups_fallback:
        candidates = []
        for m in pokemon_data['moves']:
            for detail in m['version_group_details']:
                if (detail['version_group']['name'] == vg
                        and detail['move_learn_method']['name'] == 'level-up'):
                    candidates.append((detail['level_learned_at'], m['move']['name']))
        if candidates:
            break

    candidates.sort(key=lambda x: x[0], reverse=True)  # highest level first

    names = []
    for _, name in candidates:
        if name not in names:
            names.append(name)
        if len(names) == limit:
            break
    return names


def build_pokemon_entry(name_or_id):
    r = requests.get(f'https://pokeapi.co/api/v2/pokemon/{name_or_id}/')
    raw = r.json()

    stats = {s['stat']['name']: s['base_stat'] for s in raw['stats']}
    types = format_types([t['type']['name'] for t in raw['types']])
    move_names = get_top_moves(raw)

    moves = [get_move(m) for m in move_names]
    while len(moves) < 4:  # garante sempre 4, mesmo que a API retorne menos
        moves.append({"name": "", "type": "NONE_TYPE", "category": "STATUS", "power": 0, "pp": 0, "accuracy": 0})

    pokemon = {
        "name": raw['name'].capitalize(),
        "pokedex_code": raw['id'],
        "hp": stats['hp'],
        "attack": stats['attack'],
        "defense": stats['defense'],
        "sp_atk": stats['special-attack'],
        "sp_def": stats['special-defense'],
        "speed": stats['speed'],
        "types": types,
        "height": raw['height'] / 10,
        "weight": raw['weight'] / 10,
        "moves": moves,
    }
    return pokemon


def pokemon_to_line(p):
    base = [
        p["name"], p["pokedex_code"], p["hp"], p["attack"], p["defense"],
        p["sp_atk"], p["sp_def"], p["speed"], p["types"][0], p["types"][1],
        p["height"], p["weight"],
    ]
    move_fields = []
    for m in p["moves"]:
        move_fields += [m["name"], m["type"], m["category"], m["power"], m["pp"], m["accuracy"]]
    return ";".join(str(x) for x in base + move_fields)


def save_all(names, path="pokemon.txt"):
    with open(path, "w", encoding="utf-8") as f:
        for n in names:
            try:
                entry = build_pokemon_entry(n)
                f.write(pokemon_to_line(entry) + "\n")
                f.flush()  # guarantees writing on disk even if it crashes later
                print(f"Saved: {entry['name']}")
            except Exception as e:
                print(f"Error while fetching '{n}': {e}")
            time.sleep(0.67)  # pause between requests to avoid rate limiting


if __name__ == "__main__":
    save_all(range(1, 902))


    # usage example to generate the file with several pokemon
    # save_all(["pikachu", "charmander", "bulbasaur", "squirtle"])