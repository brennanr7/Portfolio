//Version2
//read node list
//produce graph

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <unistd.h>
#include <stack>
#include <queue>

#include "DataStorage.h"

using namespace std;

/* Constructor
*
*   @Brief: Initializes member variables
*/
DataStorage::DataStorage()
{
    m_Scrapfilename = "";
    m_numVertices = 0;
    m_totalCost = 0;
}

/* Deconstructor
*
*
*/
DataStorage::~DataStorage()
{
}

/* Populate
*
*   @Brief: Actracts from files, the grid and the nodes.
*
*   @param1[in]: gridFilename -> The grid file as an argument from the command line
*   @param2[in]: nodeFilename -> The node file as an argument from the command line
*   
*   @returns: Void
*/
void DataStorage::populate(string gridFilename, string nodeFilename)
{
    int countVertices = 0;
    ifstream inFile;

    inFile.open(nodeFilename);
    inFile >> m_numVertices;
    m_nodes.resize(m_numVertices);
    //ERROR CHECKING FOR VALID NODES AND VALID GRID SIZE
    int x, y;
    Node tempNode;
    //sort pairs, find the highest row and column, set matrix to that, create adj matrix that fits the size of row and column
    for (int i = 0; i < m_numVertices; i++)
    {
        inFile >> tempNode.row >> tempNode.column;
        tempNode.index = i;
        m_adjList.push_back(tempNode);
    }
    inFile.close();

    inFile.open(gridFilename);
    inFile >> gridColumn >> gridRow;

    //temp variables for parsing file lines
    string line;
    string num;
    vector<float> vec;

    getline(inFile, line);
    while(!inFile.eof())
    {
        getline(inFile, line);
        istringstream iss(line);  
        while(getline(iss, num, ' '))
        {
            vec.push_back(stof(num));
        }
        m_grid.push_back(vec);
        vec.clear();
     }
     m_grid.pop_back();
    manhattan();
}

/* setScrapFolderPath
*
*   @Brief: Sets the file path of the Scrap folder to be used for the child and grandchild processes
*
*   @param1[in]: filepath -> the file path of the scrap folder from the command line
*
*   @returns: void
*/
void DataStorage::setScrapFolderPath(string filepath)
{
    m_Scrapfilename = filepath;
}

/* getScrapFile
*
*   @Brief: Returns the scrap file
*
*   @returns: a string to the path of the scrap file
*/
string DataStorage::getScrapFile()
{
    return m_Scrapfilename;
}

/* setParentOutputFile
*
*   @Brief: Sets the output file for the parent process
*
*   @param1: file -> the output file passed in from the command line
*
*   @returns: void
*/
void DataStorage::setParentOutputFile(string file)
{
    m_outPutFile = file;
}

/* getParentOutputFile
*
*   @Brief: Gets the output file for the parent
*
*   @returns: A string of the output file
*/
string DataStorage::getParentOutputFile()
{
    return m_outPutFile;
}

/* compareDistances
*
*   @Brief: compares the distances of the first node manahattan distance to the second
*
*   @param1: first -> the first node to be compared
*   @param2: second -> the second node to be compared
*
*   @returns: a bool true if second's distance is greater than first's distance, otherwise false
*/
bool compareDistances(const Neighbors &first, const Neighbors &second)
{
    return first.distance < second.distance;
}

/* manhattan
*
*   @Brief: Outerloop to traverse each node to calculate manhattan distance
*   @Details: Sorts the neighbor nodes based on distances
*   
*   @returns: void
*/
void DataStorage::manhattan()
{
    //push back the node to traverse
    for(int i = 0; i < m_adjList.size(); i++)
    {
        manhattanInnerLoop(m_adjList.at(i).row, m_adjList.at(i).column, i);

        //sort distances
        sort(m_adjList.at(i).neighborNodes.begin(), m_adjList.at(i).neighborNodes.end(), &compareDistances);
        m_adjList.at(i).neighborNodes.erase(m_adjList.at(i).neighborNodes.begin());
        closestNeighbors(i);
    }
    finalNeighborsCheck();
}

