/*****************************************************************************
 FILE      :  particles.c
 PROGRAM   :  Particle System
 AUTHOR    :  Warsame Egal and Charles Ambaiowei
 DUE DATE  :  November 02, 2015
 COURSE    :  CST8234, Carolina Ayala
 PURPOSE   :  Implement a particle system
 CHALLENGES:  Linked List 
 DIFFICULTY:  3-4
*****************************************************************************/

/***********************************************
 Include private library headers.
***********************************************/
#include "p.h"

/********************************************************************* 
 FUNCTION :  particle_init 
 PURPOSE  :  initialize the properties of a single particle 
 INPUT    :  pointer to the particle structure to be initialized 
 OUTPUT   :  returns ­1 on error, 0 on success 
 NOTES    :  
 *********************************************************************/
int particle_init(struct particle* p) {

   /* particle color is randomized*/
   p->color.r = ((float)rand()/(float)RAND_MAX);
   p->color.g = ((float)rand()/(float)RAND_MAX);
   p->color.b = ((float)rand()/(float)RAND_MAX);
   p->color.a = 1.0f;

   /* particle direction is randomized*/
   p->dir.x = ((float)rand()/(float)RAND_MAX);
   p->dir.y = ((float)rand()/(float)RAND_MAX);
   p->dir.z = ((float)rand()/(float)RAND_MAX);
   
   /* particle speed is set*/
   p->spd.x = 5.0f;
   p->spd.y = 5.0f;
   p->spd.z = 5.0f;

   /* particle position is randomized*/
   p->pos.x = ((float)rand()/(float)RAND_MAX);
   p->pos.y = ((float)rand()/(float)RAND_MAX);
   p->pos.z = ((float)rand()/(float)RAND_MAX);

   /*lifespan of partricle*/
   p->lifespan = 500; 

   /*particle size*/
   p->size = 1;	
   
   return 0;		
}

/********************************************************************* 
 FUNCTION :  particle_add 
 PURPOSE  :  add a particle to the dynamic particle linked list 
 INPUT    :  struct particle *head. Head of the particle list 
 OUTPUT   :  returns ­1 on error, 0 on success 
 NOTES    :  Calls particle_init()
 ********************************************************************/
int particle_add(struct particle **head) {
   struct particle *part = malloc(sizeof(struct particle));

    part->next = *head;
    particle_init(part); /*call function with particle properties adds the particle*/
   *head = part; /*first node*/

   return 0;
}

/********************************************************************* 
 FUNCTION :  particle_remove 
 PURPOSE :   remove a specific particle from the dynamic 
               particle linked list 
 INPUT    :  pointer to the particle to remove 
 OUTPUT   :  returns ­1 on error, 0 on success 
 NOTES    :  Particle can be situated in any place in the list.  
             Usually deleted because the lifespan ran out
 ********************************************************************/
int particle_remove(struct particle* p) {
   struct particle *temp; 
   int count = 0;

   temp = p;/*temp points to the head*/

   /*lifespan decreased by 1 everytime it loops through linkedlist*/
   while(temp->lifespan > 0) { /*5 lifespan first*/ 
      temp->lifespan = temp->lifespan-1;     
      count++;
   } 

   return 0;
}

/********************************************************************* 
 FUNCTION :  particle_destroy 
 PURPOSE  :  free memory used by the dynamic particle linked list 
 INPUT    :  struct particle **head. Head of the particle list 
 OUTPUT   :  returns ­1 on error, 
               the number of particles destroyed on success 
 NOTES    :  removes all particles from the list 
               Calls particle_remove()
 ********************************************************************/
int particle_destroy(struct particle **head) {  
   struct particle *temp;
   int count;

   if(*head == NULL) return 1; /*if true exit*/

  /*loop list and calculate amount of lifespanthat will be freed*/
   while(*head !=NULL) { 
      temp = *head;           /*pass pointer to temp*/ 
      count = temp->lifespan ;/*pass the amount of lifespan before deletion*/
      particle_remove(*head); /*calls remove function*/
      *head = temp->next;     /*go through the list*/
      free(temp);             /*list is now empty*/
   }
   
   printf("count of free: %d\n", count ); /*count before free*/
   printf("lifespanAfter: %d\n", temp->lifespan); /*count of lifespan after free*/

   return count; /*return the number of particles destroyed from the list */
}

/******************************************************************** 
 FUNCTION :  particle_update 
 PURPOSE  :  update the particles properties to be rendered 
               in the next frame 
 INPUT    :  struct particle **head. Head of the particle list 
 OUTPUT   :  returns ­1 on error, 0 on success 
 NOTES    :  Creativity and more creativity here for you !!!
 ********************************************************************/
int particle_update(struct particle **head) {

   struct particle *current;
   
   current = *head; 

   if(current == NULL) return 1; /*error then exit nothing in list*/
   
   /*loop through list and change the particles movements*/
   while(current != NULL) {
      current->pos.x += current->spd.x * current->dir.x; 
      current->pos.y += current->spd.y * current->dir.y;
      current->pos.z += current->spd.z * current->dir.z;
      
     /*particles bounce off screen sides by setting boundries, must alter when changing screen size*/
      if (current->pos.x > 120 || current->pos.x < -120) { 
         current->dir.x *= -1;
      }
      else if (current->pos.y > 100 || current->pos.y < -100){
         current->dir.y *= -1;
      }

      current = current->next; 
   }

   return 0;
}

