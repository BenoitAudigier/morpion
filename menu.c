#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "menu.h"
#include "jeu.h"

#define HAUTEUR_ECRAN 600//un autre dans main et jeu
#define LARGEUR_ECRAN 900
#define ECRAN_ROUGE 120
#define ECRAN_VERT 190
#define ECRAN_BLEU 80
#define CURSEUR_SUR_PLAY 1
#define CURSEUR_SUR_QUIT 2


int menu(SDL_Surface* ecran)
{

    afficherMenu(ecran, 0);

    SDL_Surface *play1 = IMG_Load("play1.png");
    SDL_Surface *quit1 = IMG_Load("quit1.png");

    SDL_Rect positionPlay;
    positionPlay.y = HAUTEUR_ECRAN/2 - play1->h/2;
    positionPlay.x = LARGEUR_ECRAN/3 - play1->w/2;
    int hauteurPlay = play1->h;
    int largeurPlay = play1->w;

    SDL_Rect positionQuit;
    positionQuit.y = HAUTEUR_ECRAN/2 - quit1->h/2;
    positionQuit.x = (LARGEUR_ECRAN/3)*2 - quit1->w/2;
    int hauteurQuit = quit1->h;
    int largeurQuit = quit1->w;

    SDL_FreeSurface(play1);
    SDL_FreeSurface(quit1);


    SDL_Event event;
    int menu = 1;
    while (menu == 1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
                if (event.motion.x > positionPlay.x   // Si le curseur est sur l'image play
                    && event.motion.x < (positionPlay.x + largeurPlay)
                    && event.motion.y > positionPlay.y
                    && event.motion.y < (positionPlay.y + hauteurPlay) )
                {
                    afficherMenu(ecran, CURSEUR_SUR_PLAY);
                }
                else if (event.motion.x > positionQuit.x   // Si le curseur est sur l'image quit
                    && event.motion.x < (positionQuit.x +largeurQuit)
                    && event.motion.y > positionQuit.y
                    && event.motion.y < (positionQuit.y + hauteurQuit) )
                {
                    afficherMenu(ecran, CURSEUR_SUR_QUIT);
                }
                else
                {
                    afficherMenu(ecran, 0);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.motion.x > positionQuit.x   // Si le curseur est sur l'image quit
                    && event.motion.x < (positionQuit.x + largeurQuit)
                    && event.motion.y > positionQuit.y
                    && event.motion.y < (positionQuit.y + hauteurQuit)
                    && event.button.button == SDL_BUTTON_LEFT)
                    {
                        menu = 0;
                    }
                if (event.motion.x > positionPlay.x   // Si le curseur est sur l'image play
                    && event.motion.x < (positionPlay.x + largeurPlay)
                    && event.motion.y > positionPlay.y
                    && event.motion.y < (positionPlay.y + hauteurPlay) )
                    {
                        menu = jeu(ecran);
                        afficherMenu(ecran, 0);

                    }
                break;
            case SDL_KEYUP:
                if ((event.key.keysym.sym & SDLK_ESCAPE) == SDLK_ESCAPE)
                {
                    menu = 0;
                }
                break;
            case SDL_QUIT:
                menu = 0;
                break;
            default:
                break;
        }
    }

    return menu;
}

void afficherMenu(SDL_Surface *ecran, int curseur)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, ECRAN_ROUGE, ECRAN_VERT, ECRAN_BLEU));
    SDL_Surface *play;
    SDL_Surface *quit;
    SDL_Surface *texteJouer = IMG_Load("playTexte.png");
    SDL_Surface *texteQuitter = IMG_Load("quitTexte.png");
    if ((curseur & CURSEUR_SUR_PLAY) == CURSEUR_SUR_PLAY)
    {
        play = IMG_Load("play2.png");
        SDL_Rect positionTexteJouer;
        positionTexteJouer.x = LARGEUR_ECRAN/2 - texteJouer->w/2;
        positionTexteJouer.y = HAUTEUR_ECRAN - texteJouer->h - 10;
        SDL_BlitSurface(texteJouer, NULL, ecran, &positionTexteJouer);
    }
    else
    {
        play = IMG_Load("play1.png");
    }

    SDL_Rect positionPlay;
    positionPlay.y = HAUTEUR_ECRAN/2 - play->h/2;
    positionPlay.x = LARGEUR_ECRAN/3 - play->w/2;
    SDL_SetColorKey(play, SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));


    SDL_Surface* titre = IMG_Load("titre.png");
    SDL_Rect positionTitre;
    positionTitre.y = 0;
    positionTitre.x = LARGEUR_ECRAN/2 - titre->w/2;
    SDL_SetColorKey(titre, SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));

    if ((curseur & CURSEUR_SUR_QUIT) == CURSEUR_SUR_QUIT)
    {
        quit = IMG_Load("quit2.png");
        SDL_Rect positionTexteQuitter;
        positionTexteQuitter.x = LARGEUR_ECRAN/2 - texteQuitter->w/2;
        positionTexteQuitter.y = HAUTEUR_ECRAN - texteQuitter->h - 10;
        SDL_BlitSurface(texteQuitter, NULL, ecran, &positionTexteQuitter);
    }
    else
    {
        quit = IMG_Load("quit1.png");
    }
    SDL_Rect positionQuit;
    positionQuit.y = HAUTEUR_ECRAN/2 - quit->h/2;
    positionQuit.x = (LARGEUR_ECRAN/3)*2 - quit->w/2;

    SDL_BlitSurface(play, NULL, ecran, &positionPlay);
    SDL_BlitSurface(titre, NULL, ecran, &positionTitre);
    SDL_BlitSurface(quit, NULL, ecran, &positionQuit);

    SDL_Flip(ecran);

    SDL_FreeSurface(play);
    SDL_FreeSurface(quit);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(texteJouer);
    SDL_FreeSurface(texteQuitter);
}
