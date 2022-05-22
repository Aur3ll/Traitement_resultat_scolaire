#include "Etudiant.h"



size_t chargerFichier(std::string matricules[], float notes[], const size_t& entreeMax, std::ifstream& fichier)
{
	size_t i{ 0 };
	for (; !fichier.eof() and i < entreeMax; i++)
	{
		fichier >> matricules[i];
		fichier >> notes[i];
	}
	return i;
}

FORMAT validationMatricule(const std::string matricules[], size_t T[], std::string& matricule,const size_t& taille)
{
	
	if (matricule == "")
	{
		return FORMAT::vide;
	}
	if (matricule.size() != 6)
	{
		return FORMAT::invalide;
	}
	for (size_t i{ 0 }; i < 6 and i < matricule.size(); i++)
	{
		if (i % 2 == 0 and !isalpha(matricule[i]))
		{
			return FORMAT::invalide;
		}
		else if (i % 2 == 1 and !isdigit(matricule[i]))
		{
			return FORMAT::invalide;
		}
	}

	majString(matricule);
	for (size_t i{ 0 }; i < taille; i++)
	{
		if (matricules[T[i]] == matricule)
		{
			return FORMAT::doublon;
		}
	}
	return FORMAT::valide;
}

std::string obtenirMatricule()
{
	std::cout << "Entrer le Matricule de l'élève: ";
	std::string matricule{};
	getline(std::cin, matricule);
	std::cout << std::endl;
	return matricule;

}

size_t trouverIdx(const std::string t[], const size_t& taille, const std::string& str)
{
	for (size_t i{ 0 }; i < taille; i++)
	{
		if (t[i] == str)
		{
			return i;
		}
	}
	return std::string::npos;
}

char evaluerCote(const float& note)
{
	char cote{ 'E' };
	if (90 <= note)
	{
		cote = 'A';
	}
	else if (80 <= note)
	{
		cote = 'B';
	}
	else if (70 <= note)
	{
		cote = 'C';
	}
	else if (60 <= note)
	{
		cote = 'D';
	}
	return cote;
}

void majString(std::string& str)
{
	for (char& c : str)
	{
		c = toupper(c);
	}
	
}

bool validationChoix(char& c)
{
	switch(c)
	{
	case 'u':case 'g':
		c = toupper(c);
	case 'U':case 'G':
		return true;
	}
	
	return false;
}

void triBulle(unsigned short idxs[],const float notes[],const size_t& taille)
{
	bool swapped{ true };
	for (size_t pass{ taille - 1 }; swapped and pass > 0; pass--)
	{
		swapped = false;
		
		for (size_t idx{ 0 }; idx < pass; idx++)
		{
			if (notes[idxs[idx]] > notes[idxs[idx + 1]])
			{
				std::swap(idxs[idx], idxs[idx + 1]);
				swapped = true;

			}
		}
	}
}

void triBulle(size_t idxs[],const float notes[],const size_t& taille)
{
	bool swapped{ true };
	for (size_t pass{ taille - 1 }; swapped and pass > 0; pass--)
	{
		swapped = false;

		for (size_t idx{ 0 }; idx < pass; idx++)
		{
			if (notes[idxs[idx]] > notes[idxs[idx + 1]])
			{
				std::swap(idxs[idx], idxs[idx + 1]);
				swapped = true;

			}
		}
	}
}

float mediane(const float notes[],const unsigned short idxs[],const size_t& taille)
{
	if (taille % 2 == 0)
	{
		return notes[idxs[(taille / 2) - 1]];
	}
	return notes[idxs[(taille / 2)]];
}

float mediane(const float notes[],const size_t idxs[], const size_t& taille)
{
	if (taille % 2 == 0)
	{
		return notes[idxs[(taille / 2) -1]];
	}
	return notes[idxs[(taille / 2)]];
}

float moyenne(const float notes[], const size_t & taille)
{
	float total{ 0 };
	for (int i{ 0 }; i < (int)taille; i++)
	{
		total += notes[i];
	}
	return total / taille;
}

	float moyenne(const float notes[], size_t idxs[],const size_t& taille)
	{
		float total{ 0 };
		for (int i{ 0 }; i < (int)taille; i++)
		{
			total += notes[idxs[i]];
		}
		return total / taille;
	}

	void genererTableauIndices(unsigned short T[], const size_t& taille)
	{
		for (unsigned short i{ 0 }; i < (unsigned short)taille; i++)
		{
			T[i] = i;
		}
	}

	float carre(float& nb)
	{
		return nb * nb;
	}

	float ecartType(const float notes[], const size_t idxs[], const size_t& taille, const float& moyenne)
	{
		float total{};
		for (size_t i{ 0 }; i < taille; i++)
		{
			float calcul{ notes[idxs[i]] - moyenne };
			total += carre(calcul); // note - moyenne dans le carré me donnais une erreur en rapport au left value
		}
		return sqrt(total/taille);
	}

	float ecartType(const float notes[], const size_t& taille, const float& moyenne)
	{
		float total{};
		for (size_t i{ 0 }; i < taille; i++)
		{
			float calcul{ notes[i] - moyenne };
			total += carre(calcul);
		}
		return sqrt(total / taille);
	}