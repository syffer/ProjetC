
#include "graphique.h"

//#include "arbitre.h"


/*
int afficherPlateau()
{

// initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1200, 700, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* de1;
    SDL_Surface* de2;

    char* pathCompletDe1 = "Images/Des/de1.bmp";
    char* pathCompletDe2 = "Images/Des/de1.bmp";
    SDL_Event event;

    unsigned char dices[2];

    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption("Ma super fenetre SDL !", NULL);


    // load an image
    SDL_Surface* plateau = SDL_LoadBMP("Images/plateau.bmp");

    if (!plateau)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - plateau->w) / 2;
    dstrect.y = (screen->h - plateau->h) / 2;

    SDL_Rect posDe1; // rect du d�1
    SDL_Rect posDe2; // rect du d�2

    //initialisation des d�s
    de1 = SDL_LoadBMP(pathCompletDe1);
    de2 = SDL_LoadBMP(pathCompletDe2);
    positionnerDes(&posDe1, &posDe2);



    // program main loop
    int done = 0;
    while (done != 1)
    {
        // message processing loop
        SDL_WaitEvent(&event);

            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = 1;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        // exit if ESCAPE is pressed
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                        case SDLK_g:

                            lancerLesDes(dices);

                            // on actualise le chemin de l'image des d�s
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
             // end switch
        } // end of message processing

        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // on applique l'image de fond
        SDL_BlitSurface(plateau, 0, screen, &dstrect);

        // on applique l'image des d�s
        SDL_BlitSurface(de1, 0, screen, &posDe1);
        SDL_BlitSurface(de2, 0, screen, &posDe2);
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(de1);
    SDL_FreeSurface(de2);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

char* retournerPathDe(char dice)
{
    switch(dice)
    {
        case 1:
            return "Images/Des/de1.bmp";
        case 2:
            return "Images/Des/de2.bmp";
        case 3:
            return "Images/Des/de3.bmp";
        case 4:
            return "Images/Des/de4.bmp";
        case 5:
            return "Images/Des/de5.bmp";
        case 6:
            return "Images/Des/de6.bmp";
        default:
            return NULL;
    }
}

void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2)
{
    posDe1 -> x = 883;
    posDe1 -> y = 360;

    posDe2 -> x = 945;
    posDe2 -> y = 360;
}

*/
