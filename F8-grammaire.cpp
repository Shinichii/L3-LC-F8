#include "F8-grammaire.h"

grammaire::grammaire()
{
    //ctor
    axiome = '#';
	this->tableAnalyse = NULL;
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
	this->afficherTableAnalyse();
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
			nonTerminal *temporaire = recupererElement(regle.at(i));
			if (this->recupererElement(temporaire->premiersContientEpsilon()))
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
	//Allocation
	this->tableAnalyse = new std::string*[this->NT.size()];
	for (int i = 0; i < NT.size(); i++)
	{
		this->tableAnalyse[i] = new std::string[this->terminaux.size()+1];//derniere case est $
		for (int j = 0; j < terminaux.size()+1; j++)
		{
			this->tableAnalyse[i][j] = " ";
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
				if (caractere != '#')
				{
					auto rechercheIndice = std::find(this->terminaux.begin(), this->terminaux.end(), caractere);
					if (rechercheIndice != this->terminaux.end())
					{
						int j = std::distance(this->terminaux.begin(), rechercheIndice);
						this->tableAnalyse[i][j] = std::string(regle.begin(), regle.end());
					}
				}
					else
					{
						std::set<char>aAjouter = NT.at(i).getSuivants();
						for (char suivantA : aAjouter)
						{
							if (suivantA == '$')
							{
								this->tableAnalyse[i][terminaux.size()] = std::string(regle.begin(), regle.end());
							}
							else 
							{
								auto rechercheIndice = std::find(this->terminaux.begin(), this->terminaux.end(), suivantA);
								if (rechercheIndice != this->terminaux.end())
								{
									int j = std::distance(this->terminaux.begin(), rechercheIndice);
									this->tableAnalyse[i][j] = std::string(regle.begin(), regle.end());
								}
							}
						}
					}
				}
			}
		}
	
}

void grammaire::afficherTableAnalyse()
{
	if (this->tableAnalyse == NULL)
	{
		std::cout << "[INFO] : Table d'analyse non generee. On ne l'affiche pas"<<std::endl;
		return;
	}
	for (char terminal : terminaux)
	{
		std::cout << "\t" << terminal;
	}
	std::cout << "\t$" << std::endl;
	for (int i = 0; i < NT.size(); i++)
	{
		std::cout << NT.at(i).getNom() << " ";
		for (int j = 0; j < terminaux.size() + 1; j++)
		{
			if (tableAnalyse[i][j] != " ")
			{
				std::cout << "\t" << NT.at(i).getNom() << "->" << this->tableAnalyse[i][j];
			}
			else
			{
				std::cout << "\t";
			}
		}
		std::cout << std::endl;
	}
}

void grammaire::testerMot()
{
	char reponseUtilisateur = 'n';
	do
	{
		std::string entree;
		std::cout << "Veuillez saisir une chaine de caracteres a tester" << std::endl;
		std::cin >> entree;
		lireMot(entree);
		std::cout << "Voulez-vous essayer une autre chaine de caracteres ?(O/N)";
		do
		{
			std::cin >> reponseUtilisateur;
		} while (std::cin.bad() && reponseUtilisateur != 'O' && reponseUtilisateur != 'o' && reponseUtilisateur != 'n' && reponseUtilisateur != 'N');
	} while (reponseUtilisateur == 'o' || reponseUtilisateur == 'O');
}

void grammaire::lireMot(std::string w)
{
	//Initialisation
	std::deque<char> pile;
	pile.push_back('$');
	pile.push_back(this->getAxiome());
	validationChaine(w);
	int ps = 0;
	char X, a;
	std::cout << "Pile\tEntree\tSortie" << std::endl;
	do
	{
		std::cout << std::endl;
		for (std::deque<char> tmp = pile; !tmp.empty(); tmp.pop_front())
		{
			std::cout << tmp.front();
		}
		std::cout << "\t" << w.substr(ps) << "\t";
		X = pile.back();
		a = w.at(ps);
		if (X == '$' || estTerminal(X)) 
		{
			if (X == a)
			{
				pile.pop_back();
				ps++;
			}
			else
			{
				messageErreurLecture(w, ps);
				return;
			}
		}
		else //X est un nonTerminal
		{
			int i = 0, j = 0;
			auto positionItTerminal = std::find(terminaux.begin(), terminaux.end(), a);
			nonTerminal elementRecupere = *(this->recupererElement(X));
			auto positionItNT = std::find(this->NT.begin(), this->NT.end(), elementRecupere);
			if (a == '$' && positionItNT != NT.end())
			{
				i = std::distance(NT.begin(), positionItNT);
				j = terminaux.size();
				std::string tmp = this->tableAnalyse[i][j];
				if (tmp != " ")
				{
					pile.pop_back();
					for (int k = tmp.length() - 1; k >= 0; k--)
					{
						if (tmp.at(k) != '#')
						{
							pile.push_back(tmp.at(k));
						}
					}
					std::cout << X << "->" << tmp;
				}
				else
				{
					messageErreurLecture(w, ps);
					return;
				}
			}
			else if (positionItTerminal == terminaux.end() || positionItNT == this->NT.end())
			{
				messageErreurLecture(w, ps);
				return;
			}
			else
			{
				i = std::distance(NT.begin(), positionItNT);
				j = std::distance(terminaux.begin(), positionItTerminal);
				std::string tmp = this->tableAnalyse[i][j];
				if (tmp != " ")
				{
					pile.pop_back();
					for (int k = tmp.length()-1; k >= 0; k--)
					{
						if (tmp.at(k) != '#')
						{
							pile.push_back(tmp.at(k));
						}
					}
					std::cout << X << "->" << tmp;
				}
				else
				{
					messageErreurLecture(w, ps);
					return;
				}
			}
		}
	} while (X != '$');
	std::cout << std::endl <<"[INFO] La chaine : " << w << " a ete lue avec succes !" << std::endl;
}

void grammaire::validationChaine(std::string& w)
{
	if (w.at(w.length()-1) != '$')
	{
		w.append("$");
	}
	return;
}

void grammaire::messageErreurLecture(std::string w, int ps)
{
	std::cout << std::endl;
	std::cout << "[ERREUR] : La grammaire ne peut interpreter cette chaine" << std::endl;
	std::cout << w<<std::endl;
	for (int i = 0; i < ps; i++)
	{
		std::cout << " ";
	}
	std::cout << "*" << std::endl;
}

