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

    virtual void paint();

    // Mode
    virtual void changeModeF(); //filled
    virtual void changeModeL(); //lines

private:
    Montagne* maMontagne;

public:
    //Position de la camera:
    float m_fTX, m_fTY, m_fTZ; //translation
    float m_fRX, m_fRY, m_fRZ; //rotation

public:
    void upVariance();
    void decVariance();
    void generate(unsigned int unPower, float fVariability, float fSize);

    Montagne* getMontagne();

};
