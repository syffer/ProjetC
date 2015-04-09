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

Ce fichier contient les informations concernants les différentes stratégies
du bot, les informations nécessaires à la compilation et l'exécution.

Sommaire :
1) Compilation
2) Execution
3) botSimplet
4) botTricheur
5) botRandom
6) botAntiJeu
7) botLynx
8) botFusion

1) Compilation
La compilation se fait via l'exécution du makefile : 
- se rendre dans le dossier du Makefile
- $make

2) Execution
Le programme prend trois paramètres : 
- le premier est obligatoire et correspond à un entier supérieur à 0. Il 
correspond au nombre de points à atteindre pour gagner le match.
- le deuxième et troisième paramètres ne sont pas obligatoires et correspondent 
aux librairies (bots)

exemple : ./backgammon 5 IA/libBotLynx.so IA/libBotRandom.so

3) botSimplet
Ce bot est simpliste. Il ne prend pas en compte l'état du terrain (placement de 
l'adversaire). Il se contente de déplacer ses pions les plus éloignés, et 
d'accepter une nouvelle mise si jamais l'adversaire lui propose.

4) botTricheur
Ce bot tente de gagner en envoyant des données corrompues à l'arbitre. Il 
essaie via celles-ci de gagner dès le premier tour. Il n'envoie pas de 
mouvements.

5) botRandom
Ce bot regarde tous les coups possibles et en sélectionne un aléatoirement. Ce 
coup n'est pas forcément valide. Il ne propose jamais de doubler la mise mais 
l'accepte à chaque fois que l'adversaire lui demande.

6) botAntiJeu
Ce bot joue en privilégiant la prise de pions adverses. Il favorise ensuite le 
déplacement sécurisé de ses pions si possible.

7) botLynx
Ce bot étudie l'état du jeu (placement adverse, les pions à sécuriser, les 
pions possibles à capturer, etc.) et choisit un déplacement en fonction. Il 
peut proposer de doubler la mise et accepte, selon les cas, la nouvelle mise 
de l'adversaire.

8) botFusion
Ce bot est une fusion des bots AntiJeu et Lynx. Il favorise la prise de pions 
adversaises et la sécurité des siens.