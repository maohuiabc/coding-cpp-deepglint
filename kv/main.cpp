#include "kv.h"
#include <utility>
#include <vector>
#include <set>
#include <thread>
using namespace std;

bool running = true;
void thr1_add_data(KV * kv, int interval){
    int i=0;
    while(running){
        char k[64];
        char v[64];
        char line[128];
        sprintf(k,"thr1_k%d",i);
        sprintf(v,"thr1_v%d",i);
        sprintf(line,"--------thr 1 --- %d ----------\n",i);
        cout<<line;
        kv->Set(k,v);
        //kv->Show();
        std::chrono::milliseconds du(interval);
        std::this_thread::sleep_for(du);
        i++;
    }
}

void thr2_add_data(KV * kv, int interval){
    int i=0;
    while(running){
        char k[64];
        char v[64];
        char line[128];
        sprintf(k,"thr2_k%d",i);
        sprintf(v,"thr2_v%d",i);

        sprintf(line,"--------thr 2 --- %d ----------\n",i);
        cout<<line;
        kv->Set(k,v);
        //kv->Show();
        std::chrono::milliseconds du(interval);
        std::this_thread::sleep_for(du);
        i++;
    }
}

void thr3_show_data(KV * kv, int interval){
    int i=0;
    while(running){
        char k[64];
        char v[64];
        char line[128];
        sprintf(k,"thr2_k%d",i);
        sprintf(v,"thr2_v%d",i);

        sprintf(line,"--------thr 3 --- %d ----------\n",i);
        cout<<line;
        //kv->Set(k,v);
        kv->Show();
        std::chrono::milliseconds du(interval);
        std::this_thread::sleep_for(du);
        i++;
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

    KV kv(20,10000);
    std::thread thr1(&thr1_add_data,&kv,100);
    std::thread thr2(&thr2_add_data,&kv,200);
    std::thread thr3(&thr3_show_data,&kv,1000);

    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}