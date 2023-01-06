#include <GL/glut.h>
#include <glm/glm.hpp>
#include<iostream>
using namespace std;

#include <stdlib.h>


#include <vector>
#include <sstream>

#include<string>

#include "Montagne.h"
#include "Interface.h"

using namespace std;
void affichage(void);

void clavier(unsigned char touche, int x, int y);

void mouse(int, int, int, int);
void mouseMotion(int, int);


// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance = 0.;

Interface* interface;




void initMontagne()
{
    interface = new Interface();
}


//----------------------------------------------------------------------------------
void initOpenGl()
//----------------------------------------------------------------------------------
{
    //initMesh();
    initMontagne();

    //lumiere 

    //glClearColor(.5, .5, 0.5, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat l_pos[] = { 3.,3.5,3.0,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_pos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_pos);

     glDepthFunc(GL_LESS);
     glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    // Configurez la projection en perspective ici
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(30.0f, (GLfloat)200 / (GLfloat)200, 0.1f, 100.0f);
    //gluPerspective(30.0f, (GLfloat)200 / (GLfloat)200, 0.1f, 0.0f);
    // Configurez la vue de la caméra ici
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

//------------------------------------------------------
void display(void)
//----------------------------------------------------------------------------------
{
    interface->paint();

}
int main(int argc, char** argv)
{

    /* initialisation de glut et creation
       de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutCreateWindow("montagne fractale");

    ///* Initialisation d'OpenGL */
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glColor3f(1.0, 1.0, 1.0);
    //glPointSize(1.0);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    initOpenGl();

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}
//------------------------------------------------------



//------------------------------------------------------
void affichage(void)
{
    glMatrixMode(GL_MODELVIEW);
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1., 0., 0.);
    glRotatef(cameraAngleY, 0., 1., 0.);
    //--------------------------------
    display();

    glPopMatrix();
    /* on force l'affichage du resultat */
    glFlush();
}

//------------------------------------------------------


//------------------------------------------------------
void clavier(unsigned char touche, int x, int y)
{

    switch (touche)
    {
    case '+': //* incrémenter de la variance
        interface->upVariance();
        glutPostRedisplay();
        break;
    case '-': //* decrémenter la variance
        interface->decVariance();
        glutPostRedisplay();
        break;
    case 'f': //* affichage en mode fil de fer 
        interface->changeModeF();
        glutPostRedisplay();
        break;
    case 'p': //* affichage du carre plein 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case 's': //* Affichage en mode sommets seuls 
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();
        break;
    case 'l': //* Affichage en mode plein et fil de fer
        interface->changeModeL();
        break;
    case 'q': //*la touche 'q' permet de quitter le programme 
        exit(0);

    }

}
void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if (state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if (state == GLUT_UP)
            mouseRightDown = false;
    }

    else if (button == GLUT_MIDDLE_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if (state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mouseMotion(int x, int y)
{
    if (mouseLeftDown)
    {
        interface->m_fRX += (x - mouseX);
        interface->m_fRY += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if (mouseRightDown)
    {
        interface->m_fTY += (y - mouseY) * 0.2f;
        //cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}



