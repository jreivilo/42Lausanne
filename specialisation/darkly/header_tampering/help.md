## Header Tampering

En changeant les headers de vos requetes, vous pouvez acceder a du contenu ou des acces qui sont censer etre confidentiels, dans des sites mal configures.
Encore une fois curl va nous permettre de faire ces requetes modifier, mais des outils d'interception de requetes tels que burp suite permette de faire pareil et plus de choses.

### Trouver le flag
Tout en bas de la page d'accueil, on peut cliquer sur BornToSec dans le footer, ce qui nous redirige sur une page avec des albatros. En ayant la console ouverte en regardant le html, on voit les commentaires suivants (cachés par d'autres commentaires avec du lorem ipsum et une tonne de whitespace):
<!--
You must come from : "https://www.nsa.gov/".
-->
<!--
Let's use this browser : "ft_bornToSec". It will help you a lot.
-->

C'est un indice pour nous indiquer de changer les headers pour dire qu'on a ete rediriger sur ce site depuis la page nsa.gov (ce qui veut dire, pour le site, que l'on vient d'une page safe, meme si c'est faux), et dire que l'on utilise le browser ft_bornToSec (pas trop sur de l'impact dangereux de cette derniere modif).

Les options curl que l'on utilise sont les suivantes:
- `-H` pour rajouter un headers: `-H "Referer: https://www.nsa.gov/"`
- `-A` pour indiquer le brwoser utiliser pour la requete: `-A "ft_bornToSec"`
- ensuite l'url de la page
- ensuite ca renvoie tout le html de la page, mais avec le flag rajouter, donc on pipe ca dans 'grep flag' et boom on a (the msuic playing when you load the page is a hint to find the flag)
```html
    0<center><h2 style="margin-top:50px;"> The flag is : f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188</h2><br/><img src="images/win.png" alt="" width=200px height=200px></center> <audio id="best_music_ever" src="audio/music.mp3"preload="true" loop="loop" autoplay="autoplay">
```

Dans burp suite il s'agirait juste d'allumer l'intercepteur, de loader la page, et ensuite vu qu'elle est bloquer on peut changer les headers directement en plaintext dans burp, et envoyer la requete modifier, donnant le meme resultat.

Quand on decrypte le flag avec sha256 sur dcode.fr (incroyable ce site, marche mieux que tout les autres qui ont plein de pubs), on obtient la string: `albatroz`