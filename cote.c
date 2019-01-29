#define PROGRAM_TITLE "Vincent Cote Assignment 1"
#define DISPLAY_INFO "First OpenGL Program - Assn 1"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

// Some global variables.
// Window IDs, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

// Cube position and rotation speed variables.
float X_Rot   = 0.9f;  // Initially only rotate around X-axix.
float Y_Rot   = 0.0f;  // Later on you can use control keys to change
float X_Speed = 0.0f;  // the rotation.
float Y_Speed = 0.5f;
float Z_Off   =-5.0f;

//////////////////////////////////////////////////////////
// String rendering routine; leverages on GLUT routine. //
//////////////////////////////////////////////////////////
static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
   char buf[80]; // For our strings.
   
   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);

   // Reset to 0,0,0; no rotation, no scaling.
   glLoadIdentity();

   // Move the object back from the screen.
   glTranslatef(0.0f,0.0f,Z_Off);

   // Rotate the calculated amount.
   glRotatef(X_Rot,1.0f,0.0f,0.0f);
   glRotatef(Y_Rot,0.0f,1.0f,0.0f);

   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // OK, let's start drawing our planer quads.
   glBegin(GL_QUADS);

   // Far face.  Green, 50% opaque, non-uniform texture cooridinates.
   glNormal3f( 0.0f, 0.0f,-1.0f);
   glColor4f(0.2,0.9,0.2,.5);

   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glTexCoord2f(2.995f, 2.995f); glVertex3f(-1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.0f, -1.0f, -1.0f);

   // top face. Light blue
   glNormal3f(0.0f, 0.0f,1.0f);
   glColor4f(0.2,0.9,1.2,.5);

   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, 1.0f, -1.0f);
   glTexCoord2f(2.995f, 2.995f); glVertex3f(1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  1.0f, 1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( -1.0f, 1.0f, 1.0f);

   // bottom face. Yellow
   glNormal3f(0.0f, 0.0f,1.0f);
   glColor4f(1.2,0.9,0.2,.5);

   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glTexCoord2f(2.995f, 2.995f); glVertex3f(1.0f,  -1.0f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  -1.0f, 1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( -1.0f, -1.0f, 1.0f);

   // Right face.  Blue; 25% opaque
   glNormal3f( 1.0f, 0.0f, 0.0f);
   glColor4f(0.2,0.2,0.9,.25);

   glTexCoord2f(0.995f, 0.005f); glVertex3f( 1.0f, -1.0f, -1.0f);
   glTexCoord2f(0.995f, 0.995f); glVertex3f( 1.0f,  1.0f, -1.0f);
   glTexCoord2f(0.005f, 0.995f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glTexCoord2f(0.005f, 0.005f); glVertex3f( 1.0f, -1.0f,  1.0f);

   // Front face; offset.  Multi-colored, 50% opaque.
   glNormal3f( 0.0f, 0.0f, 1.0f);
   glColor4f( 0.9f, 0.2f, 0.2f, 0.5f);

   glTexCoord2f( 0.005f, 0.005f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glColor4f( 0.2f, 0.9f, 0.2f, 0.5f);
   glTexCoord2f( 0.995f, 0.005f); glVertex3f( 1.0f, -1.0f,  1.0f);
   glColor4f( 0.2f, 0.2f, 0.9f, 0.5f);
   glTexCoord2f( 0.995f, 0.995f); glVertex3f( 1.0f,  1.0f,  1.0f);
   glColor4f( 0.1f, 0.1f, 0.1f, 0.5f);
   glTexCoord2f( 0.005f, 0.995f); glVertex3f(-1.0f,  1.0f,  1.0f);


   // Left Face; offset.  Yellow, varying levels of opaque.
   glNormal3f(-1.0f, 0.0f, 0.0f);
   glColor4f(0.9,0.9,0.2,0.0);

   glTexCoord2f(0.005f, 0.005f); glVertex3f(-1.0f, -1.0f, -1.0f);
   glColor4f(0.9,0.9,0.2,0.66);
   glTexCoord2f(0.995f, 0.005f); glVertex3f(-1.0f, -1.0f,  1.0f);
   glColor4f(0.9,0.9,0.2,1.0);
   glTexCoord2f(0.995f, 0.995f); glVertex3f(-1.0f,  1.0f,  1.0f);
   glColor4f(0.9,0.9,0.2,0.33);
   glTexCoord2f(0.005f, 0.995f); glVertex3f(-1.0f,  1.0f, -1.0f);

   // All polygons have been drawn.
   glEnd();

   // Move back to the origin
   glLoadIdentity();

   // We need to change the projection matrix for the text rendering.
   glMatrixMode(GL_PROJECTION);

   // But we like our current view too; so we save it here.
   glPushMatrix();

   // Display a string
   // Now we set up a new projection for the text.
   glLoadIdentity();
   glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
   glColor4f(0.6,1.0,0.6,1.00);
   sprintf(buf,"%s", DISPLAY_INFO); // Print the string into a buffer
   glRasterPos2i(2,2);                         // Set the coordinate
   PrintString(GLUT_BITMAP_HELVETICA_12, buf);  // Display the string.

   
   // To ease, simply translate up.  Note we're working in screen
   // pixels in this projection.
   glTranslatef(6.0f, Window_Height - 14, 0.0f);

   // Done with this special projection matrix.  Throw it away.
   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   // We start with GL_DECAL mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

   // All done drawing.  Let's show it.
   glutSwapBuffers();

   // Now let's do the motion calculations.
   X_Rot+=X_Speed;
   Y_Rot+=Y_Speed;
}

////////////////////////////////////////////////////////////
// Callback function called when a normal key is pressed. //
////////////////////////////////////////////////////////////
void myCBKey(unsigned char key, int x, int y)
{
   switch (key) {
      case 113: // q
	 // Destroy the window and quit.
	 glutDestroyWindow(Window_ID);
	 exit(1);
	 break; // exit doesn't return, but anyway...
      case 97: // a
	      Z_Off -= 0.5f;
	 break;
      case 122: // z
         Z_Off += 0.5f;
      break;
   default:
      printf ("KP: No action for %d.\n", key);
      break;
    }
}

///////////////////////////////////////////////////////////////
// Callback routine executed whenever the window is resized. //
//////////////////////////////////////////////////////////////
void CallBackResizeScene(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
void MyInit(int Width, int Height) 
{
   // Color to clear color buffer to.
   glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

   // Depth to clear depth buffer to; type of test.
   glClearDepth(1.0);
   glDepthFunc(GL_LESS); 

   // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
   glShadeModel(GL_SMOOTH);

   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
}

///////////////////////////////////////////////////
// main() function.                              //
//   There are general steps in making           //
//   an OpenGL application.                      //
//   Inits OpenGL.                               //
//   Calls our own init function                 //
//   then passes control onto OpenGL.            //   
///////////////////////////////////////////////////
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   
   // To see OpenGL drawing, take out the GLUT_DOUBLE request.
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // The following is for window creation.
   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);
   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   // Register and install the callback function to do the drawing. 
   glutDisplayFunc(&CallBackRenderScene);

   // If there's nothing to do, draw.
   glutIdleFunc(&CallBackRenderScene);

   // It's a good idea to know when our window's resized.
   glutReshapeFunc(&CallBackResizeScene);

   // Register and install the callback function for
   // Some keys and special keys.
   glutKeyboardFunc(&myCBKey);

   // OK, OpenGL's ready to go.  Let's call our own init function.
   MyInit(Window_Width, Window_Height);

   // Print out a bit of help dialog.
   printf("\n%s\n\n", PROGRAM_TITLE);
   printf("Print out some helpful information here.\n");
   printf("When you program, you can also use\n");
   printf("printf to do debugging.\n\n");

   // Above functions represents those you will do to set up your
   // application program.
   // Now pass off control to OpenGL.
   glutMainLoop(); 
   // Never returns.
   return 1;
}
