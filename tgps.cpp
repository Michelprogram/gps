#include "tgps.h"
#include <string>

using namespace std;

tGPS::tGPS()
{
    init_listvilles();
}

void tGPS::init_listvilles()
{
    listvilles[0] = ville {"Lyon",45.75,4.85};
    listvilles[1] = ville {"Paris",48.8534,2.3488};
    listvilles[2] = ville {"Bordeaux",44.8333,-0.5667};
    listvilles[3] = ville {"Toulouse",43.6043,1.4437};
    listvilles[4] = ville {"Marseille",43.3,5.4};
    listvilles[5] = ville {"Nantes",47.2173,-1.5534};
    listvilles[6] = ville {"Tours",47.394144,0.68484};
    listvilles[7] = ville {"Strasbourg",48.5833,7.75};
    listvilles[8] = ville {"Brest",48.4,-4.5};
    listvilles[9] = ville {"Nice",43,7};

}

void tGPS::SetVilleDebut(short position)
{
    ville_debut = listvilles[position].nom;
}

void tGPS::SetVilleFin(short position)
{
    ville_fin = listvilles[position].nom;
}

void tGPS::SetCourse(bool flag)
{
    course = flag;
}

string tGPS::GetVilleDebut()
{
    return ville_debut;
}

string tGPS::GetVilleFin()
{
    return ville_fin;
}

void tGPS::Menu()
{
    short k=0,ville_start,ville_end;
    char response;
    do
    {
        printf("Choisir une villes parmit la liste (0-9) : \n\n");
        for (auto i=listvilles.begin();i != listvilles.end(); i++)
        {
            printf("%d-%s \n",k,i->nom.c_str());
            k++;
        }

        printf("Ville de départ : \n");
        scanf("%d",&ville_start);


        printf("Ville d'arrivée : \n");
        scanf("%d",&ville_end);

        printf("Course Rapide ou Course courte (O/N) : \n");
        scanf("%c",response);

        if(response == 'O')
            SetCourse(true);
        else
            SetCourse(false);

        k=0;
    }

    while( (ville_start > -1 && ville_start < 10) && (ville_end > -1 && ville_end < 10) &&(ville_end == ville_start) && (response != 'O' || response != 'N') );

    SetVilleDebut(ville_start);
    SetVilleFin(ville_end);

}
