#include "F8-file_Finder.h"
#include <iostream>
#include "F8-parser.h"


int main()
{
    grammaire g;
    lectureFichier("D:\\LangagesEtCompilation\\L3-LC-F8\\F8-G2.txt", g);
    g.afficher();
	g.traitementGrammaireRecursive();
	g.afficher();
	return 0;
}
