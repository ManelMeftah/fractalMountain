#include "Interface.h"
#include <iostream>

Interface::Interface()
{
    // DiamondSquare
    maMontagne = new Montagne(6, 1.0f, 2.0f);
    //maMontagne->Generate();
    maMontagne->DiamondSquare(maMontagne->getSize(), maMontagne->getVariance());


    m_fTX = m_fTZ = 0.0f;
    m_fTY = 0.0f;
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
    glClearColor(0.4, 0.8, 1.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0 + m_fTX + m_fRX, 100.0 + m_fTY + m_fRY, 0.0 + m_fTZ + m_fRZ,  // position de la caméra
        50.0 + m_fTX, 0.0 + m_fTY, 50.0 + m_fTZ,  // point vers lequel la caméra regarde
        0.0, 1.0, 0.0);  // vecteur "up"

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);

    if (maMontagne != NULL)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        maMontagne->Draw();
    }
}

void Interface::changeModeF()
{
    maMontagne->ChangeModeFilled();
    glutPostRedisplay();
}

void Interface::changeModeL()
{
    maMontagne->ChangeModeLines();
    glutPostRedisplay();
}


void Interface::upVariance()
{
    getMontagne()->setVariance(maMontagne->getVariance() + 10.0f);
    //maMontagne->Generate();
    maMontagne->DiamondSquare(maMontagne->getSize(), maMontagne->getVariance());
    paint();
}

void Interface::decVariance()
{
    getMontagne()->setVariance(maMontagne->getVariance() - 10.0f);
    //maMontagne->Generate();
    maMontagne->DiamondSquare(maMontagne->getSize(), maMontagne->getVariance());

    paint();
}

void Interface::generate(unsigned int unPower, float fVariability,
    float fSize)
{
    std::cout << unPower << ", " << fVariability << ", " << fSize << std::endl;
    delete maMontagne;
    maMontagne = new Montagne(unPower, fVariability, fSize);
    //maMontagne->Generate();
    maMontagne->DiamondSquare(maMontagne->getSize(), maMontagne->getVariance());

    glutPostRedisplay();
}

Montagne* Interface::getMontagne()
{
    return maMontagne;
}


