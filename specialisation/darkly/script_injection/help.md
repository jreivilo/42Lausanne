# Injection de Script dans le Feedback

## Problématique
Il est possible de soumettre un script malveillant via le formulaire de feedback sur le site, conduisant à une attaque de type **Cross-Site Scripting (XSS)**.

### Exemple de script :
```html
<script>alert('XSS')</script>


## Solution
1. **Filtrer les entrées utilisateur** : Valider et nettoyer les données avant de les afficher.
2. **Échapper les caractères spéciaux** : Convertir les caractères spéciaux en entités HTML.

Dans notre cas, le site le fait déjà mais écrire "script" dans le feedback nous donne le flag.