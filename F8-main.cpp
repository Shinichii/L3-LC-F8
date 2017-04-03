#include "F8-file_Finder.h"
#include <iostream>
#include "F8-parser.h"


int main()
{
	char reponse;
	bool continuer = true;
	while (continuer)
	{
		grammaire g;
		//lectureFichier(choisirElement(".txt"), g);
		lectureFichier("D:\\LangagesEtCompilation\\L3-LC-F8\\F8-G9.txt", g);
		g.afficher();
		g.traitementGrammaireRecursive();
		g.calculPremiers();
		g.calculSuivants();
		g.afficher();
		g.constructionTableAnalyse();
		g.afficher();
		g.testerMot();
		std::cout << "Voulez-vous continuer ? (O/N)" << std::endl;
		do
		{
			reponse = 'K';
			std::cin >> reponse;
		} while (cin.bad() && reponse != 'O' && reponse != 'o' && reponse != 'n' && reponse != 'N');
		if (reponse == 'N' || reponse == 'n')
		{
			continuer = false;
		}
	}

	return 0;
}
