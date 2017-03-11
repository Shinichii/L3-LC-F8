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
nonTerminal& grammaire::recupererElement(char nom)
{
        for(int i = 0; i < this->NT.size(); i++)
    {
        if(this->NT.at(i).getNom() == nom)
        {
            return this->NT.at(i);
        }
    }
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
