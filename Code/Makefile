# http://www.labri.fr/perso/billaud/IUT/AP2-POO-0910/060-faire-makefile.pdf



# pour récupérer : Linux Win32
OS = 'echo -n %OS%'
LINUX =%OS%


# ensemble des exécutable à produire
all:: libBot.dll libBot.so backgammon 



# creation des librairies
libBot.dll: bot.o
	gcc -shared -o libBot.dll bot.o

libBot.so: bot.o
	gcc -shared -o libBot.so bot.o

bot.o: bot.c
	gcc -c -fpic bot.c




# creation de l'executable du jeu
backgammon: backgammon.o arbitre.o graphique.o joueur.o verifications.o
	gcc -Wall backgammon.o arbitre.o graphique.o joueur.o verifications.o -o backgammon -ldl `sdl-config --cflags --libs` -lSDL -lSDL_ttf


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
reset:: 	
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
