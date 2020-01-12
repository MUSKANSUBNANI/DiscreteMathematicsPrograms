#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#define INT_MAX 100000000  //some random number to represent infinity distance when vertice has not been visited yet

using namespace std;

class Vertex; //forward declaration
class Edge;

void Dijkstras();
vector<Vertex*>* AdjacentVertices(Vertex* vertex);
Vertex* SmallestDistance(vector<Vertex*>& vertex);
int Distance(Vertex* V1, Vertex* V2);
void ShortestPath(Vertex* dest);

vector<Vertex*> vertices;
vector<Edge*> edges;
void DijkstrasTest();

class Vertex
{
public:
	Vertex()
	{

	}
	Vertex(char v) 
		: id(v), previous(nullptr), distanceFromStart(INT_MAX)
	{
		
	}

	char id;
	Vertex* previous;
	int distanceFromStart;
};


class Edge
{
public:
	Edge()
	{
		
	}
	Edge(Vertex* Vertex1, Vertex* Vertex2, int distance) 
		: Vertex1(Vertex1), Vertex2(Vertex2), distance(distance)
	{
	
	}

	Vertex* Vertex1;
	Vertex* Vertex2;
	int distance;
};

void Dijkstras()
{
	while (vertices.size() != 0)
	{
		Vertex* smallest = SmallestDistance(vertices);
		vector<Vertex*>* adjacentvertices = AdjacentVertices(smallest);
		for (unsigned int i=0; i<adjacentvertices->size(); i++)
		{
			Vertex* adjacent = adjacentvertices->at(i);
			int distance = Distance(smallest, adjacent) +
				smallest->distanceFromStart;
			
			if (distance < adjacent->distanceFromStart)
			{
				adjacent->distanceFromStart = distance;
				adjacent->previous = smallest;
			}
		}
		delete adjacentvertices;
	}
}

// Find the Vertex with the smallest distance,
// remove it, and return it.
Vertex* SmallestDistance(vector<Vertex*>& vertices)
{
	int size = vertices.size();
	if (size == 0) 
    {
        return nullptr;
    }
	int smallestPosition = 0;
	Vertex* smallest = vertices.at(0);
	for (int i=1; i<size; ++i)
	{
		Vertex* current = vertices.at(i);
		if (current->distanceFromStart <
			smallest->distanceFromStart)
		{
			smallest = current;
			smallestPosition = i;
		}
	}
	vertices.erase(vertices.begin() + smallestPosition);//removes the vertex with smallest Vertex
	return smallest;
}

// Return all Vertexs adjacent to 'Vertex' which are still
// in the 'Vertices' collection.
vector<Vertex*>* AdjacentVertices(Vertex* vertex)
{
	vector<Vertex*>* adjacentvertices = new vector<Vertex*>();
	for(unsigned int i=0; i<edges.size(); i++)
	{
		Edge* edge = edges.at(i);
		Vertex* adjacent = nullptr;
		if (edge->Vertex1 == vertex)
		{
			adjacent = edge->Vertex2;
		}
		else if (edge->Vertex2 == vertex)
		{
			adjacent = edge->Vertex1;
		}
		if (adjacent!=nullptr)
		{
			adjacentvertices->push_back(adjacent);
		}
	}
	return adjacentvertices;
}

// Return distance between two connected Vertexs
int Distance(Vertex* V1, Vertex* V2)
{   int distance=0;
	for(unsigned int i=0; i<edges.size(); i++)
	{
		Edge* edge = edges.at(i);
        if((edge->Vertex1==V1 &&edge->Vertex2==V2)||(edge->Vertex1==V2 &&edge->Vertex2==V1))
			{
                distance=edge->distance;
		    }
	}
	return  distance;
}

void ShortestPath(Vertex* dest)
{
	Vertex* destination = dest;
    vector<char> route;
	cout<< dest->distanceFromStart << endl;  
	while (destination)
	{
		route.push_back( destination->id );
		destination= destination->previous;
	}
    reverse(route.begin(),route.end());// to match the output, the vector route is reversed
	for(unsigned int i=0;i<route.size();i++)     //prints route
    {
        cout<<route.at(i);
		if(i==(route.size()-1))
		{
			cout<<" ";

		}
		else
		{
			cout<<", ";
		}
    }
}

int main(int argc, char* argv[]) {
  if (argc > 1) {   
    ifstream fin;
    fin.open(argv[1]);
    string str;
    getline(fin,str);
    Vertex* a = new Vertex(str[0]);
	vertices.push_back(a);
    Vertex* b = new Vertex(str[2]);
	vertices.push_back(b);
    Vertex* c = new Vertex(str[4]);
	vertices.push_back(c);
    Vertex* d = new Vertex(str[6]);
	vertices.push_back(d);
    getline(fin,str);
   	getline(fin,str);
	string strint1(1,str[4]);
    Edge* e1 = new Edge(a, b, stoi(strint1));
	edges.push_back(e1);
    getline(fin,str);
	string strint2(1,str[4]);
    Edge* e2 = new Edge(c, b, stoi(strint2));
	edges.push_back(e2);
    getline(fin,str);
	string strint3(1,str[4]);
   	Edge* e3 = new Edge(a, c,stoi(strint3));
	edges.push_back(e3);
    getline(fin,str);
	string strint4(1,str[4]);
	Edge* e4 = new Edge(d, a, stoi(strint4));
	edges.push_back(e4);
    getline(fin,str);
	string strint5(1,str[4]);
    Edge* e5 = new Edge(c, d, stoi(strint5));
	edges.push_back(e5);
    getline(fin,str);
	string strint6(1,str[4]);
    Edge* e6=new Edge(c,c,stoi(strint6));
	edges.push_back(e6);

    a->distanceFromStart = 0; // set start Vertex   
	Dijkstras();
	ShortestPath(c);
  }

  return 0;
  }