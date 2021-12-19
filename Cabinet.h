//Nisa Yılmaz 22001849

#ifndef CABINET_H
#define CABINET_H
#include "Chemical.h"
#include <iostream>
using namespace std;

class Cabinet {
    public:
        Cabinet(int, int, int); //id,row,column
        Cabinet();
        ~Cabinet();
        int getId();
        int getRow();
        int getColumn();
        int getEmptyPlaces();
        int getChemicalType(int, int);
        int getChemicalNumber();
        int getChemicalId(int, int);
        void printChemicals();
        void placeChemical(int,int,int,int);
        void removeChemical(int,int);
        void findChemical(int, int&, int&, int&);
        void recommendPlace(int,int,int,int);
        void decreaseChemicalNumber();
        bool isCombustivePlaceable(int, int);




    private:
        int row;
        int column;
        int id;
        int emptyPlaces;
        int places;
        int numberOfChemicals;
        Chemical **cabinet;
        string *recommendedPlaces;
        string *letters;
        string *numbers; 

};

#endif // CABINET_H