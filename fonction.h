#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include <stdbool.h> 
#define NUM_FRAMES_RIGHT 13
#define NUM_FRAMES_LEFT 13
#define NUMM_FRAMES_RIGHT 10
#define NUMM_FRAMES_LEFT 10

typedef struct ES ES ;
struct ES
{

SDL_Surface *image;

SDL_Rect espos;



};
struct Animation {
    SDL_Surface* anim_right[NUM_FRAMES_RIGHT]; // Array for right direction animation frames
    SDL_Surface* anim_left[NUM_FRAMES_LEFT];   // Array for left direction animation frames
    SDL_Rect pos;
    SDL_Rect espos;
    SDL_Surface *ennemi;
};


typedef struct EnemyHealth {
    SDL_Surface* full_hp;
    SDL_Surface* half_hp;
    SDL_Surface* dead;
    int current_hp;
    int cooldown;       // Cooldown timer
    int cooldown_time;  // How long between hits (in frames)
} EnemyHealth;

void initializeEnemyHealth(EnemyHealth* health);
void updateEnemyHealth(EnemyHealth* health, int* game_state);

bool init_animation_right(struct Animation* anim);
bool init_animation_left(struct Animation* anim);
void afficher_animation_right(struct Animation anim, SDL_Surface* screen);
void afficher_animation_left(struct Animation anim, SDL_Surface* screen);
void liberer_animation(struct Animation* anim);
//lvl2 animation
bool init_animation_right2(struct Animation* anim);
bool init_animation_left2(struct Animation* anim);
void afficher_animation_right2(struct Animation anim, SDL_Surface* screen);
void afficher_animation_left2(struct Animation anim, SDL_Surface* screen);
void liberer_animation2(struct Animation* anim);
void move_bird_animation2(SDL_Rect* pos, int* tempsp, int* tempsa, int* v);
void initializeEnemyHealth2(EnemyHealth* health);
void updateEnemyHealth2(EnemyHealth* health, int* game_state);

int checkBirdCollision(SDL_Rect characterRect, SDL_Rect birdRect);
void move_bird_animation(SDL_Rect* pos, int* tempsp, int* tempsa, int* v);
int collitrigo(SDL_Surface *  box,SDL_Surface *circle,SDL_Rect boxpos,SDL_Rect circlepos);
void scorecount(int* score , SDL_Surface ** coeur, int etat );
void initializeES(ES* es);
void initializeES2(ES* es);
void mves(SDL_Rect* pos,int* tempsp, int* tempsa, int* v);
void mves2(SDL_Rect* pos,int* tempsp, int* tempsa, int* v);

void initializeES3(ES* es);
void mves3(SDL_Rect* pos,int* tempsp, int* tempsa, int* v);


