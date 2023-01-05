#include "Montagne.h" 

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////// 
///// Construction / Destruction 
///////////////////////////////////////////////////////////////////////////////////////// 

/**
 *   Constructeur
 *
 *   @param Steps : puissance de 2 -> longeur = largeur =
 *  (2^pas+1)
 *   @param Variability : controle de la variabilité de la hauteur
 *   @param Spacing : espace entre 2 points
 */
Montagne::Montagne(unsigned int pas, float variance,
	float espacement)
{
	Size = (1 << pas) + 1; //size = 2^n+1 
	Variability = variance;
	Spacing = espacement;
	srand(10);
	isFilled = true;
}

/**
 *   Destructeur
 *
 */
Montagne::~Montagne(void)
{

}


///////////////////////////////////////////////////////////////////////////////////////// 
///// Construction / Destruction 
///////////////////////////////////////////////////////////////////////////////////////// 

/**
 *   Generation d'un nombre aleatoire
 *
 *   @return le nombre aleatoire genere
 */
float Montagne::Randomize()
{
	const int limit = 1000000;
	return static_cast<float>((rand() % limit)) / limit;
}

/**
 *   Allocation de la memoire necessaire pour contenir la
 *  matrice representant les ordonnées
 *
 */
void Montagne::Init()
{
	// Reserve the memory 
	pointMatrix.resize(Size);
	for (unsigned int unI = 0; unI < Size; unI++)
	{
		pointMatrix[unI].resize(Size);
	}
}

unsigned int Montagne::getSize()
{
	return Size;
}

float Montagne::getVariance()
{
	return Variability;
}

float Montagne::getSpacing()
{
	return Spacing;
}


/**
 *   Phase du "diamant" : on se positionne sur le centre du
 *  carre precedemment obtenu(unI, unJ), puis on genere une
 *  valeur moyenne pour le centre des 4 nouveaux diamants
 *  obtenus
 *
 *   @param unI : abscisse du centre
 *   @param unJ : ordonnee du centre
 *   @param unHalfSpacing : "largeur" d'un diamant interne
 */
//float Montagne::DiamondStep(unsigned int unI, unsigned int unJ, unsigned int unHalfSpacing)
//{
//	float sum = 0.0;
//	int n = 0;
//
//	if ((unI >= unHalfSpacing) &&
//		(unJ >= unHalfSpacing))
//	{
//		sum += pointMatrix[unI - unHalfSpacing][unJ - unHalfSpacing];
//		n++;
//	}
//
//	if ((unI >= unHalfSpacing) &&
//		(unJ + unHalfSpacing < Size))
//	{
//		sum += pointMatrix[unI - unHalfSpacing][unJ + unHalfSpacing];
//		n++;
//	}
//
//	if ((unI + unHalfSpacing < Size) &&
//		(unJ >= unHalfSpacing))
//	{
//		sum += pointMatrix[unI + unHalfSpacing][unJ - unHalfSpacing];
//		n++;
//	}
//
//	if ((unI + unHalfSpacing < Size) &&
//		(unJ + unHalfSpacing < Size))
//	{
//		sum += pointMatrix[unI + unHalfSpacing][unJ + unHalfSpacing];
//		n++;
//	}
//
//	return sum / n;
//}

float Montagne::DiamondStep(unsigned int i, unsigned int j, unsigned int halfSpacing)
{
	float sum = 0.0;
	int count = 0;

	// Check if the points to the top left and bottom right of (i, j) are within the grid
	if (i >= halfSpacing && j >= halfSpacing)
	{
		sum += pointMatrix[i - halfSpacing][j - halfSpacing];
		count++;
	}
	if (i + halfSpacing < Size && j + halfSpacing < Size)
	{
		sum += pointMatrix[i + halfSpacing][j + halfSpacing];
		count++;
	}

	// Check if the points to the top right and bottom left of (i, j) are within the grid
	if (i >= halfSpacing && j + halfSpacing < Size)
	{
		sum += pointMatrix[i - halfSpacing][j + halfSpacing];
		count++;
	}
	if (i + halfSpacing < Size && j >= halfSpacing)
	{
		sum += pointMatrix[i + halfSpacing][j - halfSpacing];
		count++;
	}

	return sum / count;
}


