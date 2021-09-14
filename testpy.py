from collections import defaultdict
class Graph:
    def __init__(self):
        self.graph = defaultdict(list)

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def bfs(self, s):
        visited = [False] * (max(self.graph) + 1)

        queue = []
        queue.append(s)
        visited[s] = True
        
        while queue:
            s = queue.pop() 
            print(s, end = " ")
            
            for i in self.graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
    
    def dfsUlil(self, v, visited):
        visited.add(v)
        print(v, end = " ")

        for neighbor in self.graph[v]:
            if neighbor not in visited:
                self.dfsUlil(neighbor, visited)

    def dfs(self, v):
        visited = set()
        self.dfsUlil(v, visited)

g = Graph()
g.addEdge(0,1)
g.addEdge(0,2)
g.addEdge(1,2)
g.addEdge(2,0)
g.addEdge(2,3)
g.addEdge(3,3)

print("Breadth first search:""(Starting from vertex 2)")
g.bfs(2)
print("\n")
print("Depth first search:""(Starting from vertex 2)")
g.dfs(2)