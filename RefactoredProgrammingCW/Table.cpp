#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<cmath>

using namespace std;

class Table
{

    float getStandardise();

    vector <vector <float> > data;
    vector <vector<float> > getData(){return data;}

    public:
    float getValue(int x, int y){ return data[x][y]; }
    void setCellValue(int x, int y, float newVal){ data[x][y] = newVal; }
    int getRowSize(){ return data.size(); }
    int getColumnSize(){ return data[1].size(); }
    void removeRow(int r){ data.erase(data.begin() + r); }

    int valueCount;




    Table(string fileName, int rows, int columns)
    {
        populateTable(fileName);
    }




    void populateTable(string fileName)
    {
    ifstream file( fileName.c_str() );

    string str;
    int countingy = 0;
    int countingx = 0;
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

    int getInfo()
    {
    int size = 0;
    for (vector<vector<float> >::iterator it = data.begin(); it != data.end(); ++it)
    size += it->size();
    return size;
    }

    string getAllValues()
    {
        string tmps = " ";
        for(int i = 0; i < getRowSize(); i++)
        {
            for(int ii = 0; ii < getColumnSize(); ii++)
            {
            float f = data[i][ii];
            tmps += floatToString(f) + ", ";
            }
            tmps += "\n";
        }
        return tmps;
    }


    float stringToFloat(string str2)
    {
       stringstream stream;
       float flotmp = 0.0f;
       stream << str2;
       stream >> flotmp;
       return flotmp;
    }

    string floatToString(float float2)
    {
        stringstream stream;
        string str2 = " ";
        stream << float2;
        stream >> str2;
        return str2;
    }

    float average(vector<float> &vec)
    {
     float total;
     for(vector<float>::iterator item =vec.begin(); item!=vec.end();item++)
     {
     total += *item;
     //cout << "t: " << total << "i: " << *item << "\n";
     }
     return total / vec.size();
}


    float getRowAverage(int row)
    {
     vector<float> aver;
     for(int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[row][i]);
     }
     return average(aver);
    }



    float getColumnAverage(int col)
    {
     vector<float> aver;
     for(int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[i][col]);
     }
     return average(aver);
    }

    float getStandardDev(int col)
    {
     vector<float> aver;
     for(int i = 0; i < getRowSize(); i++)
     {
     aver.push_back(data[i][col]);
     }
     return StandardDev(aver);
    }

    float StandardDev(vector<float> &vec)
    {
     float total = 0;
     float result = 0;
     float resultsum = 0;

     for(vector<float>::iterator item =vec.begin(); item!=vec.end();item++)
     {
     total += *item;
     }
     float average = ((float)total / vec.size());

     for (int i = 0; i < vec.size(); i++)
     {
         float tmp = vec[i] - average;
         result = pow(tmp, 2);
         resultsum += result;
     }
     float ans = 1.0 / (vec.size() - 1.0);
     float answer = sqrt((ans * resultsum));

     return answer;
}

    friend ostream &operator<<(ostream &stream, Table obj)
    {
        int row = 0;
        int col = 0;
        vector<vector<float> > Data = obj.getData();
        for(vector<vector<float> >::iterator itemrow = Data.begin(); itemrow!=Data.end(); itemrow++, row++)
        {
            stream << "ROW[" << row << "]: ";
            for(vector<float>::iterator itemcol = Data[row].begin(); itemcol!=Data[row].end(); itemcol++, col++)
            {
                stream << obj.getValue(row, col) << ", ";
            }
            stream << "\n";
            col = 0;
        }
        return stream;
    }

    void removeColumn(int c)
    {
        for (int i = 0; i < getRowSize(); i++)
        {
        data[i].erase(data[i].begin() + c);
        }
    }

    void stdData()
    {
        for(int row = 0; row < getRowSize(); row++)
        {
            for(int col = 0; col < getColumnSize(); col++)
            {
            float value = data[row][col];
            float colAverage = getColumnAverage(col);
            float exp = (value - colAverage);
            float base = getStandardDev(col);
            float result = exp / base;
            data[row][col] = result;
            }
        }
    }



};

int main()
{
cout << "creating objects \n";
Table tb1("data.csv", 0, 10);
cout << "populating table \n";
//tb1.populateTable();
//cout << tb1.getAllValues();
//cout << "geting value " << tb1.getValue(2, 5) << "\n";
//tb1.setCellValue(2,5,3.14);
//cout << "getting new Value " << tb1.getValue(2, 5) << "\n";
//cout << "Row Size: " << tb1.getRowSize() << "\n";
//cout << "Column Size: " << tb1.getColumnSize() << "\n";
//cout << "info: " << tb1.getInfo();
//cout << "\n";
//cout << "get row average: " << tb1.getRowAverage(5) << "\n";
//cout << "get row average: " << tb1.getRowAverage(8) << "\n";
//cout << "get column average: " << tb1.getColumnAverage(3) << "\n";
//cout << "get standard dev: " << tb1.getStandardDev(2) << "\n";
//cout << tb1;
//cout << "before remove row: " << tb1.getRowSize() << "\n";
//tb1.removeRow(4);
//cout << "after remove row: " << tb1.getRowSize() << "\n";

//cout << "before remove col 0 : " << tb1.getColumnSize() << "\n";
//tb1.removeColumn(0);

//cout << "before remove col 1 : " << tb1.getColumnSize() << "\n";
//tb1.removeColumn(1);
//tb1.removeColumn(0);
//tb1.removeColumn(0);
//tb1.removeColumn(0);
//tb1.removeColumn(0);
//tb1.removeColumn(0);
//cout << "after remove col 1 : " << tb1.getColumnSize() << "\n";
//cout << tb1;
//cout << "after remove col 1 : " << tb1.getColumnSize() << "\n";

//cout << "info: " << tb1.getInfo() << "\n";
cout << tb1;
cout << "\n \n";
tb1.stdData();
cout << tb1;

//float test = tb1.stringToFloat("3.141");
//float test2 = tb1.stringToFloat("1.141");

//cout << "testing string to float: " << test + test2 << "\n";
//tb1.getValues();
//tb1.populateTable();

}
