#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "fonctionsJeu.h"

#define HAUTEUR_ECRAN 600//un autre dans main et menu
#define LARGEUR_ECRAN 900
#define RIEN 0
#define CROIX 1
#define RONDS 2


int jeu(SDL_Surface* ecran)
{
    int terrain[3][3] = {{0}};
    afficherTableau(terrain, ecran);

    SDL_Event event;

    int jouer = 1;
    int totalQuit = 1;
    int gagnant = 0;
    while (jouer == 1)
    {
        SDL_WaitEvent(&event);
        int caseX = 0;
        int caseY = 0;
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if ((event.button.button & SDL_BUTTON_LEFT) == SDL_BUTTON_LEFT)
                {
                    if (ouEstClic(event.button.x, event.button.y, &caseX, &caseY))
                    {
                        if (terrain [caseX] [caseY] == 0)
                        {
                            terrain [caseX] [caseY] = tour(terrain);
                        }
                        caseX = 0;
                        caseY = 0;
                        afficherTableau(terrain, ecran);
                        if (gagne(terrain, &gagnant))
                        {
                            totalQuit = 1;
                            victoire(ecran, gagnant, &totalQuit);
                            jouer = 0;
                        }
                        if (gagnant == 3)
                        {
                            totalQuit = 1;
                            victoire(ecran, gagnant, &totalQuit);
                            jouer = 0;
                        }
                    }
                    if (event.button.x > LARGEUR_ECRAN - 48
                        && event.button.y <49)
                    {
                        jouer = 0;
                        totalQuit = 1;
                    }
                }
                break;
            case SDL_QUIT:
                jouer = 0;
                totalQuit = 0;
                break;
            case SDL_KEYUP:
                if ((event.key.keysym.sym & SDLK_ESCAPE) == SDLK_ESCAPE)
                {
                    jouer = 0;
                    totalQuit = 1;
                }
                break;
            default:
                break;
        }
    }
    return totalQuit;
}

