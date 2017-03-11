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
    friend std::ostream& operator<<(std::ostream &flux, nonTerminal const& nt );
    char getNom();
	bool estRecursif();
	bool regleExiste(std::vector<char> regle);
	void mettreAJourRegles(nonTerminal &nt);
protected:
private:
    char nom;
    std::vector<std::vector<char>> regles;
};

#endif // NONTERMINAL_H
