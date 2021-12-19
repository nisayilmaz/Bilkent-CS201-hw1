//Nisa Yılmaz 22001849

#ifndef CHEMICAL_H
#define CHEMICAL_H


class Chemical{
    public:
        Chemical(int, int);
        Chemical();
        int getId();
        int getType();
        void setID(int);
        void setType(int);

    private:
        int chemicalId;
        int chemicalType; //0 for retardant, 1 for combustive
};

#endif // CHEMICAL_H
