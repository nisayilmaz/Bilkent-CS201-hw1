//Nisa Yılmaz 22001849

#include "Chemical.h"
#include <iostream>
using namespace std;

Chemical::Chemical(int id, int type){
    chemicalId = id;
    chemicalType = type;

}


Chemical::Chemical(){
    chemicalId = -1;
    chemicalType = -1;

}

int Chemical::getId() {
    return chemicalId;
}

int Chemical::getType() {
    return chemicalType;
}

void Chemical::setID(int givenId) {
    chemicalId = givenId;
}

void Chemical::setType(int givenType) {
    chemicalType=givenType;
}





