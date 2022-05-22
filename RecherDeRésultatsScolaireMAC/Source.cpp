#include "Etudiant.h"
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;


static  string NOM_DE_FICHIER("etudiants.resultats"); // j'ai tout mis les tableau endehors du main sinon ca donnait un avertissement que je dépassais la taille de  pile.
static  const size_t NB_MAX_ELEVES{ 10000 };
static  string matricules[NB_MAX_ELEVES]{};
static  float notes[NB_MAX_ELEVES]{};
static unsigned short tableauIndices[NB_MAX_ELEVES]{ 0 };
static size_t matriculesRecherchees[NB_MAX_ELEVES]{ 0 };

void ecrireEntete(string titre, string nom, string session)
{
	for (int i = 0; i < 5; i++)
	{
		cout << setw(25) << setfill(' ') << " ";
		switch (i)
		{
		case 1:
			cout << '*' << right << setw(31)   << "Lab  :  " << left << titre << setw(40 - titre.length()) << right << setfill(' ') << '*' << endl;
			break;
		case 2:
			cout << '*' << right  << setw(31)  << "Étutidant  :  " << left << nom << setw(40 - nom.length()) << right << setfill(' ') << '*' << endl;
			break;
		case 3:
			cout << '*' << right << setw(31)  << "Session  :  " << left << session << setw(40 - session.length()) << right << setfill(' ') << '*' << endl;
			break;
		default:
			cout << setw(72) << setfill('#') << '#' << endl;

		}

	}
	cout << endl;
}


void tracerLigne(const int largeur)
{
	cout << setfill('-') << setw(largeur) << '-' << endl;
}

void afficherResultat(const size_t& idx)
{
	system("cls");
	ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
	float moyenneGlobale{ moyenne(notes, NB_MAX_ELEVES) };
	float ecartTypeGlobale{ ecartType(notes, NB_MAX_ELEVES, moyenneGlobale) };
	cout << left << setfill(' ') << fixed << setprecision(1);
	cout << setw(25) << "Matricule: " << matricules[idx] << endl;
	cout << setw(25) << "Note: "<< notes[idx] << '%' << endl;
	cout << setw(25) << "Cote: " << evaluerCote(notes[idx]) << endl;
	cout << setw(25) << "Moyenne Globale: " << moyenneGlobale << '%' << endl;
	cout << setw(25) << "Médianne Globale: " << mediane(notes, tableauIndices, NB_MAX_ELEVES) << '%' << endl;
	cout << setw(25) << "Écart type global: " << ecartTypeGlobale << '%' << endl;
	cin.get();
}

void afficherResultat(size_t idxs[], const size_t& taille)
{
	float moyenneGroupe{ moyenne(notes, idxs, taille) };
	float moyenneGlobale{ moyenne(notes, NB_MAX_ELEVES) };
	float ecartTypeGroupe{ecartType(notes, idxs, taille, moyenneGroupe)};
	float ecartTypeGlobale{ecartType(notes, NB_MAX_ELEVES, moyenneGlobale)};

	tracerLigne(60);
	cout << "| " << left << setfill(' ') << setw(18) << "Matricules" << setw(20) << "| Notes" << setw(19) << "| Cotes" << '|' << endl;
	tracerLigne(60);
	cout.precision(1);
	cout << fixed;
	for (size_t i{ 0 }; i < taille; i++)
	{	
		
		cout << "| " << right << setfill(' ') << setw(17) << matricules[idxs[i]] << " | " << setw(16) << notes[idxs[i]] << '%' << " | " << setw(16) << evaluerCote(notes[idxs[i]]) << " |" << endl;
	}
	tracerLigne(60);
	cout << left << setfill(' ');
	cout << setw(25) << "Moyenne du groupe: " << moyenneGroupe << '%' << endl;
	cout << setw(25) << "Moyenne globale: " << moyenneGlobale << '%' << endl << endl;
	triBulle(idxs, notes, taille);
	cout << setw(25) << "Médiane du groupe: " << mediane(notes, idxs, taille) << '%' << endl;
	cout << setw(25) << "Médianne globale: " << mediane(notes, tableauIndices, NB_MAX_ELEVES) << '%' << endl << endl;
	cout << setw(25) << "Écart type du groupe: " << ecartTypeGroupe << '%' << endl;
	cout << setw(25) << "Écart type global: " << ecartTypeGlobale << '%' << endl;
}

void afficherTableau(const size_t idxs[], size_t& taille)
{
	for (size_t i{ 0 }; i < taille; i++)
	{
		cout << '[' << matricules[idxs[i]] << ']' << endl;
	}
}

MODE obtenirChoix()
{
	char c{};
	do
	{
		cout << "Choisir  le mode de sélection des matricules" << endl << "format (U)nique ou de (G)roupe: ";
		cin >> c;
		cin.ignore(1000, '\n');
		cout << endl;
	} while (!validationChoix(c));

	switch (c)
	{
	case 'U':
		return MODE::UNIQUE;
	}
	return MODE::GROUPE;
	
}

size_t rechercherMatricules(size_t matriculesRecherchees[],  size_t& taille, MODE choix )
{
	FORMAT etat{ FORMAT::vide };
	size_t matriculesValides{ 0 };
	do
	{
	
		string matricule{ obtenirMatricule() };
		etat = validationMatricule(matricules,matriculesRecherchees, matricule, matriculesValides );
		switch (etat)
		{
		case FORMAT::invalide:
			cout << "Matricule invalide: LCLCLC (L = Lettre, C = Chiffre)" << endl;
			break;
		case FORMAT::doublon:
			cout << "Matricule déjà entrer!" << endl;
			break;
		case FORMAT::valide:
			size_t idx{ trouverIdx(matricules,taille, matricule) };
			if (idx == string::npos)
			{
				cout << "Matricule introuvable!" << endl;
			}
			else if (choix == MODE::UNIQUE)
			{
				afficherResultat(idx);
				system("cls");
				ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
			}
			else if (choix == MODE::GROUPE)
			{
				matriculesRecherchees[matriculesValides] = idx;
				matriculesValides++;
				system("cls");
				ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
				afficherTableau(matriculesRecherchees, matriculesValides);
			}		
		}
	}while(etat != FORMAT::vide);

	return matriculesValides;
}

int main()
{
	
	setlocale(LC_ALL, "");
	ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
	ifstream fichier(NOM_DE_FICHIER);
	if (!fichier)
	{
		cout << "le fichier est introuvable!" << endl;
		return -1;
	}
	size_t taille(chargerFichier(matricules, notes, NB_MAX_ELEVES, fichier));
	cout << "Prière de patienter quelques secondes";
	genererTableauIndices(tableauIndices, NB_MAX_ELEVES);
	triBulle(tableauIndices,notes, NB_MAX_ELEVES);
	system("cls");
	ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
	MODE choix{ obtenirChoix() };
	size_t nbMatriculesValide{ rechercherMatricules(matriculesRecherchees, taille, choix )};
	if (choix == MODE::GROUPE)
	{
		system("cls");
		ecrireEntete("Recherche de résultats scolaires", "Marc-André Couturier", "Hiver 2021");
		afficherResultat(matriculesRecherchees, nbMatriculesValide);
	}
	


	return 0;
}