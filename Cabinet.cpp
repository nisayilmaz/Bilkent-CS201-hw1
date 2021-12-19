//Nisa Yılmaz 220018

#include "Cabinet.h"

Cabinet::Cabinet(const int cabinetId, const int cabinetRow,const int cabinetColumn) {
    id = cabinetId;
    row = cabinetRow;
    column = cabinetColumn;
    cabinet = new Chemical* [cabinetRow];
    for (int i = 0; i < cabinetRow; i++){
        cabinet[i] = new Chemical[cabinetColumn];
    }
    numbers = new string[9];
    letters = new string[9];
    for (int i = 0; i < 9; i++) {
        letters[i] = 65 + i;
        numbers[i] = 49 + i;
    }
    
    numberOfChemicals = 0;
    places = row * column;
    emptyPlaces = places;
    
    
}

Cabinet::Cabinet() {
    id = -1;
    row = 0;
    column = 0;

}

Cabinet::~Cabinet() {
    if (id >= 0){
        for(int i = 0; i < row; i++) {
            delete [] cabinet[i];
        }
        delete [] cabinet;
    }  
    delete [] numbers;
    delete []  letters;
}

int Cabinet::getId(){
    return id;
}

int Cabinet::getRow() {
    return row;
}

int Cabinet::getColumn() {
    return column;
}

int Cabinet::getEmptyPlaces() {
    return places - numberOfChemicals;
}

int Cabinet::getChemicalNumber() {
    return numberOfChemicals;

}

void Cabinet::placeChemical(const int row, const int column, const int id,const int type) {

    cabinet[row][column] = Chemical(id,type);
    numberOfChemicals++;
   
}

void Cabinet::decreaseChemicalNumber() {
    numberOfChemicals--;
}

int Cabinet::getChemicalType(const int row, const int column){
    return cabinet[row][column].getType();

}

int Cabinet::getChemicalId(const int row, const int column){
    return cabinet[row][column].getId();

}

void Cabinet::findChemical(const int chemId, int& rowIndex, int& columnIndex, int& cabinetId) {
    rowIndex = -1;
    columnIndex = -1;
    cabinetId = -1;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            if (cabinet[i][j].getId() == chemId){
                rowIndex = i;
                columnIndex = j;
                cabinetId = id;
            }   
        }
    }
}

void Cabinet::printChemicals() {
    int m = numberOfChemicals;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            if (cabinet[i][j].getId() != -1){
                cout << letters[i] << numbers[j] << ": " << cabinet[i][j].getId();
                if(m > 1){
                    cout << ", ";
                }
                m--;
            }   
        }
    }
    
}

void Cabinet::removeChemical(const int row,const int column) {
    cabinet[row][column].setID(-1);
    cabinet[row][column].setType(-1);
}

bool Cabinet::isCombustivePlaceable(const int rowIndex, const int columnIndex) {
    bool b = true;
    for(int i = rowIndex - 1; i <= rowIndex + 1; i++) {
        for(int j = columnIndex - 1; j <= columnIndex + 1; j++) {
            if (!(i ==rowIndex && j == columnIndex)){
                if( i >= 0 && i < row && j < column && j >= 0) {
                    if (cabinet[i][j].getType() == 1) {
                        b = false;
                    }
                }
            }     
        }
    }
   return b;
}

void Cabinet::recommendPlace(const int chemType, int rowIndex, int columnIndex, const int distance) {
    int no = 0;
    for(int i = rowIndex - distance; i <= rowIndex + distance; i++) {
        for(int j = columnIndex - distance; j <= columnIndex + distance; j++) {
            if (!(i ==rowIndex && j == columnIndex)){
                if( i >= 0 && i < row && j < column && j >= 0) {
                    if(chemType==0) {
                        if (cabinet[i][j].getType() == -1) {
                            if(no == 0) {
                                cout << " ";
                            }
                            else {
                                cout << ",";
                            }
                            cout <<letters[i] << numbers[j];
                            no++;
                        }
                    }
                    else if(chemType == 1) {
                        if (cabinet[i][j].getType() == -1 && isCombustivePlaceable(i,j)) {
                            if(no == 0) {
                                cout << " ";
                            }
                            else {
                                cout << ",";
                            }
                            cout <<letters[i] << numbers[j];
                            no++;
                        
                        }
                    }
                  
                }
            }     
        }
    }
    if(no == 0) {
        if(distance >= row && distance >= column) {
            cout << "No places are available" << endl;
            return;
        }
        else {
            recommendPlace(chemType, rowIndex, columnIndex, distance + 1);
        }
    }
}


