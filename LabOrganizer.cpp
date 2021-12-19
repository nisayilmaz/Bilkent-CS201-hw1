//Nisa Yılmaz 22001849

#include "LabOrganizer.h"
#include <iostream>
using namespace std;

LabOrganizer::LabOrganizer() {
    numberOfCabinets = 0;
    chemicalNumber = 0;
    cabinets = NULL;
    chemicalIds = NULL;
    numbers = new char[9];
    letters = new char[9];
    for (int i = 0; i < 9; i++) {
        letters[i] = 65 + i;
        numbers[i] = 49 + i;
    }
}

LabOrganizer::~LabOrganizer() {
    if(numberOfCabinets != 0) {
        for(int i = 0; i < numberOfCabinets; i++) {
        delete cabinets[i];
        }
        delete [] cabinets;
     
    }
    delete [] chemicalIds;
    delete [] numbers;
    delete []  letters;
    
}

void LabOrganizer::addCabinet(int id, int rows, int columns) {
    //Check bounds
    if(rows > 9 || columns > 9) {
        cout << "Cannot add the cabinet: dimensions are out of bounds" << endl;
    }
    else {
        bool isUnique = true;
        for(int i = 0; i < numberOfCabinets; i++) {
            if(cabinets[i]->getId() == id) {
                isUnique = false;
                cout <<"Cannot add the cabinet: ID " << id << " is already in the system"  << endl;
            }
        }
        if(isUnique) {
            if(cabinets == NULL) {
                cabinets = new Cabinet* [numberOfCabinets + 1];

            }
            else {
                Cabinet** tempArr = new Cabinet*[numberOfCabinets+1];
                for(int i = 0; i < numberOfCabinets; i++) {
                    tempArr[i] = cabinets[i];
                }
                delete [] cabinets;
                cabinets = tempArr;

            }
            cabinets[numberOfCabinets] = new Cabinet(id,rows,columns);
            numberOfCabinets++;
            cout << "Added a cabinet: ID " << id << " and dimensions " << rows << " to " << columns << endl; 
        }
    }
}

void LabOrganizer::removeCabinet(int id) {
    int index = getCabinet(id);
    if(index < 0) {
        cout << "Cabinet " << id << " does not  exist in the system" << endl;
    }
    else {
        int cabIndex = getCabinet(id);
        for (int i = 0; i < cabinets[cabIndex]->getRow(); i++) {
            for (int j = 0; j < cabinets[cabIndex]->getColumn(); j++) {
                if(cabinets[cabIndex]->getChemicalId(i,j) != -1) {
                    cout << "Chemical " << cabinets[cabIndex]->getChemicalId(i,j) <<  " removed from cabinet " << id << endl;
                    cabinets[cabIndex]->removeChemical(i, j);
                    cabinets[cabIndex]->decreaseChemicalNumber();
                }
            }
        }
        Cabinet** tempArr = new Cabinet* [numberOfCabinets-1];
        int j = 0;
        for(int i = 0; i < numberOfCabinets; i++) {
            if(i != index) {
                tempArr[j] = cabinets[i];
                j++;
            }
            else{
                delete cabinets[i];
            }
        }
        delete [] cabinets;
        cabinets = tempArr;
        numberOfCabinets--;
        cout << "Cabinet " << id << " has been removed" << endl; 
        //cout << index << endl;
    }
}

void LabOrganizer::listCabinets() {
    if (numberOfCabinets > 0) {
        cout << "List of all cabinets:" << endl;
        for(int i = 0; i < numberOfCabinets; i++) {
            cout << "ID: " << cabinets[i]->getId() << ", Dim: " << cabinets[i]->getRow() << "x" << cabinets[i]->getColumn() << ", Number of empty slots: " << cabinets[i]->getEmptyPlaces() << endl;
        }
    }
    
}

int LabOrganizer::getCabinet(int id) {
    bool isPresent = false;
    int index;
    for(int i = 0; i < numberOfCabinets; i++) {
        if(cabinets[i]->getId() == id) {
            isPresent = true;
            index = i;
        }
    }

    if(isPresent) {
        return index;
    }
    else {
        return -1;
    }
}

void LabOrganizer::cabinetContents(int id) {
    int cabinetIndex = getCabinet(id);
    cout << endl;
    if(getCabinet(id) < 0) {
        cout << "Cabinet " << id << " is not in the system" << endl;
    }
    else {
        cout << "ID: " << id << ", " << cabinets[getCabinet(id)]->getRow() << "x" << cabinets[cabinetIndex]->getColumn() << ", empty: " << cabinets[cabinetIndex]->getEmptyPlaces() << ". Chemicals: ";
        if(cabinets[cabinetIndex]->getChemicalNumber() == 1) {
            cout << "none" << endl;
        }
        else {
            cabinets[cabinetIndex]->printChemicals();
            cout << endl;
        }
        
        for(int i = 0; i <= cabinets[cabinetIndex]->getRow(); i++) {
            if(i!= 0) {
                cout << " "<< letters[i - 1] << " ";
            } 
            for(int j = 0; j <= cabinets[cabinetIndex]->getColumn(); j++) {
                if (i == 0 && j == 0){
                    cout << "   ";
                }
                else if(i == 0 && j!= 0) {
                    cout << " " << j << " ";
                }
                else if (j > 0) {
                    int type = cabinets[cabinetIndex]->getChemicalType(i-1, j-1);
                    
                    if(type == -1) {
                        cout  << " + ";
                    }
                    else if (type == 0) {
                        cout << " r ";
                    }
                    else {
                        cout << " c ";
                    }
                } 

            }
            cout << endl;
        }
    }

}

