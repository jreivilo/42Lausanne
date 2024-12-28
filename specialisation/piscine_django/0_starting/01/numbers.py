# numbers.py

def main():
    try:
        # Ouvrir le fichier numbers.txt en mode lecture
        with open('numbers.txt', 'r') as file:
            # Lire le contenu du fichier
            content = file.read()
            # Diviser les nombres en une liste, en utilisant la virgule comme séparateur
            numbers = content.split(',')
            # Afficher chaque nombre sur une ligne séparée
            for number in numbers:
                print(number.strip())
    except FileNotFoundError:
        print("Erreur : Le fichier numbers.txt est introuvable.")
    except Exception as e:
        print(f"Une erreur est survenue : {e}")

# Point d'entrée du script
if __name__ == "__main__":
    main()
