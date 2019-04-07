#include "kv.h"
#include <utility>
#include <vector>
#include <set>
using namespace std;

bool running = true;
void thr1_add_data(KV & kv){
    int i=0;
    while(running){
        char k[64];
        char v[64];
        sprintf(k,"thr1_k%d",i);
        sprintf(v,"thr1_v%d",i);

        cout<<"--------thr1---"<<i<<"-----------"<<endl;
        kv.Set(k,v);
        kv.Show();
        std::chrono::milliseconds du(200);
        std::this_thread::sleep_for(du);
    }
}
void thr2_add_data(KV & kv){
    int i=0;
    while(running){
        char k[64];
        char v[64];
        sprintf(k,"thr2_k%d",i);
        sprintf(v,"thr2_v%d",i);

        cout<<"--------thr2---"<<i<<"-----------"<<endl;
        kv.Set(k,v);
        kv.Show();
        std::chrono::milliseconds du(200);
        std::this_thread::sleep_for(du);
    }
}

void test(){
    vector<std::pair<string,string> > data ={
        {string("k0"),string("v0")},
        {string("k1"),string("v1")},
        {string("k2"),string("v2")},
        {string("k3"),string("v3")},
        {string("k0"),string("v0")},
        {string("k2"),string("v2")},
        {string("k4"),string("v4")},
        {string("k5"),string("v5")},
        {string("k6"),string("v6")},
        {string("k7"),string("v7")},
        {string("k0"),string("v0")},
        {string("k8"),string("v8")},
        {string("k3"),string("v3")},
        {string("k9"),string("v9")}
    };
    set<string> s;
    for(const auto & p : data){
        s.insert(p.first);
    }
    
    KV kv(5,500);
    for(int i=0;i<data.size();i++){
        cout<<"-----------"<<i<<"-----------"<<endl;
        kv.Set(data[i].first,data[i].second);
        kv.Show();
        std::chrono::milliseconds du(200);
        std::this_thread::sleep_for(du);
    }

    cout<<"-----------Get-----------"<<endl;
    for(const auto & k : s){
        V v= kv.Get(k);
        cout<<k<<":"<<v<<endl;

        kv.Show();
        std::chrono::milliseconds du(200);
        std::this_thread::sleep_for(du);
    }
}
int main(){
    KV kv(100,1000);
    std::thread thr1(thr1_add_data,kv);
    std::thread thr2(thr1_add_data,kv);

    return 0;
}