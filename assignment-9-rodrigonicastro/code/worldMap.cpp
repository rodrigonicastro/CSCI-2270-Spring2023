#include "worldMap.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

WorldMap::WorldMap() {}

void WorldMap::createWorldMap(string fileName)
{
    ifstream fin;
    fin.open(fileName);

    if(fin.is_open()){
        string line;
        getline(fin, line);

        stringstream ss(line);
        string numRows;
        string numCols;
        
        ss >> numRows;
        ss >> numCols;

        rows = stoi(numRows);
        cols = stoi(numCols);

        worldMap = new int*[rows];

        for(int i = 0; i < rows; i++){
            worldMap[i] = new int[cols];
        }        
                
        for(int i = 0; i < rows; i++){
            getline(fin, line);
            stringstream s(line);
            string coordinate;

            for(int j = 0; j < cols; j++){
                s >> coordinate;
                worldMap[i][j] = stoi(coordinate);
            }
        }
    }
}

void WorldMap::printWorldMap()
{
    for(int i = 0; i < cols; i++){
        cout << "|";
        for(int j = 0; j < rows; j++){
            cout << " " << worldMap[i][j] << " |";
        }
        cout << endl;
    }
}

void WorldMap::addRegion(int x, int y)
{
    bool regionExists = false;

    for(auto region : regions){
        if(region->x == x && region->y == y){
            regionExists = true;
            break;
        }
    }

    if(!regionExists){
        Region* newRegion = new Region;

        newRegion->x = x;
        newRegion->y = y;
        
        regions.push_back(newRegion);
    }
}

bool checkIfEdgeExists(Region *r, int x2, int y2)
{
    // for(int i = 0; i < r->neighbors.size(); i++){
    //     if(r->neighbors[i].region->x == x2 && r->neighbors[i].region->y == y2) return true;
    // }

    for(auto neighbor : r->neighbors){
        if(neighbor.region->x == x2 && neighbor.region->y == y2) return true;
    }

    return false;
}

void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2)
{
    // TODO START
    for (unsigned int i = 0; i < regions.size(); i++)
    {
        if (regions[i]->x == x1 && regions[i]->y == y1)
        {
            for (unsigned int j = 0; j < regions.size(); j++)
            {
                if (i != j && regions[j]->x == x2 && regions[j]->y == y2)
                {
                    if (!checkIfEdgeExists(regions[i], x2, y2))
                    {
                        NeighboringRegion av;
                        av.region = regions[j];
                        regions[i]->neighbors.push_back(av);
                        // another vertex for edge in other direction
                        NeighboringRegion av2;
                        av2.region = regions[i];
                        regions[j]->neighbors.push_back(av2);
                    }
                }
            }
        }
    }
    // TODO END
}

vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y)
{
    // TODO START
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<vector<int>> neighbors;
    for (int i = x - 1; i <= x + 1; i++)
    {
        if (i < 0 || i >= this->rows)
        {
            continue;
        }
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (j < 0 || j >= this->cols)
            {
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if (!(i == x && j == y) && worldMap[i][j] == 1)
            {
                neighbors.push_back({i, j});
            }
        }
    }
    return neighbors;
    // TODO END
}

void WorldMap::convertWorldMapToAdjacencyListGraph()
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(worldMap[i][j] == 1) addRegion(i, j);
        }
    }

    for(auto region : regions){
        vector<vector<int>> adjRegions = findAdjacentLandRegions(region->x, region->y);
        for(int i = 0; i < adjRegions.size(); i++){
            addEdgeBetweenRegions(region->x, region->y, adjRegions[i][0], adjRegions[i][1]);
        }
    }


}

// helper function to check if v2 is a neighbor of verter v1
bool isNeighbor(int x1, int y1, int x2, int y2, const vector<Region *> regions)
{
    return false;
}

WorldMap::~WorldMap()
{
    for(int i = 0; i < rows; i++){
        delete[] worldMap[i];
    }

    delete[] worldMap;

    rows = 0;
    cols = 0;

    for(auto region : regions){
        delete region;
    }
}

void WorldMap::displayEdges()
{
    for(auto region : regions){
        region->visited = false;
    }

    for(auto region : regions){
        if(!region->visited){
            region->visited = true;
            cout << "(" << region->x << "," << region->y << ") --> ";

            for(auto neighbor : region->neighbors){
                cout << "(" << neighbor.region->x << "," << neighbor.region->y << ") ";    
            }
            cout << endl;
        }
    }
}

// HELPER FOR findNumOfIslands
void findNumOfIslandsHelper(Region *r)
{
    return;
}

int WorldMap::findNumOfIslands()
{
    int numIslands = 0;
    resetVisited();

    for(auto region : regions){
        if(!region->visited){
            DFSTraverse(region);
            numIslands++;
        }
    }    

    return numIslands;
}

void WorldMap::_DFSHelper(Region* _src){
    _src->visited = true;

    cout << "Reached vertex: " << "(" << _src->x << ',' << _src->y << ")" << endl; 

    for(auto edge : _src->neighbors){
        if(!edge.region->visited) _DFSHelper(edge.region);
    }
}

void WorldMap::DFSTraverse(Region* src){
    if(src) _DFSHelper(src);
}

void WorldMap::resetVisited(){
    for(auto region : regions){
        region->visited = false;
    }
}

vector<Region *> &WorldMap::getRegions()
{
    return regions;
}
