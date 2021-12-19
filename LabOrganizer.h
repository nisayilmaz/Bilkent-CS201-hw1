//Nisa Yılmaz 22001849

#ifndef LABORGANIZER_H
#define LABORGANIZER_H
#include <iostream>
#include "Cabinet.h"
using namespace std;
class LabOrganizer{
private:
    Cabinet **cabinets;
    int *chemicalIds;
    int numberOfCabinets;
    int chemicalNumber;
    char *letters;
    char *numbers; 

    

public:
    LabOrganizer();
    ~LabOrganizer();
    void addCabinet(int id, int rows, int columns);
    void removeCabinet(int id);
    void listCabinets();
    void cabinetContents(int id);
    void placeChemical(int cabinetId, string location, string chemType, int chemID);
    void findChemical(int id);
    void removeChemical(int id);
    int getCabinet(int);

};

#endif // LABORGANIZER_H