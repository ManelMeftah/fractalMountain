#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <cmath>

/**
 *   Classe permettant de generer une montagne aleatoire en
 *  utilisant l'algorithme "Diamond-Square"
 *
 */
class Montagne
{
	// Members
private:
	std::vector< std::vector<float> > pointMatrix;  //Matrice de points generee par l'algorithme diamant-carré
	unsigned int Size;  //Largeur de la matrice 
	float Variability;  //Variabilite de la hauteur 
	float Spacing;  // Espace entre 2 points 
	float hMin; // Hauteur minimale de la map */
	float hMax; // Hauteur maximale de la map */
	//Booleens permettant de savoir si on est en mode filaire
	bool isFilled; //Booleens permettant de savoir si on est en mode filaire
	bool isShowLines;

					 // Destruction / Construction
public:
	/* Montagne(void); */
	Montagne(unsigned int pas,
		float variance, float espacement);
	virtual ~Montagne(void);

	// Generation
private:
	float Randomize();
	void SetColor(float tmpH, float slope, float orientation);
	void Init();

public:
	unsigned int getSize();
	float getVariance();
	float getSpacing();
	void DiamondSquare(unsigned int size, float variance);	
	void Smooth();
	void ChangeModeFilled();
	void ChangeModeLines();
	void setVariance(float variance);


	// Drawing
public:
	virtual void Draw();
	float CalculateSlope(float hA, float hB, float hC, float hD, float dAB, float dBC);
	float CalculateOrientation(float hA, float hB, float hC, float hD);
};

