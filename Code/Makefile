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
backgammon: backgammon.o jeux.o graphique.o
	gcc -Wall backgammon.o jeux.o graphique.o -o backgammon -ldl


backgammon.o: backgammon.c
	gcc -Wall -c backgammon.c

jeux.o: jeux.c
	gcc -Wall -c jeux.c


graphique.o: graphique.c
	gcc -Wall -c graphique.c


# on supprime les fichiers temporaires
# make clean
clean::
	@rm -f *.i
	@rm -f *.s
	@rm -f *.o
	


# on recrée tout les exécutables
# fait "le grand menage"
# make mrproper
mrproper:: 	
	rm -f libBot.dll
	rm -f libBot.so 
	rm -f backgammon
	rm -f *.so
	rm -f *.dll
