# Vulnérabilité : MIME Spoofing

## Description
La faille MIME Spoofing consiste à faire croire à un serveur qu’un fichier uploadé est d’un certain type (par exemple une image), alors qu’il ne l’est pas réellement. Cela peut permettre de téléverser des fichiers malveillants tels que des scripts exécutables.

## Exploitation
Un attaquant peut exploiter cette faille en modifiant le type MIME du fichier via des outils comme `curl`, tout en envoyant un fichier contenant du code malveillant. Par exemple, un fichier `.php` peut être déguisé en image (`image/jpeg`) et exécuté si le serveur est vulnérable.

## Correctifs
1. **Validation stricte du contenu** : Vérifier le contenu réel des fichiers uploadés (par exemple, vérifier la structure interne des images).
2. **Limiter les extensions autorisées** : Refuser les fichiers contenant des extensions ou types potentiellement dangereux.
3. **Désactiver l’exécution** : Configurer le serveur pour empêcher l'exécution des fichiers uploadés dans les répertoires de destination.
4. **Renommer les fichiers uploadés** : Remplacer les extensions dangereuses par des extensions inoffensives (e.g., `.txt`).
