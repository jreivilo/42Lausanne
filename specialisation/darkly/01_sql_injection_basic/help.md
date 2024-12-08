
# Injection SQL via une search bar pour image

La faille est due au fait que l'input va directement dans une requête SQL.  
C'est une search bar pour des images qui attend un chiffre, l'index de l'image.  

Les injections SQL (SQLi) fonctionnent en manipulant la logique de la commande SQL du backend pour retourner plus d'informations que prévu.  
Ici, lorsqu'on met "1" dans la barre de recherche et qu'on clique sur *enter*, le serveur va lancer la requête suivante (ou similaire, selon la DB) vers la base de données et renvoyer le résultat (les infos par rapport à une image, au client).  

```sql  
SELECT id, title, url FROM list_images  
```  

### Exemple d'injection  

```sql  
1 OR 1=1  
```  

Cela signifie : renvoie la première photo ou tout autre résultat si 1 est égal à 1. Cet opérateur conditionnel est toujours vrai, donc tous les résultats sont renvoyés.  

### Pour aller plus loin  

Si on veut accéder à plus d'infos dans la DB, on doit découvrir le nom des tables et des colonnes, ainsi que rajouter des résultats après ceux qu'on a déjà.  

Avec `UNION`, on peut coller les résultats d'une autre requête SQL à la première. C'est une sorte d'extension qui rajoute les résultats à la fin.  
`SELECT` est le début d'une nouvelle requête pour renvoyer plus d'infos.  

Ici, on peut faire :  

```sql  
1 UNION SELECT table_name, column_name FROM information_schema.columns  
```  

Cela va renvoyer les détails de la première image **ET** le nom de chaque colonne et table dans la DB. La table `information_schema.columns` contient ces informations qui décrivent la DB. Pour trouver le nom de cette table-là, on se penche sur la documentation de la DB dès qu'une erreur dans nos essais précédents nous indique avec quelle base de données nous travaillons.  

Ayant ainsi acquis la "topologie" de la base de données, nous pouvons maintenant lancer des requêtes qui récupèrent tout le contenu, de la manière suivante :  

```sql  
1 UNION SELECT colonne1, colonne2 FROM nom_de_table  
```  

Après exploration, on tombe sur la table `list_images`, qui contient les colonnes `id`, `title`, `url` et `comment`.  

Avec l'injection SQL suivante, on récupère des commentaires sur les images, l'un d'entre eux contenant le flag :  

```sql  
1 OR 1=1 UNION SELECT title, comment FROM list_images  
```  

(Vu que la requête renvoie seulement 2 colonnes, on peut tester seulement 2 colonnes à la fois.)  

#### Résultat  

La requête renvoie ce résultat parmi plusieurs autres :  

```
ID: 1 OR 1=1 UNION SELECT title, comment FROM list_images  
Title: If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46  
Url: Hack me  
```  

Cela révèle une clé MD5 : `1928e8083cf461a51303633093573c46`, ainsi qu'une instruction : déchiffrer le hash en MD5, puis utiliser SHA256 pour obtenir le flag.  

1. **MD5** : En utilisant un décodeur MD5, l'attaquant découvre que le hash MD5 `1928e8083cf461a51303633093573c46` correspond au mot **"albatroz"**.  
2. **SHA256** : Ensuite, l'attaquant applique le hash SHA256 sur "albatroz" et trouve la valeur correspondante, qui est le flag final.  

### Conclusion  

Cette exploitation montre une faille critique d'injection SQL dans la barre de recherche.  
L'attaquant a pu accéder aux métadonnées de la base de données, extraire des informations sensibles, et, en utilisant des techniques de hachage MD5 et SHA256, obtenir le flag.  

Cela met en évidence l'importance de valider et protéger les entrées utilisateur pour empêcher des attaques de ce type.  

**Protéger le backend contre les injections SQL consiste principalement à utiliser des requêtes préparées (parameterized queries).**  
Cela signifie que les inputs des utilisateurs sont strictement contrôlés : ils sont pré-formatés et traités séparément de la commande SQL. Ainsi, toute tentative de manipulation est neutralisée avant l'insertion dans la requête.  
