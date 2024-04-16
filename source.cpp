#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::tuple;
using std::vector;

void dfs(int node, int to, vector<bool> &visited, vector<vector<int>> &adjList, bool &result)
{
    visited[node] = true;
    for (int i : adjList[node])
    {
        if (i == to)
        {
            result = true;
            return;
        }
        else if (!visited[i])
        {
            dfs(i, to, visited, adjList, result);
        }
    }
}

bool DFS(vector<vector<int>> &adjList, int from, int to)
{
    bool result = false;
    int N = adjList.size();
    vector<bool> visited(N, false);
    dfs(from, to, visited, adjList, result);

    return result;
}

void genCombinations(size_t pivot, int combSize, const vector<int> &fromElements,
                     vector<int> &currComb, vector<vector<int>> &result)
{
    if (currComb.size() == combSize)
    {
        result.push_back(currComb);
    }
    else
    {
        for (size_t i = pivot; i < fromElements.size(); i++)
        {
            currComb.push_back(fromElements[i]);
            genCombinations(i + 1, combSize, fromElements, currComb, result);
            currComb.pop_back();
        }
    }
}

vector<vector<int>> combinations(const vector<int> &fromElements, int combSize)
{
    vector<int> currComb;
    vector<vector<int>> result;
    genCombinations(0, combSize, fromElements, currComb, result);
    return result;
}

vector<int> range(int start, int end, int step = 1)
{
    vector<int> result;
    for (size_t i = start; i < end; i += step)
    {
        result.push_back(i);
    }
    return result;
}

bool DFSwithRemovedRoads(const vector<vector<int>> &adjList, vector<tuple<int, int, int>> &roads,
                         vector<vector<int>> &cmbntns, int from, int to)
{
    bool result = false;
    for (size_t i = 0; i < cmbntns.size(); i++)
    {
        vector<vector<int>> adjListCopy = adjList;
        for (size_t j = 0; j < cmbntns[i].size(); j++)
        {
            int roadId = cmbntns[i][j];
            int fromNode = std::get<1>(roads[roadId]);
            int toNode = std::get<2>(roads[roadId]);
            adjListCopy[fromNode].erase(std::find(adjListCopy[fromNode].begin(), adjListCopy[fromNode].end(), toNode));
            adjListCopy[toNode].erase(std::find(adjListCopy[toNode].begin(), adjListCopy[toNode].end(), fromNode));
        }

        if (!DFS(adjListCopy, from, to))
        {
            cout << "Roads to remove:";
            for (size_t j = 0; j < cmbntns[i].size(); j++)
            {
                cout << cmbntns[i][j] << " ";
            }
            cout << endl;
            result = true;
        }
    }

    return result;
}

int main()
{

    // Number of nodes
    int N = 5;
    int start_id = 0;

    // adjacency list
    std::vector<std::vector<int>> adjList(N);

    // id, from, to
    vector<tuple<int, int, int>> roads;

    adjList[0].push_back(1);
    adjList[1].push_back(0);
    roads.push_back(tuple<int, int, int>{start_id++, 0, 1});

    adjList[0].push_back(1);
    adjList[1].push_back(0);
    roads.push_back(tuple<int, int, int>{start_id++, 0, 1});

    adjList[1].push_back(2);
    adjList[2].push_back(1);
    roads.push_back(tuple<int, int, int>{start_id++, 1, 2});

    adjList[1].push_back(3);
    adjList[3].push_back(1);
    roads.push_back(tuple<int, int, int>{start_id++, 1, 3});

    adjList[2].push_back(4);
    adjList[4].push_back(2);
    roads.push_back(tuple<int, int, int>{start_id++, 2, 4});

    adjList[3].push_back(4);
    adjList[4].push_back(3);
    roads.push_back(tuple<int, int, int>{start_id++, 3, 4});

    for (int i = 0; i < N; i++)
    {
        std::cout << "Node " << i << ": ";
        for (int j = 0; j < adjList[i].size(); j++)
        {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < roads.size(); i++)
    {
        std::cout << endl
                  << "Road " << std::get<0>(roads[i]) << ": " << std::get<1>(roads[i]) << " -> " << std::get<2>(roads[i]) << std::endl;
    }

    // Generate all combinations of 3 elements
    vector<int> fromElements = range(0, N + 1);
    vector<vector<int>> comb_result = combinations(fromElements, 3);
    for (size_t i = 0; i < comb_result.size(); i++)
    {
        for (size_t j = 0; j < comb_result[i].size(); j++)
        {
            std::cout << comb_result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    cout << DFSwithRemovedRoads(adjList, roads, comb_result, 0, 4) << endl;
}
