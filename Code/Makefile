
# commentaire

# http://www.labri.fr/perso/billaud/IUT/AP2-POO-0910/060-faire-makefile.pdf


# ensemble des exécutable à produire
# on supprime ensuite les fichiers temporaires
all:: libBot.dll libBot.so backgammon clean


# creation des librairies
libBot.dll: bot.o
	gcc -shared -o libBot.dll bot.o

libBot.so: bot.o
	gcc -shared -o libBot.so bot.o

bot.o: bot.c
	gcc -c -fpic bot.c



# creation de l'executable du jeu
backgammon: backgammon.c
	gcc -Wall backgammon.c -o backgammon




# on supprime les fichiers temporaires
# make clean
clean::
	@rm -f *.o


# on recrée tout les exécutables
# fait "le grand menage"
# make mrproper
mrproper:: 	
	rm -f libBot.dll
	rm -f libBot.so 
	rm -f backgammon
