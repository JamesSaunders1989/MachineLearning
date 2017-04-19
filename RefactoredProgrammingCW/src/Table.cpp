#include "Table.h"


    Table::Table(){}
    Table::Table(string filen){Table::populateTable(filen);}
    Table::~Table(){}




    vector <vector<float> > Table::getData(){return data;}

    float Table::getValue(unsigned int row, unsigned int col){
        if(row < 0 || row > data.size() - 1 || col < 0 || col > data[0].size() - 1)
        {throw out_of_range("cell out of range");}
            return data[row][col]; }
    void Table::setCellValue(unsigned int row, unsigned int col, float newVal){
        if(row < 0 || row > data.size()-1 || col < 0 || col > data[0].size()-1)
        {throw out_of_range("cell out of range");}
        data[row][col] = newVal; }
    unsigned int Table::getRowSize(){ return data.size(); }
    unsigned int Table::getColumnSize(){ return data[1].size(); }
    void Table::removeRow(unsigned int row){
        if(row < 0 || row > data.size() - 1)
        {throw out_of_range("row out of range");}
        data.erase(data.begin() + row); }
    void Table::addDataTable(vector<vector <float> > &vec) { data = vec; }

    void Table::populateTable(string fileName)
    {
    ifstream file( fileName.c_str() );
    if(file.fail())
    {
        throw out_of_range("csv import failed");
    }
    string str;
    int countingy = 0;
    while (getline(file, str))
    {
        countingy++;
        vector <float> row;
        istringstream iss(str);

        while(getline(iss, str, ','))
        {
            float fieldvalue = 0.0f;
            istringstream(str) >> fieldvalue;
            row.push_back(fieldvalue);
        }
        data.push_back(row);
    }
    }

    void Table::addColumn(vector<float> &vec)
    {
        for(unsigned int i = 0; i < getRowSize(); i++)
        {
            data[i].push_back(vec[i]);
        }
    }

    void Table::addRow(vector<float> &vec)
    {
        data.push_back(vec);
    }

    unsigned int Table::getTotalCells()
    {
    int size = 0;
    for (vector<vector<float> >::iterator it = data.begin(); it != data.end(); ++it)
    size += it->size();
    return size;
    }

    string Table::getAllValues()
    {
        string tmps = " ";
        for(unsigned int i = 0; i < getRowSize(); i++)
        {
            for(unsigned int ii = 0; ii < getColumnSize(); ii++)
            {
            float f = data[i][ii];
            tmps += "[" + floatToString(i) + "]" + floatToString(f) + ", ";
            }
            tmps += "\n";
        }
        return tmps;
    }


    float Table::stringToFloat(string str2)
    {
       stringstream stream;
       float flotmp = 0.0f;
       stream << str2;
       stream >> flotmp;
       return flotmp;
    }

    string Table::floatToString(float float2)
    {
        stringstream stream;
        string str2 = " ";
        stream << float2;
        stream >> str2;
        return str2;
    }

    float Table::getAverage(vector<float> &vec)
    {
     float total;
     for(vector<float>::iterator item =vec.begin(); item!=vec.end();item++)
     {
     total += *item;
     }
     return total / vec.size();
    }


    float Table::getRowAverage(unsigned int row)
    {
    if(row < 0 || row > data.size() - 1)
        {throw out_of_range("row out of range");}
     vector<float> aver;
     for(unsigned int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[row][i]);
     }
     return getAverage(aver);
    }





    float Table::getColumnAverage(unsigned int col)
    {
        if(col < 0 || col > data[0].size() - 1)
        {throw out_of_range("column out of range");}
     vector<float> aver;
     for(unsigned int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[i][col]);
     }
     return getAverage(aver);
    }

    float Table::getStandardDev(unsigned int col)
    {
        if(col < 0 || col > data[0].size() -1)
        {throw out_of_range("column out of range");}
     vector<float> aver;
     for(unsigned int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[i][col]);
     }
     return StandardDev(aver);
    }

    float Table::StandardDev(vector<float> &vec)
    {
     float total = 0;
     float result = 0;
     float resultsum = 0;

     for(vector<float>::iterator item =vec.begin(); item!=vec.end();item++)
     {
     total += *item;
     }
     float average = ((float)total / vec.size());

     for (unsigned int i = 0; i < vec.size(); i++)
     {
         float tmp = vec[i] - average;
         result = pow(tmp, 2);
         resultsum += result;
     }
     float ans = 1.0 / (vec.size() - 1.0);
     float answer = sqrt((ans * resultsum));

     return answer;
}

    ostream &operator<<(ostream &stream, Table obj)
    {
        int row = 0;
        int col = 0;
        //vector<vector<float> > Data = obj.getData();
        for(vector<vector<float> >::iterator itemrow = obj.data.begin(); itemrow!=obj.data.end(); itemrow++, row++)
        {
            stream << "ROW[" << row << "]: ";
            for(vector<float>::iterator itemcol = obj.data[row].begin(); itemcol!=obj.data[row].end(); itemcol++, col++)
            {
                stream << obj.getValue(row, col) << ", ";
            }
            stream << "\n";
            col = 0;
        }
        return stream;
    }

    void Table::removeColumn(unsigned int col)
    {
        if(col < 0 || col > data[0].size() - 1)
        if(col < 0 || col > data[0].size() - 1)
        {throw out_of_range("column out of range");}
        for (unsigned int i = 0; i < getRowSize(); i++)
        {
        data[i].erase(data[i].begin() + col);
        }
    }

    void Table::standardizeData()
    {
        vector <float> valuestmp;
        vector <float> standarddevtmp;
        for(unsigned int i = 0; i < getColumnSize(); i++)
        {
            valuestmp.push_back(getColumnAverage(i));
            standarddevtmp.push_back(getStandardDev(i));
        }
        for(unsigned int row = 0; row < getRowSize(); row++)
        {
            for(unsigned int col = 0; col < getColumnSize(); col++)
            {
            float value = data[row][col];
            float colAverage = valuestmp[col];
            float exp = (value - colAverage);
            float base = standarddevtmp[col];
            float result = (exp / base);
            data[row][col] = result;
            }
        }
    }