/**
 *    Phase du "carre" : on se positionne sur le centre du
 *  diamant precedemment obtenu(unI, unJ), puis on genere une
 *  valeur moyenne pour le centre des 4 nouveaux carres
 *  obtenus
 *
 *   @param unI : abscisse du centre
 *   @param unJ : ordonnee du centre
 *   @param unHalfSpacing : "largeur" d'un carre interne
 */
float Montagne::SquareStep(unsigned int unI, unsigned int unJ, unsigned int unHalfSpacing)
{
	float sum = 0.0;
	int n = 0;

	if (unI >= unHalfSpacing)
	{
		sum += pointMatrix[unI - unHalfSpacing][unJ];
		n++;
	}

	if (unI + unHalfSpacing < Size)
	{
		sum += pointMatrix[unI + unHalfSpacing][unJ];
		n++;
	}

	if (unJ >= unHalfSpacing)
	{
		sum += pointMatrix[unI][unJ - unHalfSpacing];
		n++;
	}

	if (unJ + unHalfSpacing < Size)
	{
		sum += pointMatrix[unI][unJ + unHalfSpacing];
		n++;
	}

	return sum / n;
}



///////////////////////////////////////////////////////////////////////////////////////// 
///// Generation / Affichage 
///////////////////////////////////////////////////////////////////////////////////////// 
/*!
 *   Generation du terrain aleatoire :
 *      - on reserve la memoire
 *      - on se place une hauteur pour les coins
 *      - on applique l'algorithme "Diamond-Square"
 *
 *   @param fLeftBottom : hauteur du coin inferieur gauche
 *   @param fLeftTop : hauteur du coin superieur gauche
 *   @param fRightTop : hauteur du coin superieur droit
 *   @param fRightBottom : hauteur du coin inferieur droit
 */
void Montagne::Generate(float fLeftBottom, float fLeftTop,
	float fRightTop, float fRightBottom)
{
	// Reserve memory 
	Init();

	// Init corners 
	pointMatrix[0][0] = fLeftBottom;
	pointMatrix[0][Size - 1] = fRightBottom;
	pointMatrix[Size - 1][0] = fLeftTop;
	pointMatrix[Size - 1][Size - 1] = fRightTop;

	// Init spacing value 
	unsigned int unSpacing = Size - 1;

	while (unSpacing > 1)
	{
		int unHalfSpacing = unSpacing / 2;

		// Make the Diamond Step 
		for (unsigned int unI = unHalfSpacing; unI < Size; unI += unSpacing)
		{
			for (unsigned int unJ = unHalfSpacing; unJ < Size; unJ += unSpacing)
			{
				pointMatrix[unI][unJ] = DiamondStep(unI, unJ, unHalfSpacing) + Randomize() * unSpacing * Variability;
			}
		}

		// Make the Square Step 
		for (unsigned int unI = 0; unI < Size; unI += unHalfSpacing)
		{
			unsigned int unJStart = ((unI / unHalfSpacing) % 2 == 0) ? unHalfSpacing : 0;

			for (unsigned int unJ = unJStart; unJ < Size; unJ += unSpacing)
			{
				pointMatrix[unI][unJ] = SquareStep(unI, unJ, unHalfSpacing) + Randomize() * unSpacing * Variability;
			}
		}

		// Divide the used map by 2 
		unSpacing = unHalfSpacing;

	}

	// Find the min and the max of the map
	hMax = pointMatrix[0][0];
	hMin = pointMatrix[0][0];
	for (unsigned int unI = 0; unI < (Size - 1); unI++)
		for (unsigned int unJ = 0; unJ < (Size - 1); unJ++)
		{
			if (pointMatrix[unI][unJ] > hMax)
			{
				hMax = pointMatrix[unI][unJ];
			}
			if (pointMatrix[unI][unJ] < hMin)
			{
				hMin = pointMatrix[unI][unJ];
			}
		}
}


