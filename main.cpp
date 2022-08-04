#include <iostream>
#include "AVLTree.h"
#include <vector>
#include <string>
#include <fstream>
#include "include/rapidjson/document.h"
#include "DocumentParser.h"
#include "porter2_stemmer.h"
#include "EngineDriver.h"


using namespace std;
int main(int argc, char** argv)
{

            // DRIVER CLASS
    EngineDriver driver =  EngineDriver(argv);
            // PROMPT USER
    driver.displayMenu(argv);

    while(driver.requestedAction == 'S')
    {
        driver.displayMenu(argv);
    }










    return 0;
}
