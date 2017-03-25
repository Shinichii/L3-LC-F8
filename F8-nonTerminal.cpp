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
void nonTerminal::ajouterRegles(std::vector<std::vector<char>> regles)
{
	for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
	{
		ajouterRegle(*it);
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

std::vector<std::vector<char>> const & nonTerminal::getRegles() const
{
	return this->regles;
}

bool nonTerminal::estRecursif()
{
	DEBUG_MSG("[INFO] : Test de la recursivite a gauche sur " << this->getNom());
	for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
	{
		if (estRecursif(it->begin()))
		{
			return true;
		}
	}
	return false;
}
bool nonTerminal::estRecursif(std::vector<char>::iterator regle)
{
	if (*regle == this->nom)
	{
		DEBUG_MSG("[INFO]Grammaire recursive a gauche detectee.");
		return true;
	}
	return false;
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

void nonTerminal::eliminationRecursivite(nonTerminal* etatPrime)
{
	std::vector<std::vector<char>> reglesNonRecursives;
	std::vector<std::vector<char>> reglesNonRecursivesPrime;
	for (int i =0; i < regles.size(); i++)
	{
		
		if (estRecursif(regles.at(i).begin()))
		{
			int offset = 0;
			while (regles.at(i).at(offset) == this->getNom() && offset < regles.at(i).size()-1)
			{
				std::cout << regles.at(i).at(offset) << std::endl;
				offset++;
			}
			std::vector<char> nouvelleRegle(regles.at(i).begin()+offset, regles.at(i).end());
			nouvelleRegle.push_back(etatPrime->getNom());
			reglesNonRecursivesPrime.push_back(nouvelleRegle);
			
		}
		else
		{
			if (regles.at(i).at(0) == '#')
			{
				std::vector<char> st;
				st.push_back('#');
				reglesNonRecursives.push_back(st);
				//On fait rien
			}
			else
			{
				std::vector<char> nouvelleRegle(regles.at(i).begin(), regles.at(i).end());
				nouvelleRegle.push_back(etatPrime->getNom());
				reglesNonRecursives.push_back(nouvelleRegle);
			}
		}
	}
	regles.clear();
	ajouterRegles(reglesNonRecursives);
	etatPrime->ajouterRegles(reglesNonRecursivesPrime);
}

void nonTerminal::ajouterPremier(char c)
{
	this->premier.insert(c);
}

void nonTerminal::ajouterPremiers(std::set<char> caracteres)
{
	for (char caractere : caracteres)
	{
		ajouterPremier(caractere);
	}
}

void nonTerminal::ajouterSuivant(char c)
{
	this->suivant.insert(c);
}

void nonTerminal::ajouterSuivants(std::set<char> caracteres)
{
	for (char caractere : caracteres)
	{
		this->ajouterSuivant(caractere);
	}
}

std::set<char> nonTerminal::getPremiers()
{
	return std::set<char>(this->premier);
}

void nonTerminal::afficherPremiers()
{
	std::cout << "PREMIER [ " << this->nom << " ] =" << std::endl;
	for (std::set<char>::iterator it = premier.begin(); it != premier.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}
