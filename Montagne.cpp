#include "Montagne.h" 

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////// 
///// Construction / Destruction 
///////////////////////////////////////////////////////////////////////////////////////// 

/**
 *   Constructeur
 *
 *   @param unSteps : puissance de 2 -> longeur = largeur =
 *  (2^unSteps+1)
 *   @param fVariability : controle de la variabilit� de la hauteur
 *   @param fSpacing : espace entre 2 points
 */
Montagne::Montagne(unsigned int unSteps, float fVariability,
	float fSpacing)
{
	m_unSize = (1 << unSteps) + 1; //size = 2^n+1 
	m_fVariability = fVariability;
	m_fSpacing = fSpacing;
	srand(10);
	m_bFilled = true;
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
 *  matrice representant les ordonn�es
 *
 */
void Montagne::Init()
{
	// Reserve the memory 
	m_vectPoints.resize(m_unSize);
	for (unsigned int unI = 0; unI < m_unSize; unI++)
	{
		m_vectPoints[unI].resize(m_unSize);
	}
}

unsigned int Montagne::getSize()
{
	return m_unSize;
}

float Montagne::getVariance()
{
	return m_fVariability;
}

float Montagne::getSpacing()
{
	return m_fSpacing;
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
float Montagne::DiamondStep(unsigned int unI, unsigned int unJ, unsigned int unHalfSpacing)
{
	float sum = 0.0;
	int n = 0;

	if ((unI >= unHalfSpacing) &&
		(unJ >= unHalfSpacing))
	{
		sum += m_vectPoints[unI - unHalfSpacing][unJ - unHalfSpacing];
		n++;
	}

	if ((unI >= unHalfSpacing) &&
		(unJ + unHalfSpacing < m_unSize))
	{
		sum += m_vectPoints[unI - unHalfSpacing][unJ + unHalfSpacing];
		n++;
	}

	if ((unI + unHalfSpacing < m_unSize) &&
		(unJ >= unHalfSpacing))
	{
		sum += m_vectPoints[unI + unHalfSpacing][unJ - unHalfSpacing];
		n++;
	}

	if ((unI + unHalfSpacing < m_unSize) &&
		(unJ + unHalfSpacing < m_unSize))
	{
		sum += m_vectPoints[unI + unHalfSpacing][unJ + unHalfSpacing];
		n++;
	}

	return sum / n;
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
		sum += m_vectPoints[unI - unHalfSpacing][unJ];
		n++;
	}

	if (unI + unHalfSpacing < m_unSize)
	{
		sum += m_vectPoints[unI + unHalfSpacing][unJ];
		n++;
	}

	if (unJ >= unHalfSpacing)
	{
		sum += m_vectPoints[unI][unJ - unHalfSpacing];
		n++;
	}

	if (unJ + unHalfSpacing < m_unSize)
	{
		sum += m_vectPoints[unI][unJ + unHalfSpacing];
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
	m_vectPoints[0][0] = fLeftBottom;
	m_vectPoints[0][m_unSize - 1] = fRightBottom;
	m_vectPoints[m_unSize - 1][0] = fLeftTop;
	m_vectPoints[m_unSize - 1][m_unSize - 1] = fRightTop;

	// Init spacing value 
	unsigned int unSpacing = m_unSize - 1;

	while (unSpacing > 1)
	{
		int unHalfSpacing = unSpacing / 2;

		// Make the Diamond Step 
		for (unsigned int unI = unHalfSpacing; unI < m_unSize; unI += unSpacing)
		{
			for (unsigned int unJ = unHalfSpacing; unJ < m_unSize; unJ += unSpacing)
			{
				m_vectPoints[unI][unJ] = DiamondStep(unI, unJ, unHalfSpacing) + Randomize() * unSpacing * m_fVariability;
			}
		}

		// Make the Square Step 
		for (unsigned int unI = 0; unI < m_unSize; unI += unHalfSpacing)
		{
			unsigned int unJStart = ((unI / unHalfSpacing) % 2 == 0) ? unHalfSpacing : 0;

			for (unsigned int unJ = unJStart; unJ < m_unSize; unJ += unSpacing)
			{
				m_vectPoints[unI][unJ] = SquareStep(unI, unJ, unHalfSpacing) + Randomize() * unSpacing * m_fVariability;
			}
		}

		// Divide the used map by 2 
		unSpacing = unHalfSpacing;

	}

	// Find the min and the max of the map
	m_fMax = m_vectPoints[0][0];
	m_fMin = m_vectPoints[0][0];
	for (unsigned int unI = 0; unI < (m_unSize - 1); unI++)
		for (unsigned int unJ = 0; unJ < (m_unSize - 1); unJ++)
		{
			if (m_vectPoints[unI][unJ] > m_fMax)
			{
				m_fMax = m_vectPoints[unI][unJ];
			}
			if (m_vectPoints[unI][unJ] < m_fMin)
			{
				m_fMin = m_vectPoints[unI][unJ];
			}
		}
}

/**
 *   Methode permettant d'adapter la couleur a la hauteur du
 *  point
 *
 *   @param fTmp : hauteur temporaire
 */
void Montagne::SetColor(float fTmp)
{
	if (fTmp < 0.3)
	{
		glColor3f(0, 0, fTmp);
	}
	else
	{
		if (fTmp < 0.7)
		{
			glColor3f(fTmp, fTmp/6, 0);
		}
		else
		{
			glColor3f(fTmp, fTmp, fTmp);
		}
	}
}

/**
 *   Methode permettant d'alterner entre fil de fer et mode
 *  rempli
 *
 */
void Montagne::ChangeMode()
{
	m_bFilled = !m_bFilled;
}

/**
 *   Affichage du terrain en utilisant OpenGL. Il est
 *  possible de surcharger la methode pour choisir une autre
 *  methode d'affichage
 *
 */
void Montagne::Draw()
{
	// Generate the appropriate boundaries 
	float fMax = m_fSpacing * (m_unSize / 2);
	float fMin = -fMax;
	float fTmp, fDiff;

	fDiff = m_fMax - m_fMin;

	// Drawing the map 
	for (unsigned int unI = 0; unI < (m_unSize - 1); unI++)
	{
		float fZ = fMin + unI * m_fSpacing;
		for (unsigned int unJ = 0; unJ < (m_unSize - 1); unJ++)
		{
			float fX = fMin + unJ * m_fSpacing;

			if (m_bFilled)
			{
				glBegin(GL_QUADS);

				fTmp = (m_vectPoints[unI][unJ] - m_fMin) / fDiff;
				SetColor(fTmp);
				glVertex3f(fX, m_vectPoints[unI][unJ], fZ);

				fTmp = (m_vectPoints[unI + 1][unJ] - m_fMin) / fDiff;
				SetColor(fTmp);
				glVertex3f(fX, m_vectPoints[unI + 1][unJ], fZ + m_fSpacing);

				fTmp = (m_vectPoints[unI + 1][unJ + 1] - m_fMin) / fDiff;
				SetColor(fTmp);
				glVertex3f(fX + m_fSpacing, m_vectPoints[unI + 1][unJ + 1], fZ + m_fSpacing);

				fTmp = (m_vectPoints[unI][unJ + 1] - m_fMin) / fDiff;
				SetColor(fTmp);
				glVertex3f(fX + m_fSpacing, m_vectPoints[unI][unJ + 1], fZ);

				glEnd();
			}
			else
			{
				glBegin(GL_LINES);

				glColor3f(0, 1.0, 0);

				glVertex3f(fX, m_vectPoints[unI][unJ], fZ);
				glVertex3f(fX, m_vectPoints[unI + 1][unJ], fZ + m_fSpacing);

				glVertex3f(fX, m_vectPoints[unI + 1][unJ], fZ + m_fSpacing);
				glVertex3f(fX + m_fSpacing, m_vectPoints[unI + 1][unJ + 1], fZ + m_fSpacing);

				glVertex3f(fX + m_fSpacing, m_vectPoints[unI + 1][unJ + 1], fZ + m_fSpacing);
				glVertex3f(fX + m_fSpacing, m_vectPoints[unI][unJ + 1], fZ);

				glVertex3f(fX + m_fSpacing, m_vectPoints[unI][unJ + 1], fZ);
				glVertex3f(fX, m_vectPoints[unI][unJ], fZ);

				glEnd();
			}

		}
	}


}
