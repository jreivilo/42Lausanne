def main():
    d = [
        ('Hendrix', '1942'),
        ('Allman', '1946'),
        ('King', '1925'),
        ('Clapton', '1945'),
        ('Johnson', '1911'),
        ('Berry', '1926'),
        ('Vaughan', '1954'),
        ('Cooder', '1947'),
        ('Page', '1944'),
        ('Richards', '1943'),
        ('Hammett', '1962'),
        ('Cobain', '1967'),
        ('Garcia', '1942'),
        ('Beck', '1944'),
        ('Santana', '1947'),
        ('Ramone', '1948'),
        ('White', '1975'),
        ('Frusciante', '1970'),
        ('Thompson', '1949'),
        ('Burton', '1939')
    ]

    # Création du dictionnaire avec l'année comme clé et les noms comme valeurs
    year_to_musicians = {}
    for name, year in d:
        if year not in year_to_musicians:
            year_to_musicians[year] = []
        year_to_musicians[year].append(name)

    # Affichage du dictionnaire avec le format demandé
    for year, names in sorted(year_to_musicians.items()):
        print(f"{year} : {' '.join(names)}")

if __name__ == "__main__":
    main()
