
# Vulnérabilité liée aux Sélecteurs HTML et Comment la Corriger

## Description de la Vulnérabilité

Le code suivant contient une liste déroulante `<select>` qui permet de choisir une valeur :
```html
<select name="valeur" onchange="javascript:this.form.submit();">
    <option value="1">1</option>
    <option value="2">2</option>
    <option value="3">3</option>
    <option value="4">4</option>
    <option value="5">5</option>
    <option value="6">6</option>
    <option value="7">7</option>
    <option value="8">8</option>
    <option value="9">9</option>
    <option value="10">10</option>
</select>
```

Un attaquant peut facilement modifier les valeurs de cette sélection en utilisant les outils de développement de son navigateur (comme "Inspecter l'élément") pour soumettre une valeur qui n'est pas prévue (par exemple, une valeur de 100 ou -1). Si le serveur ne vérifie pas ces valeurs, l'application peut être vulnérable à des attaques, comme l'exécution de commandes non-autorisées ou la manipulation des données.

### Exploitation Potentielle

Un attaquant peut modifier la valeur soumise par cette liste déroulante à quelque chose d'inattendu, comme :
```html
<option value="100">100</option>
```
Ou même une valeur négative, pour tester les limites du système :
```html
<option value="-1">-1</option>
```

### Risques :
- **Modification des données** : L'attaquant peut soumettre des valeurs hors des limites prévues, perturbant le fonctionnement normal de l'application.
- **Exécution non sécurisée** : Cela peut mener à des bugs ou à des comportements imprévus si le serveur ne gère pas correctement les valeurs modifiées.

## Solution

### 1. **Vérification côté serveur**
Il est indispensable de vérifier la valeur soumise côté serveur pour s'assurer qu'elle correspond à une valeur attendue (dans ce cas, entre 1 et 10). Ne vous fiez jamais aux données envoyées par le client.


### 2. **Utilisation de la validation côté client (facultatif)**
Bien que la validation côté client puisse améliorer l'expérience utilisateur, elle ne doit pas être considérée comme une mesure de sécurité, car elle peut être contournée. Cependant, vous pouvez toujours utiliser JavaScript ou HTML5 pour ajouter des validations supplémentaires.

### Conclusion

Pour éviter les vulnérabilités liées à la modification des valeurs dans les formulaires, il est essentiel de toujours vérifier les données côté serveur. Cela garantit que seules des valeurs valides sont traitées par l'application, même si un attaquant modifie les entrées du formulaire.

