#include "Montagne.h" 
#include <algorithm>
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
 *   @return un nombre aleatoir entre -1 et 1
 */
float Montagne::Randomize()
{
	/*const int limit = 1;
	return static_cast<float>((rand() % limit)) / limit;*/
	return (2.0 * rand()) / RAND_MAX - 1.0;
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


void Montagne::setVariance(float variance)
{
	this->Variability = variance;
}

float Montagne::getSpacing()
{
	return Spacing;
}



///////////////////////////////////////////////////////////////////////////////////////// 
///// Generation / Affichage 
///////////////////////////////////////////////////////////////////////////////////////// 


/**
* Generation du terrain aleatoire en utilisant l'algorithme Diamond-Square :
*		- on reserve la memoire de la matrice
*		- on initialise les coins de la matrice avec une hauteur nulle
*		- on initialise les coins de la matrice avec une hauteur nulle
*		- on applique l'algorithme récursivement en divisant la taille par 2 à chaque étape jusqu'à ce que la taille atteigne 1
*		- pour chaque point du carré, on calcule la moyenne des 4 points de coin et on lui applique une perturbation aléatoire
*		- pour chaque point du diamant, on calcule la moyenne des 4 points adjacents et on lui applique une perturbation aléatoire
*		- on utilise une variable "variance" pour contrôler l'amplitude de la perturbation aléatoire
* 
*	 @param size : taille de la matrice
*	@param variance : amplitide de la perturbation aléatoire
*/
void Montagne::DiamondSquare(unsigned int size, float variance)
{
	// Reserve memory 
	Init();

	// Init corners 
	pointMatrix[0][0] = 0.0f;
	pointMatrix[0][Size - 1] = 0.0f;
	pointMatrix[Size - 1][0] = 0.0f;
	pointMatrix[Size - 1][Size - 1] = 0.0f;

	if (size == 1)
	{
		// Cas de base : on a atteint une taille de 1, on ne peut plus continuer
		
		return;
	}

	// Calculer la moitié de la distance entre les points
	int half = size / 2;

	// Pour chaque point du carré
	for (unsigned int x = half; x < pointMatrix.size() - half; x += size)
	{
		for (unsigned int y = half; y < pointMatrix[x].size() - half; y += size)
		{
			// Calculer la moyenne des 4 points de coin du carré
			float avg = (pointMatrix[x - half][y - half] +
						 pointMatrix[x - half][y + half] + 
						 pointMatrix[x + half][y - half] +
						 pointMatrix[x + half][y + half]) / 4.0;
			// Appliquer la perturbation
			avg += Randomize() * variance * pow(2, -half);
			// Affecter la valeur au point central du carré
			pointMatrix[x][y] = avg;
		}
	}
	
	//METHODE 3

	// Pour chaque point du diamant
	for (unsigned int i = 0; i < pointMatrix.size(); i += half)
	{
		for (unsigned int j = (i + half) % size; j < pointMatrix[i].size(); j += size)
		{
			float sum = 0.0;
			int count = 0;

			// Check if the points to the top left and bottom right of (i, j) are within the grid
			if (i >= half && j >= half)
			{
				sum += pointMatrix[i - half][j - half];
				count++;
			}
			if (i + half < Size && j + half < Size)
			{
				sum += pointMatrix[i + half][j + half];
				count++;
			}

			// Check if the points to the top right and bottom left of (i, j) are within the grid
			if (i >= half && j + half < Size)
			{
				sum += pointMatrix[i - half][j + half];
				count++;
			}
			if (i + half < Size && j >= half)
			{
				sum += pointMatrix[i + half][j - half];
				count++;
			}
			sum /= count;
			// Appliquer la perturbation
			sum += Randomize() * variance * pow(2, -half);
			// Affecter la valeur au point central du diamant
			pointMatrix[i][j] = sum;
		}
	}

	//METHODE 2

	//// Pour chaque point du diamant
	//for (unsigned int x = 0; x < pointMatrix.size(); x += half)
	//{
	//	for (unsigned int y = (x + half) % size; y < pointMatrix[x].size(); y += size)
	//	{
	//		// Vérifier que les indices sont bien compris entre 0 et la taille de la matrice - 1
	//		if (x < half || y < half || x >= pointMatrix.size() - half || y >= pointMatrix[x].size() - half)
	//		{
	//			// Si l'un des indices est hors de la matrice, on utilise la valeur du bord de la matrice
	//			pointMatrix[x][y] = pointMatrix[std::min<unsigned int>(int(pointMatrix.size() - 1), std::max<unsigned int>(0, x))]
	//										   [std::min<unsigned int>(int(pointMatrix[x].size() - 1), std::max<unsigned int>(0, y))];
	//		}
	//		else
	//		{
	//			// Calculer la moyenne des 4 points de coin du diamant
	//			float avg = 0.0;
	//			int count = 0;
	//			if (x - half >= 0)
	//			{
	//				avg += pointMatrix[x - half][y];
	//				count++;
	//			}
	//			if (x + half < pointMatrix.size())
	//			{
	//				avg += pointMatrix[x + half][y];
	//				count++;
	//			}
	//			if (y - half >= 0)
	//			{
	//				avg += pointMatrix[x][y - half];
	//				count++;
	//			}
	//			if (y + half < pointMatrix[x].size())
	//			{
	//				avg += pointMatrix[x][y + half];
	//				count++;
	//			}
	//			avg /= count;
	//			// Appliquer la perturbation
	//			avg += Randomize() * variance * pow(2, -half);
	//			// Affecter la valeur au point central du diamant
	//			pointMatrix[x][y] = avg;
	//		}
	//	}
	//}

	//METHODE 1

	// Pour chaque point du diamant
	//for (unsigned int x = 0; x < pointMatrix.size(); x += half)
	//{
	//	for (unsigned int y = (x + half) % size; y < pointMatrix[x].size(); y += size)
	//	{
	//		// Vérifier que les indices sont bien compris entre 0 et la taille de la matrice - 1
	//		int newX = x;
	//		int newY = y;
	//		if (newX < 0)
	//		{
	//			newX = pointMatrix.size() - 1;
	//		}
	//		else if (newX >= pointMatrix.size())
	//		{
	//			newX = 0;
	//		}
	//		if (newY < 0)
	//		{
	//			newY = pointMatrix[x].size() - 1;
	//		}
	//		else if (newY >= pointMatrix[x].size())
	//		{
	//			newY = 0;
	//		}
	//		// Calculer la moyenne des 4 points de coin du diamant
	//		float avg = 0.0;
	//		int count = 0;
	//		if (newX - half >= 0)
	//		{
	//			avg += pointMatrix[newX - half][newY];
	//			count++;
	//		}
	//		if (newX + half < pointMatrix.size())
	//		{
	//			avg += pointMatrix[newX + half][newY];
	//			count++;
	//		}
	//		if (newY - half >= 0)
	//		{
	//			avg += pointMatrix[newX][newY - half];
	//			count++;
	//		}
	//		if (newY + half < pointMatrix[newX].size())
	//		{
	//			avg += pointMatrix[newX][newY + half];
	//			count++;
	//		}
	//		avg /= count;
	//		// Appliquer la perturbation
	//		avg += Randomize() * variance * pow(2, -half);
	//		// Affecter la valeur au point central du diamant
	//		pointMatrix[newX][newY] = avg;
	//	}
	//}


	//FILTRE GAUSSIEN
	
	//// Appliquer le filtre Gaussien
	//for (unsigned int x = 0; x < pointMatrix.size(); x++)
	//{
	//	for (unsigned int y = 0; y < pointMatrix[x].size(); y++)
	//	{
	//		float sum = 0.0;
	//		int count = 0;
	//		for (int i = -1; i <= 1; i++)
	//		{
	//			for (int j = -1; j <= 1; j++)
	//			{
	//				if (x + i < 0 || x + i >= pointMatrix.size() || y + j < 0 || y + j >= pointMatrix[x].size())
	//				{
	//					continue;
	//				}
	//				sum += pointMatrix[x + i][y + j];
	//				count++;
	//			}
	//		}
	//		pointMatrix[x][y] = sum / count;
	//	}
	//}


	Smooth();
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


/*!
* 	Lissage du terrain :
* 		- on initialise une nouvelle matrice
* 		- pour chaque point de l'ancienne matrice, on calcule la moyenne de ses points adjacents
* 		- on remplace l'ancienne matrice par la nouvelle
*/
void Montagne::Smooth()
{
	// Initialiser la nouvelle matrice 
	std::vector<std::vector<float>> newPointMatrix(pointMatrix.size(), std::vector<float>(pointMatrix[0].size()));
	
	// Pour chaque point de la matrice
	for (unsigned int x = 0; x < pointMatrix.size(); x++)
	{
		for (unsigned int y = 0; y < pointMatrix[x].size(); y++)
		{
			float sum = 0.0;
			int count = 0;

			// Pour chaque point adjacent à (x, y)
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					// Vérifier que les indices (x + i, y + j) sont bien compris entre 0 et la taille de la matrice - 1
					if (x + i >= 0 && x + i < pointMatrix.size() && y + j >= 0 && y + j < pointMatrix[x].size())
					{
						sum += pointMatrix[x + i][y + j];
						count++;
					}
				}
			}
			// Calculer la moyenne des points adjacents
			newPointMatrix[x][y] = sum / count;
		}
	}

	// Remplacer l'ancienne matrice par la nouvelle
	pointMatrix = newPointMatrix;
}


