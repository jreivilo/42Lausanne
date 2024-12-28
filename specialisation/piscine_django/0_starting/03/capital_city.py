import sys

# Dictionnaires fournis
states = {
    "Oregon": "OR",
    "Alabama": "AL",
    "New Jersey": "NJ",
    "Colorado": "CO"
}

capital_cities = {
    "OR": "Salem",
    "AL": "Montgomery",
    "NJ": "Trenton",
    "CO": "Denver"
}

# Fonction principale
def main():
    # Vérifier le nombre d'arguments
    if len(sys.argv) != 2:
        return

    # Extraire l'état depuis les arguments
    state = sys.argv[1]

    # Chercher le code de l'état
    state_code = states.get(state)
    
    # Vérifier si le code de l'état existe
    if state_code:
        # Chercher la capitale correspondante
        capital = capital_cities.get(state_code)
        if capital:
            print(capital)
            return

    # Si aucun résultat n'est trouvé
    print("Unknown state")

if __name__ == "__main__":
    main()
