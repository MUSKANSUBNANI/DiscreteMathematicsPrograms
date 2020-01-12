import sys
from collections import deque, namedtuple


# we'll use infinity as a default distance to nodes.
inf = float('inf')
Edge = namedtuple('Edge', 'start, end, cost')


def make_edge(start, end, cost=1):
  return Edge(start, end, cost)


class Graph:
    def __init__(self, edges):
        # let's check that the data is right
        wrong_edges = [i for i in edges if len(i) not in [2, 3]]
        if wrong_edges:
            raise ValueError('Wrong edges data: {}'.format(wrong_edges))

        self.edges = [make_edge(*edge) for edge in edges]

    @property
    def vertices(self):
        return set(
            sum(
                ([edge.start, edge.end] for edge in self.edges), []
            )
        )

    def get_node_pairs(self, n1, n2, both_ends=True):
        if both_ends:
            node_pairs = [[n1, n2], [n2, n1]]
        else:
            node_pairs = [[n1, n2]]
        return node_pairs

    def remove_edge(self, n1, n2, both_ends=True):
        node_pairs = self.get_node_pairs(n1, n2, both_ends)
        edges = self.edges[:]
        for edge in edges:
            if [edge.start, edge.end] in node_pairs:
                self.edges.remove(edge)

    def add_edge(self, n1, n2, cost=1, both_ends=True):
        node_pairs = self.get_node_pairs(n1, n2, both_ends)
        for edge in self.edges:
            if [edge.start, edge.end] in node_pairs:
                return ValueError('Edge {} {} already exists'.format(n1, n2))

        self.edges.append(Edge(start=n1, end=n2, cost=cost))
        if both_ends:
            self.edges.append(Edge(start=n2, end=n1, cost=cost))

    @property
    def neighbours(self):
        neighbours = {vertex: set() for vertex in self.vertices}
        for edge in self.edges:
            neighbours[edge.start].add((edge.end, edge.cost))

        return neighbours

    def dijkstra(self, source, dest):
        assert source in self.vertices, 'Such source node doesn\'t exist'
        distances = {vertex: inf for vertex in self.vertices}
        previous_vertices = {
            vertex: None for vertex in self.vertices
        }
        distances[source] = 0
        vertices = self.vertices.copy()

        while vertices:
            current_vertex = min(
                vertices, key=lambda vertex: distances[vertex])
            vertices.remove(current_vertex)
            if distances[current_vertex] == inf:
                break
            for neighbour, cost in self.neighbours[current_vertex]:
                alternative_route = distances[current_vertex] + cost
                if alternative_route < distances[neighbour]:
                    distances[neighbour] = alternative_route
                    previous_vertices[neighbour] = current_vertex

        path, current_vertex = deque(), dest
        while previous_vertices[current_vertex] is not None:
            path.appendleft(current_vertex)
            current_vertex = previous_vertices[current_vertex]
        if path:
            path.appendleft(current_vertex)
        return path

    
def main():
   
    startend=None
    edge1=None
    edge2=None
    edge3=None
    edge4=None
    edge5=None
    edge6=None
    with open(sys.argv[1],'r') as f: 
        startend=f.readline()
        startend=f.readline()
        edge1=f.readline()
        edge2=f.readline()
        edge3=f.readline()
        edge4=f.readline()
        edge5=f.readline()
        edge6=f.readline()

    edge1src=edge1[0]
    edge1des=edge1[2]
    edge1wgt=int(edge1[4])
    edge2src=edge2[0]
    edge2des=edge2[2]
    edge2wgt=int(edge2[4])
    edge3src=edge3[0]
    edge3des=edge3[2]
    edge3wgt=int(edge3[4])
    edge4src=edge4[0]
    edge4des=edge4[2]
    edge4wgt=int(edge4[4])
    edge5src=edge5[0]
    edge5des=edge5[2]
    edge5wgt=int(edge5[4])
    edge6src=edge6[0]
    edge6des=edge6[2]
    edge6wgt=int(edge6[4])
    
    graph2 = Graph([(edge1src,edge1des,edge1wgt), (edge2src,edge2des,edge2wgt),
     (edge3src,edge3des,edge3wgt),(edge4src,edge4des,edge4wgt),(edge5src,edge5des,edge5wgt),(edge6src,edge6des,edge6wgt)])

    path=list(graph2.dijkstra(startend[0], startend[2]))
   
    print(path)



if __name__ == "__main__":
    main()
