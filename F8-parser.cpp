#include "F8-parser.h"
bool estTerminal(char c)
{
    return !(c >= 'A' && c <= 'Z') && c !='\n' && c != '\0' && c != '|';
}
void lectureFichier(std::string cheminFichier, grammaire& g)
{
    std::ifstream fichier(cheminFichier.c_str(), std::ios::in);
    if(!fichier)
    {
        std::cout << "Erreur, le fichier n'a pas pu etre ouvert" << std::endl;
    }

    else
    {
        while(!fichier.eof())
        {
            std::cout << std::endl;
            char caractereLu = '\0';
            fichier.get(caractereLu);
            if(g.getAxiome()== '#' && !estTerminal(caractereLu))
            {
                g.setAxiome(caractereLu);
            }
            nonTerminal nt(caractereLu);
            fichier.get(caractereLu); // Pour ignorer le =
            std::vector<char> regle;
            while(caractereLu != '\n' && !fichier.eof())
            {
                caractereLu = '\0';
                fichier.get(caractereLu);
                if(estTerminal(caractereLu))
                {
                    g.ajouterTerminal(caractereLu);
                }
                if(caractereLu!= '\n' && caractereLu != '|' && caractereLu != '\0')
                {
                    regle.push_back(caractereLu);
                }
                else if(caractereLu == '\0')
                {
					if (regle.size() > 0)
					{
						nt.ajouterRegle(regle);
						regle.clear();
					}
                    //do  nothing
                }
                else
                {
                    nt.ajouterRegle(regle);
                    regle.clear();
                }

            }
            if(!g.estDansLEnsembleNonTerminal(nt.getNom()))
            {
                g.ajouterNonTerminal(nt);
            }
			else
			{
				g.mettreAJourRegles(nt.getNom(), nt);
			}
            std::cout << nt << std::endl;
        }
        fichier.close();
    }
}
