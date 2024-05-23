#include<iostream>
#include <vector>
#include<queue>
#include<omp.h>
using namespace std;
class Graph{
    int V;
    vector<vector<int>> adj;
    public:
    Graph(int V)
    {
       this->V=V;
       adj.resize(V);
    }
    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void parallelBFS(int source)
    {
        vector<bool> visited(V,false);
        queue<int> q;
        visited[source]=true;
        q.push(source);
        while(!q.empty())
        #pragma omp parallel
        {
            
            #pragma omp parallel for
            for(int i=0;i<q.size();i++)
            {
                int u=q.front();
                q.pop();
                cout<<u<<" ";
                for(int v:adj[u])
                {
                    if(!visited[v])
                    {
                        visited[v]=true;
                        q.push(v);
                    }

                }

            }

        }
    }
    void paralleldfsUtil(int v,vector<bool> &visited)
    {
        visited[v]=true;
        cout<<v<<" ";
        #pragma omp parallel for
        for(int i=0;i<adj[v].size();i++)
        {
            int u=adj[v][i];
            if(!visited[u])
            {
                paralleldfsUtil(u,visited);
            }
        }


    }
    void parallelDFS(int source)
    {
        vector<bool> visited(V,false);
        paralleldfsUtil(source,visited);
    }

};
int main()
{
  Graph g(6);
  g.addEdge(0,1);
  g.addEdge(0,2);
  g.addEdge(1,3);
  g.addEdge(1,4);
  g.addEdge(3,5);
  g.addEdge(4,5);
  g.addEdge(2,4);
  cout<<"Parallel BFS : "<<endl;
  g.parallelBFS(0);
  cout<<"Parallel DFS : "<<endl;
  g.parallelDFS(0);
  return 0;
}