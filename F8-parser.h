#ifndef F8_PARSER_H_INCLUDED
#define F8_PARSER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include "F8-grammaire.h"

void lectureFichier(std::string cheminFichier, grammaire& g);

#endif // F8_PARSER_H_INCLUDED
