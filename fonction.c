#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "fonction.h"
#include <SDL/SDL_ttf.h>

#define CHARACTER_WIDTH 100
#define CHARACTER_HEIGHT 195
#include <stdbool.h> 

#define NUM_FRAMES_RIGHT 13
#define NUM_FRAMES_LEFT 13

#define NUMM_FRAMES_RIGHT 10
#define NUMM_FRAMES_LEFT 10

// Function to initialize animation frames for both directions
// Function to initialize animation frames for right direction
bool init_animation_right(struct Animation* anim) {
    char filename[50];

    // Load frames for right direction animation
    for (int i = 0; i < NUM_FRAMES_RIGHT; ++i) {
        snprintf(filename, sizeof(filename), "right/background%d.png", i);
        anim->anim_right[i] = IMG_Load(filename);
        if (!anim->anim_right[i]) {
            printf("Error loading right frame %d: %s\n", i, SDL_GetError());
            return false; // Return failure if any frame fails to load
        }
    }

    return true; // Return success
}

// Function to initialize animation frames for left direction
bool init_animation_left(struct Animation* anim) {
    char filename[50];

    // Load frames for left direction animation
    for (int i = 0; i < NUM_FRAMES_LEFT; ++i) {
        snprintf(filename, sizeof(filename), "left/background%d.png", i);
        anim->anim_left[i] = IMG_Load(filename);
        if (!anim->anim_left[i]) {
            printf("Error loading left frame %d: %s\n", i, SDL_GetError());
            return false; // Return failure if any frame fails to load
        }
    }

    return true; // Return success
}

// Function to display animation frames for right direction
void afficher_animation_right(struct Animation anim, SDL_Surface* screen) {
    static int frameIndex = 0; // Static variable to retain frame index between function calls
    SDL_Surface* currentFrame = anim.anim_right[frameIndex];

    // Blit the current animation frame onto the screen
    SDL_BlitSurface(currentFrame, NULL, screen, &anim.pos);

    // Increment frame index
    frameIndex++;

    // Reset frame index if it exceeds the number of frames
    if (frameIndex == NUM_FRAMES_RIGHT) {
        frameIndex = 0;
    }
}

// Function to display animation frames for left direction
void afficher_animation_left(struct Animation anim, SDL_Surface* screen) {
    static int frameIndex = 0; // Static variable to retain frame index between function calls
    SDL_Surface* currentFrame = anim.anim_left[frameIndex];

    // Blit the current animation frame onto the screen
    SDL_BlitSurface(currentFrame, NULL, screen, &anim.pos);

    // Increment frame index
    frameIndex++;

    // Reset frame index if it exceeds the number of frames
    if (frameIndex == NUM_FRAMES_LEFT) {
        frameIndex = 0;
    }
}

// Function to free resources used by animation frames
void liberer_animation(struct Animation* anim) {
    // Free surfaces for right direction animation frames
    for (int i = 0; i < NUM_FRAMES_RIGHT; ++i) {
        SDL_FreeSurface(anim->anim_right[i]);
    }

    // Free surfaces for left direction animation frames
    for (int i = 0; i < NUM_FRAMES_LEFT; ++i) {
        SDL_FreeSurface(anim->anim_left[i]);
    }
}


   void move_bird_animation(SDL_Rect* pos, int* tempsp, int* tempsa, int* v) {
    *tempsa = SDL_GetTicks();
    if (*tempsa - *tempsp > 20) {
        if (pos->x <= 1200 && *v == 1) {
            pos->x += 15;
            if (pos->x >= 1200)
                *v = 2;
        }
        if (*v == 2) {
            pos->x -= 15;
            if (pos->x <= 900)
                *v = 1;
        }
        *tempsp = *tempsa;
    }
}
int collitrigo(SDL_Surface *  box,SDL_Surface *circle,SDL_Rect boxpos,SDL_Rect circlepos)
{

float a,b,r,x;

a=circlepos.x+(circlepos.w/2);
b=circlepos.y+(circlepos.h/2);
r=(circlepos.w/2)*(circlepos.w/2);//rayon carre 

   if( ( ( (boxpos.x+boxpos.w)<a || boxpos.x>a) || (((b-boxpos.y)*(b-boxpos.y)) > r) )
      &&( ( (boxpos.x+boxpos.w)<a || boxpos.x>a) || (((b-(boxpos.y+boxpos.h))*(b-(boxpos.y+boxpos.h))) > r) )
      &&(( ( ( (boxpos.x-a)*(boxpos.x-a))+(((boxpos.y+boxpos.h)-b)*((boxpos.y+boxpos.h)-b))) )>r)
      &&(( ((boxpos.x-a)*(boxpos.x-a))+((boxpos.y-b)*(boxpos.y-b)))>r)
      &&( ( (boxpos.y+boxpos.h)<b || boxpos.y>b) || ( ( (a-boxpos.x)*(a-boxpos.x)) > r) )
      &&(( ( ( ((boxpos.x+boxpos.w)-a)*((boxpos.x+boxpos.w)-a))+(((boxpos.y+boxpos.h)-b)*((boxpos.y+boxpos.h)-b))) )>r)
     &&(( (((boxpos.x+boxpos.w)-a)*((boxpos.x+boxpos.w)-a))+((boxpos.y-b)*(boxpos.y-b)))>r) 
       && ( ( (boxpos.y+boxpos.h)<b || boxpos.y>b) || ( ( (a-(boxpos.x+boxpos.w))*(a-(boxpos.x+boxpos.w))) > r) )
      )
return 1;
else return 0;
}