/**
 *   Methode permettant d'adapter la couleur a la hauteur du
 *  point
 *		 - Si l'altitude est inférieure à 0.3, la couleur est bleue
 *		 - Si l'altitude est inférieure à 0.7, la couleur est marron ou verte (en fonction de l'altitude)
 *		 - Si l'altitude est supérieure à 0.7, la couleur est blanche (pour simuler la neige)
 *		 - Si la facette est oriente nord, on augmente la quantité de neigne
 *
 *   @param fTmp : hauteur du point
 *	 @param slope : pente du point
 *	 @param orientation : orientation de la facette, >0 : Nord, <0 : Sud
 */

//void Montagne::SetColor(float fTmp, float slope, float orientation)
//{
//	if (fTmp < 0.3)
//	{
//		// Partie basse de la montagne: couleur bleue
//		glColor3f(0, 0, fTmp);
//	}
//	else if (fTmp < 0.7)
//	{
//		// Partie haute de la montagne: couleur marron ou verte
//		glColor3f(fTmp, fTmp / 6, 0);
//	}
//	else
//	{
//		// Couleur blanche pour simuler la neige
//		float snow = 1.0 - slope;
//		glColor3f(snow, snow, snow);
//	}
//}
//

void Montagne::SetColor(float fTmp, float slope, float orientation)
{
	if (fTmp < 0.3)
	{
		// Partie basse de la montagne: couleur bleue
		glColor3f(0, 0, fTmp);
	}
	else if (fTmp < 0.7)
	{
		// Partie haute de la montagne: couleur marron ou verte
		glColor3f(fTmp, fTmp / 6, fTmp/3);
	}
	else
	{
		// Couleur blanche pour simuler la neige
		float snow = 1.0 - slope;
		// Si la facette est orientée vers le nord, augmenter la quantité de neige
		if (orientation > 0)
		{
			snow += 0.3;
		}
		glColor3f(snow, snow, snow);
	}
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

				float orientation = CalculateOrientation(hA, hB, hC, hD);

				fTmp = (pointMatrix[unI][unJ] - hMin) / fDiff; //normalize
				SetColor(fTmp, slope, orientation);
				glVertex3f(fX, pointMatrix[unI][unJ], fZ);

				fTmp = (pointMatrix[unI + 1][unJ] - hMin) / fDiff;
				SetColor(fTmp, slope, orientation);
				glVertex3f(fX, pointMatrix[unI + 1][unJ], fZ + Spacing);

				fTmp = (pointMatrix[unI + 1][unJ + 1] - hMin) / fDiff;
				SetColor(fTmp, slope, orientation);
				glVertex3f(fX + Spacing, pointMatrix[unI + 1][unJ + 1], fZ + Spacing);

				fTmp = (pointMatrix[unI][unJ + 1] - hMin) / fDiff;
				SetColor(fTmp, slope, orientation);
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

/**
* Calcul de la pente de la facette ABCD
*	@param hA : hauteur du point A de la facette
*	@param hB : hauteur du point B de la facette
*	@param hC : hauteur du point C de la facette
*	@param hD : hauteur du point D de la facette
*	@param dAB : distance entre le point A et le point B
*	@param dBC : distance entre le point B et le point C 
*/

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

float Montagne::CalculateOrientation(float hA, float hB, float hC, float hD)
{
	// Calculer les pentes des différentes aretes de la facette
	float slopeAB = hB - hA;
	float slopeBC = hC - hB;
	float slopeCD = hD - hC;
	float slopeDA = hA - hD;

	// Calculer l'orientation de la facette en utilisant la pente des arêtes
	float orientation = atan2(slopeAB, slopeDA) - atan2(slopeCD, slopeBC);

	// Normaliser l'orientation entre 0 et 2pi
	while (orientation < 0)
	{
		orientation += 2 * M_PI;
	}
	while (orientation >= 2 * M_PI)
	{
		orientation -= 2 * M_PI;
	}

	return orientation;
}