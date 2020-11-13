#include "tgps.h"
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

tGPS::tGPS()
{
    init_listvilles();
    init_Nb_villes();
    init_distanceVilles();
    InitMap();
}

void tGPS::init_Nb_villes()
{
    Nb_villes = listvilles.size();
}

void tGPS::init_listvilles()
{
    //Name x ,y
    listvilles[0] = ville {"Lyon",702,582};
    listvilles[1] = ville {"Paris",525,252};
    listvilles[2] = ville {"Bordeaux",303,669};
    listvilles[3] = ville {"Toulouse",451,820};
    listvilles[4] = ville {"Marseille",763,834};
    listvilles[5] = ville {"Nantes",235,423};
    listvilles[6] = ville {"Tours",402,411};
    listvilles[7] = ville {"Strasbourg",847,258};
    listvilles[8] = ville {"Brest",50,282};
    listvilles[9] = ville {"Nice",889,786};

}

void tGPS::init_distanceVilles()
{

    tab_distance[0] = {0,MAX_double,436.41,MAX_double,275.95,MAX_double,366.58,384.03,MAX_double,297.14}; //Lyon -> Marseille / Lyon -> Tours / Lyon -> Bordeaux / Lyon -> Strasbourg / Lyon -> Nice
    tab_distance[1] = {MAX_double,0,MAX_double,MAX_double,MAX_double,MAX_double,205.01,397.09,MAX_double,MAX_double}; //Paris -> Tours / Paris -> Strasbourg
    tab_distance[2] = {436.41,MAX_double,0,211.98,MAX_double,274.83,MAX_double,MAX_double,MAX_double,MAX_double}; //Bordeaux -> Nantes / Bordeaux -> Toulouse / Bordeaux -> Lyon
    tab_distance[3] = {MAX_double,MAX_double,211.98,0,319.74,MAX_double,MAX_double,MAX_double,MAX_double,MAX_double}; //Toulouse -> Bordeaux / Toulouse -> Marseille
    tab_distance[4] = {275.95,MAX_double,MAX_double,379.14,0,MAX_double,MAX_double,MAX_double,MAX_double,159.65}; //Marseille -> Nice / Marseille -> Lyon / Marseille -> Toulouse
    tab_distance[5] = {MAX_double,MAX_double,274.83,MAX_double,MAX_double,0,169.72,MAX_double,255,MAX_double}; //Nantes -> Brest / Nantes -> Tours / Nantes -> Bordeaux
    tab_distance[6] = {366.58,205.01,MAX_double,MAX_double,MAX_double,169.72,0,MAX_double,MAX_double,MAX_double}; //Tours -> Paris / Tours -> Nantes / Tours -> Lyon
    tab_distance[7] = {384.03,397.09,MAX_double,MAX_double,MAX_double,MAX_double,MAX_double,0,MAX_double,MAX_double}; //Strasbourg -> Paris / Strasbourg -> Lyon
    tab_distance[8] = {MAX_double,MAX_double,MAX_double,MAX_double,MAX_double,255,MAX_double,MAX_double,0,MAX_double}; //Brest -> Nantes
    tab_distance[9] = {297.14,MAX_double,MAX_double,MAX_double,159.65,MAX_double,MAX_double,MAX_double,MAX_double,0}; //Nice -> Marseille / Nice -> Lyon
}

void tGPS::InitTabDistPred(double *distance, int *predecesseur)
{
    for (short i = 0;i<Nb_villes;i++) {
        distance[i] = MAX_double;
        predecesseur[i] = MAX_int;
    }
}

void tGPS::InitMap()
{
    if(Image.ReadFromFile("../empty_map.bmp")==false)
    {
        cout << "fichier non trouver"<<endl;
        exit(0);
    }

    for (auto i = listvilles.begin();i != listvilles.end();i++) {
        for (short ligne = i->Pixel_y-10;ligne<i->Pixel_y+10;ligne++) {
            for (short colonne = i->Pixel_x-10;colonne<i->Pixel_x+10;colonne++) {
                Image(colonne,ligne)->Red = 0;
                Image(colonne,ligne)->Green = 0;
                Image(colonne,ligne)->Blue = 0;
            }
        }
    }

    Image.WriteToFile("../complete_map.bmp");
}

void tGPS::SetVilleDebut(short position)
{
    ville_debut = position;
}

void tGPS::SetVilleFin(short position)
{
    ville_fin = position;
}

void tGPS::SetDistance(double dist)
{
    distance = dist;
}

void tGPS::SetCourse(bool flag)
{
    course = flag;
}

short tGPS::GetVilleDebut()
{
    return ville_debut;
}

short tGPS::GetVilleFin()
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

        cout << "Ville de départ :" << endl;
        cin >> ville_start;

        cout << "Ville d'arrivée : "<<endl;
        cin >> ville_end ;

        /*
        printf("Course Rapide ou Course courte (O/N) : \n");
        scanf("%c",response);

        if(response == 'O')
            SetCourse(true);
        else
            SetCourse(false);
        */

        k=0;
    }

    while( (ville_start > -1 && ville_start < 10) && (ville_end > -1 && ville_end < 10) &&(ville_end == ville_start) && (response != 'O' || response != 'N') );

    SetVilleDebut(ville_start);
    SetVilleFin(ville_end);

}

void tGPS::Calculitineraire()
{
    int BF_predecesseur[Nb_villes];
    double BF_distances[Nb_villes];

    bool BF_fin = false;

    InitTabDistPred(BF_distances,BF_predecesseur);

    BF_distances[ville_debut] = 0;

    while (!BF_fin)
    {
        BF_fin = true;
        for (short i = 0;i<Nb_villes;i++)
        {
            for (short j = 0;j<Nb_villes;j++)
            {
                if(tab_distance[i][j] != MAX_double)
                {
                    if(BF_distances[i] + tab_distance[i][j] < BF_distances[j])
                    {
                        BF_distances[j] = BF_distances[i] + tab_distance[i][j];
                        BF_predecesseur[j] = i;
                        BF_fin = false;
                    }
                }
            }
        }
    }

    SetDistance(BF_distances[ville_fin]);

    InitTabRoutes(BF_predecesseur);
}




void tGPS::InitTabRoutes(int* predecesseur)
{
    short tempo = 0;
    listroutes.push_back(listvilles[ville_fin]);
    tempo = predecesseur[ville_fin];
    listroutes.push_back(listvilles[tempo]);

    do
    {
        tempo = predecesseur[tempo];
        listroutes.push_back(listvilles[tempo]);

    }while(tempo != ville_debut);
    listroutes.reverse();

}


void tGPS::AffichageRoutes()
{
    for (auto i=listroutes.begin();i != listroutes.end();i++) {
        cout << i->nom << endl;
    }
}






