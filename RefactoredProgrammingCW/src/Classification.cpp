#include "Table.h"
#include "Classification.h"



    Classification::Classification(string dataName, string learningdataName, string learningdatalabelsName, unsigned int k1)
    {
        Table d(dataName);
        Table ld(learningdataName);
        Table ldl(learningdatalabelsName);
        data = d;
        learning_data = ld;
        learning_data_labels = ldl;
        if(k1 < 1 || k1 > learning_data.getRowSize())
        {
             throw out_of_range("k is out of range");
        }
        k = k1;
    }

    Classification::Classification(string dataName, string learningdataName, string learningdatalabelsName, string correctdatalabelsName, unsigned int k1)
    {
        Table d(dataName);
        Table ld(learningdataName);
        Table ldl(learningdatalabelsName);
        Table cdl(correctdatalabelsName);
        data = d;
        learning_data = ld;
        learning_data_labels = ldl;
        correct_data_labels = cdl;
        if(k1 < 1 || k1 > learning_data.getRowSize())
        {
             throw out_of_range("k is out of range");
        }
        k = k1;
    }

    Classification::Classification(string dataName, unsigned int k1)
    {
        Table d(dataName);
        data = d;
        if(k1 < 1 || k1 > data.getRowSize())
        {
             throw out_of_range("k is out of range");
        }
        k = k1;
    }

    void Classification::addCorrectDataLabels(Table &correctDL) { correct_data_labels = correctDL; }
    void Classification::addDataTable(Table &dataTable) { data = dataTable; }
    void Classification::addLearningData(Table &learningData) { learning_data = learningData; }
    void Classification::addLearningDataLabels(Table &learningDataLabels) { learning_data_labels = learningDataLabels; }

    void Classification::addTables(Table datatable, Table learningdatatable, Table learningdatalabelstable)
    {
        data = datatable;
        learning_data = learningdatatable;
        learning_data_labels = learningdatalabelstable;
    }

    Table Classification::getDataTable()
    {
        return data;
    }

    Table Classification::getLearningDataTable()
    {
        return learning_data;
    }

    Table Classification::getLearningDataLabelsTable()
    {
        return learning_data_labels;
    }

    Table Classification::getDataLabels()
    {
        return data_labels;
    }

    Table Classification::getCorrectDataLabels()
    {
        return correct_data_labels;
    }

    vector<vector <float> > Classification::getEuclideanDist(Table &tableA, Table &tableB)
    {
        //distance.clear();

        vector<vector <float> > dis;


        for (unsigned int pos = 0; pos < tableA.getRowSize(); pos++)
        {
        vector<float> row2;
        for(unsigned int row = 0; row < tableB.getRowSize() && row < tableB.getRowSize(); row++)
        {
            float total = 0.0f;
            for(unsigned int col = 0; col < tableB.getColumnSize(); col++)
            {
                float valA = tableA.getValue(pos, col);
                float valB = tableB.getValue(row, col);
                float val2 = valA - valB;
                float val3 = pow(val2, 2);
                total += val3;
            }
            float total2 = sqrt(total);
            row2.push_back(total2);
        }
        dis.push_back(row2);
        }

        return dis;
    }


    void Classification::getMinValue(vector<vector<float> > &vec)
    {
        for(unsigned int a = 0; a < vec.size(); a++)
        {
        vector <float> row3;
        float maxValue = ((*max_element(vec[a].begin(), vec[a].end())) + 1);
        for(unsigned int i = 0; i < k; i++)
        {
            float minValue = *min_element(vec[a].begin(), vec[a].end());

            for(unsigned int x = 0; x < vec[a].size() ; x++)
            {
                if(vec[a][x] == minValue)
                {
                    float tmp = 0.0f;
                    tmp = learning_data_labels.getValue(x, 0);
                    vec[a][x] = maxValue;
                    row3.push_back(tmp);
                }
            }

        }

        minPositions.push_back(row3);
        }

        setMode(minPositions);
        }

        void Classification::setMode(vector<vector <float> > &vec)
        {

            for(unsigned int i = 0; i < vec.size(); i++)
            {
            vector <float> vtmp;
            int highestFreq = 0;
            float modeNumber = 0;


            vector<float> vecTmp = vec[i];
            for(vector <float>::iterator it = vecTmp.begin(); it!=vecTmp.end(); it++)
            {

                float point = *it;

                int counting = count(vec[i].begin(), vec[i].end(), point);



                if (counting > highestFreq)
                {
                    modeNumber = point;
                    highestFreq = counting;
                }
            }

            vtmp.push_back(modeNumber);
            modeVector.push_back(vtmp);
            }

            createDataLabelsClass(modeVector);

        }

        unsigned int Classification::getK()
        {
            return k;
        }

        void Classification::setK(unsigned int l)
        {
            if(l < 1 || l > data.getRowSize())
            {
                throw out_of_range("k is out of range");
            }
            k = l;
        }



    float Classification::getAccuracy(Table &tableA, Table &tableB)
    {
        float accuracy = 0.0f;
        for(unsigned int i = 0; i < tableA.getRowSize(); i++)
        {
            float posTmp = tableA.getValue(i, 0);
            float corTmp = tableB.getValue(i, 0);

            if(posTmp == corTmp)
            {
                accuracy++;
            }
            posTmp = 0.0f;
            corTmp = 0.0f;
        }
        return ((accuracy) / (tableA.getRowSize()) * 100);
    }

    float Classification::getAccuracy()
    {
        return getAccuracy(data_labels, correct_data_labels);
    }



    void Classification::createDataLabelsClass(vector<vector <float> > &vec)
    {
        Table tab;
        tab.addDataTable(vec);
        data_labels = tab;
    }

    vector <vector <float> > Classification::getManhattanDist(Table &tableA, Table &tableB)
    {

        vector<vector <float> > dis;


        for (unsigned int pos = 0; pos < tableA.getRowSize(); pos++)
        {
        vector<float> row2;
        for(unsigned int row = 0; row < tableB.getRowSize() && row < tableB.getRowSize(); row++)
        {
            float total = 0.0f;
            for(unsigned int col = 0; col < tableB.getColumnSize(); col++)
            {
                float valA = tableA.getValue(pos, col);
                float valB = tableB.getValue(row, col);
                float val2 = valA - valB;
                float val3 = fabs(val2);
                total += val3;
            }
            float total2 = sqrt(total);
            row2.push_back(total2);
        }
        dis.push_back(row2);
        }

        return dis;
    }



    void Classification::getEuclideanDist()
    {
        vector <vector <float> > vec = getEuclideanDist(data, learning_data);
        getMinValue(vec);
    }

    void Classification::getManhattanDist()
    {
        vector <vector <float> > vec = getManhattanDist(data, learning_data);
        getMinValue(vec);
    }

    void Classification::standardiseAllData()
    {
        data.standardizeData();
        learning_data.standardizeData();
        learning_data_labels.standardizeData();
    }


    void Classification::calculateDistance(vector<vector <float> > (*distanceMethod)(Table&, Table&))
    {
        distance.clear();
        Table tableA = data;
        Table tableB = learning_data;
        vector<vector <float> >distancex = distanceMethod(tableA, tableB);


        getMinValue(distancex);



    }






    int main()
    {
        try
        {
        Classification classif("data.csv", "learning_data.csv", "learning_data_labels.csv", "correct_data_labels.csv", 142);
        vector <vector <float> > (*pDistanceType)(Table&, Table&) = Classification::getEuclideanDist;
        classif.calculateDistance(pDistanceType);
        cout << "Accuracy Percentage: " << classif.getAccuracy();
        }
        catch(out_of_range e)
        {
            cout << e.what();
        }
//
//        float myFloat[] = {1.5f,10.1f,0.4f,3.2f};
//        vector <float> myVec (myFloat, myFloat + sizeof(myFloat) / sizeof(float));
    }

