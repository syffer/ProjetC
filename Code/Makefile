# http://www.labri.fr/perso/billaud/IUT/AP2-POO-0910/060-faire-makefile.pdf

CFLAGS=-Wall 


all:: ia gui commun


################## Commun

##### creation de l'executable du jeu
commun:: backgammon.o arbitre.o graphique.o joueur.o verifications.o
	gcc $(CFLAGS) Commun/backgammon.o Commun/arbitre.o GUI/graphique.o Commun/joueur.o Commun/verifications.o -o backgammon -ldl `sdl-config --cflags --libs`


backgammon.o: Commun/backgammon.c
	gcc $(CFLAGS) -c Commun/backgammon.c -o Commun/backgammon.o


arbitre.o: Commun/arbitre.c
	gcc $(CFLAGS) -c Commun/arbitre.c -o Commun/arbitre.o

joueur.o: Commun/joueur.c
	gcc $(CFLAGS) -c Commun/joueur.c -o Commun/joueur.o


verifications.o: Commun/verifications.c
	gcc $(CFLAGS) -c Commun/verifications.c -o Commun/verifications.o



################## IA
ia:: libBotTricheur.so libBotRandom.so libBotSimplet.so libBotLynx.so 

# manque bot joueur  libJoueur.so

# manque bot parfait ??  libBotParfait.so

# manque bot anti jeu  libBotAntiJeu.so

###### bot Lynx
libBotLynx.so: botLynx.o fonctionsBot.o ListeChainee.o
	gcc -shared IA/botLynx.o IA/fonctionsBot.o IA/ListeChainee.o -o IA/libBotLynx.so 

botLynx.o: IA/botLynx.c
	gcc $(CFLAGS) -o IA/botLynx.o -fpic -c IA/botLynx.c


###### bot simplet
libBotSimplet.so: botSimplet.o fonctionsBot.o ListeChainee.o
	gcc -shared IA/botSimplet.o IA/fonctionsBot.o IA/ListeChainee.o -o IA/libBotSimplet.so 

botSimplet.o: IA/botSimplet.c
	gcc $(CFLAGS) -o IA/botSimplet.o -fpic -c IA/botSimplet.c


###### bot random
libBotRandom.so: botRandom.o fonctionsBot.o ListeChainee.o
	gcc -shared IA/botRandom.o IA/fonctionsBot.o IA/ListeChainee.o -o IA/libBotRandom.so 

botRandom.o: IA/botRandom.c
	gcc $(CFLAGS) -o IA/botRandom.o -fpic -c IA/botRandom.c


###### bot tricheur
libBotTricheur.so: botTricheur.o fonctionsBot.o ListeChainee.o
	gcc -shared IA/botTricheur.o IA/fonctionsBot.o IA/ListeChainee.o -o IA/libBotTricheur.so 

<<<<<<< HEAD
botTricheur.o: IA/botTricheur.c
	gcc $(CFLAGS) -o IA/botTricheur.o -fpic -c IA/botTricheur.c
=======
botTricheur.o: botTricheur.c
	gcc -fpic -c botTricheur.c 
	
# bot random
libBotRandom.so: botRandom.o fonctionsBot.o ListeChainee.o
	gcc -shared botRandom.o fonctionsBot.o ListeChainee.o -o libBotRandom.so 

botRandom.o: botRandom.c
	gcc -fpic -c botRandom.c 

# bot anti jeu
libBotAntiJeu.so: botAntiJeu.o fonctionsBot.o ListeChainee.o
	gcc -shared botAntiJeu.o fonctionsBot.o ListeChainee.o -o libBotAntiJeu.so 
>>>>>>> b3b9b03d3f24f538a8d2d730d0d9016cd4fdc69e

botAntiJeu.o: botAntiJeu.c
	gcc -fpic -c botAntiJeu.c 
	
# bot parfait
libBotParfait.so: botParfait.o fonctionsBot.o ListeChainee.o
	gcc -shared botParfait.o fonctionsBot.o ListeChainee.o -o libBotParfait.so 

botParfait.o: botParfait.c
	gcc -fpic -c botParfait.c 
	
	

###### fichiers utilisés par tous les bots
fonctionsBot.o: IA/fonctionsBot.c
	gcc $(CFLAGS) -o IA/fonctionsBot.o -fpic -c IA/fonctionsBot.c 

ListeChainee.o: IA/ListeChainee.c
	gcc $(CFLAGS) -o IA/ListeChainee.o -fpic -c IA/ListeChainee.c 






################## GUI
gui:: graphique.o

graphique.o: GUI/graphique.c
	gcc $(CFLAGS) -c GUI/graphique.c -o GUI/graphique.o





################## suppression fichiers

### supprime les fichiers intermediaires
clean::
	# fichiers temporaires
	rm -rf *.i IA/*.i GUI/*.i Commun/*.i
	rm -rf *.s IA/*.s GUI/*.s Commun/*.s
	rm -rf *.o IA/*.o GUI/*.o Commun/*.o



### supprimes tous les fichies créer
mrproper::	clean
	# librairies
	rm -rf IA/*.so 
	rm -rf IA/*.dll
	# exécutable
	rm -f backgammon
	rm -f backgammon.exe



