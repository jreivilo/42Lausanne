# Path traversal

La navigation des chemins est un type de vulnérabilité qui permet d'accéder à des fichiers et dossiers qui ne sont pas censés être accessibles aux utilisateurs.

Dans ce site, les pages sont chargées via le paramètre URL page, qui indique le chemin vers un fichier HTML et/ou JS, probablement. On peut "exploiter" cet input en essayant de remonter dans des dossiers parents sur le serveur, pour accéder à /etc/passwd, un fichier qui ne requiert pas de permissions spécifiques pour être lu.

Quand on fait ?page=../, le site renvoie une alerte nous disant "nope", et plus on en rajoute, plus les messages indiquent que l'on se rapproche, jusqu'à avoir "You can DO it". À ce moment-là, on ajoute ../etc/passwd, et une alerte nous donne le flag, car cela correspond à une lecture des mots de passe du serveur.

![alt text](image.png)

Comment se protéger contre ça ? Plusieurs solutions :

Restreindre les permissions pour bloquer la lecture des fichiers sensibles tels que /etc/passwd.
- Utiliser chroot ou des "jails", qui sont des outils permettant "d'enfermer" le user du serveur dans un dossier, sans visibilité ni permissions sur les niveaux supérieurs.
- faire un enum avec les chemins autorisés, et toujours vérifier que l'input utilisateur correspond à l'un d'eux.
