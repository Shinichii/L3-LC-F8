#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include<vector>
#include<set>
#include <fstream>
using namespace std;
class nonTerminal
{
public:
    nonTerminal(char nom);
    void ajouterRegle(std::vector<char> regle);
    friend ostream& operator<<( ostream &flux, nonTerminal const& nt );
    char getNom();
protected:
private:
    char nom;
    std::vector<std::vector<char>> regles;
};

#endif // NONTERMINAL_H
