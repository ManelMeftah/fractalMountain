#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

/**
 *   Classe permettant de generer une montagne aleatoire en
 *  utilisant l'algorithme "Diamond-Square"
 *
 */
class Montagne
{
	// Members
private:
	std::vector< std::vector<float> > m_vectPoints;  /**< Matrice de points */
	unsigned int m_unSize;  /**< Largeur de la matrice */
	float m_fVariability;  /**< Variabilite de la hauteur */
	float m_fSpacing;  /**< Espace entre 2 points */
	float m_fMin; /**< Hauteur maximale de la map */
	float m_fMax; /**< Hauteur minimale de la map */
	bool m_bFilled; /**< Booleen permettant de passer du mode
					 * filaire en mode "rempli"
					 */

					 // Destruction / Construction
public:
	/* Montagne(void); */
	Montagne(unsigned int unSteps,
		float fVariability, float fSpacing);
	virtual ~Montagne(void);

	// Generation
private:
	float Randomize();
	float DiamondStep(unsigned int unI, unsigned int unJ,
		unsigned int unHalfSpacing);
	float SquareStep(unsigned int unI, unsigned int unJ,
		unsigned int unHalfSpacing);
	void SetColor(float fTmp);
	void Init();

public:
	unsigned int getSize();
	float getVariance();
	float getSpacing();
	void Generate(float fLeftBottom = 0.0f, float fLeftTop = 0.0f,
		float fRightTop = 0.0f, float fRightBottom = 0.0f);
	void ChangeMode();

	// Drawing
public:
	virtual void Draw();
};
