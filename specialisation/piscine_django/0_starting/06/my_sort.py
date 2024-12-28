def main():
	d = {
		'Hendrix': '1942',
		'Allman': '1946',
		'King': '1925',
		'Clapton': '1945',
		'Johnson': '1911',
		'Berry': '1926',
		'Vaughan': '1954',
		'Cooder': '1947',
		'Page': '1944',
		'Richards': '1943',
		'Hammett': '1962',
		'Cobain': '1967',
		'Garcia': '1942',
		'Beck': '1944',
		'Santana': '1947',
		'Ramone': '1948',
		'White': '1975',
		'Frusciante': '1970',
		'Thompson': '1949',
		'Burton': '1939',
	}

	# Trier par année croissante, puis par ordre alphabétique des noms
	# On suppose que 'd' est un dictionnaire
	# sorted() trie les éléments du dictionnaire 'd' en utilisant une fonction de clé personnalisée
	sorted_musicians = sorted(
		d.items(),  # d.items() retourne une vue sur les paires (clé, valeur) du dictionnaire
		key=lambda item: (item[1], item[0])  # La fonction de clé trie d'abord par valeur (item[1]), puis par clé (item[0])
	)

	# Afficher uniquement les noms, un par ligne
	for musician, _ in sorted_musicians:
		print(musician)

if __name__ == "__main__":
	main()
