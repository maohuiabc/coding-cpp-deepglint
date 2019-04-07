#ifndef undigraph_H
#define undigraph_H

#include <functional>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

template<class TVertex> 
struct Edge{
    TVertex v1;
    TVertex v2;
};

template<class TVertex>
class Undigraph{
public:
    
    //插入边
    void InsertEdge(const TVertex & v1, const TVertex & v2){
        m_adjacency[v1].insert(v2);
        m_adjacency[v2].insert(v1);
    }

    //插入边
    void InsertEdge(const Edge<TVertex> & e){
        InsertEdge(e.v1,e.v2);
    }
    //插入边
    void InsertEdge(const vector<Edge<TVertex>> & edges){
        for(const auto & e : edges){
            InsertEdge(e.v1,e.v2);
        }
    }

    //打印邻接表
    void Show() const {
        for(const auto& s : m_adjacency){
            cout<<s.first<<": ";
            for(const auto& v :s.second){
                cout<<v<<" ";
            }
            cout<<endl;
        }
    }

    //深度优先遍历
    vector<vector<TVertex>>  DFSTraverse(std::function<void(const TVertex & v1)> f_visit){
        //TODO
    }

    //广度优先遍历
    vector<vector<TVertex>> BFSTraverse(std::function<void(const TVertex & v1)> f_visit){
        //TODO
    }
    
    //广度优先遍历获取各连通分量的顶点列表
    vector<vector<TVertex>> GetConnectedComponetVertexByBFSTraverse(){
        unordered_set<TVertex> visited;
        queue<TVertex> q;
        vector<vector<TVertex>> res;
        for(const auto & s : m_adjacency){
            if(!visited.count(s.first)){
                vector<TVertex> path;
                path.push_back(s.first);
                visited.insert(s.first);
                q.push(s.first);
                while(!q.empty()){
                    auto & v= q.front();
                    q.pop();
                    for(const auto & w : m_adjacency[v]){
                        if(!visited.count(w)){
                            path.push_back(w);
                            visited.insert(w);
                            q.push(w);

                        }
                    }
                }
                res.push_back(path);
            }
        }
        return res;
    }
    

    //获取连通分量
    vector<Undigraph> GetConnectedComponets(){
        vector<Undigraph>  res;
        auto com_vertexs = GetConnectedComponetVertexByBFSTraverse();
        for(const auto & c : com_vertexs){
            Undigraph g;
            for(const auto & v : c){
                g.m_adjacency[v] = this->m_adjacency[v];
            }
            res.push_back(g);
            
        }
        return res;
    }

    //显示连通分量邻接表
    void ShowConnectedComponets(){
        vector<Undigraph> coms = GetConnectedComponets();
        
    }

    //是否是连通图
    bool IsConnected(){
        if(m_adjacency.size()==0)return false;
        unordered_set<TVertex> visited;
        queue<TVertex> q;
        int count = 0;
        for(const auto & s : m_adjacency){
            if(!visited.count(s.first)){
                if(count)return false;
                count++;
                visited.insert(s.first);
                q.push(s.first);
                while(!q.empty()){
                    auto & v= q.front();
                    q.pop();
                    for(const auto & w : m_adjacency[v]){
                        if(!visited.count(w)){
                            visited.insert(w);
                            q.push(w);

                        }
                    }
                }
            }
        }
        return true;
    }
private:
    unordered_map<TVertex , unordered_set<TVertex > > m_adjacency;
  
};


#endif