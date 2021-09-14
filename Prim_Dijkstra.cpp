#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2147483647

struct Node{
    int key;
    std::vector<std::pair<int, int>> node;
    //first => destnation; second => total cost, edge weight
};

struct Graph{
    int V;
    Node* E;
};

void addEdge(Graph& graph, int vertex1, int vertex2, int weight){
    if (vertex1 >= graph.V || vertex2 >= graph.V)
        return;
    graph.E[vertex1].node.push_back({vertex2, weight});
    graph.E[vertex2].node.push_back({vertex1, weight});
}

Graph initGraph(int vertices){
    Node *Edges = new Node[vertices];
    for (int i = 0; i < vertices; i++)
        Edges[i].key = i;
    Graph out;
    out.E = Edges;
    out.V = vertices;
    return out;
}

Graph setValueGraph(){
    int v, e; std::cin >> v >> e;
    Node *Edges = new Node[v];
    for (int i = 0; i < v; i++)
        Edges[i].key = i;
    Graph out;
    out.E = Edges;
    out.V = v;
    for (int i = 0; i < e; i++){
        int u, w, cost; std::cin >> u >> w >> cost;
        addEdge(out, u, w, cost);
    }
    return out;
}

void free(Graph graph){
    delete[] graph.E;
}

void print(Graph graph){
    for (int i = 0; i < graph.V; i++){
        for (int j =0; j < graph.E[i].node.size(); j++){
            std::cout << '[' << i << "] -" << graph.E[i].node[j].second << "- [" << graph.E[i].node[j].first << "]" << std::endl;  
        }
        std::cout << std::endl;
    }
}

int find(std::vector<int> arr, int key){
    for (int i = 0; i < arr.size(); i++){
        if (arr[i] == key) return i; 
    }
    return -1;
}

Graph PrimMST(Graph graph, int root){
    Graph F = initGraph(graph.V);
    int *C = new int[graph.V]; //current cost 
    for (int i = 0; i < graph.V; i++){
        C[i] = INF;
    }
    int *parent= new int[graph.V];
    std::vector<int> Q; //queue for unvisited node
    Q.push_back(root); parent[root] = 0;
    for (int i = 0; i < graph.V; i++){
        if (i == root) continue;
        Q.push_back(i);
    }
    while(!Q.empty()){
        //peek queue
        int u = Q.front();
        Q.erase(Q.begin());
        //find minimum cost
        for (int v = 0; v < graph.E[u].node.size(); v++){
            int j = find(Q, graph.E[u].node[v].first);
            if (j >= 0 && graph.E[u].node[v].second < C[graph.E[u].node[v].first]){
                C[graph.E[u].node[v].first] = graph.E[u].node[v].second;
                parent[graph.E[u].node[v].first] = u;
                //swap to the first pos so the next node is somewhat smallest cost
                std::swap(Q[0], Q[j]);
            }
        }
    }
    for (int i = 0; i < graph.V; i++){
        if (i == root) continue;
        addEdge(F, i, parent[i], C[i]);
    }
    return F;
}

std::pair<int*, int*> Dikstra(Graph graph, int root){
    int *C = new int[graph.V]; //current cost 
    for (int i = 0; i < graph.V; i++){
        C[i] = INF;
    }
    int *parent= new int[graph.V]; //last node
    std::vector<int> Q; //queue for unvisited node
    Q.push_back(root); parent[root] = 0; C[root] = 0;
    for (int i = 0; i < graph.V; i++){
        if (i == root) continue;
        Q.push_back(i);
    }
    while(!Q.empty()){
        //peek queue
        int u = Q.front();
        Q.erase(Q.begin());
        //find minimum cost
        //std::cout << std::endl << u << std::endl;
        int i = 0; int min = INF; int min_pos = 0;
        for (int v = 0; v < graph.E[u].node.size(); v++){
            int j = find(Q, graph.E[u].node[v].first);
            int dis = graph.E[u].node[v].second + C[u];
            //std::cout << graph.E[u].node[v].first << "\t" << dis << " " << C[graph.E[u].node[v].first] << std::endl;
            if (dis < C[graph.E[u].node[v].first]){
                C[graph.E[u].node[v].first] = dis;
                parent[graph.E[u].node[v].first] = u;
                if(graph.E[u].node[v].second < min && j >= 0){
                    min_pos = i;
                    min = graph.E[u].node[v].second;
                }
                //swap to the first pos so the next node is somewhat smallest cost
                if(j >= 0)
                    std::swap(Q[i], Q[j]); i++;
            }

        }
        std::swap(Q[0], Q[min_pos]);
    
    }
    //distance
    for (int i = 0; i < graph.V; i++)
        std::cout << C[i] << '\t';
    std::cout << std::endl;
    //last conected node
    for (int i = 0; i < graph.V; i++)
        std::cout << parent[i] << '\t';  
    return {C, parent};
}

int main(){
    // Graph G = initGraph(9);
    // addEdge(G, 0, 8, 4);
    // addEdge(G, 0, 1, 3);
    // addEdge(G, 0, 3, 2);
    // addEdge(G, 1, 7, 4);
    // addEdge(G, 2, 3, 6);
    // addEdge(G, 2, 7, 2);
    // addEdge(G, 2, 5, 1);
    // addEdge(G, 3, 4, 1);
    // addEdge(G, 4, 8, 8);
    // addEdge(G, 5, 6, 8);

    Graph G = setValueGraph();

    print(G);
    Graph F = PrimMST(G, 0);
    print(F);
    Dikstra(G, 1);
    free(G); free(F);
}