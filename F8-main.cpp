#include "dirent.h"
#include <iostream>
#include "F8-parser.h"

void listingFichiers()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("Z:\\LangageEtCompilation")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
        return;
    }
}
int main()
{
    grammaire g;
    lectureFichier("Z:\\LangageEtCompilation\\F8test2.txt", g);
    g.afficher();
}