void Montagne::DiamondSquare(unsigned int size, float variance)
{
	// Reserve memory 
	Init();

	// Init corners 
	pointMatrix[0][0] = 0.0;
	pointMatrix[0][Size - 1] = 0.0;
	pointMatrix[Size - 1][0] = 0.0;
	pointMatrix[Size - 1][Size - 1] = 0.0;

	if (size == 1)
	{
		// Cas de base : on a atteint une taille de 1, on ne peut plus continuer
		return;
	}

	// Calcul du pas (demi-taille du diamant/carré)
	unsigned int halfSpacing = size / 2;

	// Phase du diamant
	for (unsigned int i = halfSpacing; i < pointMatrix.size() - halfSpacing; i += size)
	{
		for (unsigned int j = halfSpacing; j < pointMatrix[i].size() - halfSpacing; j += size)
		{
			float sum = pointMatrix[i - halfSpacing][j - halfSpacing] + pointMatrix[i - halfSpacing][j + halfSpacing] +
				pointMatrix[i + halfSpacing][j - halfSpacing] + pointMatrix[i + halfSpacing][j + halfSpacing];
			pointMatrix[i][j] = sum / 4 - variance * (Randomize() * 2 - 1);
		}
	}

	// Phase du carré
	for (unsigned int i = 0; i < pointMatrix.size(); i += halfSpacing)
	{
		for (unsigned int j = (i + halfSpacing) % size; j < pointMatrix[i].size(); j += size)
		{
			float sum = 0;
			int n = 0;
			if (i >= halfSpacing)
			{
				sum += pointMatrix[i - halfSpacing][j];
				n++;
			}
			if (i + halfSpacing < pointMatrix.size())
			{
				sum += pointMatrix[i + halfSpacing][j];
				n++;
			}
			if (j >= halfSpacing)
			{
				sum += pointMatrix[i][j - halfSpacing];
				n++;
			}
			if (j + halfSpacing < pointMatrix[i].size())
			{
				sum += pointMatrix[i][j + halfSpacing];
				n++;
			}
			pointMatrix[i][j] = sum / n - variance * (Randomize() * 2 - 1);
		}
	}

	// Find the min and the max of the map
	hMax = pointMatrix[0][0];
	hMin = pointMatrix[0][0];
	for (unsigned int unI = 0; unI < (Size - 1); unI++)
		for (unsigned int unJ = 0; unJ < (Size - 1); unJ++)
		{
			if (pointMatrix[unI][unJ] > hMax)
			{
				hMax = pointMatrix[unI][unJ];
			}
			if (pointMatrix[unI][unJ] < hMin)
			{
				hMin = pointMatrix[unI][unJ];
			}
		}

	// Appel récursif sur les sous-grilles
	DiamondSquare(size / 2, variance / 2);
}



/**
 *   Methode permettant d'adapter la couleur a la hauteur du
 *  point
 *
 *   @param fTmp : hauteur temporaire
 */

void Montagne::SetColor(float fTmp, float slope)
{
	if (fTmp < 0.3)
	{
		// Partie basse de la montagne: couleur bleue
		glColor3f(0, 0, fTmp);
	}
	else if (fTmp < 0.7)
	{
		// Partie haute de la montagne: couleur marron ou verte
		glColor3f(fTmp, fTmp / 6, 0);
	}
	else
	{
		// Couleur blanche pour simuler la neige
		float snow = 1.0 - slope;
		glColor3f(snow, snow, snow);
	}
}




void Montagne::setVariance(float variance)
{
	this->Variability = variance;
}


/**
 *   Methode permettant d'alterner entre fil de fer et mode
 *  rempli
 *
 */
