#include "Interface.h"
#include <iostream>

Interface::Interface()
{
    // DiamondSquare
    pEngine = new Montagne(6, 1.5f, 2.0f);
    pEngine->Generate();

    m_fTX = m_fTY = m_fTZ = 0.0f;
    m_fRX = m_fRY = m_fRZ = 0.0f;
}

/*!
  Release allocated resources
*/
Interface::~Interface()
{
}


/*!
  Paint the box. The actual openGL commands for drawing the box are
  performed here.
*/

void Interface::paint()
{
    glClearColor(0.4, 0.4, 1.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0 + m_fTX + m_fRX, 24.0 + m_fTY + m_fRY, 40.0 + m_fTZ + m_fRZ,  // position de la caméra
    //    0.0 + m_fTX, 24.0 + m_fTY, 0.0 + m_fTZ,  // point vers lequel la caméra regarde
    //    0.0, 1.0, 0.0);  // vecteur "up"

    gluLookAt(0.0 + m_fTX + m_fRX, 100.0 + m_fTY + m_fRY, 0.0 + m_fTZ + m_fRZ,  // position de la caméra
        50.0 + m_fTX, 0.0 + m_fTY, 50.0 + m_fTZ,  // point vers lequel la caméra regarde
        0.0, 1.0, 0.0);  // vecteur "up"

   /* gluLookAt(0.0 + m_fTX + m_fRX, 24.0 + m_fTY + m_fRY, 20.0 + m_fTZ + m_fRZ,
        0.0 + m_fTX, 24.0 + m_fTY, 0.0 + m_fTZ,
        0.0, 1.0, 0.0);*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

    if (pEngine != NULL)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        pEngine->Draw();
    }
}


/*!
  Set up the OpenGL rendering state, and define display list
*/

void Interface::initializeGL()
{
    // qglClearColor( black ); 		// Let OpenGL clear to black

}

/*!
  Set up the OpenGL view port, matrix mode, etc.
*/

void Interface::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void Interface::changeModeF()
{
    pEngine->ChangeModeFilled();
    glutPostRedisplay();
}

void Interface::changeModeL()
{
    pEngine->ChangeModeLines();
    glutPostRedisplay();
}

void Interface::rotateMinusXSlot()
{
    m_fRX -= 2.0f;
    glutPostRedisplay();
}

void Interface::rotateMinusYSlot()
{
    m_fRY -= 2.0f;
    glutPostRedisplay();
}

void Interface::rotateMinusZSlot()
{
    m_fRZ -= 2.0f;
    glutPostRedisplay();
}

void Interface::rotatePlusXSlot()
{
    m_fRX += 2.0f;
    glutPostRedisplay();
}

void Interface::rotatePlusYSlot()
{
    m_fRY += 2.0f;
    glutPostRedisplay();
}

void Interface::rotatePlusZSlot()
{
    m_fRZ += 2.0f;
    glutPostRedisplay();
}

void Interface::translateMinusXSlot()
{
    m_fTX -= 2.0f;
    glutPostRedisplay();
}

void Interface::translateMinusYSlot()
{
    m_fTY -= 2.0f;
    glutPostRedisplay();
}

void Interface::translateMinusZSlot()
{
    m_fTZ -= 2.0f;
    glutPostRedisplay();
}

void Interface::translatePlusXSlot()
{
    m_fTX += 2.0f;
    glutPostRedisplay();
}

void Interface::translatePlusYSlot()
{
    m_fTY += 2.0f;
    glutPostRedisplay();
}

void Interface::translatePlusZSlot()
{
    m_fTZ += 2.0f;
    glutPostRedisplay();
}

void Interface::upVariance()
{/*
    float variance = pEngine->getVariance();
    variance++;
    generate(pEngine->getSize(), variance, pEngine->getSpacing());*/

    getMontagne()->setVariance(pEngine->getVariance() + 0.1f);
    pEngine->Generate();
    paint();
    //glutPostRedisplay();
}

void Interface::generate(unsigned int unPower, float fVariability,
    float fSize)
{
    std::cout << unPower << ", " << fVariability << ", " << fSize << std::endl;
    delete pEngine;
    pEngine = new Montagne(unPower, fVariability, fSize);
    pEngine->Generate();
    glutPostRedisplay();
}

Montagne* Interface::getMontagne()
{
    return pEngine;
}


