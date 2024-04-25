#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void dfs(int node, vector<bool> &visited, vector<vector<int>> &adjList, int &count)
{
    visited[node] = true;
    count++;
    for (int i : adjList[node])
    {
        if (!visited[i])
        {
            dfs(i, visited, adjList, count);
        }
    }
}

vector<int> components(vector<vector<int>> &adjList)
{
    int N = adjList.size();
    vector<bool> visited(N, false);
    vector<int> result;
    for (int i = 0; i < N; i++)
    {
        int count = 0;
        if (!visited[i])
        {
            dfs(i, visited, adjList, count);
            int component = count;
            result.push_back(component);
        }
    }

    return result;
}

void print_graph(const vector<vector<int>> &adjList)
{
    for (int i = 0; i < adjList.size(); i++)
    {
        cout << "Node " << i << " -> ";
        for (int j = 0; j < adjList[i].size(); j++)
        {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<int> find_godfather(const vector<vector<int>> &adjList)
{
    vector<int> godfathers(adjList.size());
    print_graph(adjList);
    for (int j = 0; j < adjList.size(); j++)
    {
        cout << endl
             << "Removing node " << j << endl;

        vector<vector<int>> adjListCopy = adjList;
        for (int vertex : adjListCopy[j])
        {
            adjListCopy[vertex].erase(find(adjListCopy[vertex].begin(),
                                           adjListCopy[vertex].end(), j));
        }
        adjListCopy[j].clear();
        print_graph(adjListCopy);

        vector<int> componentsSizes = components(adjListCopy);
        godfathers[j] = *max_element(componentsSizes.begin(), componentsSizes.end());

        for (int i = 0; i < componentsSizes.size(); i++)
        {
            cout << "Component size: " << componentsSizes[i] << endl;
        }
        cout << "Max component size: " << godfathers[j] << endl
             << endl;
    }

    int minElem = *min_element(godfathers.begin(), godfathers.end());
    vector<int> result;
    for (int i = 0; i < godfathers.size(); i++)
    {
        if (godfathers[i] == minElem)
        {
            result.push_back(i + 1);
        }
    }

    return result;
}

int main()
{
    // int N = 6;
    int N = 5;

    // adjacency list
    std::vector<std::vector<int>> adjList(N);

    // adjList[0].push_back(1);
    // adjList[1].push_back(0);

    // adjList[1].push_back(2);
    // adjList[2].push_back(1);

    // adjList[1].push_back(4);
    // adjList[4].push_back(1);

    // adjList[2].push_back(3);
    // adjList[3].push_back(2);

    // adjList[2].push_back(5);
    // adjList[5].push_back(2);

    adjList[0].push_back(4);
    adjList[4].push_back(0);

    adjList[2].push_back(3);
    adjList[3].push_back(2);

    adjList[1].push_back(3);
    adjList[3].push_back(1);

    adjList[4].push_back(3);
    adjList[3].push_back(4);

    vector<int> godfathers = find_godfather(adjList);
    for (auto elem : godfathers)
    {
        cout << "Possible godfather: " << elem << endl;
    }
    return 0;
}