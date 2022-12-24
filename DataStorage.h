#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include <set>
#include <queue>

//neighbor struct
struct Neighbors
{
    int row, column, index, distance;
    bool visited;
};

//node struct
struct Node
{
    //row, column, index of vector
    int row, column, index;
    //vector to store neighbors
    std::vector<Neighbors> neighborNodes;
};

class DataStorage
{
public:
    DataStorage();
    ~DataStorage();

    void populate(std::string gridFilename, std::string nodeFilename);
    void manhattan();
    void manhattanInnerLoop(int row, int column, int i);
    void setScrapFolderPath(std::string file);
    void setParentOutputFile(std::string file);
    std::string getParentOutputFile();
    void closestNeighbors(int index);
    void determinePath(std::vector<int> visited, int srcIndex, int destIndex);
    void finalNeighborsCheck();
    void finalNeighborsHelper(int childRow, int childColumn, int i);
    int validateNode(int nodeRow, int nodeColumn);
    bool validateNodeIndex(int indexOne, int indexTwo);
    bool isVisited(std::vector<int> visited, int index);
    void printChildFile(int processIndex);
    void printGrandChildFile(int parentProcessIndex, int grandProcessIndex);
    void minPath(int processIndex, int j);
    void createForking();
    float costTraversal(int row, int column, int destRow, int destColumn);
    bool ifVisited(std::vector<std::vector<bool> > visited, int row, int col);
    void printParentFile();
    void grandChildForking(int processIndex);
    std::string getScrapFile();

private: 
    //scrap file path
    std::string m_Scrapfilename;
    //output file 
    std::string m_outPutFile;
    //number of nodes
    int m_numVertices;
    //adjList for graph
    std::vector<Node> m_adjList; 
    //node vector
    std::vector<Node> m_nodes;
    //grid
    std::vector<std::vector<float> > m_grid;
    //grid indicies
    int gridRow, gridColumn;
    //every possible path
    std::vector<std::vector<int> > path;
    //total cost of path
    float m_totalCost;
    //grid rows of a path
    std::vector<int> m_pathRow;
    //grid columns of a path
    std::vector<int> m_pathCol;
};

#endif