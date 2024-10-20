
# Exploitation d'une Injection SQL via la barre de recherche d'images

## Étape 1 : Exécution de la première commande

La commande suivante est entrée dans la barre de recherche d'images :
```
1 OR 1=1 UNION SELECT table_name, column_name FROM information_schema.columns
```

### Explication
- **`1 OR 1=1`** : Cette partie crée une condition toujours vraie, ce qui permet d'exploiter la logique SQL de l'application pour retourner des données supplémentaires.
- **`UNION SELECT`** : L'opérateur `UNION` permet de combiner les résultats de deux requêtes SQL différentes. Ici, il est utilisé pour récupérer des informations d'autres tables.
- **`information_schema.columns`** : Cette partie de la requête interroge une table spéciale dans la base de données, qui contient les noms de toutes les tables et colonnes. Cela permet à l'attaquant de lister les tables et colonnes disponibles dans la base de données.

#### Résultat
On tombre sur la table `list_images` qui contient les colonnes `id`, `title`, `url`, et `comment`.

(En vrai faut essayer plein de table aha)

## Étape 2 : Exécution de la seconde commande

Ensuite, l'attaquant utilise cette commande SQL pour obtenir des informations supplémentaires :
```
1 OR 1=1 UNION SELECT title,comment from list_images

(Vu que la requete renvie que 2 col, on peut tester que 2 col a la fois)
```

### Explication
- **`list_images`** : Cette table semble contenir les images affichées dans l'application. L'attaquant tente ici de récupérer les colonnes `title` (titre) et `comment` (commentaire) de cette table pour trouver des informations sensibles.
  
#### Résultat
La requête renvoie :
```
ID: 1 OR 1=1 UNION SELECT title,comment from list_images
Title: If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46
Url : Hack me
```
Cela révèle une clé MD5 : `1928e8083cf461a51303633093573c46` ainsi qu'une instruction : déchiffrer le hash en MD5, puis utiliser SHA256 pour obtenir le flag.

## Étape 3 : Décodage du hash MD5 et calcul du SHA256

1. **MD5** : En utilisant un décodeur MD5, l'attaquant découvre que le hash MD5 `1928e8083cf461a51303633093573c46` correspond au mot **"albatroz"**.
   
2. **SHA256** : Ensuite, l'attaquant applique le hash SHA256 sur "albatroz", et trouve la valeur correspondante, qui est le flag final.

### Conclusion
Cette exploitation montre une faille critique d'injection SQL dans la barre de recherche. L'attaquant a pu accéder aux métadonnées de la base de données, extraire des informations sensibles, et, en utilisant des techniques de hachage MD5 et SHA256, obtenir le flag. Cela met en évidence l'importance de valider et protéger les entrées utilisateurs pour empêcher des attaques de ce type. **Juste protéger aussi le backend contre les injections SQL en utilisant des requetes préparées.**