/* manhattanInnerLoop
*
*   @Brief: Traverses each node and calculates the manhattan distance from a single source node
*   @Details: A single source node adds each calculated node and its distance to its neighbor list
*
*   @param1: row -> The row of the source node
*   @param2: column -> The column of the source node
*   @param3: i -> The index of the source node
*
*   @returns: void
*/
void DataStorage::manhattanInnerLoop(int row, int column, int i)
{
    //sort all of the distances and only grab the first 3 or 4 distances depending on whether index 3 + n == value at index 3
    int currSum = 0;
    for(int x = 0; x < m_adjList.size(); x++)
    {
        Neighbors tempNeighbor;
        currSum += (abs(m_adjList.at(x).row - row) + abs(m_adjList.at(x).column - column));
        tempNeighbor.distance = currSum;
        tempNeighbor.index = validateNode(m_adjList.at(x).row, m_adjList.at(x).column);
        tempNeighbor.row = m_adjList.at(x).row;
        tempNeighbor.column = m_adjList.at(x).column;

        m_adjList.at(i).neighborNodes.push_back(tempNeighbor);
        currSum = 0;
    }
}

/* closestNeighbors
*
*   @Brief: Calculates the closest neighbors of a single source node
*   @Details: Removes nodes if the 4th neighbor is not equal to the 3rd node
*
*   @param1: index -> the index of the source node to determine its closest nieghbors
*
*   @returns: void
*/
void DataStorage::closestNeighbors(int index)
{
    for(int j = 3; j < m_adjList.at(index).neighborNodes.size(); j++)
    {
        if(m_adjList.at(index).neighborNodes.at(2).distance != m_adjList.at(index).neighborNodes.at(j).distance)
        {
            m_adjList.at(index).neighborNodes.erase(m_adjList.at(index).neighborNodes.begin()+j, m_adjList.at(index).neighborNodes.end());
            return;
        }
    }
}

/* determinePath
*
*   @Brief: Determines the path between a given source and destination node from the command line
*   @Details: A recursive function, constructing the actual undirected graph
*
*   @param1: visited -> A vector of booleans to track each visited node in the tree/graph
*   @param2: srcIndex -> A source node from the command line to find a path from
*   @param3: destIndex -> A destination node from the command line to find a path to
*
*   @returns: void
*/
void DataStorage::determinePath(vector<int> visited, int srcIndex, int destIndex)
{
    //find all paths algo
    if(visited.back() == destIndex)
    {
        //if path size > 5 || 3
        if(visited.size() < 3 || visited.size() > 5)
        {
            return;
        }
        else
        {
            path.push_back(visited);
        }

    }
    if (visited.size() > 5)
    {
        return;
    }
    //go through neighbor nodes from the last node added 
    for(int j = 0; j < m_adjList.at(visited.back()).neighborNodes.size(); j++)
    {
        //if the node is visited, don't traverse that nodes neighbors
        if(isVisited(visited, m_adjList.at(visited.back()).neighborNodes.at(j).index))
        {
            if(j > m_adjList.at(visited.back()).neighborNodes.size())
            {
                return;
            }
        }
        else
        {
            visited.push_back(m_adjList.at(visited.back()).neighborNodes.at(j).index);
            determinePath(visited, visited.back(), destIndex); 
            visited.pop_back();
        }
    }
}

/* isVisited
*
*   @Brief: A helper function to determine if a node in a vector has been visited
*
*   @param1: visited -> A vector of booleans storing the visited nodes
*   @param2: index -> The index of the node to check its visited status
*
*   @returns: A boolean specifying true if the the node has been seen, false otherwise
*/
bool DataStorage::isVisited(vector<int> visited, int index)
{
    for(int i = 0; i < visited.size(); i++)
    {
        if(visited.at(i) == index)
        {
            return true;
        }
    }
    return false;

}

/*  finalNeighborsCheck
*
*   @Brief: A function to make the graph undirected
*   @Details: Handles the source node neighbors' row and column and calls the helper function for the source node's neighbor's
*
*   @returns: void
*   @note: I should have just handed in the index of the node, not its row and column
*/
void DataStorage::finalNeighborsCheck()
{
    for(int i = 0; i < m_adjList.size(); i++)
    {
        for(int j = 0; j < m_adjList.at(i).neighborNodes.size(); j++)
        {
            finalNeighborsHelper(m_adjList.at(i).neighborNodes.at(j).row, m_adjList.at(i).neighborNodes.at(j).column, i);
        }
        
    }
}

