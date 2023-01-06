#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "DataStorage.h"

using namespace std;

int main(int argc, char* argv[])
{
    DataStorage storage;
    storage.populate(argv[1], argv[2]);

    //argv[3] is src node index
    int firstNode = stoi(argv[3]) - 1;
    //argv[4] is dest node index;
    int secondNode = stoi(argv[4]) - 1;

    storage.setScrapFolderPath(argv[5]);

    storage.setParentOutputFile(argv[6]);

    if(storage.validateNodeIndex(firstNode, secondNode))
    {
        vector<int> visited;
        visited.push_back(firstNode);

        storage.determinePath(visited, firstNode, secondNode);

        storage.createForking();

    }
    
    return 0;
}