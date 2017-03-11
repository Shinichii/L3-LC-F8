/*
	@Auteur : Aurelien DENIS
	@Groupe : F8
*/

#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <vector>
using namespace std;

namespace fs = std::experimental::filesystem;

bool extensionValide(string s, string extension);

void recupererElements(vector<string>& listeFichiers, string extension);

string choisirElement(string extension);

