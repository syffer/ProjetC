# http://www.labri.fr/perso/billaud/IUT/AP2-POO-0910/060-faire-makefile.pdf



# pour récupérer : Linux Win32
OS = 'echo -n %OS%'
LINUX =%OS%


# ensemble des exécutable à produire
all:: backgammon libBotTricheur.so libBotSimplet.so libBotLinx.so libJoueur.so libBotRandom.so libBotAntiJeu.so libBotParfait.so




##### creation des librairies

# librairie du joueur (réel)
libJoueur.so: botJoueur.o
	gcc -shared botJoueur.o -o libJoueur.so

botJoueur.o: botJoueur.c
	gcc -fpic -c botJoueur.c


# librairie linx
libBotLinx.so: botLinx.o fonctionsBot.o ListeChainee.o
	gcc -shared botLinx.o fonctionsBot.o ListeChainee.o -o libBotLinx.so
	
botLinx.o: botLinx.c
	gcc -fpic -c botLinx.c 


# bot simplet
libBotSimplet.so: botSimplet.o fonctionsBot.o ListeChainee.o
	gcc -shared botSimplet.o fonctionsBot.o ListeChainee.o -o libBotSimplet.so 

botSimplet.o: botSimplet.c
	gcc -fpic -c botSimplet.c 


# bot tricheur
libBotTricheur.so: botTricheur.o fonctionsBot.o ListeChainee.o
	gcc -shared botTricheur.o fonctionsBot.o ListeChainee.o -o libBotTricheur.so 

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

botAntiJeu.o: botAntiJeu.c
	gcc -fpic -c botAntiJeu.c 
	
# bot parfait
libBotParfait.so: botParfait.o fonctionsBot.o ListeChainee.o
	gcc -shared botParfait.o fonctionsBot.o ListeChainee.o -o libBotParfait.so 

botParfait.o: botParfait.c
	gcc -fpic -c botParfait.c 
	
	

fonctionsBot.o: fonctionsBot.c
	gcc -fpic -c fonctionsBot.c 

ListeChainee.o: ListeChainee.c
	gcc -fpic -c ListeChainee.c



##### creation de l'executable du jeu
backgammon: backgammon.o arbitre.o graphique.o joueur.o verifications.o
	gcc -Wall backgammon.o arbitre.o graphique.o joueur.o verifications.o -o backgammon -ldl `sdl-config --cflags --libs`


backgammon.o: backgammon.c
	gcc -Wall -c backgammon.c


arbitre.o: arbitre.c
	gcc -Wall -c arbitre.c

graphique.o: graphique.c
	gcc -Wall -c graphique.c

joueur.o: joueur.c
	gcc -Wall -c joueur.c
	
verifications.o: verifications.c
	gcc -Wall -c verifications.c




# on supprime les fichiers temporaires
# make clean
clean::
	@rm -f *.i
	@rm -f *.s
	@rm -f *.o
	


# on recrée tout les exécutables
# fait "le grand menage"
# make mrproper
mrpropre:: 	
	# fichiers temporaires
	rm -f *.i
	rm -f *.s
	rm -f *.o
	#librairies
	rm -f *.so
	rm -f *.dll
	# l'exécutable
	rm -f backgammon
	rm -f backgammon.exe
