===========================================================================
===========================================================================
===========================================================================
									README
===========================================================================
===========================================================================
===========================================================================

Ce projet a été réalisé par :
- Cyril CARON
- Pauline HOULGATTE
- Titouan PASQUET
- Maxime PINEAU

Ce fichier contient les informations concernants les différentes
stratégies du bot.

Sommaire :
1) botSimplet
2) botTricheur
3) botRandom
4) botAntiJeu
5) botLynx
6) botParfait

1) botSimplet
Ce bot est simpliste. Il ne prend pas en compte l'état du terrain (placement de l'adversaire). Il se contente de déplacer ses pions les plus éloignés, et d'accepter une nouvelle mise si jamais l'adversaire lui propose.

2) botTricheur
Ce bot tente de gagner en envoyant des données corrompues à l'arbitre. Il essaie via celles-ci de gagner dès le premier tour. Il n'envoie pas de mouvements.

3) botRandom
Ce bot regarde tous les coups possibles et en sélectionne un aléatoirement. Ce coup n'est pas forcément valide. Il ne propose jamais de doubler la mise mais l'accepte à chaque fois que l'adversaire lui demande.

4) botAntiJeu
Ce bot joue en privilégiant la prise de pions adverses. Il favorise ensuite le déplacement sécurisé de ses pions si possible.

5) botLynx
Ce bot étudie l'état du jeu (placement adverse, les pions à sécuriser, les pions possibles à capturer, etc.) et choisit un déplacement en fonction. Il peut proposer de doubler la mise et accepte, selon les cas, la nouvelle mise de l'adversaire.

6) botParfait
Ce bot est une fusion des bots AntiJeu et Lynx. Il favorise la prise de pions adversaises et la sécurité des siens.