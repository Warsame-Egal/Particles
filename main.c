/*****************************************************************************
 FILE      :  particles.c
 PROGRAM   :  Particle System
 AUTHOR    :  Warsame Egal
 PURPOSE   :  Implement a particle system
 CHALLENGES:  Linked List 
*****************************************************************************/

/***********************************************
 Include private library headers.
***********************************************/
#include "p.h"

/* particle list head*/
struct particle* particles = NULL;

/*****************************************************************************
  FUNCTION :  main
  PURPOSE  :  create the window and particle list, start the glut main loop
  INPUT    :  command line arguments 
  OUTPUT   :  returns 0 (but not really since glutMainLoop doesn't return)
  NOTES    :
 ******************************************************************************/
int main(int argc, char **argv)  {  

   	/*
    	 *  Create the window & basic initialiation
	 *  The window starts in position ( DFLT_INIT_POS, DFLT_INIT_POS ) 
	 *  The screen starts in ( 0, 0 ) in the upper left corner
    	 *  The window size is DFLT_INIT_WINDOW_W x  DFLT_INIT_WINDOW_H in pixels
    	 *  The window title is WINDOW_TITLE 
    	 */
   	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
   	glutInitWindowSize(DFLT_INIT_WINDOW_W, DFLT_INIT_WINDOW_H);
   	glutInitWindowPosition(DFLT_INIT_POS, DFLT_INIT_POS);  
   	window = glutCreateWindow(WINDOW_TITLE);

	/*
	 *  Basic OpenGL functions 
	 *  Register for the glutMainLoop
	 */
   	glutDisplayFunc( RenderParticles );

        glutReshapeFunc(reshape);
   	glutMouseFunc(mouse);
   	glutKeyboardFunc(keyboard);

   	/*
	 * Initialization of OpenGL + Particles
	 */
   	Init( );

	/*
	 *  Register function to be called when exit
	 */
   	atexit(exit_func);

   	/*
	 *  Timer function to redraw depending of your frames per seconds
	 */
   	glutTimerFunc(MS, animate, 0);

   	/*
	 *  Main loop for opengl
	 */
   	glutMainLoop();
 
   	/*
	 * MainLoop never returns to this main
	 * Here to be ansi
 	 */
   	return OK;
}


/*****************************************************************************
 FUNCTION :  init
 PURPOSE  :  Basic initialization of OpenGL - done once
             Create the particles at the beginning
 INPUT    :  void
 OUTPUT   :  void
 NOTES    :  Enable 3D, color blending
 *****************************************************************************/
void Init( void ) {

	int i;
        GLfloat lightPos0[] = { 20.0, 20.0, 20.0, 1.0 };
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glEnable( GL_COLOR_MATERIAL );
        glEnable( GL_NORMALIZE );
        glLightfv( GL_LIGHT0, GL_POSITION, lightPos0 );
   	glClearColor(R, B, G, A);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glClearDepth(1.0);		
	glEnable( GL_DEPTH_TEST ); 
	glEnable( GL_CULL_FACE );

   	srand(time(NULL));

        /* 
         * DFLT_INIT_NUM_PARTICLES defined in particles.h
         * Create particles and add them into the particles list
         * Here first call to one of your functions
         */

	for ( i = 0; i < DFLT_INIT_NUM_PARTICLES; i++ ) {
		particle_add( &particles);
        }

	return;

}

/*****************************************************************************
 FUNCTION :  exit_func
 PURPOSE  :  calls particle_destroy to free the link list if it exists
 INPUT    :  void
 OUTPUT   :  void
 NOTES    :  
 ******************************************************************************/
void exit_func(void) {

   	particle_destroy( &particles );

}


/*****************************************************************************
 FUNCTION :  animate 
 PURPOSE  :  update the particles, redraw the screen, restart the timer
 INPUT    :  not used
 OUTPUT   :  void
 NOTES    :
 ******************************************************************************/
