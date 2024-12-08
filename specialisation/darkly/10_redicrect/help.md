
# Redirection Ouverte : Vulnérabilité et Solution

## Description de la Problématique
Une redirection ouverte se produit quand un utilisateur est redirigé vers une URL externe sans contrôle adéquat. Cela peut mener à des attaques de phishing ou des redirections malveillantes.

Exemple de code vulnérable :
```html
<a href="index.php?page=redirect&site=facebook"></a>
```
Un attaquant peut modifier le paramètre `site` pour diriger l’utilisateur vers un site malveillant :
```html
index.php?page=redirect&site=malicious-site.com
```

### Risques :
1. **Phishing** : Redirection vers des sites frauduleux.
2. **Logiciels malveillants** : Exposition à des contenus dangereux.
3. **Perte de confiance** : Les utilisateurs peuvent ne plus faire confiance au site légitime.

## Solution

1. **Valider l’URL côté serveur** : Autoriser uniquement les domaines de confiance.

2. **Utiliser HTTPS** : Garantir des connexions sécurisées pour les redirections.

### Conclusion
Corriger les redirections ouvertes est simple : valider les URL et protéger les utilisateurs contre les attaques malveillantes.
