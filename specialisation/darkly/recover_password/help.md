# Exploitation et Solution

Ce formulaire contient un champ caché `mail` avec une valeur définie à `webmaster@borntosec.com`. Un attaquant peut facilement modifier ce champ à l'aide des outils de développement du navigateur.

### Exemple d'exploitation
1. Ouvrir les outils de développement du navigateur (clic droit > Inspecter).
2. Modifier la valeur du champ caché à `attacker@example.com`.
3. Soumettre le formulaire pour envoyer cette nouvelle valeur.

#### Conséquences :
L'attaquant pourrait recevoir des informations sensibles.

### Solution
- **Supprimer le champ caché** et gérer l'email côté serveur :
    ```html
    <form action="#" method="POST">
        <input type="submit" name="Submit" value="Submit">
    </form>
    ```

- **Côté serveur**, récupérer l'email depuis une session ou base de données sécurisée :
    ```php
    session_start();
    $email = $_SESSION['user_email']; // Email stocké de manière sécurisée
    ```