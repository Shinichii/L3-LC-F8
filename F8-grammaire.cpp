#include "F8-grammaire.h"

grammaire::grammaire()
{
    //ctor
    axiome = '#';
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
    for(int i = 0; i < this->NT.size(); i++)
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
        for(int i = 0; i < this->NT.size(); i++)
    {
        if(this->NT.at(i).getNom() == nom)
        {
            return &(this->NT.at(i));
        }
    }
}
void grammaire::traitementGrammaireRecursive()
{
	bool* aTraiter = new bool[NT.size()];

	for (int i = 0; i < NT.size(); i++)
	{
		if (!NT.at(i).estRecursif())
		{
			DEBUG_MSG("[INFO] : Le non terminal " << NT.at(i).getNom() << " n'est pas recursif");
			aTraiter[i] = false;
		}
		else
		{
			DEBUG_MSG("[INFO] : Le non terminal : " << NT.at(i).getNom() << " est recursif. La grammaire est donc recursive");
			aTraiter[i] = true;
		}
	}
	for (int i = 0; i < NT.size(); i++)
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
    std::cout << " [ AXIOME ] : " << axiome << std::endl;
    std::cout << " =============" << std::endl;
    std::cout << " [ TERMINAUX ]" << std::endl;
    for(std::set<char>::iterator it = terminaux.begin(); it != terminaux.end(); it++)
    {
        std::cout<< *it << std::endl;
    }
    std::cout << "===============" << std::endl;
    std::cout << "[ NON TERMINAUX ]" << std::endl;
    for(int i = 0; i < NT.size();i++)
    {
            std::cout << NT.at(i).getNom() << std::endl;
    }
    std::cout << "===============" << std::endl;
    std::cout << "[ REGLES ]" << std::endl;
    for(int i = 0; i < NT.size();i++)
    {
            std::cout << NT.at(i) << std::endl;
    }

}
