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

		char creerEtatPrime();

        bool estDansLEnsembleNonTerminal(char nom);
        nonTerminal* recupererElement(char nom);

		void traitementGrammaireRecursive();
		void mettreAJourRegles(char nom, nonTerminal nt);

        void afficher();

		void calculPremiers();
		std::set<char> calculPremier(nonTerminal *nt);
		void calculSuivants();

		std::set<char> getPremiersDuneRegle(std::vector<char> regle);

		void constructionTableAnalyse();
    protected:
    private:
        char axiome;
        std::set<char> terminaux;
        std::vector<nonTerminal> NT;
		
};

bool estTerminal(char c);
#endif // GRAMMAIRE_H