void Montagne::ChangeModeFilled()
{
	isFilled = !isFilled;
}

void Montagne::ChangeModeLines()
{
	isShowLines = !isShowLines;
}

/**
 *   Affichage du terrain en utilisant OpenGL. Il est
 *  possible de surcharger la methode pour choisir une autre
 *  methode d'affichage
 *
 */
void Montagne::Draw()
{
	//glScalef(0.5f, 0.5f, 0.5f);

	// Activer l'éclairage
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Définir les paramètres de la lumière
	GLfloat light_position[] = { 5.0f, 10.0f, 5.0f, 0.0f };
	GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// Generate the appropriate boundaries 
	float fMax = Spacing * (Size / 2);
	float fMin = -fMax;
	float fTmp, fDiff;

	fDiff = hMax - hMin;


	// Drawing the map 
	for (unsigned int unI = 0; unI < (Size - 1); unI++)
	{
		float fZ = fMin + unI * Spacing;
		for (unsigned int unJ = 0; unJ < (Size - 1); unJ++)
		{
			float fX = fMin + unJ * Spacing;

			if (isShowLines)
			{
				glLineWidth(2.0);  // Épaisseur de 2 pixels
				glBegin(GL_LINES);

				glColor3f(0, 0, 0);

				glVertex3f(fX, pointMatrix[unI][unJ], fZ);
				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);

				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);
				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);

				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);
				glVertex3f(fX + Spacing, pointMatrix[unI][unJ + 1], fZ);

				glVertex3f(fX + Spacing, pointMatrix[unI][unJ + 1], fZ);
				glVertex3f(fX, pointMatrix[unI][unJ], fZ);

				glEnd();
			}
			

			if (isFilled)
			{
				glBegin(GL_QUADS);
				// Calculer la pente de la facette courante
				float hA = pointMatrix[unI][unJ];
				float hB = pointMatrix[unI + 1][unJ];
				float hC = pointMatrix[unI + 1][unJ + 1];
				float hD = pointMatrix[unI][unJ + 1];
				float dAB = Spacing;
				float dBC = Spacing;
				float slope = CalculateSlope(hA, hB, hC, hD, dAB, dBC);

				fTmp = (pointMatrix[unI][unJ] - hMin) / fDiff; //normalize
				SetColor(fTmp, slope);
				glVertex3f(fX, pointMatrix[unI][unJ], fZ);

				fTmp = (pointMatrix[unI + 1][unJ] - hMin) / fDiff;
				SetColor(fTmp, slope);
				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);

				fTmp = (pointMatrix[unI + 1][unJ + 1] - hMin) / fDiff;
				SetColor(fTmp, slope);
				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);

				fTmp = (pointMatrix[unI][unJ + 1] - hMin) / fDiff;
				SetColor(fTmp, slope);
				glVertex3f(fX + Spacing, pointMatrix[unI][unJ + 1], fZ);

				glEnd();
			}
			else
			{
				glBegin(GL_LINES);

				glColor3f(0, 1.0, 0);

				glVertex3f(fX, pointMatrix[unI][unJ], fZ);
				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);

				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);
				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);

				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);
				glVertex3f(fX + Spacing, pointMatrix[unI][unJ + 1], fZ);

				glVertex3f(fX + Spacing, pointMatrix[unI][unJ + 1], fZ);
				glVertex3f(fX, pointMatrix[unI][unJ], fZ);

				glEnd();
			}

		}
	}

}

float Montagne::CalculateSlope(float hA, float hB, float hC, float hD, float dAB, float dBC)
{
	// Calculer les pentes des différentes arêtes de la facette
	float slopeA = abs(hA - hB) / dAB;
	float slopeB = abs(hB - hC) / dBC;
	float slopeC = abs(hC - hD) / dAB;
	float slopeD = abs(hD - hA) / dBC;
	// Calculer la pente moyenne de la facette
	return (slopeA + slopeB + slopeC + slopeD) / 4.0;
}
