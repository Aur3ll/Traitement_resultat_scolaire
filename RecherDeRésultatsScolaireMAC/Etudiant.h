#pragma once
#include <string>
#include <fstream>
#include <iostream>


enum class FORMAT
{
	valide,
	invalide,
	doublon,
	vide

};

enum class MODE
{
	UNIQUE,
	GROUPE
};


size_t chargerFichier(std::string matricules[], float notes[], const size_t& entreeMax, std::ifstream& fichier);
FORMAT validationMatricule(const std::string matricules[], size_t T[], std::string& matricule, const size_t& taille);
std::string obtenirMatricule();
size_t trouverIdx(const std::string t[], const size_t& taille, const std::string& str);
char evaluerCote(const float& note);
void majString(std::string& str);
bool validationChoix(char& c);
float moyenne(const float notes[],const size_t& taille);
float moyenne(const float notes[], size_t idxs[], const size_t& taille);
void triBulle(unsigned short idxs[], const float notes[],const size_t& taille);
void triBulle(size_t idxs[],const float notes[],const size_t& taille);
float mediane(const float notes[],const unsigned short idxs[], const size_t& taille);
float mediane(const float notes[],const size_t idxs[], const size_t& taille);
void genererTableauIndices(unsigned short T[], const size_t& taille);
float ecartType(const float notes[],const size_t idxs[], const size_t& taille, const float& moyenne);
float ecartType(const float notes[], const size_t& taille, const float& moyenne);
float carre(float& nb);
