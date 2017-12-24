#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "menu.c"
#include "jeu.h"
#include "jeu.c"
#include "fonctionsJeu.h"
#include "fonctionsJeu.c"


#define HAUTEUR_ECRAN 600 //un autre dans jeu et menu
#define LARGEUR_ECRAN 900


int main ( int argc, char** argv )
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
            exit(EXIT_FAILURE);
        }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Morpion", NULL);

    SDL_Surface* ecran = SDL_SetVideoMode(900, 600, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

    if (ecran == 0)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de l'ecran : %s", SDL_GetError() );
    }

    int continuer = 1;
    while (continuer)
    {
        continuer = menu(ecran);
    }

    SDL_FreeSurface(ecran);
    SDL_Quit();
    return 0;
}
