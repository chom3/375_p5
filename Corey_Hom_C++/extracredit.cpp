#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

//In the following algorithm, the code u := vertex in Q with min dist[u],
//searches for the vertex u in the vertex set Q that has the least dist[u] value. length(u, v)
int minDist(vector<int> dist, vector<bool> previous)
{
    int min = INT_MAX;
    int index = 0;
    for (int i = 0; i < 11; i++)
    {
        if (previous[i] == false && dist[i] <= min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
int main(){
    //create a matrix
    vector<vector<int> > matrix(15);
    for ( int i = 0 ; i < 15 ; i++ ){
        matrix[i].resize(15);
    }
    
    //hardcode into the matrix
    //all the nodes
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    int g = 6;
    int h = 7;
    int i = 8;
    int j = 9;
    int k = 10;
    //the nodes and their edges
    matrix[a][j] = 1;
    matrix[a][i] = 15;
    matrix[a][e] = 12;
    matrix[a][g] = 21;
    matrix[a][b] = 5;
    matrix[b][j] = 20;
    matrix[b][g] = 18;
    matrix[b][c] = 9;
    matrix[c][g] = 17;
    matrix[c][d] = 16;
    matrix[c][k] = 8;
    matrix[d][g] = 11;
    matrix[d][h] = 14;
    matrix[d][f] = 7;
    matrix[e][g] = 2;
    matrix[e][i] = 10;
    matrix[e][f] = 6;
    matrix[f][k] = 13;
    matrix[f][j] = 19;
    matrix[g][h] = 3;
    //pseudocode from wikipedia
    //initialize dijkstra algorithm
    //initialize vectors
    //initialize distance to max distance and every node as undefined
    vector<int> path;
    vector<int> dist(12);
    vector<bool> previous(12);
    //we start at node d and find the shortest distance to node a by traversing the matrix
    //push those possible nodes into the vector path
    for (int i =0; i < 11; i++)
    {
        if (dist[i] != d){
            dist[i] = INT_MAX;
        }
        previous[i] = false;
    }
    dist[d] = 0;
     //initialize int u to find minDist (source node in first case)
     for (int i = 0; i < 11; i++)
     {
         //find min distance
         int u = minDist(dist, previous);
         
         //we visited this node
         previous[u] = true;
         
         //for each neight v of u
         //find the shorter path
         //we update the value of dist
         for (int j = 0; j < 11; j++)
         {
             //condition to update dist if the edge and weight is smaller than what it currently is
             if (!previous[j] && matrix[u][j] && dist[u] != INT_MAX && dist[u]+matrix[u][j] < dist[j]){
                 dist[j] = dist[u] + matrix[u][j];
             }
         }
     }
     
     //print out and check
     for (int i = 0; i < 11; i++){
         cout << i << " " << dist[i] << endl;
     }
}