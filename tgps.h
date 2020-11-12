#ifndef TGPS_H
#define TGPS_H
#include <string>
#include <array>

using namespace std;

struct ville
{
    string nom;
    double latitude;
    double longitude;
};

class tGPS
{
private:
    string ville_debut,ville_fin;
    bool course = false;
    array<ville,10> listvilles;

    void init_listvilles();

public:
    tGPS();

    void SetVilleDebut(short);
    void SetVilleFin(short);
    void SetCourse(bool);

    string GetVilleDebut();
    string GetVilleFin();
    bool GetCourse();

    void Menu();
};

#endif // TGPS_H
