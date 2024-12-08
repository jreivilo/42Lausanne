# Injection de Script dans le Feedback

## Problématique
Il est possible de soumettre un script malveillant via le formulaire de feedback sur le site, conduisant à une attaque de type **Cross-Site Scripting (XSS)**.

Ces attaques fonctionnent en envoyant via un input utilisateur, du contenu qui sera afficher sur le site et qui contient du javascript qui sera lancer quand le user ouvre la page contenant cet input (un commentaire par example).
Selon le site il faut adapter la maniere d'inserer le code, pour qu'il puisse bien s'executer.

### Exemple de script :
```html
<script>alert('XSS')</script>
```

## Solution
1. **Filtrer les entrées utilisateur** : Valider et nettoyer les données avant de les afficher.
2. **Échapper les caractères spéciaux** : Convertir les caractères spéciaux en entités HTML.

Dans notre cas, le site le fait déjà mais écrire "script" dans le feedback nous donne le flag.