void animate(int step) {

	/*
	 * Update the particles
	 */
   	particle_update( &particles );

   	/*
	 * Render the particles again 
	 */
   	glutPostRedisplay();

   	/*
	 * Restart the timer
	 */
   	glutTimerFunc(MS, animate, 0);
}

/*****************************************************************************
  FUNCTION :  RenderParticles
  PURPOSE  :  clear the screen, render the particles, swap the buffers
  INPUT    :  void
  OUTPUT   :  void
  NOTES    :
 ******************************************************************************/
void RenderParticles(void) {

   	struct particle* tmp = particles;

   	/*
	 *   clear the buffers
	 */
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	/*
	 *  Draw my particles
	 *  if POINTS is set to 1, then draws in just points
	 *  if POINTS is set to 0, then draws 3D spheres of size particle->size
	 */

	if ( POINTS ) {
  		while (tmp != NULL ) {
			glColor4f(tmp->color.r, tmp->color.g, tmp->color.b, tmp->color.a); 
			glPointSize(tmp->size);
			glBegin(GL_POINTS);
				glVertex3f(tmp->pos.x, tmp->pos.y, tmp->pos.z); 
			glEnd();
			tmp = tmp->next; 
  		}
	}
	else
   		while (tmp != NULL ) {
  			glColor4f(tmp->color.r, tmp->color.g, tmp->color.b, tmp->color.a); 
			glPushMatrix( );
				glTranslatef( tmp->pos.x, tmp->pos.y, tmp->pos.z );
				glutSolidSphere( tmp->size, 50, 50 );
			glPopMatrix();
      			tmp = tmp->next; 
   		}
		
	/*
	 * Swap the buffers
	 */
   	glutSwapBuffers();

}

/*****************************************************************************
  FUNCTION :  keyboard
  PURPOSE  :  callback
  INPUT    :  the key pressed
  OUTPUT   :  void
  NOTES    :  exits on 'q' or 'Q'
 ******************************************************************************/
void keyboard(unsigned char key, int x, int y) {

   	switch(key) {
		/*
		 * Press the space bar to add a particle
		 */
   		case ' ':
   			particle_add( &particles);
   			break;
                case 'L':
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
                break;

                case 'l':
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
                break;
                
                case 'C': 
                glEnable( GL_COLOR_MATERIAL );
                break;
 
                case 'c': 
                glDisable( GL_COLOR_MATERIAL );
                break;

                case 'S': 
                glShadeModel( GL_SMOOTH );
                break;
 
                case 's': 
                glShadeModel( GL_FLAT );
                break;

      		case 'q': 
 
      		case 'Q':  {
   			glutDestroyWindow(window);
   			exit( 0 );
        		break;
      		}
   	}
	glutPostRedisplay();
  
}

/*****************************************************************************
 FUNCTION :  mouse
 PURPOSE  :  callback
 INPUT    :  the button and its state
 OUTPUT   :  void
 NOTES    :  exits on middle mouse click
 *****************************************************************************/
void mouse(int button, int state, int x, int y) {
   	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
      		glutDestroyWindow(window);
   		exit(0);
   	}

	glutPostRedisplay();
}


/*****************************************************************************
  FUNCTION :  reshape
  PURPOSE  :  handle window resizing by updating the viewport and ortho
  INPUT    :  new window width and height
  OUTPUT   :  void
  NOTES    :  The ortho function defines the viewable world in which you
              render your particles.
              Ortho creates a 3D cube, anything you draw inside the cube
              gets render in your window.
              The world is centered in ( 0, 0, 0 ) in the middle of the screen
 ******************************************************************************/
void reshape(int w, int h) {

   	if (h == 0) h = 1;
   	glViewport( 0, 0, w, h );
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
        
   	if (w <= h)  glOrtho( -ORTHO, ORTHO, -ORTHO * h / w,  ORTHO * h / w, -ORTHO, ORTHO);
   	else    glOrtho( -ORTHO * w / h,  ORTHO * w / h, -ORTHO,          ORTHO,         -ORTHO, ORTHO );

   	glMatrixMode(GL_MODELVIEW);

}
































