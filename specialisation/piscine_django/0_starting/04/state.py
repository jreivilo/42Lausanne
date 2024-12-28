import sys

def main():
    # Dictionnaire des capitales par État
    states = {
        "Oregon": "Salem",
        "Alabama": "Montgomery",
        "New Jersey": "Trenton",
        "Colorado": "Denver"
    }

    if len(sys.argv) != 2:
        return
    
    # Dictionnaire inversé pour rechercher l'État à partir de la capitale
    capitals = {capital: state for state, capital in states.items()}

    # Récupération de l'argument (nom de la capitale)
    capital_name = sys.argv[1]

    # Recherche de l'État correspondant à la capitale
    state_name = capitals.get(capital_name, "Unknown capital city") # Si la capitale n'est pas trouvée, on affiche "Unknown capital city"

    print(state_name)

if __name__ == "__main__":
    main()