void scorecount(int* score , SDL_Surface ** coeur, int etat )
{

if (etat)
(*score)--;
else
(*score)++;
if (*score<0)
*score=0;
if(*score>3)
*score=3;
if (*score==0)
*coeur= IMG_Load("v4.png");
if (*score==1)
*coeur= IMG_Load("v3.png");
if (*score==2)
*coeur= IMG_Load("v2.png");
if (*score==3)
*coeur= IMG_Load("v1.png");




}



void initializeEnemyHealth(EnemyHealth* health) {
    health->full_hp = IMG_Load("ennemi_full.png");
    health->half_hp = IMG_Load("ennemi_half.png");
    health->dead = IMG_Load("dead.png");
    health->current_hp = 3;  // 3 hits to kill
    health->cooldown = 0;
    health->cooldown_time = 30; // About 0.5 seconds at 60 FPS
}

void updateEnemyHealth(EnemyHealth* health, int* game_state) {
    // Only process hit if cooldown is over
    if (health->cooldown <= 0) {
        if (health->current_hp > 0) {
            health->current_hp--;
            health->cooldown = health->cooldown_time; // Reset cooldown
            
            // Push enemy back slightly to prevent immediate re-collision
            // You'll need to pass the enemy position here
        }
        
        if (health->current_hp <= 0) {
            *game_state = 1;
        }
    } else {
        health->cooldown--; // Decrement cooldown timer
    }
}


void initializeES(ES* es)
{
	SDL_Surface* tmp  ;
         tmp = IMG_Load("bonus.png");
	es->image = tmp;


	SDL_Rect pos;
	pos.x=1000;
	pos.y=850;
	es->espos=pos;
	
}
void mves(SDL_Rect* pos,int* tempsp, int* tempsa, int* v)
{

*tempsa=SDL_GetTicks();
if(*tempsa-*tempsp>20)
{
if(pos->x<=1200&&*v==1)
{
pos->x+=15;
if(pos->x>=1200)
*v=2;
}
if (*v==2)
{pos->x-=15;
if(pos->x<=900)
*v=1;
}
*tempsp=*tempsa;
}
}

void initializeES2(ES* es)
{
	SDL_Surface* tmp  ;
         tmp = IMG_Load("ennemi.png");
	es->image = tmp;


	SDL_Rect pos;
	pos.x=300;
	pos.y=730;
	es->espos=pos;
	
}


void mves2(SDL_Rect* pos,int* tempsp, int* tempsa, int* v)
{

*tempsa=SDL_GetTicks();
if(*tempsa-*tempsp>20)
{
if(pos->x<=300&&*v==1)
{
pos->x+=15;
if(pos->x>=300)
*v=2;
}
if (*v==2)
{pos->x-=15;
if(pos->x<=1)
*v=1;
}
*tempsp=*tempsa;
}
}

void initializeES3(ES* es)
{
	SDL_Surface* tmp  ;
    tmp = IMG_Load("ennemi2.png");
	es->image = tmp;

	SDL_Rect pos;
	pos.x = 650; // Keep the x coordinate the same as before
	pos.y = 50; // Set the initial y coordinate
	es->espos = pos;
}

void mves3(SDL_Rect* pos,int* tempsp, int* tempsa, int* v)
{
	*tempsa = SDL_GetTicks();
	if(*tempsa - *tempsp > 20)
	{
		if(pos->y <= 530 && *v == 1) // Modify this condition to move up
		{
			pos->y += 35; // Move down
			if(pos->y >= 530)
				*v = 2;
		}
		if(*v == 2)
		{
			pos->y -= 35; // Move up
			if(pos->y <= 1)
				*v = 1;
		}
		*tempsp = *tempsa;
	}
}





