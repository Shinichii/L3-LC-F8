#include "F8-grammaire.h"

grammaire::grammaire()
{
    //ctor
    axiome = '#';
}
bool estTerminal(char c)
{
	return !(c >= 'A' && c <= 'Z') && c != '\n' && c != '\0' && c != '|';
}
void grammaire::setAxiome(char axiome)
{
    this->axiome = axiome;
}
char grammaire::getAxiome()
{
    return this->axiome;
}
void grammaire::ajouterTerminal(char terminal)
{
    this->terminaux.insert(terminal);
}
void grammaire::ajouterNonTerminal(nonTerminal nt)
{
    this->NT.push_back(nt);
}
/*
Fonction : creerEtatPrime
Arguments : Aucun
Description : Le programme cherche dans sa grammaire un caractere non terminal pas encore attribue
Et cree un nonterminal associe avant de le renvoyer
*/
char grammaire::creerEtatPrime()
{
	bool alphabet[26] = { false };
	for (std::vector<nonTerminal>::iterator it = NT.begin(); it < NT.end(); it++)
	{
		alphabet[it->getNom() - 'A'] = true;
	}
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i] == false)
		{
			nonTerminal prime = nonTerminal(i + 'A');
			std::vector<char> st;
			st.push_back('#');
			prime.ajouterRegle(st);
			ajouterNonTerminal(prime);

			return prime.getNom();
		}
	}
	return '\0';
}
bool grammaire::estDansLEnsembleNonTerminal(char nom)
{
    for(unsigned int i = 0; i < this->NT.size(); i++)
    {
        if(this->NT.at(i).getNom() == nom)
        {
            return true;
        }
    }
    return false;
}
nonTerminal* grammaire::recupererElement(char nom)
{
        for(unsigned int i = 0; i < this->NT.size(); i++)
    {
        if(this->NT.at(i).getNom() == nom)
        {
            return &(this->NT.at(i));
        }
    }
		return NULL;
}
void grammaire::traitementGrammaireRecursive()
{
	bool* aTraiter = new bool[NT.size()];

	for (unsigned int i = 0; i < NT.size(); i++)
	{
		if (!NT.at(i).estRecursif())
		{
			DEBUG_MSG("[INFO] : Le non terminal " << NT.at(i).getNom() << " n'est pas recursif");
			aTraiter[i] = false;
		}
		else
		{
			DEBUG_MSG("[INFO] : Le non terminal : " << NT.at(i).getNom() << " est recursif.");
			aTraiter[i] = true;
		}
	}
	for (unsigned int i = 0; i < NT.size(); i++)
	{
		if (aTraiter[i] == true)
		{
			char nom = creerEtatPrime();
			NT.at(i).eliminationRecursivite(recupererElement(nom));
		}
	}
}
void grammaire::mettreAJourRegles(char nom, nonTerminal nt)
{
	nonTerminal* aChanger = recupererElement(nom);
	aChanger->mettreAJourRegles(nt);
}
void grammaire::afficher()
{
	std::set<char> premiers;
    std::cout << " [ AXIOME ] : " << axiome << std::endl;
    std::cout << " =============" << std::endl;
    std::cout << " [ TERMINAUX ]" << std::endl;
    for(std::set<char>::iterator it = terminaux.begin(); it != terminaux.end(); it++)
    {
        std::cout<< *it << std::endl;
    }
    std::cout << "===============" << std::endl;
    std::cout << "[ NON TERMINAUX ]" << std::endl;
    for(unsigned int i = 0; i < NT.size();i++)
    {
            std::cout << NT.at(i).getNom() << std::endl;
    }
    std::cout << "===============" << std::endl;
    std::cout << "[ REGLES ]" << std::endl;
    for(unsigned int i = 0; i < NT.size();i++)
    {
            std::cout << NT.at(i);
			
    }
	std::cout << "[PREMIERS]" << std::endl;
	for (unsigned int i = 0; i < NT.size(); i++)
	{
		NT.at(i).afficherPremiers();
	}
	for (std::set<char>::iterator it = terminaux.begin(); it != terminaux.end(); it++)
	{
		std::cout << "PREMIER [ " << *it << " ] =  " << *it << std::endl;
	}
	std::cout << "[SUIVANTS]" << std::endl;
	for (unsigned int i = 0; i < NT.size(); i++)
	{
		NT.at(i).afficherSuivants();
	}
}

void grammaire::calculPremiers()
{
	for (unsigned int i = 0; i < NT.size(); i++)
	{
		calculPremier(&(NT.at(i)));
	}
}

std::set<char> grammaire::calculPremier(nonTerminal *nt)
{
	std::vector<std::vector<char>> regles = nt->getRegles();
	for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
	{
		if (estTerminal(it->at(0)))
		{
			nt->ajouterPremier(it->at(0));
		}
		else
		{
			nt->ajouterPremiers(calculPremier(recupererElement(it->at(0))));
		}
	}
	return nt->getPremiers();
}