void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int ChemId) {
    int cab =  getCabinet(cabinetId);
    //Converst the location from string to int
    int rowIndex;
    for(int i = 0; i < 9; i++) {
        if(location.at(0) == letters[i]){
            rowIndex = i;
            break;
        }
    }
    int columnIndex;
    for(int i = 0; i < 9; i++) {
        if(location.at(1) == numbers[i]){
            columnIndex = i;
            break;
        }
    }
    //Convert type from string to int
    int type;
    if(chemType == "combustive") {
        type = 1;
    }
    if(chemType == "retardant") {
        type = 0;
    }
    int r = rowIndex;
    int c = columnIndex;
    int no;

    //Check if the cabinet exists
    if(cab < 0) {
        cout << "Cabinet " << cabinetId <<  " does not exist in the system" << endl;
    }
    else {
        //Check if the location is occupied
        if(cabinets[cab]->getChemicalType(rowIndex,columnIndex) != -1) {
            cout << "Location "<< location <<  " in cabinet " << cabinetId << " is already occupied. Nearest possible locaitons for this chemical:";
            cabinets[cab]->recommendPlace(type,r,c,1); 
            cout << endl;         
        }
        else {
            //Check if chemId is unique
            bool isUnique = true;
            for(int i = 0; i < chemicalNumber; i++) {
                if(chemicalIds[i] == ChemId) {
                    isUnique = false;
                }    
            }

            if (isUnique) {
                string typeStr;
                if(type == 1){typeStr = "Combustive";}
                else if(type == 0) {typeStr = "Retardant";}

                if(type == 1) { 
                    if(cabinets[getCabinet(cabinetId)]->isCombustivePlaceable(rowIndex, columnIndex)) {
                        if(chemicalIds == NULL) {
                            chemicalIds = new int [1];
                        }
                        else {
                            int* tempArr = new int[chemicalNumber + 1];
                            for(int i = 0; i < chemicalNumber; i++) {
                                tempArr[i] = chemicalIds[i];
                            }
                            delete [] chemicalIds;
                            chemicalIds = tempArr;
                        }
                    chemicalIds[chemicalNumber] = ChemId;
                    cabinets[cab]->placeChemical(rowIndex, columnIndex,ChemId,type); 
                    chemicalNumber++;
                    cout << typeStr << " chemical with ID " << ChemId << " has been placed at location " << location << " in cabinet " << cabinetId << endl;
                    
                    }
                    else {
                        cout << "Location " << location << " in cabinet " << cabinetId << " is not suitable for a combustive chemical. Nearest possible locaitons for this chemical:";
                        cabinets[cab]->recommendPlace(type,r,c,1);
                        cout << endl;
                    }
                }
                    
                else {
            
                    if(chemicalIds == NULL) {
                        chemicalIds = new int [1];
                    }
                    else {
                        int* tempArr = new int[chemicalNumber + 1];
                        for(int i = 0; i < chemicalNumber; i++) {
                            tempArr[i] = chemicalIds[i];
                        }
                        delete [] chemicalIds;
                        chemicalIds = tempArr;
                    }
                    chemicalIds[chemicalNumber] = ChemId;
                    cabinets[cab]->placeChemical(rowIndex, columnIndex,ChemId,type); 
                    chemicalNumber++;
                    cout << typeStr << " chemical with ID " << ChemId << " has been placed at location " << location << " in cabinet " << cabinetId << endl;
                }
            }
            
            else {
                cout << "Chemical with id " << ChemId << " already exists in the system" << endl;
            }
            
        }
           
    }

}

void LabOrganizer::findChemical(int chemId) {
    int rowIndex, columnIndex, cabinetId;
    bool found = false;
    int m = 0;
    for(int i = 0; i < numberOfCabinets; i++) {
        m++;
        cabinets[i]->findChemical(chemId, rowIndex, columnIndex, cabinetId);
        if (cabinetId != -1){
            cout  << "Chemical " << chemId << " is at location " << letters[rowIndex] << numbers[columnIndex] << " in cabinet " << cabinetId << endl;
            found = true;
        }     
    }
    if(!found && m > 0) {
        cout << "Chemical " << chemId << " is not in the system"  << endl;
    } 
}

void LabOrganizer::removeChemical(int thisId) {
    int rowIndex, columnIndex, cabinetId;
    int m = 0;
    bool found = false;
    for(int i = 0; i < numberOfCabinets; i++) {
        m++;
        cabinets[i]->findChemical(thisId, rowIndex, columnIndex, cabinetId);
        if (cabinetId != -1){
            cabinets[getCabinet(cabinetId)]->removeChemical(rowIndex,columnIndex);
            cout << "Chemical " << thisId <<  " removed from cabinet " << cabinetId << endl;
            found = true;
            break;
        }       
    }
    
    if(!found && m > 0) {
        cout << "Chemical " << thisId << " is not in the system" << endl;
    } 

}





