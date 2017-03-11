#ifndef GRAMMAIRE_H
#define GRAMMAIRE_H

#include "F8-nonTerminal.h"
#include <iostream>
class grammaire
{
    public:
        grammaire();
        void setAxiome(char axiome);
        char getAxiome();
        void ajouterTerminal(char terminal);
        void ajouterNonTerminal(nonTerminal nt);
        bool estDansLEnsembleNonTerminal(char nom);
        nonTerminal* recupererElement(char nom);
		bool testGrammaireRecursive();

		void mettreAJourRegles(char nom, nonTerminal nt);

        void afficher();
    protected:
    private:
        char axiome;
        std::set<char> terminaux;
        std::vector<nonTerminal> NT;
};

#endif // GRAMMAIRE_H
