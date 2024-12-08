# Analyse de la Faille et Solutions

## Faille
Une attaque par force brute cible une page de connexion vulnérable :
- **Mots de passe faibles**.
- **Pas de protection** (CAPTCHA, limitations).

## Exploitation
Le script teste automatiquement des combinaisons utilisateur/mot de passe et identifie les succès via des indices dans les réponses.

## Solutions
1. Bloquer après plusieurs échecs.
2. Limiter les tentatives par IP.
3. Imposer des mots de passe forts.
4. Ajouter un CAPTCHA.
5. Activer l'authentification à deux facteurs (MFA).
"""