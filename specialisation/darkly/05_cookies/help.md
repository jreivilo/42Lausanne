
# Vulnérabilité liée aux Cookies et Comment la Corriger

## Description de la Vulnérabilité

Une vulnérabilité liée aux cookies survient lorsque des informations sensibles, comme les rôles des utilisateurs, sont stockées dans des cookies sans vérification côté serveur. Un attaquant peut manipuler ces cookies pour obtenir des privilèges élevés ou accéder à des informations confidentielles.

### Exemple d'Exploitation

Un cookie nommé `I_am_admin` avec une valeur hashée `68934a3e9455fa72420237eb05902327` a été découvert, correspondant au mot **"false"** (non-admin). En modifiant ce cookie en la valeur MD5 du mot **"true"** (`b326b5062b2f0e69046810717534cb09`), l'attaquant peut obtenir des privilèges d'administration.

### Étapes d'Exploitation :
1. Ouvrir l'extension **Edit This Cookie** (ou utiliser les outils de développement du navigateur).
2. Localiser le cookie `I_am_admin` et modifier sa valeur par la chaîne `b326b5062b2f0e69046810717534cb09`.
3. Rafraîchir la page et accéder aux privilèges d'administration.

### Risques :
- **Escalade de privilèges** : Un utilisateur non-admin pourrait obtenir un accès admin.
- **Accès à des informations sensibles** : Possibilité de lire ou modifier des données critiques.
- **Actions non-autorisées** : Un attaquant pourrait exécuter des actions réservées aux administrateurs.

## Solution

1. **Ne pas stocker les rôles utilisateurs dans des cookies** : Les rôles et privilèges doivent être gérés côté serveur, et non par des cookies qui peuvent être modifiés par le client.

2. **Utiliser des cookies signés** : Si des informations doivent être stockées dans des cookies, utiliser des cookies signés cryptographiquement pour éviter toute modification.

3. **Vérifier les permissions côté serveur** : Toujours valider les actions sensibles côté serveur, en s'assurant que l'utilisateur a bien les droits nécessaires pour chaque action.

### Conclusion

En évitant de stocker des informations sensibles dans les cookies et en mettant en place une gestion sécurisée des permissions, vous pouvez protéger votre application contre les attaques d'escalade de privilèges.
