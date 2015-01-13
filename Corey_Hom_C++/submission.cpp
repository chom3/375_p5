#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//can put the edges in a vector and sort by similarity
struct Edge{
    int start;
    int end;
    int sim;
};
//function for sort to sort the vector by the sim value
bool compareSim(const Edge& a, const Edge& b)
{
    return a.sim > b.sim;
}
//struct to represent the set from MAKE-SET
//disjoint data set find, merge
struct MakeSet
{
    int parent;
    int rank;
};

//Find: Determine which subset a particular element is in. 
//Find typically returns an item from this set that serves as its "representative"; 
//by comparing the result of two Find operations, 
//one can determine whether two elements are in the same subset. (from Wikipedia, pseudocode also)
//improved Find
int find(vector<MakeSet> sets, int i)
{
    if (sets[i].parent != i)
    {
        sets[i].parent = find(sets, sets[i].parent);
    }
    return sets[i].parent;
}

//function Union: Join two subsets into a single subset. (from Wikipedia, pseudocode also)
void Union(vector<MakeSet> sets, int x, int y)
{
    int xRoot = find(sets, x);
    int yRoot = find(sets, y);
    if (xRoot == yRoot)
    {
        //return nothing
    }
    //x and y are not already in same set. Merge them
    if (sets[xRoot].rank < sets[yRoot].rank)
    {
        sets[xRoot].parent = yRoot;
    }
    else if (sets[xRoot].rank > sets[yRoot].rank)
    {
        sets[yRoot].parent = xRoot;
    }
    else
    {
        sets[yRoot].parent = xRoot;
        sets[xRoot].rank = sets[xRoot].rank + 1;
    }
}
int main(){
    //make a vector
    vector<Edge> s(39);
    //insert edges
    s[0].start = 1; s[0].end = 2; s[0].sim = 80;
    s[1].start = 5; s[1].end = 9; s[1].sim = 73; 
    s[2].start = 9;s[2].end = 13;s[2].sim = 69;
    s[3].start = 2;s[3].end = 3;s[3].sim = 10;
    s[4].start = 5;s[4].end = 7;s[4].sim = 20;
    s[5].start = 5;s[5].end = 2;s[5].sim = 74;
    s[6].start = 9;s[6].end = 18;s[6].sim = 15;
    s[7].start = 13;s[7].end = 14;s[7].sim = 21;
    s[8].start = 9;s[8].end = 1;s[8].sim = 92;
    s[9].start = 13;s[9].end = 2;s[9].sim = 59;
    s[10].start = 20;s[10].end = 4;s[10].sim = 6;
    s[11].start = 18;s[11].end = 17;s[11].sim = 17;
    s[12].start = 11;s[12].end = 3;s[12].sim = 74;
    s[13].start = 7;s[13].end = 18;s[13].sim = 83;
    s[14].start = 7;s[14].end = 12;s[14].sim = 27;
    s[15].start = 1;s[15].end = 10;s[15].sim = 16;
    s[16].start = 5;s[16].end = 15;s[16].sim = 47;
    s[17].start = 20;s[17].end = 14;s[17].sim = 94;
    s[18].start = 14;s[18].end = 18;s[18].sim = 77;
    s[19].start = 2;s[19].end = 4;s[19].sim = 30;
    s[20].start = 11;s[20].end = 14;s[20].sim = 62;
    s[21].start = 3; s[21].end = 20; s[21].sim = 85; 
    s[22].start = 11;s[22].end = 7;s[22].sim = 62;
    s[23].start = 6;s[23].end = 10;s[23].sim = 87;
    s[24].start = 12;s[24].end = 15;s[24].sim = 81;
    s[25].start = 3;s[25].end = 19;s[25].sim = 39;
    s[26].start = 9;s[26].end = 8;s[26].sim = 45;
    s[27].start = 19;s[27].end = 4;s[27].sim = 65;
    s[28].start = 8;s[28].end = 16;s[28].sim = 70;
    s[29].start = 15;s[29].end = 17;s[29].sim = 64;
    s[30].start = 1;s[30].end = 11;s[30].sim = 32;
    s[31].start = 11;s[31].end = 6;s[31].sim = 43;
    s[32].start = 12;s[32].end = 6;s[32].sim = 87;
    s[33].start = 12;s[33].end = 19;s[33].sim = 70;
    s[34].start = 7;s[34].end = 16;s[34].sim = 39;
    s[35].start = 13;s[35].end = 6;s[35].sim = 22;
    s[36].start = 4;s[36].end = 16;s[36].sim = 68;
    s[37].start = 17;s[37].end = 10;s[37].sim = 56;
    s[38].start = 19;s[38].end = 15;s[38].sim = 71;
    
    // //check values to make sure correct
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << "S(p" << s[i].start << ", p" << s[i].end << ") = " << s[i].sim << endl;
    // }
    
    //sort the vector (graph) in non-increasing order
    sort(s.begin(), s.end(), compareSim);
    
    
    // //check if in non-increasing order (descending)
    // for (int i = 0; i < s.size(); i++)
    // {
    //     cout << "S(p" << s[i].start << ", p" << s[i].end << ") = " << s[i].sim << endl;
    // }
    
    
    //now make a MST with the given points
    // KRUSKAL(G): FROM WIKIPEDIA
    //     1 A = ∅
    //     2 foreach v ∈ G.V:
    //     3   MAKE-SET(v)
    //     4 foreach (u, v) ordered by weight(u, v), increasing:
    //     5    if FIND-SET(u) ≠ FIND-SET(v):
    //     6       A = A ∪ {(u, v)}
    //     7       UNION(u, v)
    //     8 return A
    
    //create subsets with single elements
    vector<MakeSet> sets(20);
 
    //create 20 subsets for 20 vertices
    for (int v = 0; v < 20; v++)
    {
        sets[v].parent = v;
        sets[v].rank = 0;
    }
    
    //step 4
    //initialize index variable, want to start at largest edge
    int a = 0;
    //initialize vector that will hold MST, will have 19 edges
    vector<Edge> MST (19);
    //initialize index variable for the MST next edge
    int e = 0;
    //number of edge has to be equal to # of vertices - 1, 20 - 1 = 19
    while (e < 19)
    {
        //pick largest edge. check if it forms a cycle, exclude it if it does.
        //increment index for next edge
        struct Edge next = s[a++];
        
        //find set of both u and v
        int u = find(sets, next.start);
        int v = find(sets, next.end);
        //5. if FIND-SET(u) != FIND-SET(v)
        if (u != v)
        {
            MST[e++] = next;
            Union(sets, u, v);
        }
    }
    
    //print out resulting MST
    // for (int i = 0; i < MST.size(); i++)
    // {
    //     cout << "S(p" << MST[i].start << ", p" << MST[i].end << ") = " << MST[i].sim << endl;
    // }
    
    //given that it must be 3 disjoint data sets
        vector<int> p1;
        vector<int> p2;
        vector<int> p3;
        int start = MST[0].start;
        int check = 0;
    //algorithm to print push all the nodes that are connected together
    while (check != start ){
            for (int i = 0; i < MST.size(); i++){
                if (start == MST[i].end)
                {
                    check = MST[0].start;
                    p1.push_back(start);
                    start = MST[i].start;
                }
                else if (start == MST[i].start)
                {
                    check = MST[0].start;
                    p1.push_back(start);
                    start = MST[i].end;
                }
            }
            
    }
    //sort and unique the vector p1, that is the first set
    std::vector<int>::iterator it;
    sort (p1.begin(), p1.end());
    it = unique(p1.begin(), p1.end());
    p1.resize(std::distance(p1.begin(),it));
    //check
    // for (int i = 0; i < p1.size(); i++)
    // {
    //     cout << p1[i] << endl;
    // }
    
    //we'll make the vertices in the MST to be -1 so that we know we explored it already
    for (int i = 0; i < p1.size(); i++){
        for (int j = 0; j < MST.size(); j++){
            if (p1[i] == MST[j].start || p1[i] == MST[j].end){
                MST[j].start = -1;
                MST[j].end = -1;
                MST[j].sim = -1;
            }
        }
    }
    //re-sort the MST 
    sort(MST.begin(), MST.end(), compareSim);
    //we will pop all the -1 values to shrink the vector that holds the MST
    int counter = 0;
    for (int i = 0; i < MST.size(); i++)
    {
        if (MST[i].start == -1){
            counter++;
        }
    }
    for (int i = 0; i < counter;i++){
        MST.pop_back();
     }
    // for (int i = 0; i < MST.size(); i++)
    // {
    //     cout << "S(p" << MST[i].start << ", p" << MST[i].end << ") = " << MST[i].sim << endl;
    // }
    
    //now we move on to the second graph
    start = MST[0].start;
    check = 0;
    while (check != start ){
            for (int i = 0; i < MST.size(); i++){
                    if (start == MST[i].end)
                    {
                        check = MST[0].start;
                        p2.push_back(start);
                        start = MST[i].start;
                    }
                    else if (start == MST[i].start)
                    {
                        check = MST[0].start;
                        p2.push_back(start);
                        start = MST[i].end;
                    }
        }
    }
    //sort and unique the vector p1, that is the second set
    sort (p2.begin(), p2.end());
    it = unique(p2.begin(), p2.end());
    p2.resize(std::distance(p2.begin(),it));
    // for (int i = 0; i < p2.size(); i++)
    // {
    //     cout << p2[i] << endl;
    // }
    
    //we'll make the vertices in the MST to be -1 so that we know we explored it already
    for (int i = 0; i < p2.size(); i++){
        for (int j = 0; j < MST.size(); j++){
            if (p2[i] == MST[j].start || p2[i] == MST[j].end){
                MST[j].start = -1;
                MST[j].end = -1;
                MST[j].sim = -1;
            }
        }
    }
    //re-sort the MST 
    sort(MST.begin(), MST.end(), compareSim);
    //we will pop all the -1 values to shrink the vector that holds the MST
    counter = 0;
    for (int i = 0; i < MST.size(); i++)
    {
        if (MST[i].start == -1){
            counter++;
        }
    }
    for (int i = 0; i < counter;i++){
        MST.pop_back();
     }
    // for (int i = 0; i < MST.size(); i++)
    // {
    //     cout << "S(p" << MST[i].start << ", p" << MST[i].end << ") = " << MST[i].sim << endl;
    // }
    
    //now we move on to the third graph, push the remaining nodes and just unique it
    for (int i = 0; i < MST.size(); i++)
    {
        p3.push_back(MST[i].start);
        p3.push_back(MST[i].end);
    }
    //sort and unique the vector p3, that is the last set
    sort (p3.begin(), p3.end());
    it = unique(p3.begin(), p3.end());
    p3.resize(std::distance(p3.begin(),it));
    // for (int i = 0; i < p3.size(); i++)
    // {
    //     cout << p3[i] << endl;
    // }
    
    //PRINT OUT THE RESULTS
    cout << "The first group has " << p1.size() << " photos." << endl;
    cout << "The photos are: ";
    for (int i = 0; i < p1.size(); i++){
        cout << "p" << p1[i] << " ";
    }
    cout << endl;
    cout << "The second group has " << p2.size() << " photos." << endl;
    cout << "The photos are: ";
    for (int i = 0; i < p2.size(); i++){
        cout << "p" << p2[i] << " ";
    }
    cout << endl;
    cout << "The third group has " << p3.size() << " photos." << endl;
    cout << "The photos are: ";
    for (int i = 0; i < p3.size(); i++){
        cout << "p" << p3[i] << " ";
    }
    cout << endl;
}