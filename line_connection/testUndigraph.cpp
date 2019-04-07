#include <iostream>
#include <vector>
#include <string>
using namespace std;



#include "undigraph.h"


using Vertex=int;

void visit(const Vertex & v){
    cout<<v<<" ";
}



void testundigraph(){
    // vector<Edge<string>> edges={
    //     {"a","a"},
    //     {"a","b"},
    //     {"b","c"},
    //     {"b","d"},
    //     {"e","f"}};
    
    vector<Edge<Vertex>> edges={
        {1,1},
        {1,2},
        {2,3},
        {3,4},
        {5,6},
        {5,5},
        {6,6},
        {7,8},
        {8,9},
        {10,11},
        // {11,1},
        // {1,8},
        // {2,5},
        {11,12}
        };
    Undigraph<Vertex> G;
    for(int i=0;i<edges.size();i++){
        Edge<Vertex> & e=edges[i];
        G.InsertEdge(e.v1, e.v2);
    }
    G.Show();
    

    cout<<"connected="<<(G.IsConnected()?"true":"false")<<endl;
    vector<vector<Vertex>> paths = G.GetConnectedComponetVertexByBFSTraverse();
    cout<<"BFSTraverse"<<endl;
    for(const auto & path :paths){
        
        for(const auto & v :path){
            cout<<v<<" ";
        }
        cout<<endl;
    }

    cout<<"Get Connected Componets"<<endl;
    vector<Undigraph<Vertex> > components = G.GetConnectedComponets();

    int i=0;
    for(const auto & c : components){
        cout<<"ConnectedComponet["<<i++<<"]"<<endl;
        c.Show();
    }
}
int main(){
    
    testundigraph();
    return 0;
}