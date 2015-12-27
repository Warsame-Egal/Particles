/*****************************************************************************
 FILE      :  particles.c
 PROGRAM   :  Particle System
 AUTHOR    :  Warsame Egal
 PURPOSE   :  Implement a particle system
 CHALLENGES:  Linked List 
*****************************************************************************/

/***********************************************
 Include linux library headers.
 ***********************************************/
#include <time.h>

/***********************************************
 Include OpenGL library headers.
 ***********************************************/
#include <GL/glut.h>

/***********************************************
 Include C library headers.
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************
 Constant definitions.
 ***********************************************/

#define DFLT_INIT_NUM_PARTICLES 500
#define   ON    1
#define   OFF   0
#define   OK    0
#define   FAIL  -1
#define   POINTS 0

/***********************************************
 Default Window properties.
 ***********************************************/

#define WINDOW_TITLE          "CST8234 - Simple Particle Systems - Warsame Egal"
#define DFLT_INIT_POS           0
#define DFLT_INIT_WINDOW_W      800
#define DFLT_INIT_WINDOW_H      600
#define ORTHO                   100         
#define R          	       (float)rand() / (float)(RAND_MAX / 1.0f)
#define G         	       (float)rand() / (float)(RAND_MAX / 1.0f)
#define B            	       (float)rand() / (float)(RAND_MAX / 1.0f)
#define A          	        1.0f

/* animation frames per second*/
#define DFLT_FPS   30
#define MS        ( unsigned int ) ( 1000.0 / DFLT_FPS )

/***********************************************
 Struct definitions.
 ***********************************************/

struct color
{
   float r;
   float g;
   float b;
   float a;
}; 
typedef struct color Color4;

struct vector 
{
   float x;
   float y;
   float z;
};
typedef struct vector Point3D;
typedef struct vector Vector3D;

struct particle 
{
   Color4    color;
   Point3D   pos;
   Vector3D  dir;
   Vector3D  spd;	
   int       lifespan;
   int       size;
   struct particle* next;
};

/***********************************************
 Function prototype definitions.
 ***********************************************/

int particle_init(struct particle* );
int particle_add(struct particle **);
int particle_remove(struct particle* );
int particle_destroy(struct particle **);
int particle_update(struct particle **);
void exit_func(void);
void Init( void );
void RenderParticles(void);
void reshape(int, int);
void animate(int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);

/***********************************************
 * Global variables -- problem with glut
 ***********************************************/

int window;


