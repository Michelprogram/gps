#ifndef TGPS_H
#define TGPS_H
#include <string>
#include <array>
#include <list>
#include "EasyBMP.h"

using namespace std;

struct ville
{
    string nom;
    short Pixel_x;
    short Pixel_y;
};

class tGPS
{
private:
    short ville_debut,ville_fin; //Position dans listvilles
    int Nb_villes = 0;
    double distance = 0;

    BMP Image;

    const double MAX_double = 10000000000;
    const int MAX_int = 1000000000;

    bool course = false;

    list<ville>listroutes;
    array<array<double,10>,10> tab_distance;
    array<ville,10> listvilles;

    void init_listvilles();
    void init_distanceVilles();
    void init_Nb_villes();
    void InitMap();

    void InitTabDistPred(double *,int *);
    void InitTabRoutes(int*);
    void AffichageRoutes();

public:
    tGPS();

    void SetVilleDebut(short);
    void SetVilleFin(short);
    void SetCourse(bool);
    void SetDistance(double);

    short GetVilleDebut();
    short GetVilleFin();
    bool GetCourse();

    void Menu();
    void Calculitineraire();


};

#endif // TGPS_H
