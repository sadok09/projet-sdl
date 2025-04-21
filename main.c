#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "fonction.h"
#include <SDL/SDL_ttf.h>
#include <stdbool.h> 
#define NUM_FRAMES_RIGHT 13
#define NUM_FRAMES_LEFT 13
#define NUMM_FRAMES_RIGHT 10 
#define NUMM_FRAMES_LEFT 10


void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
	break;
        }
    }
}

int main (void)
{
SDL_Surface *screen =NULL;
SDL_Init(SDL_INIT_VIDEO);
SDL_EnableKeyRepeat(10,40);
int continuer=1;
screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
SDL_Surface *fond=NULL,*fond2=NULL,*dead=NULL,*perso,*flashdisk,*ennemi,*ennemi2,*coeur;
SDL_Rect positionfond,positiondead,persopos,flashdiskpos,ennemipos,ennemi2pos,poscoeur;

SDL_Event event;

int direction = 1; // 1 for right, -1 for left
struct Animation myAnimation;

// Initialize animation frames based on the initial direction
if (direction == 1) {
    if (!init_animation_right(&myAnimation)) {
        // Handle initialization failure
        printf("Failed to initialize right animation.\n");
        return 1;
    }
} else {
    if (!init_animation_left(&myAnimation)) {
        // Handle initialization failure
        printf("Failed to initialize left animation.\n");
        return 1;
    }
}
      myAnimation.pos.x =20;
    myAnimation.pos.y = 720;
    myAnimation.pos.h = 281;
     myAnimation.pos.w = 197;



// In main.c, you have:
struct Animation myAnimation2;
if (direction == 1) {
    if (!init_animation_right2(&myAnimation2)) {
        printf("Failed to initialize right animation.\n");
        return 1;
    }
} else {
    if (!init_animation_left2(&myAnimation2)) {
        printf("Failed to initialize left animation.\n");
        return 1;
    }
}
myAnimation2.pos.x = 20;
myAnimation2.pos.y = 550;
myAnimation2.pos.h = 259;
myAnimation2.pos.w = 132;




int tempsx = 0;
int tempsz = 0;
int z = 1;
int tempsp=0,tempsa=0;
int v=1;
int tempspb=0,tempsab=0;
int vb=1;
int tempspbb=0,tempsabb=0;
int vbb=1;


ES es,es2,es3;
initializeES(&es);
//initializeES2(&es2);
initializeES3(&es3);
int mvd=0,mvgg=0,mvg=0,verif1=0,verif2=0,verif3=0,etat;
int score=0;

poscoeur.x=0;
poscoeur.y=0;
coeur= IMG_Load("v4.png");


positionfond.x=0;
positionfond.y=0;
fond= IMG_Load("back.jpg");
fond2= IMG_Load("back2.jpg");
dead= IMG_Load("dead.png");
    int bird_movement_enabled = 1; // Initialize bird movement enabled flag

 EnemyHealth enemyHealth;
    initializeEnemyHealth(&enemyHealth);

 EnemyHealth enemyHealth2;
    initializeEnemyHealth2(&enemyHealth2);
    int game_state = 0;

perso=IMG_Load("perso.png");
persopos.x=650;
persopos.y=800;
persopos.h=195;
persopos.w=100;
int x=1;
int xb=1;
int xbb=1;
int die=0;
int end=0;
int current_level=1;
// Add these with your other variable declarations
Uint32 level_start_time = SDL_GetTicks();  // Gets the initial time in milliseconds
Uint32 current_time;
const Uint32 LEVEL_DURATION = 10000;  // 60,000 ms = 1 minute

while (continuer == 1)
    {

    current_time = SDL_GetTicks();  // Add this at the VERY START of your loop

if (current_time - level_start_time >= LEVEL_DURATION && current_level == 1) {
    // Clean up level 1 resources
    liberer_animation(&myAnimation);
    
    // Initialize level 2
    current_level = 2;
    if (!init_animation_right2(&myAnimation2) || !init_animation_left2(&myAnimation2)) {
        printf("Failed to initialize level 2 animations\n");
        return 1;
    }
    myAnimation2.pos.x = 20;
    myAnimation2.pos.y = 550;
  persopos.y=600;
    // Reset other game state as needed
}

if (current_level==1)
{
    if (game_state == 1) {
        SDL_BlitSurface(enemyHealth.dead, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(3000);
        continuer = 0;
        continue;
    }

    SDL_BlitSurface(fond, NULL, screen, &positionfond);
SDL_BlitSurface(es.image,NULL,screen, &es.espos);
//SDL_BlitSurface(es2.image,NULL,screen, &es2.espos);
SDL_BlitSurface(es3.image,NULL,screen, &es3.espos);
SDL_BlitSurface(perso,NULL,screen, &persopos);
SDL_BlitSurface(coeur,NULL,screen, &poscoeur);



    if (checkBirdCollision(persopos, myAnimation.pos)) {
        updateEnemyHealth(&enemyHealth, &game_state);
        persopos.x=400;
        // Optional: Add visual feedback for hit
        if (enemyHealth.cooldown == enemyHealth.cooldown_time) {
            // Flash enemy or show hit effect
        }
    }
    // Display enemy based on health
    if (enemyHealth.current_hp == 2) {
        SDL_BlitSurface(enemyHealth.full_hp, NULL, screen, &myAnimation.pos);
    } else if (enemyHealth.current_hp == 1) {
        SDL_BlitSurface(enemyHealth.half_hp, NULL, screen, &myAnimation.pos);
    }



    
   //  afficher_animation(myAnimation, screen);
if(x==1)
{
mves(&es.espos,&tempsp,&tempsa,&v);
}
if(bird_movement_enabled)
{


 mves2(&myAnimation.pos,&tempsx,&tempsz,&z);
 if (direction == 1) {
        afficher_animation_right(myAnimation, screen);
    } else if (direction == -1){
        afficher_animation_left(myAnimation, screen);
    }

    // Switch animation frames if character reached end of movement
    if (direction == 1 && myAnimation.pos.x >= 250) {
        direction = -1; // Switch to left animation
        // Re-initialize animation frames for left direction
        if (!init_animation_left(&myAnimation)) {
            // Handle initialization failure
            printf("Failed to initialize left animation.\n");
            return 1;
        }
    } else if (direction == -1 && myAnimation.pos.x <= 1) {
        direction = 1; // Switch to right animation
        // Re-initialize animation frames for right direction
        if (!init_animation_right(&myAnimation)) {
            // Handle initialization failure
            printf("Failed to initialize right animation.\n");
            return 1;
        }
    }


      
 

}
if(xbb==1)
{
mves3(&es3.espos,&tempspbb,&tempsabb,&vbb);
}

}

if (current_level==2)
{
    SDL_BlitSurface(fond2, NULL, screen, &positionfond);
SDL_BlitSurface(perso,NULL,screen, &persopos);



    if (game_state == 1) {
        SDL_BlitSurface(enemyHealth.dead, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(3000);
        continuer = 0;
        continue;
    }




    if (checkBirdCollision(persopos, myAnimation2.pos)) {
        updateEnemyHealth2(&enemyHealth2, &game_state);
                persopos.x=400;
        // Optional: Add visual feedback for hit
        if (enemyHealth2.cooldown == enemyHealth2.cooldown_time) {
            // Flash enemy or show hit effect
        }
    }
    // Display enemy based on health
    if (enemyHealth2.current_hp == 2) {
        SDL_BlitSurface(enemyHealth2.full_hp, NULL, screen, &myAnimation2.pos);
    } else if (enemyHealth2.current_hp == 1) {
        SDL_BlitSurface(enemyHealth2.half_hp, NULL, screen, &myAnimation2.pos);
    }

    

if(bird_movement_enabled)
{


 mves2(&myAnimation2.pos,&tempsx,&tempsz,&z);
 if (direction == 1) {
        afficher_animation_right2(myAnimation2, screen);
    } else if (direction == -1){
        afficher_animation_left2(myAnimation2, screen);
    }

    // Switch animation frames if character reached end of movement
    if (direction == 1 && myAnimation2.pos.x >= 250) {
        direction = -1; // Switch to left animation
        // Re-initialize animation frames for left direction
        if (!init_animation_left2(&myAnimation2)) {
            // Handle initialization failure
            printf("Failed to initialize left animation.\n");
            return 1;
        }
    } else if (direction == -1 && myAnimation2.pos.x <= 1) {
        direction = 1; // Switch to right animation
        // Re-initialize animation frames for right direction
        if (!init_animation_right2(&myAnimation2)) {
            // Handle initialization failure
            printf("Failed to initialize right animation.\n");
            return 1;
        }
    }


      
 


}



}


        SDL_PollEvent(&event);
        switch(event.type)
        {



            case SDL_QUIT:
                continuer = 0;
                break;
	    case SDL_MOUSEMOTION: 
			
                        break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {   
		    case SDLK_ESCAPE:
			continuer=0;
			break; 
		   
                   
                    case SDLK_RIGHT:

etat=0;
verif2=0;
if(mvd==1)
{

persopos.x+=20;
mvd=0;
}
else
{
if(collitrigo(perso,flashdisk,persopos,es.espos))
{

persopos.x+=20;
x=1;

}
else {mvg=1;
     x=0; 
if (!verif1)
{scorecount(&score,&coeur,etat);
verif1=1;

}
}  


}

		    break;

                    case SDLK_LEFT: 

persopos.x-=20;

                      break;
		   case SDLK_UP: 
etat=1;
verif3=0;
if(mvgg==1)
{

persopos.y-=20;
mvgg=0;
}
else
{ 
if(collitrigo(perso,ennemi2,persopos,es3.espos))
{persopos.y-=20;
xbb=1;}
else {mvd=1; mvg=1;
xbb=0;
if (!verif3)
{scorecount(&score,&coeur,etat);
verif3=1;
}

 }     
}   
		   
		      break;
		      		   case SDLK_DOWN: 

persopos.y+=20;

		   
		      break;
                }
               

                
}
 


SDL_Flip(screen);
}





}

