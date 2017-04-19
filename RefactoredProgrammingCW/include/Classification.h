#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H


#include <algorithm>
#include <vector>
#include <stdexcept>
#include <exception>



class Classification
{
    Table data;
    Table learning_data;
    Table learning_data_labels;
    Table correct_data_labels;
    Table data_labels;
    unsigned int k;
    vector <vector <float> > distance;
    vector <vector <float> > modeVector;
    vector <vector <float> > minPositions;

    vector <float > Vtmp;

    public:

    Classification(string dataName, string learningdataName, string learningdatalabelsName, unsigned int k1);

    Classification(string dataName, string learningdataName, string learningdatalabelsName, string correctdatalabelsName, unsigned int k1);

    Classification(string dataName, unsigned int k1);


    void addCorrectDataLabels(Table &correctDL);
    void addDataTable(Table &dataTable);
    void addLearningData(Table &learningData);
    void addLearningDataLabels(Table &learningDataLabels);

    void addTables(Table datatable, Table learningdatatable, Table learningdatalabelstable);

    Table getDataTable();

    Table getLearningDataTable();

    Table getLearningDataLabelsTable();

    Table getDataLabels();

    Table getCorrectDataLabels();

    static vector<vector <float> > getEuclideanDist(Table &tableA, Table &tableB);

    void getMinValue(vector<vector<float> > &vec);

    void setMode(vector<vector <float> > &vec);

    unsigned int getK();

    void setK(unsigned int l);

    float getAccuracy(Table &tableA, Table &tableB);

    float getAccuracy();

    void createDataLabelsClass(vector<vector <float> > &vec);

    static vector<vector <float> > getManhattanDist(Table &tableA, Table &tableB);

    void getEuclideanDist();


    void getManhattanDist();

    void standardiseAllData();

    void calculateDistance(vector<vector <float> > (*distanceMethod)(Table&, Table&));

//    void calcDistance(float first, float second, float (*functocall)(float, float));


};




#endif // CLASSIFICATION_H_INCLUDED
