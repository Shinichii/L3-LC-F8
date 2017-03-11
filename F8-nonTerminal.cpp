#include "F8-nonTerminal.h"

nonTerminal::nonTerminal(char nom)
{
    //ctor
    this->nom = nom;
}

void nonTerminal::ajouterRegle(std::vector<char> regle)
{
	if (!regleExiste(regle))
	{
		this->regles.push_back(regle);
	}
}
std::ostream& operator<<(std::ostream &flux, nonTerminal const& nt)
{
    //Affichage des attributs
    for(unsigned int i = 0; i < nt.regles.size(); i++)
    {
		std::string str = std::string(nt.regles.at(i).begin(), nt.regles.at(i).end());
		flux << nt.nom << " = " << str << std::endl;
    }
    return flux;
}
char nonTerminal::getNom()
{
    return this->nom;
}

bool nonTerminal::estRecursif()
{
	for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
	{
		for (std::vector<char>::iterator it2 = it->begin(); it2 != it->end(); it2++)
		{
			if (*it2 == this->nom)
			{
				DEBUG_MSG("Grammaire recursive a gauche detectee.");
				return true;
			}
		}
	}
}

bool nonTerminal::regleExiste(std::vector<char> regle)
{
	for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
	{
		if (*it == regle)
		{
			return true;
		}
	}
	return false;
}

void nonTerminal::mettreAJourRegles(nonTerminal &nt)
{
	for (std::vector<std::vector<char>>::iterator it = nt.regles.begin(); it < nt.regles.end(); it++)
	{
		this->ajouterRegle(*it);
	}
}
