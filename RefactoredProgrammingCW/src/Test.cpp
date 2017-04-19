#include "Test.h"
#include "Table.h"

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
    Table obj();
    obj.populateTable("data.csv");
}



