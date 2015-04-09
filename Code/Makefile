# http://www.labri.fr/perso/billaud/IUT/AP2-POO-0910/060-faire-makefile.pdf

CFLAGS=-Wall 


all:: ia gui commun




################## Commun

##### creation de l'executable du jeu
commun:: backgammon Commun/libJoueur.so

backgammon: Commun/backgammon.o Commun/arbitre.o GUI/graphique.o Commun/joueur.o Commun/verifications.o
	gcc $(CFLAGS) Commun/backgammon.o Commun/arbitre.o GUI/graphique.o Commun/joueur.o Commun/verifications.o -o backgammon -ldl `sdl-config --cflags --libs` -lSDL -lSDL_ttf



Commun/backgammon.o: Commun/backgammon.c
	gcc $(CFLAGS) -c Commun/backgammon.c -o Commun/backgammon.o

Commun/arbitre.o: Commun/arbitre.c Commun/arbitre.h 
	gcc $(CFLAGS) -c Commun/arbitre.c -o Commun/arbitre.o

Commun/joueur.o: Commun/joueur.c Commun/joueur.h 
	gcc $(CFLAGS) -c Commun/joueur.c -o Commun/joueur.o

Commun/verifications.o: Commun/verifications.c Commun/verifications.h 
	gcc $(CFLAGS) -c Commun/verifications.c -o Commun/verifications.o


# librairie joueur réel
Commun/libJoueur.so: Commun/libJoueur.o GUI/graphique_joueur.o IA/fonctionsBot.so
	gcc -shared Commun/libJoueur.o GUI/graphique_joueur.o IA/fonctionsBot.so -o Commun/libJoueur.so 

Commun/libJoueur.o: Commun/libJoueur.c 
	gcc $(CFLAGS) -o Commun/libJoueur.o -fpic -c Commun/libJoueur.c 

GUI/graphique_joueur.o: GUI/graphique.c GUI/graphique.h  
	gcc $(CFLAGS) -o GUI/graphique_joueur.o -fpic -c GUI/graphique.c




################## IA
ia:: IA/libBotTricheur.so IA/libBotRandom.so IA/libBotSimplet.so IA/libBotLynx.so IA/libBotAntiJeu.so IA/libBotFusion.so 


###### bot fusion
IA/libBotFusion.so: IA/botFusion.o IA/fonctionsBot.so 
	gcc -shared IA/botFusion.o IA/fonctionsBot.so -o IA/libBotFusion.so 

IA/botFusion.o: IA/botFusion.c 
	gcc $(CFLAGS) -o IA/botFusion.o -fpic -c IA/botFusion.c 


###### bot anti jeu
IA/libBotAntiJeu.so: IA/botAntiJeu.o IA/fonctionsBot.so 
	gcc -shared IA/botAntiJeu.o IA/fonctionsBot.so -o IA/libBotAntiJeu.so 

IA/botAntiJeu.o: IA/botAntiJeu.c 
	gcc $(CFLAGS) -o IA/botAntiJeu.o -fpic -c IA/botAntiJeu.c


###### bot Lynx
IA/libBotLynx.so: IA/botLynx.o IA/fonctionsBot.so
	gcc -shared IA/botLynx.o IA/fonctionsBot.so -o IA/libBotLynx.so 

IA/botLynx.o: IA/botLynx.c  
	gcc $(CFLAGS) -o IA/botLynx.o -fpic -c IA/botLynx.c


###### bot simplet
IA/libBotSimplet.so: IA/botSimplet.o IA/fonctionsBot.so
	gcc -shared IA/botSimplet.o IA/fonctionsBot.so -o IA/libBotSimplet.so 

IA/botSimplet.o: IA/botSimplet.c 
	gcc $(CFLAGS) -o IA/botSimplet.o -fpic -c IA/botSimplet.c


###### bot random
IA/libBotRandom.so: IA/botRandom.o IA/fonctionsBot.so 
	gcc -shared IA/botRandom.o IA/fonctionsBot.so -o IA/libBotRandom.so 

IA/botRandom.o: IA/botRandom.c 
	gcc $(CFLAGS) -o IA/botRandom.o -fpic -c IA/botRandom.c


###### bot tricheur
IA/libBotTricheur.so: IA/botTricheur.o IA/fonctionsBot.so
	gcc -shared IA/botTricheur.o IA/fonctionsBot.so -o IA/libBotTricheur.so 


IA/botTricheur.o: IA/botTricheur.c 
	gcc $(CFLAGS) -o IA/botTricheur.o -fpic -c IA/botTricheur.c



###### fichiers utilisés par tous les bots
IA/fonctionsBot.so: IA/fonctionsBot.o IA/ListeChainee.o IA/Coup.o IA/GameState.o
	gcc -shared IA/fonctionsBot.o IA/ListeChainee.o IA/Coup.o IA/GameState.o -o IA/fonctionsBot.so 


IA/fonctionsBot.o: IA/fonctionsBot.c IA/fonctionsBot.h 
	gcc $(CFLAGS) -o IA/fonctionsBot.o -fpic -c IA/fonctionsBot.c 

IA/ListeChainee.o: IA/ListeChainee.c IA/ListeChainee.h 
	gcc $(CFLAGS) -o IA/ListeChainee.o -fpic -c IA/ListeChainee.c 

IA/Coup.o: IA/Coup.c IA/Coup.h 
	gcc $(CFLAGS) -o IA/Coup.o -fpic -c IA/Coup.c 

IA/GameState.o: IA/GameState.c IA/GameState.h
	gcc $(CFLAGS) -o IA/GameState.o -fpic -c IA/GameState.c 





################## GUI
gui:: GUI/graphique.o

GUI/graphique.o: GUI/graphique.c GUI/graphique.h 
	gcc $(CFLAGS) -c GUI/graphique.c -o GUI/graphique.o





################## suppression fichiers

### supprime les fichiers intermediaires
clean::
	# fichiers temporaires
	rm -rf *.i IA/*.i GUI/*.i Commun/*.i
	rm -rf *.s IA/*.s GUI/*.s Commun/*.s
	rm -rf *.o IA/*.o GUI/*.o Commun/*.o



### supprimes tous les fichies créés
reset::	clean
	# librairies
	rm -rf IA/*.so IA/*.dll Commun/*.so Commun/*.dll GUI/*.so GUI/*.dll
	rm -rf IA/*.so.copy IA/*.dll.copy Commun/*.so.copy Commun/*.dll.copy GUI/*.so.copy GUI/*.dll.copy
	# exécutable
	rm -f backgammon
	rm -f backgammon.exe