int checkBirdCollision(SDL_Rect characterRect, SDL_Rect birdRect) {
    // Define the region where collision detection should occur based on the bird's movement range
    int birdMovementStartX = 10; // Adjust according to the starting x-coordinate of the bird's movement range
    int birdMovementEndX = 400; // Adjust according to the ending x-coordinate of the bird's movement range
    int birdY = birdRect.y + (birdRect.h / 2); // Calculate the y-coordinate of the bird's center

    // Check if the character's position overlaps with the bird's movement range vertically
    if (characterRect.y + characterRect.h >= birdRect.y && characterRect.y <= birdRect.y + birdRect.h) {
        // Check if the character's position overlaps with the bird's movement range horizontally
        if (characterRect.x + characterRect.w >= birdMovementStartX && characterRect.x <= birdMovementEndX) {
            // Collision detected within the specified bird movement range
            return 1;
        }
    }
    // No collision within the specified bird movement range
    return 0;
}








////////animation level 2

bool init_animation_right2(struct Animation* anim) {
    char filename[50];

    // Load frames for right direction animation
    for (int i = 0; i < NUMM_FRAMES_RIGHT; ++i) {
        snprintf(filename, sizeof(filename), "cowboy/right/background%d.png", i);
        anim->anim_right[i] = IMG_Load(filename);
        if (!anim->anim_right[i]) {
            printf("Error loading right frame %d: %s\n", i, SDL_GetError());
            return false; // Return failure if any frame fails to load
        }
    }

    return true; // Return success
}

// Function to initialize animation frames for left direction
bool init_animation_left2(struct Animation* anim) {
    char filename[50];

    // Load frames for left direction animation
    for (int i = 0; i < NUMM_FRAMES_LEFT; ++i) {
        snprintf(filename, sizeof(filename), "cowboy/left/background%d.png", i);
        anim->anim_left[i] = IMG_Load(filename);
        if (!anim->anim_left[i]) {
            printf("Error loading left frame %d: %s\n", i, SDL_GetError());
            return false; // Return failure if any frame fails to load
        }
    }

    return true; // Return success
}

// Function to display animation frames for right direction
void afficher_animation_right2(struct Animation anim, SDL_Surface* screen) {
    static int frameIndex = 0; // Static variable to retain frame index between function calls
    SDL_Surface* currentFrame = anim.anim_right[frameIndex];

    // Blit the current animation frame onto the screen
    SDL_BlitSurface(currentFrame, NULL, screen, &anim.pos);

    // Increment frame index
    frameIndex++;

    // Reset frame index if it exceeds the number of frames
    if (frameIndex == NUMM_FRAMES_RIGHT) {
        frameIndex = 0;
    }
}

// Function to display animation frames for left direction
void afficher_animation_left2(struct Animation anim, SDL_Surface* screen) {
    static int frameIndex = 0; // Static variable to retain frame index between function calls
    SDL_Surface* currentFrame = anim.anim_left[frameIndex];

    // Blit the current animation frame onto the screen
    SDL_BlitSurface(currentFrame, NULL, screen, &anim.pos);

    // Increment frame index
    frameIndex++;

    // Reset frame index if it exceeds the number of frames
    if (frameIndex == NUMM_FRAMES_LEFT) {
        frameIndex = 0;
    }
}

// Function to free resources used by animation frames
void liberer_animation2(struct Animation* anim) {
    // Free surfaces for right direction animation frames
    for (int i = 0; i < NUMM_FRAMES_RIGHT; ++i) {
        SDL_FreeSurface(anim->anim_right[i]);
    }

    // Free surfaces for left direction animation frames
    for (int i = 0; i < NUMM_FRAMES_LEFT; ++i) {
        SDL_FreeSurface(anim->anim_left[i]);
    }
}


   void move_bird_animation2(SDL_Rect* pos, int* tempsp, int* tempsa, int* v) {
    *tempsa = SDL_GetTicks();
    if (*tempsa - *tempsp > 20) {
        if (pos->x <= 1200 && *v == 1) {
            pos->x += 15;
            if (pos->x >= 1200)
                *v = 2;
        }
        if (*v == 2) {
            pos->x -= 15;
            if (pos->x <= 900)
                *v = 1;
        }
        *tempsp = *tempsa;
    }
}



void initializeEnemyHealth2(EnemyHealth* health) {
    health->full_hp = IMG_Load("ennemi_full.png");
    health->half_hp = IMG_Load("ennemi_half.png");
    health->dead = IMG_Load("dead.png");
    health->current_hp = 3;  // 3 hits to kill
    health->cooldown = 0;
    health->cooldown_time = 30; // About 0.5 seconds at 60 FPS
}

void updateEnemyHealth2(EnemyHealth* health, int* game_state) {
    // Only process hit if cooldown is over
    if (health->cooldown <= 0) {
        if (health->current_hp > 0) {
            health->current_hp--;
            health->cooldown = health->cooldown_time; // Reset cooldown
            
            // Push enemy back slightly to prevent immediate re-collision
            // You'll need to pass the enemy position here
        }
        
        if (health->current_hp <= 0) {
            *game_state = 1;
        }
    } else {
        health->cooldown--; // Decrement cooldown timer
    }
}














