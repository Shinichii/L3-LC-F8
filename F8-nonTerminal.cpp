#include "F8-nonTerminal.h"

nonTerminal::nonTerminal(char nom)
{
    //ctor
    this->nom = nom;
}

void nonTerminal::ajouterRegle(std::vector<char> regle)
{
    this->regles.push_back(regle);
}
ostream& operator<<( ostream &flux, nonTerminal const& nt)
{
    //Affichage des attributs
    for(int i = 0; i < nt.regles.size(); i++)
    {
        flux << nt.nom << " = " << string(nt.regles.at(i).begin(), nt.regles.at(i).end()) << std::endl;
    }
    return flux;
}
char nonTerminal::getNom()
{
    return this->nom;
}
