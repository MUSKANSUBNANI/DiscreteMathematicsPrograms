import sys
from collections import defaultdict
import math

class Graph(dict):
    #A graph class. Keys(vertices) contains a dictionary of other vertices they are connected to.which is nested to 
    #containing the weight of the edge.
    def __missing__(self, key):
        value = self[key] = {key:0}  #Empty dictionary
        return value
    
    def Edge(self, vertex1, vertex2, distance):
        vertices = self.keys()
        if vertex1 not in vertices:
            self[vertex1]
        if vertex2 not in vertices:
            self[vertex2]
        self[vertex1][vertex2] = distance
        print(self)

    def ConnectedVertices(self, vertex):
        return {k: v for k, v in self[vertex].items() if k != vertex}# returns a key value pair of vertices and distance from the passed vertex

    def Dijkstras(self, start, end):
        def get_next():
            unvisited = {k: v for k, v in distance.items() if k not in visited}
            next_vertex = min(unvisited, key=unvisited.get)
            return next_vertex 
            
        def step(vertex):
            cost = 0 if parent[vertex] is None else distance[vertex]  # If no parents, then this is the starting node
            for n, w in self.ConnectedVertices(vertex).items():
                if distance[n] is None or distance[n] > w + cost:
                    parent[n] = vertex
                    distance[n] = cost + w
            visited.append(vertex)

        def print_path():
            path = [end]
            vertex = end
            while parent[vertex] != start:
                path.append(parent[vertex])
                vertex = parent[vertex]
            path.append(start)
            path.reverse()
            # print("The shortest path from A to D is: ")
            print("--->".join(path))
        
        visited = []
        distance = {}
        parent = {}
        for vertex in self.keys():
            distance[vertex] = 0 if (vertex == start) else math.inf   
            parent[vertex] = None

        step(start)
        while end not in visited:
            nextvertex = get_next()
            step(nextvertex)

        print (distance[end])
        print_path()
        print("finished: ", visited)
        print("Parent: ", parent)


def main():
    totalvertices=None
    startend=None
    edge1=None
    edge2=None
    edge3=None
    edge4=None
    edge5=None
    edge6=None
    with open(sys.argv[1],'r') as f: 
        totalvertices=f.readline()
        startend=f.readline()
        edge1=f.readline()
        edge2=f.readline()
        edge3=f.readline()
        edge4=f.readline()
        edge5=f.readline()
        edge6=f.readline()

    g=Graph()
    g.Edge(edge1[0],edge1[2],int(edge1[4]))
    g.Edge(edge2[0],edge2[2],int(edge2[4]))
    g.Edge(edge3[0],edge3[2],int(edge3[4]))
    g.Edge(edge4[0],edge4[2],int(edge4[4]))
    g.Edge(edge5[0],edge5[2],int(edge5[4]))
    g.Edge(edge6[0],edge6[2],int(edge6[4]))
    g.Dijkstras(startend[0],startend[2])

if __name__ == "__main__":
    main()


