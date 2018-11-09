#include <iostream>
#include <cstdio>
#include <climits>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

// Custom comparator for priority queue
class Compare
{
public:
	bool operator() (pair<int, int> p1, pair<int, int> p2)
	{
	    return p2.second < p1.second;
	}
};

void dijkstra(list< pair<int, int> > adjacencyList[], int vertices, int startVertex, int distances[], int parent[])
{
    int i;
    priority_queue<pair<int, int>, vector< pair<int, int> >, Compare> pQueue; //Uses compare to determine the priority

    // Set everthing to max int and no parents.
    for (i = 1; i <= vertices; ++i)
	{
        distances[i] = INT_MAX;
        parent[i] = 0;
    }

    // Setting distance to source to zero
    distances[startVertex] = 0;
	pQueue.push(make_pair(startVertex, 0));

	for (i = 1; i <= vertices; ++i)
	{   
		//Set the min Vertex to the top and then pop it (get rid of it from queue)
        pair<int, int> minVertex = pQueue.top();
        pQueue.pop();

		//U is set to first, which in the pair is the Vertex it has a edge to
		int u = minVertex.first;
		//itr lets us go through the adjacency list
		list< pair<int, int> >::iterator itr = adjacencyList[u].begin();

		// Checking all adjacent verticies
        while (itr != adjacencyList[u].end())
		{
			//This is the first and second of the pushed pairs
        	int dest = itr->first;
        	int weight = itr->second;

			//Check to see if it has already been visited
			//And if it has, is it a better route?
            if (distances[u] != INT_MAX && distances[dest] > distances[u] + weight)
			{
                //New shortest route
                distances[dest] = distances[u] + weight;
                parent[dest] = u;
                //Push it back onto Queue instead of Decrease Key
                pQueue.push(make_pair(dest, distances[dest]));
            }
            //Go to the next 'node' in the adj list
            ++itr;
        }
    }
}

int main()
{
	int vertices, edges, i, v1, v2, w;
	string line;

	ifstream file("input.txt");
	ofstream outFile("output.txt");
	if (file)
	{
		getline(file, line);  //Dummy Input line

		// pair.first = edge's destination vertex
		// pair.second = edge weight
		file >> vertices >> edges;
		
		//A list of pairs, both ints
		list< pair<int, int> > adjacencyList[vertices+1];
		
		//Array of Distances and Parent Vertex
		
		//i.e. Distance of 10 in slot 2 means that it takes
		//10 to get to the second vertex through some path
		int distances[vertices + 1];
		int parent[vertices + 1];
		
		//Read the file and push it into the Adjacency list
		while (file >> v1 >> v2 >> w)
			adjacencyList[v1].push_back(make_pair(v2, w));
		
		//Call the Dijkstra with 0 always the starting point
		dijkstra(adjacencyList, vertices, 0, distances, parent);
		
		//File Writing
		outFile<<"Output:\n";
		outFile<<"Vertex:   ";
		for(i = 0; i < vertices; ++i)
		{
			outFile<<i<<"   ";
		}
		outFile<<"\nDistance: ";
		for(i = 0; i < vertices; ++i)
		{
			outFile<<distances[i]<<"   ";
		}
		outFile<<endl;
		outFile.close();
	}
	else
	{
		cout<<"Invalid File."<<endl;
		exit(0);
	}
    return 0;
}