/*  finalNeighborsHelper
*
*   @Brief: Iterates through the nieghbors of the source node to ensure that graph is undirected
*   @Details: The neighbor nodes check if the parent node is in it's neighbors, if not then the parent is added
*   
*   @param1: childRow -> the row of the parents neighbor
*   @param2: childColumn -> the column of the parents neighbor
*   @param3: i -> the index of the parent
*
*   @returns: void
*   @note: I should have just handed in the index of the node, not its row and column
*/
void DataStorage::finalNeighborsHelper(int childRow, int childColumn, int i)
{
    bool found = true;
    for(int j = 0; j < m_adjList.size(); j++)
    {
        if(m_adjList.at(j).row == childRow && m_adjList.at(j).column == childColumn)
        {
            for(int x = 0; x < m_adjList.at(j).neighborNodes.size(); x++)
            {
                if((m_adjList.at(j).neighborNodes.at(x).row != m_adjList.at(i).row) || (m_adjList.at(j).neighborNodes.at(x).column != m_adjList.at(i).column))
                {
                    found = false;
                }
                else
                {
                    found = true;
                    return;
                }
            }
            if(found == false)
            {
                Neighbors newNeighbor;
                newNeighbor.row = m_adjList.at(i).row;
                newNeighbor.column = m_adjList.at(i).column;
                newNeighbor.distance = (abs(m_adjList.at(j).row - m_adjList.at(i).row) + abs(m_adjList.at(j).column - m_adjList.at(i).column));
                newNeighbor.index = validateNode(m_adjList.at(i).row, m_adjList.at(i).column);
                m_adjList.at(j).neighborNodes.push_back(newNeighbor);
            }
        }
    }
}

/*  validateNode
*
*   @Brief: validates if the given node is valid and returns its index
*   
*   @param1: nodeRow -> the nodes row to validate
*   @param2: nodeColumn -> the nodes column to validate
*
*   @returns: the index of the node if valid, otherwise -1
*/
int DataStorage::validateNode(int nodeRow, int nodeColumn)
{
    for(int i = 0; i < m_adjList.size(); i++)
    {
        if(m_adjList.at(i).row == nodeRow && m_adjList.at(i).column == nodeColumn)
        {
            return m_adjList.at(i).index;
        }
    }
    return -1;
}

/*  validateNodeIndex
*
*   @Brief: Validates if a given node index is in the list
*
*   @param1: indexOne -> the first index of a node
*   @param2: indexTwo -> the second index of a node
*
*   @returns: true if valid, false if not
*/
bool DataStorage::validateNodeIndex(int indexOne, int indexTwo)
{
    if(indexOne > m_nodes.size() - 1 || indexOne < 0 || indexTwo > m_nodes.size() - 1 || indexTwo < 0)
    {
        return false;
    }
    return true;
}

/*  printChildFile
*
*   @Brief: Prints the child process grid search results
*   @Details: A child file traverses its grandchild processes output file who found a path
*
*   @param1: processIndex -> the child process number
*
*   @returns: void
*/
void DataStorage::printChildFile(int processIndex)
{
    //path.size() created num children
    //path.at(processIndex).size() - 1 created grandchildren
    string cost;
    float finalCost = 0.0;
    float tempCost = 0.0;
    string initPath = "";
    string fullPath = "";
    int numCoordinates;
    int finalNumCoordinates = 0;
    string nodes;
    for(int i = 0; i < path.size(); i++)
    {
        for(int j = 0; j < path.at(processIndex).size() - 1; j++)
        {
            ifstream file;
            file.open(getScrapFile() + "/grandchild_" + to_string(processIndex) + "_" + to_string(j)+".txt");
            file >> tempCost;
            finalCost += tempCost;
            getline(file, initPath);
            getline(file, initPath);
            if(j + 1 != path.at(processIndex).size() - 1)
            {
                fullPath += initPath;
                fullPath += ", ";
            }
            else
            {
                fullPath += initPath;
            }
            file >> numCoordinates;
            finalNumCoordinates += numCoordinates;
            file.close();
        }
        ofstream childFile;
        childFile.open(getScrapFile() + "/child_" + to_string(processIndex) + ".txt");
        childFile << finalCost << endl;
        childFile << fullPath << endl;
        childFile << finalNumCoordinates << endl;
        for(int x = 0; x < path.at(processIndex).size(); x++)
        {
            childFile << path[processIndex][x] + 1;
            if(x+ 1 != path.at(processIndex).size())
            {
                childFile << " ";
            }
        }
        childFile << endl;
        childFile << path.at(processIndex).size();
        tempCost = 0.0;
        finalCost = 0.0;
        numCoordinates = 0;
        finalNumCoordinates = 0;
        fullPath = "";
        childFile.close();
    }
}

