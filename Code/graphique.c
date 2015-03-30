#include "graphique.h"
#include "arbitre.h"

// Permet d'afficher la fenêtre de jeu
int afficherJeu()
{

    // Initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Impossible de démarrer la fenêtre SDL : %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();

    int maxW=videoInfo->current_w;
    int maxH=videoInfo->current_h;
  // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(maxW, maxH, 16, SDL_FULLSCREEN|SDL_DOUBLEBUF);
    SDL_Surface* de1;
    SDL_Surface* de2;

    char* pathCompletDe1 = "./Images/Des/de1.bmp";
    char* pathCompletDe2 = "./Images/Des/de1.bmp";
    SDL_Event event;

    Pion tabPions[30]; // tableau de pions des joueurs

    unsigned char dices[2];

    if ( !screen )
    {
        printf("Impossible d'afficher l'écran : %s\n", SDL_GetError());
        return 1;
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Backgammon", NULL);


    // load an image
    SDL_Surface* plateau = SDL_LoadBMP("./Images/plateau.bmp");

    if (!plateau)
    {
        printf("Impossible de charger l'image bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - plateau->w) / 2;
    dstrect.y = (screen->h - plateau->h) / 2;

    SDL_Rect posDe1; // rect du dé1
    SDL_Rect posDe2; // rect du dé2

    //initialisation des dés
    de1 = SDL_LoadBMP(pathCompletDe1);
    de2 = SDL_LoadBMP(pathCompletDe2);

    int i;
    for(i = 0; i< 30; i++)
    {
        creerPion(tabPions, i, 10*i, 50, "./Images/noir.bmp");
    }

    // si impossible de charger les images des dés
    if (!de1 || !de2)
    {
        printf("Impossible de charger l'image : %s", SDL_GetError());
        return 1;
    }
    positionnerDes(&posDe1, &posDe2);

    // program main loop
    int done = 0;
    while (done != 1)
    {
        // message processing loop
        SDL_WaitEvent(&event);

            // Gestion des évènements
            switch (event.type)
            {
                // sortie si on ferme la fenêtre
            case SDL_QUIT:
                done = 1;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        // si appui sur touche echap
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                        // si appui sur touche espace
                        case SDLK_SPACE:

                            lancerLesDes(dices);

                            // on actualise le chemin de l'image des dés
                            pathCompletDe1 = retournerPathDe(dices[0]);
                            pathCompletDe2 = retournerPathDe(dices[1]);

                            printf("%i - %i\n", dices[0], dices[1]);
                            de1 = SDL_LoadBMP(pathCompletDe1);
                            de2 = SDL_LoadBMP(pathCompletDe2);

                        break;

                        default:
                            break;
                    }
                }
                break;

            default:
                break;

        }
        // Début de la partie pour redessiner les éléments
        // réinitialisation de l'écran
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // on applique l'image de fond
        SDL_BlitSurface(plateau, 0, screen, &dstrect);

        // on applique l'image des dés
        SDL_BlitSurface(de1, 0, screen, &posDe1);
        SDL_BlitSurface(de2, 0, screen, &posDe2);

        for(i = 0; i < 30; i++)
        {
            SDL_BlitSurface(tabPions[i].imagePion, 0, screen, &tabPions[i].posPion);
        }

        // On met à jour l'écran
        SDL_Flip(screen);
    } // end main loop

    // libération des surfaces
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(de1);
    SDL_FreeSurface(de2);

    for(i = 0; i < 30; i++)
        {
            SDL_FreeSurface(tabPions[i].imagePion);
        }

    printf("Terminé correctement\n");
    return 0;
}

// retourne le chemin de l'image selon la valeur retournée par le lancement de dés
char* retournerPathDe(char dice)
{
    switch(dice)
    {
        case 1:
            return "./Images/Des/de1.bmp";
        case 2:
            return "./Images/Des/de2.bmp";
        case 3:
            return "./Images/Des/de3.bmp";
        case 4:
            return "./Images/Des/de4.bmp";
        case 5:
            return "./Images/Des/de5.bmp";
        case 6:
            return "./Images/Des/de6.bmp";
        default:
            return NULL;
    }
}

// initialisation de la position des dés
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2)
{
    posDe1 -> x = 883;
    posDe1 -> y = 360;

    posDe2 -> x = 945;
    posDe2 -> y = 360;
}

void creerPion(Pion pions[30], int positionPion, int posX, int posY, char* image){

    Pion pion;
    SDL_Rect* posPion;

    posPion -> x = posX;
    posPion -> y = posY;

    pion.posPion = posPion;

    SDL_Surface* imagePion = SDL_LoadBMP(image);
    pion.imagePion = imagePion;

    pions[positionPion] = pion;

}

positionnerPion(Pion *pion, SDL_Rect *pos){

    pion -> posPion = pos;

}


