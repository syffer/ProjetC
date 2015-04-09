===========================================================================
===========================================================================
===========================================================================
									README
===========================================================================
===========================================================================
===========================================================================

Ce projet a été réalisé par :			sous-groupe:
- Cyril CARON 							(gui)
- Titouan PASQUET						(gui)
- Pauline HOULGATTE						(ia)
- Maxime PINEAU							(ia)

Ce fichier contient les informations concernants les différentes stratégies
du bot, les informations nécessaires à la compilation et l'exécution.

Sommaire :
1) Compilation
2) Execution
3) Organisation des fichiers
4) Le fonctionnement des bots
	a. botSimplet
	b. botTricheur
	c. botRandom
	d. botAntiJeu
	e. botLynx
	f. botFusion
5) Le fonctionnement pour un joueur réel
6) Les problèmes non résolus


1) Compilation
La compilation se fait via l'exécution du makefile : 
- se rendre dans le dossier du Makefile
- $make

Vous pouvez également compiler les trois parties (commune, ia et graphique) de façon indépendante en utilisant les commandes suivantes:
- $make gui
- $make ia
- $make commun

Enfin, il est également possible de supprimer les fichiers temporaires, et tous les fichiers créés avec :
- $make clean
- $make reset

2) Execution
Le programme prend trois paramètres : 
- le premier est obligatoire et correspond à un entier supérieur à 0. Il 
correspond au nombre de points à atteindre pour gagner le match.
- le deuxième et troisième paramètres ne sont pas obligatoires et correspondent 
aux librairies (bots). L'absence de ces paramètres entrainera le chargement du jeu
en mode "joueur réel".

exemple : ./backgammon 5 IA/libBotLynx.so IA/libBotRandom.so


3) Organisation des fichiers
Nous avons séparer ce projet en 3 sous dossiers :
- IA : contient tous les fichiers concernant les librairies (bots)
- GUI : contient tous les fichiers concernant l'affichage graphique du plateau (images...)
- Commun : contient le fichier contenant le main(), la librairie du joueur réel, et les fichiers 
relatifs aux chargement des librairies.


4) Le fonctionnement des bots

	a. botSimplet
Ce bot est simpliste. Il ne prend pas en compte l'état du terrain (placement de 
l'adversaire). Il se contente de déplacer ses pions les plus éloignés, et 
d'accepter une nouvelle mise si jamais l'adversaire lui propose.

	b. botTricheur
Ce bot tente de gagner en envoyant des données corrompues à l'arbitre. Il 
essaie via celles-ci de gagner dès le premier tour. Il n'envoie pas de 
mouvements.

	c. botRandom
Ce bot regarde tous les coups possibles et en sélectionne un aléatoirement. Ce 
coup n'est pas forcément valide. Il ne propose jamais de doubler la mise mais 
l'accepte à chaque fois que l'adversaire lui demande.

	d. botAntiJeu
Ce bot joue en privilégiant la prise de pions adverses. Il favorise ensuite le 
déplacement sécurisé de ses pions si possible.

	e. botLynx
Ce bot étudie l'état du jeu (placement adverse, les pions à sécuriser, les 
pions possibles à capturer, etc.) et choisit un déplacement en fonction. Il 
peut proposer de doubler la mise et accepte, selon les cas, la nouvelle mise 
de l'adversaire.

	f. botFusion
Ce bot est une fusion des bots AntiJeu et Lynx. Il favorise la prise de pions 
adversaises et la sécurité des siens.


5) Le fonctionnement pour un joueur réel



6) Les problèmes non résolus