/*  printGrandChildFile
*
*   @Brief: Prints the grandchild Process
*   @Details: Prints the result of the grid traversal to a file that the grandchild process did
*
*   @param1: parentProcessIndex -> The child processes number
*   @param2: grandProcessIndex -> The grandchild process number
*
*   @returns: void
*/
void DataStorage::printGrandChildFile(int parentProcessIndex, int grandProcessIndex)
{
    ofstream grandFile;
    string file = getScrapFile() + "/grandchild_" + to_string(parentProcessIndex) + "_" + to_string(grandProcessIndex)+".txt";
    grandFile.open(file);

    grandFile << m_totalCost << endl;

    for(int i = 0; i < m_pathRow.size(); i++)
    {
        grandFile << "{" << m_pathRow.at(i) + 1<< ", " << m_pathCol.at(i) + 1<< "}";
        if(i+ 1 != m_pathRow.size())
        {
            grandFile << ", ";
        }
    }
    grandFile << endl;
    grandFile << m_pathRow.size() << endl;
    m_pathRow.clear();
    m_pathCol.clear();


    grandFile << path[parentProcessIndex][grandProcessIndex] << " " << path[parentProcessIndex][grandProcessIndex + 1] << endl;
    m_totalCost = 0;

    grandFile.close();
}

/*  createForking
*
*   @Brief: Creates n number of child processes based on the number of paths found
*
*   @returns: void
*/
void DataStorage::createForking()
{
    for(int i = 0; i < path.size(); i++)
    {
       pid_t PID = fork();
        if(PID == 0)
        {
            grandChildForking(i);
            printChildFile(i);
            exit(0);
        }
        else if(PID < 0)
        {
            // No child created
            return;
        }
        else
        {
            // I am the parent 
        }
    }
    int k;
    while((k=wait(NULL)) > 0);
    printParentFile();
}

/* grandChildForking
*
*   @Brief: creates the grandchild of the parent process
*   
*   @returns: void
*/
void DataStorage::grandChildForking(int processIndex)
{
    for(int j = 0; j < path.at(processIndex).size() - 1; j++)
    {
        pid_t grandChild = fork();
        if(grandChild == 0)
        {
            minPath(processIndex, j);
            printGrandChildFile(processIndex, j);
            exit(0);

        }
    }
    int k;
    while((k=wait(NULL)) > 0);
}

/* minPath
*
*   @Brief: Uses the nodes from the paths produced to enter another function to handle the cost
*   @Details: Handles traversal of two specific nodes in the path that was found previously
*   
*   @param1: processIndex -> the process index of the child process
*   @param2: j -> the index of the grandchild process
*
*   @reurns: void
*/
void DataStorage::minPath(int processIndex, int j)
{
    int nodeArray[path.at(processIndex).size()];
    int destRow = m_adjList.at(path.at(processIndex).back()).row;
    int destColumn = m_adjList.at(path.at(processIndex).back()).column;

    float total1 = 0.0, total2 = 0.0;
    m_pathRow.clear();
    m_pathCol.clear();

    nodeArray[j] = path[processIndex][j];
    if(path[processIndex][j + 1] == path.at(processIndex).back())
    {
        total1 += costTraversal(m_adjList.at(nodeArray[j]).row, m_adjList.at(nodeArray[j]).column, destRow, destColumn); 
        total1 += m_grid[destRow][destColumn];  
    }
    else
    {
        total2 += costTraversal(m_adjList.at(path[processIndex][j]).row, m_adjList.at(path[processIndex][j]).column, m_adjList.at(path[processIndex][j + 1]).row, m_adjList.at(path[processIndex][j + 1]).column);
        m_pathRow.pop_back();
        m_pathCol.pop_back();
    }
    m_totalCost = total1 + total2;
}

