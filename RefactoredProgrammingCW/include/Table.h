#ifndef TABLE_H
#define TABLE_H


#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<cmath>
#include<stdexcept>
using namespace std;


class Table
{
    private:
    vector <vector <float> > data;

    public:
        Table();
        Table(string filename);
        virtual ~Table();




public:




    vector <vector<float> > getData();

    public:
    float getValue(unsigned int row, unsigned int col);
    void setCellValue(unsigned int row, unsigned int col, float newVal);
    unsigned int getRowSize();
    unsigned int getColumnSize();
    void removeRow(unsigned int row);

    void populateTable(string fileName);

    unsigned int getTotalCells();

    string getAllValues();

    void addColumn(vector<float> &vec);

    void addRow(vector<float> &vec);

    float stringToFloat(string str2);

    string floatToString(float float2);

    float getAverage(vector<float> &vec);

    void addDataTable(vector <vector <float> > &vec);

    float getRowAverage(unsigned int row);

    float getColumnAverage(unsigned int col);

    float getStandardDev(unsigned int col);

    float StandardDev(vector<float> &vec);

    friend ostream &operator<<(ostream &stream, Table obj);
    void removeColumn(unsigned int col);

    void standardizeData();

    protected:

    private:
};




#endif // TABLE_H
