#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#include "undigraph.h"

using Vertex=string;

//能连成一条线的条件为：能构成无向连通图，度为奇数的顶点的个数不大于2
bool canBeConnected(vector<Edge<Vertex>> & edges){

    //构建无向图
    Undigraph<Vertex> G;
    G.InsertEdge(edges);
    G.Show();
    bool isConnected = G.IsConnected();
    cout<<"connected="<<(isConnected?"true":"false")<<endl;
    if(isConnected){
        unordered_map<Vertex,int> m;
        //计算顶点的度
        for(const auto & e : edges){
            if(m.count(e.v1)==0){
                m[e.v1]=1;
            }else{
                m[e.v1]++;
            }
            if(m.count(e.v2)==0){
                m[e.v2]=1;
            }else{
                m[e.v2]++;
            }
        }
        //统计奇数度顶点
        int count_odd=0;
        for(const auto & v : m){
            //cout<<"count "<<v.first<<" = "<< v.second<<endl;
            if(v.second% 2!= 0){
                count_odd++;
            }
        }
        if(count_odd<=2)return true;
    }
    return false;
}

vector<Edge<Vertex>> loadData(const string & filename){
    vector<Edge<Vertex>> res;
    ifstream is = ifstream(filename);
    if (!is.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        Vertex v,w;
        while(!is.eof()){
            is>>v>>w;
            //cout<<v<<" "<<w<<endl;
            res.push_back({v,w});
        }
        
    }
    return res;
}

int main(){

    for(int i=0;i<=2;i++){
        //加载数据
        char filename[128];
        sprintf(filename,"data%d.txt",i);
        cout<<"-----------------"<<filename<<"-----------------"<<endl;
        vector<Edge<Vertex>> edges = loadData(filename);

        cout<<"canBeConnected = "<<(canBeConnected(edges)?"true":"false")<<endl;

    }
    
    return 0;
}