//global variables to state directions north, south, east, and west
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { -1, 0, 1, 0 };

/* costTraversal
*
*   @Brief: A dfs grid traversal implementation
*   @Details: Handles grid traversal of a source and destination node
*
*   @param1: row -> The row of the source node
*   @param2: column -> The column of the source node
*   @param3: destRow -> The row of the destination node
*   @param3: destColumn -> The column of the destination node
*/
float DataStorage::costTraversal(int row, int column, int destRow, int destColumn)
{
    vector<vector<bool> > visited;
    vector<bool> temp;
    for(int i = 0; i < gridRow; i++)
    {
        for(int j = 0; j < gridColumn; j++)
        {
            temp.push_back(false);
        }
        visited.push_back(temp);
        temp.clear();
    }
    stack<pair<int, int> > st;
    st.push(make_pair(row, column));
    visited[row][column] = true;
    vector<int> pathRow;
    vector<int> pathCol;
    float total = 0;

    while(!st.empty())
    {
        pair<int, int> curr = st.top();
        st.pop();
        int row = curr.first;
        m_pathRow.push_back(row);
        int col = curr.second;
        m_pathCol.push_back(col);
        if(row == destRow && col == destColumn)
        {
            return total - m_grid[row][col];
        }

        total += m_grid[row][col];
        visited[row][col] = true;

        for(int i = 0; i < 4; i++)
        {
            int adjx = row + dr[i];
            int adjy = col + dc[i];

            if(ifVisited(visited, adjx, adjy))
            {
                st.push(make_pair(adjx, adjy));
                visited[adjx][adjy] = true;
            }
        }
    }
    return total;
}

/* ifVisited
*
*   @Brief: A helper function for DFS to determine if a set of coordinates should be added to the stack
*   @Details: The function checks the row and column to be added are valid or visited
*   
*   @param1: visited -> a vector of booleans of stored visited indices
*   @param2: row -> row to check
*   @param3: col -> column to check
*
*   @returns: false if the node is out of bounds or visited already, true if needed to be visited
*/
bool DataStorage::ifVisited(vector<vector<bool> > visited, int row, int col)
{
    if(row < 0 || col < 0 || row > gridRow - 1 || col > gridColumn - 1)
    {
        return false;
    }

    if(visited[row][col])
    {
        return false;
    }
    return true;
}

/* printParentFile
*
*   @Brief: A function to print the results of the lowest cost path
*   @Details: The parent process traverses through the child files and determines the lowest cost path
*
*   @returns: void
*/
void DataStorage::printParentFile()
{
    string bestPath;
    string nodes;
    string numNodes;
    string numCoordinates;
    float currCost = 0;
    float nextCost = 0;
    int bestChildPathFile;
    for(int i = 0; i < path.size(); i++)
    {
        ifstream file;
        file.open(getScrapFile() + "/child_" + to_string(i) + ".txt");
        file >> nextCost;
        if(i == 0)
        {
        getline(file, bestPath);
        getline(file, bestPath);
        getline(file, numCoordinates);
        getline(file, nodes);
        getline(file, numNodes);
            currCost = nextCost;
            bestChildPathFile = i;
            continue;
        }
        if(nextCost < currCost)
        {
            getline(file, bestPath);
            getline(file, bestPath);
            getline(file, numCoordinates);
            getline(file, nodes);
            getline(file, numNodes);
            currCost = nextCost;
            bestChildPathFile = i;
        }
        file.close();
    }

    ofstream parentFile;
    parentFile.open(getParentOutputFile());

    parentFile << "Lowest cost path found:" << endl;
    parentFile << "\t" << numNodes << " nodes: " << nodes << endl;
    parentFile << "\t" << numCoordinates << " grid points {row, col}:" << endl;
    parentFile << "\t\t" << bestPath << endl;
    parentFile << "\t" << "Total cost: " << currCost << endl;

    parentFile.close();
}