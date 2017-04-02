#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include<vector>
#include<set>
#include <fstream>
#include<string>
#include <algorithm>
#include <iostream>
#include "F8-debug.h"

class nonTerminal
{
public:
    nonTerminal(char nom);

    void ajouterRegle(std::vector<char> regle);
	void ajouterRegles(std::vector<std::vector<char>> regles);

    friend std::ostream& operator<<(std::ostream &flux, nonTerminal const& nt );

    char getNom();
	std::vector<std::vector<char>> const& getRegles() const;
	bool estRecursif();
	bool estRecursif(std::vector<char>::iterator regle);
	bool regleExiste(std::vector<char> regle);
	void mettreAJourRegles(nonTerminal &nt);

	void eliminationRecursivite(nonTerminal *etatPrime);

	void ajouterPremier(char c);
	void ajouterPremiers(std::set<char> caracteres);

	bool ajouterSuivant(char c);
	bool ajouterSuivants(std::set<char> caracteres);
	bool ajouterSuivantsSaufEpsilon(std::set<char> caracteres);

	std::set<char> getPremiers();
	
	void afficherPremiers();

	bool premiersContientEpsilon();

	std::set<char> getSuivants();
	void afficherSuivants();
protected:
private:
    char nom;
    std::vector<std::vector<char>> regles;

	std::set<char> premier;
	std::set<char> suivant;
};

#endif // NONTERMINAL_H