void grammaire::calculSuivants()
{
	bool ensembleMisAJour = false;
	NT.at(0).ajouterSuivant('$');
	do
	{
		ensembleMisAJour = false;
		for (unsigned int i = 0; i < NT.size(); i++)
		{
			std::vector<std::vector<char>> regles = NT.at(i).getRegles();
			for (std::vector<std::vector<char>>::iterator it = regles.begin(); it != regles.end(); it++)
			{
				for (unsigned int j = 0; j < it->size(); j++)
				{
					if (estTerminal(it->at(j)))
					{
						//On ne fait rien
					}
					else
					{
						nonTerminal* tmp = recupererElement(it->at(j));
						if (j+1 < it->size()) //On verifie si une chaine de caractere suit l'element
						{
							if (estTerminal(it->at(j + 1)))
							{
								ensembleMisAJour = ensembleMisAJour || tmp->ajouterSuivant(it->at(j + 1));
							}
							else
							{
								nonTerminal *temporaire = recupererElement(it->at(j + 1));
								if (!temporaire->premiersContientEpsilon())
								{
									ensembleMisAJour = ensembleMisAJour || tmp->ajouterSuivantsSaufEpsilon(temporaire->getPremiers());
								}
									ensembleMisAJour = ensembleMisAJour || tmp->ajouterSuivants(NT.at(i).getSuivants());
							}
						}
						else
						{
							ensembleMisAJour = ensembleMisAJour || tmp->ajouterSuivants(NT.at(i).getSuivants());
						}
					}
				}
			}
		}
	} while (ensembleMisAJour);

}

std::set<char> grammaire::getPremiersDuneRegle(std::vector<char> regle)
{
	std::set<char> premiers;
	bool recuperer = true;
	int i = 0;
	while(i < regle.size())
	{
		if (!estTerminal(regle.at(i)) && recuperer)
		{
			if (this->recupererElement(regle.at(i))->premiersContientEpsilon())
			{
				premiers.insert('#');
				recuperer = true;
			}
			else
			{
				recuperer = false;
			}
			for (char prem : this->recupererElement(regle.at(i))->getPremiers())
			{
				premiers.insert(prem);
			}
		}
		else if (recuperer)
		{
			premiers.insert(regle.at(i));
			recuperer = false;
		}
		i++;
	}
	return std::set<char>(premiers);
}

void grammaire::constructionTableAnalyse()
{
	std::string** tableAnalyse;
	std::cout << "Not done." << std::endl;
	//Allocation
	tableAnalyse = new std::string*[this->NT.size()];
	for (int i = 0; i < NT.size(); i++)
	{
		tableAnalyse[i] = new std::string[this->terminaux.size()];
		for (int j = 0; j < terminaux.size(); j++)
		{
			tableAnalyse[i][j] = " ";
		}
	}
	//Remplir le tableau
	for (int i = 0; i < NT.size(); i++)
	{
		nonTerminal nt = NT.at(i);
		for (std::vector<char> regle : nt.getRegles())
		{
			std::set<char> premierProd = this->getPremiersDuneRegle(regle);
			for (char caractere : premierProd)
			{
				if (estTerminal(caractere))
				{
					if (caractere != '#')
					{
						auto rechercheIndice = std::find(this->terminaux.begin(), this->terminaux.end(), caractere);
						if (rechercheIndice != this->terminaux.end())
						{
							int j = std::distance(this->terminaux.begin(), rechercheIndice);
							tableAnalyse[i][j] = std::string(regle.begin(), regle.end());
						}
					}
					else
					{
						std::set<char>aAjouter = NT.at(i).getSuivants();
						for (char suivantA : aAjouter)
						{
							auto rechercheIndice = std::find(this->terminaux.begin(), this->terminaux.end(), suivantA);
							if (rechercheIndice != this->terminaux.end())
							{
								int j = std::distance(this->terminaux.begin(), rechercheIndice);
								tableAnalyse[i][j] = std::string(regle.begin(), regle.end());
							}
						}
					}
				}
			}
		}
	}
	/*http://digital.cs.usu.edu/~allanv/cs4700/HandoutScott2.pdf
	M[nt;t]
	Pour chaque règle r de NT.at(i)
		1.Pour chaque terminal k dans PREMIER(r), on ajoute r à M[nt;t]
		2.Si Epsilon dans PREMIER(r) ajouter r à M[nt;b] pour chaque terminal b dans SUIVANT(A)
		3.Si Epsilon dans PREMIER(r) ET $ dans SUIVANT(NT), ajouter r à M[nt;$]
		4.Le reste à " "
	*/
	for (char terminal : terminaux)
	{
		std::cout << "    " << terminal;
	}
	std::cout << std::endl;
	for (int i = 0; i < NT.size(); i++)
	{
		std::cout << NT.at(i).getNom() << " ";
		for (int j = 0; j < terminaux.size(); j++)
		{
			if (tableAnalyse[i][j] != " ")
			{
				std::cout << NT.at(i).getNom() << "->" << tableAnalyse[i][j] << " ";
			}
			else
			{
				std::cout << "    ";
			}
		}
		std::cout << std::endl;
	}
}

