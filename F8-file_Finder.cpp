#include "F8-file_Finder.h"

/*

	@Auteur : Aurelien DENIS
	@Groupe : F8

*/
/*
	Fonction : recupererElements
	Parametres : Un vecteur de type string qui va contenir le chemin de chaque fichier correspondant a
 	l'extension contenu dans le dossier
	Un string qui va correspondre a l'extension du fichier recherche
*/
void recupererElements(vector <string>& listeFichiers, string extension)
{
	std::string path = "..";

	for(auto &p : fs::directory_iterator(path))
	{
		if(extensionValide(p.path().extension().string(), extension))
		{
			listeFichiers.push_back(p.path().string());
		}
	}
}

/*
	Fonction : choixElement
	Parametre: L'extension des fichiers que l'on cherche
	Description : Cette fonction affiche tous les fichiers de l'extension que l'on veut
	et retourne le chemin du fichier choisi par l'utilisateur
	Si aucun fichier n'est présent dans le dossier, la fonction retourne NULL
*/
string choisirElement(string extension)
{
	std::vector<string> listeFichiers;
	unsigned int choix;
	recupererElements(listeFichiers, extension);
	if(listeFichiers.size() == 0)
	{
		cout << "[WARNING] Aucun element du type : " << extension << " n'a ete trouve" << endl;
		return "error";
	}
	for(unsigned int i = 0; i < listeFichiers.size(); i++)
	{
		cout << i + 1 << " : " << listeFichiers[i].substr(3) << endl;
	}
	do
	{
		cout << endl << "Votre choix : ";
		cin >> choix;
		cin.clear();
		cin.ignore();
	}while(choix < 1 || choix > listeFichiers.size());

	cout << endl;

	return listeFichiers[choix - 1];
}


/*
	Fonction : extensionValide
	Parametres: Une chaine de caracteres qui correspond au chemin du fichier
	Une chaine de caracteres qui correspond a l'extension nous interessant
	Description : La fonction verifie si le fichier choisi a la bonne extension
*/

bool extensionValide(string s, string extension)
{
	return s == extension;
}
