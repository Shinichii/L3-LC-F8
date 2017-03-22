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
	bool estRecursif();
	bool estRecursif(std::vector<char>::iterator regle);
	bool regleExiste(std::vector<char> regle);
	void mettreAJourRegles(nonTerminal &nt);

	void eliminationRecursivite(nonTerminal *etatPrime);

protected:
private:
    char nom;
    std::vector<std::vector<char>> regles;
};

#endif // NONTERMINAL_H
