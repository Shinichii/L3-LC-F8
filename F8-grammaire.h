#ifndef GRAMMAIRE_H
#define GRAMMAIRE_H

#include "F8-nonTerminal.h"
#include <iostream>
#include <stack>

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

		//Fonction de calcul des ensemble PREMIER(X) et SUIVANT(X)
		void calculPremiers();
		std::set<char> calculPremier(nonTerminal *nt);
		void calculSuivants();

		//Fonctions de la table d'analyse
		std::set<char> getPremiersDuneRegle(std::vector<char> regle);
		void constructionTableAnalyse();
		void afficherTableAnalyse();

		//Fonctions pour la lecture d'un mot
		void testerMot();
		void lireMot(std::string w);
		void validationChaine(std::string& w);
		void messageErreurLecture(std::string w, int ps);
    protected:
    private:
        char axiome;
        std::set<char> terminaux;
        std::vector<nonTerminal> NT;
		std::string** tableAnalyse;
		
};

bool estTerminal(char c);
#endif // GRAMMAIRE_H
