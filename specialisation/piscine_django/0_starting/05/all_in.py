import sys

def main():
    # Dictionnaire des capitales par État
    states = {
        "Oregon": "Salem",
        "Alabama": "Montgomery",
        "New Jersey": "Trenton",
        "Colorado": "Denver"
    }

    # Dictionnaire inversé pour rechercher l'État à partir de la capitale
    capitals = {capital: state for state, capital in states.items()}

    if len(sys.argv) != 2:
        return

    # Récupérer l'argument (liste des expressions)
    input_string = sys.argv[1]

    # Vérifier s'il y a des virgules successives
    if ",," in input_string:
        return

    # Diviser la chaîne en expressions et nettoyer chaque expression
    expressions = [expr.strip().lower() for expr in input_string.split(",")]

    results = []

    for expr in expressions:
        if not expr:  # Ignorer les chaînes vides
            continue

        # Recherche de l'État ou de la capitale
        state_name = next((state for state in states if state.lower() == expr), None) #lower() fait en sorte que la recherche ne soit pas sensible aux majuscules
        capital_name = next((capital for capital in capitals if capital.lower() == expr), None)

        if state_name:
            results.append(f"{state_name} is a state")
        elif capital_name:
            results.append(f"{capital_name} is the capital of {capitals[capital_name]}")
        else:
            results.append(f"{expr.capitalize()} is neither a capital city nor a state")

    # Afficher les résultats
    print("\n".join(results))

if __name__ == "__main__":
    main()