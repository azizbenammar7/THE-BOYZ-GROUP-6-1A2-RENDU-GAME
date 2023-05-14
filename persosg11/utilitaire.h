#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#define SCREEN_W 800
#define SCREEN_H 600


typedef struct
{
int joueur;// numero du joueur qui va jouer au premier 1: si joueur, 2 si ordinateur
SDL_Surface * image1,*image2,*image3;
int tabsuivi[9];// tableau representant la grille du jeu
SDL_Rect pos;// position d'un petit carreau a calculer pour chaque case
int tour;// initialement egale 0 au maximum nous avons 8 tours
TTF_Font *comic;
SDL_Color couleur;
SDL_Rect posMSG;
}tic;



typedef struct {

	SDL_Surface* textSurface;
	SDL_Rect positionText;
	char txt[20];
	SDL_Color couleurTxt;
	TTF_Font* police;
    
}Text;
typedef struct
{
    SDL_Surface *back[5];
    SDL_Rect positionBack;
} Background;
typedef struct
{
    SDL_Surface *Button1A;//active 7amra
    SDL_Surface *Button1NA;
    SDL_Surface *Button2A;
    SDL_Surface *Button2NA;
    SDL_Surface *Button3A;
    SDL_Surface *Button3NA;

    SDL_Rect Button1_position;
    SDL_Rect Button2_position;
    SDL_Rect Button3_position;

    SDL_Surface *Option;
    SDL_Rect positionOption;

    SDL_Surface *Plus;//maj
    SDL_Surface *plus;
    SDL_Rect positionPlus;

    SDL_Surface *Moins;
    SDL_Surface *moins;
    SDL_Rect positionMoins;
SDL_Surface *Normal;
    SDL_Surface *FullScreen;
    SDL_Rect positionFullscreen;

    

    SDL_Surface *Quit;
    SDL_Rect positionQuit;
} Buttons;
typedef struct
{
    Mix_Music *music;
    Mix_Chunk *bref;
} Music;
typedef struct
{
    SDL_Rect position;
    TTF_Font *font;
    SDL_Surface *surfaceTexte;
    SDL_Color textColor;
    char texte[50];
} text;
typedef struct 
{
    SDL_Rect pos; 
    SDL_Surface *spritesheet; 
    SDL_Rect clips[6]; // tableau clips de 6 cases dans chaque case  on trouve struct SDL_rect //
    int cliploaded; 
}animation;


typedef struct 
{
    SDL_Surface *img;
    SDL_Rect p; 
    int reponsevrai;       
    int reponsejoueur;
    int num_enigme; //mn 1 l 3
    animation anim;
}enigme;


//////////////////////////////
void initText(text *t);
void freeText(text A);
void displayText(text t, SDL_Surface *screen);

void initMus(Music *M, int *volume);
void freeMusic(Music M);
void volumeUp(int *niv_volume, int *volume);
void volumeDown(int *niv_volume, int *volume);

void NewGame(SDL_Surface *screen,int *mode,int* g);
void Settings(SDL_Surface *screen,int *mode, int *niv_volume, int *volume);
void SetFull(SDL_Surface *screen, int *Mode);
void SetNorm(SDL_Surface *screen, int *Mode);
void SaveScreenMode(SDL_Surface *screen, int *Mode);
void SaveScreenMode1(SDL_Surface *screen, int *Mode);


//////////////////////////////
void initButMain(Buttons *B);
void initButSet(Buttons *B);

//////////////////////////////
void freeButMain(Buttons B);
void freeButSet(Buttons B);
//////////////////////////////
void AfficherBut1(Buttons B, SDL_Surface *screen, int hover1,int presses);
void AfficherBut2(Buttons B, SDL_Surface *screen, int hover2,int presses);
void AfficherBut3(Buttons B, SDL_Surface *screen, int hover3,int presses);

void AfficherButScreen(Buttons B, SDL_Surface *screen, int *Mode);
void AfficherButQuit(Buttons B, SDL_Surface *screen);
void AfficherButPlus(Buttons B, SDL_Surface *screen);
void AfficherButMoins(Buttons B, SDL_Surface *screen);
void AfficherButOption(Buttons B, SDL_Surface *screen);

//////////////////////////////
void initBackMain(Background *Back);
void initBackNGame(Background *Back);
void initBackSet(Background *Back);
//void initBack(Background *Back);

//////////////////////////////
void AfficherMain(Background Main, SDL_Surface *screen, int i);
void AfficherNGame(Background NGame, SDL_Surface *screen);
void AfficherSet(Background Set, SDL_Surface *screen);
void Afficherback(Background Set, SDL_Surface *screen);

//////////////////////////////
void freeBackMain(Background Back);
void freeBackNGame(Background Back);
void freeBackSet(Background Back);
void freeBack(Background Back);







int initTextvie(Text* T);

void displayvie(Text T,SDL_Surface *screen);
void freeTextvie(Text T);
int loadFontvie(Text* T, char* path);
int initTextscore(Text* T);
void displayscore(Text T,SDL_Surface *screen);
void freeTextscore(Text T);
int loadFontscore(Text* T, char* path);
int initTextscore1(Text* T);
int loadFontvie1(Text* T, char* path);

////////////////////////////////
void initialisation(tic *t);

void affichage(tic t,SDL_Surface *ecran ) ;

int atilganer(int tabsuivi[]);
void animation_back(SDL_Surface *backg[], SDL_Rect pos_backg,SDL_Surface *screen,int x);

void calcul_coup(int tabsuivi[]);

void Resultat (tic t,SDL_Surface* ecran);

void liberationmemoire(tic t);
void init_enigme(enigme * e, char *nomfichier); 
void  generate_afficher (int *alea) ;
void afficherEnigme(enigme e, SDL_Surface * screen); 
int resolution (int * running,int *run); 
void afficher_resultat (SDL_Surface * screen,int s,int r,enigme *en);
void animer (enigme * e); 

#endif
