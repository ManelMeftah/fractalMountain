#pragma once


// Divers
#include <GL/glut.h>
#include <iostream>
#include "Montagne.h"

class Interface
{
public:
    Interface();
    ~Interface();

    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paint();

    // Rotation
    virtual void rotateMinusXSlot();
    virtual void rotateMinusYSlot();
    virtual void rotateMinusZSlot();
    virtual void rotatePlusXSlot();
    virtual void rotatePlusYSlot();
    virtual void rotatePlusZSlot();

    // Translation
    virtual void translateMinusXSlot();
    virtual void translateMinusYSlot();
    virtual void translateMinusZSlot();
    virtual void translatePlusXSlot();
    virtual void translatePlusYSlot();
    virtual void translatePlusZSlot();

    // Mode
    virtual void changeModeF();
    virtual void changeModeL();

private:
    Montagne* pEngine;

public:
    float m_fTX, m_fTY, m_fTZ;
    float m_fRX, m_fRY, m_fRZ;

public:
    void upVariance();
    void generate(unsigned int unPower, float fVariability, float fSize);

    Montagne* getMontagne();

};
