#include<iostream>
#include <list>
#include<queue>
#include<stack>
using namespace std;

class Adjacency
{
private:
	list<int> adjList;
	int size;
public:
	Adjacency() {}
	Adjacency(int V) {}
	void push(int data)
	{
		adjList.push_back(data);
		size++;
	}
	void print()
	{
		for (auto const& i : adjList)
			cout << " -> " << i;
	}
	void printArray()
	{
		for (auto const& i : adjList)
			cout << i << " ";
	}
	int getSize() { return adjList.size(); }
	int getElement(int idx)
	{
		auto it = adjList.begin();
		advance(it, idx);
		return *it;
	}
};

class Graph
{
private:
	int V;
	Adjacency* adj;
	bool* visited;
public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
		visited = new bool[V];
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}

	//Heling functions------------------------------------
	void Travel(int u, int dd[], stack<int>& res)
	{
		dd[u] = 1;
		for (int i = 0; i < adj[u].getSize(); i++)
		{
			int v = adj[u].getElement(i);
			if (dd[v] == 0)
				Travel(v, dd, res);
		}
		res.push(u);
	}

	void topologicalSort() {
		int dd[1010];
		for (int i = 0; i < V; i++)
			dd[i] = 0;
		stack<int> res;
		for (int i = 0; i < V; i++)
			if (dd[i] == 0)
				Travel(i, dd, res);
		while (!res.empty())
		{
			cout << res.top() << " ";
			res.pop();
		}
	}
	//-------------------------------------------------

	void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}

	Adjacency* BFS(int v)
	{
		Adjacency* my_adj = new Adjacency(V);
		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		// Create a queue for BFS
		list<int> queue;

		// Mark the current node as visited and enqueue it
		visited[v] = true;
		queue.push_back(v);


		while (!queue.empty())
		{
		
			v = queue.front();
			//cout << v << " ";	//Add code here---------------------------------
			my_adj->push(v);
			queue.pop_front();

			for (int i = 0; i < adj[v].getSize(); i++) {
				int temp = adj[v].getElement(i);
				if (!visited[temp])
				{
					visited[temp] = true;
					queue.push_back(temp);
				}
			}
		}
		return my_adj;
	}

	void MyDFS(int v, Adjacency *a, bool *visited) {
		// Mark the current node as visited and
		// print it
		visited[v] = true;
		//cout << v << endl;
		a->push(v);

		// Recur for all the vertices adjacent
		// to this vertex

		for (int i = 0; i < adj[v].getSize(); i++) {
			int temp = adj[v].getElement(i);
			if (!visited[temp]) {
				MyDFS(temp, a, visited);
			}
		}
	}

	Adjacency* DFS(int v)
	{
		Adjacency* my_adj = new Adjacency(V);
		bool* visited = new bool[V];
		for (int i = 0; i < V; i++)
		{
			visited[i] = false;
		}
		
		MyDFS(v, my_adj, visited);

		return my_adj;
	}

	
};


class DirectedGraph
{
	int V;
	list<int>* adj;
	bool isCyclicUtil(int v, bool visited[], bool* rs);
public:
	DirectedGraph() {
		V = 0;
		adj = NULL;
	}
	DirectedGraph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}

	bool isCyclicUtil(int v, bool visited[], bool* recStack)
	{
		if (visited[v] == false)
		{
			// Mark the current node as visited and part of recursion stack
			visited[v] = true;
			recStack[v] = true;

			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
			{
				if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
					return true;
				else if (recStack[*i])
					return true;
			}

		}
		recStack[v] = false;  // remove the vertex from recursion stack
		return false;
	}

	bool isCyclic()
	{
		// Mark all the vertices as not visited and not part of recursion
		// stack
		bool* visited = new bool[V];
		bool* recStack = new bool[V];
		for (int i = 0; i < V; i++)
		{
			visited[i] = false;
			recStack[i] = false;
		}

		// Call the recursive helper function to detect cycle in different
		// DFS trees
		for (int i = 0; i < V; i++)
			if (isCyclicUtil(i, visited, recStack))
				return true;

		return false;
	}
};

struct Graph
{
	int V, E;
	vector< pair<int, pair<int, int>> > edges;
	// Constructor 
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
	}

	//YOUR CODE HERE
	int find(int p[], int i)
	{
		if (p[i] != i)
		{
			p[i] = find(p, p[i]);
			return p[i];
		}
		else
			return i;
	}


	int kruskalMST() {
		// TODO: return weight of the minimum spanning tree.
		int p[100];
		for (int i = 0; i < V; i++)
		{
			p[i] = i;
		}
		int count = 0, res = 0;
		sort(edges.begin(), edges.end());
		for (size_t i = 0; i < edges.size(); i++)
		{
			int t = find(p, edges[i].second.first), v = find(p, edges[i].second.second);
			if (t != v)
			{
				p[t] = v;
				count++;
				res += edges[i].first;
				if (count == V - 1)
					return res;
			}
		}
		return -1;
	}
};

typedef pair<int, int> iPair;
int Dijkstra(int** graph, int src, int dst) {
	priority_queue<iPair, vector <iPair>, greater<iPair>> pq;
	int dist[100];
	for (int i = 0; i < 10; i++) {
		dist[i] = 1000000000;
	}

	pq.push(make_pair(0, src));
	dist[src] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		//list< pair<int, int> >::iterator i;
		for (int i = 0; i <= 5; ++i)
		{
			int v = i;
			int weight = graph[u][i];
			if (weight == 0) {
				continue;
			}
			if (dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	return dist[dst];
}

int main() {
	DirectedGraph g(8);
	int edege[][2] = { {0,6}, {1,2}, {1,4}, {1,6}, {3,0}, {3,4}, {5,1}, {7,0}, {7,1} };

	for (int i = 0; i < 9; i++)
		g.addEdge(edege[i][0], edege[i][1]);

	if (g.isCyclic())
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";
	return 0;
}