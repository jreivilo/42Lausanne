# Exposition de `.htpasswd` via `robots.txt`

## Problématique
Le fichier `robots.txt` contient une directive `Disallow` qui expose un chemin vers un fichier sensible `.htpasswd`, accessible publiquement. Ce fichier contient un identifiant chiffré : root:437394baff5aa33daa618be47b75cb49

Après analyse, le hash MD5 révèle le mot de passe en clair : `qwerty123@`.

### Risques
- **Exposition d'identifiants sensibles**.
- **Accès non autorisé à des comptes**.
- **Utilisation de l'algorithme MD5, peu sécurisé**.

## Solutions
1. **Retirer les fichiers sensibles du `robots.txt`**.
2. **Restreindre l'accès aux fichiers sensibles** via des permissions serveur.
3. **Utiliser un hachage sécurisé** comme bcrypt ou Argon2 pour stocker les mots de passe.

### Conclusion
L'exposition de fichiers sensibles via `robots.txt` est une faille critique qui nécessite une correction rapide pour éviter des compromissions.

