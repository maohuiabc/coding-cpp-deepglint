#ifndef KV_H
#define KV_H

#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <chrono>
#include <time.h>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

#define N 100
typedef string K;
typedef string V;

class KV{
public:
    KV(int capcity ,long long timeout/*milliseconds*/)
        :m_capcity(capcity),
        m_timeout(timeout),
        m_running(true){
        m_thread_timeout=std::thread(&KV::ProcessTimeout,this);
    }
    ~KV(){
        m_running = false;
        m_thread_timeout.join();
    }

    V Get(const K & k){
        V res;
        m_mutex.lock();
        auto it = m_map.find(k);
        if(it!=m_map.end()){
            res = it->second->v;
        }
        m_mutex.unlock();
        return res;
    }

    void Set(const K & k, const V & v){
        m_mutex.lock();
        auto it = m_map.find(k);
        if(it==m_map.end()){
             //超过最大存储，删除最早数据
            if(m_queue.size()==m_capcity){
                auto & back = m_queue.back();
                m_map.erase(back.k);
                m_queue.pop_back();
            }
            //加入新kv
            auto tm = steady_clock::now();
            KVInfo info = {k,v,tm};
            m_queue.push_front(info);
            m_map[k] = m_queue.begin();
            
        }else{
            //
            KVInfo item = *it->second;
            item.time = steady_clock::now();
            item.v = v;
            m_queue.erase(it->second);
            m_queue.push_front(item);
            m_map[k] = m_queue.begin();
        }
        m_mutex.unlock();
    }

    size_t Size() const{
        return m_map.size();
    }

    void Show() {
        m_mutex.lock();
        cout<<"size = "<< Size() << endl;
        for(const auto & item : m_queue){
            auto tm = steady_clock::now();
            auto span = GetTimeSpan(item.time,tm);
            cout<<item.k<<":"<<item.v<<"|"<<span<<endl;
        }
        m_mutex.unlock();
    }
protected:
    //超时处理
    void ProcessTimeout(){
        while(m_running){

            time_point waikup_at;
            //auto now = steady_clock.now();

            m_mutex.lock();
            auto tm = steady_clock::now();
            for(list<KVInfo>::reverse_iterator it=m_queue.rbegin();it!=m_queue.rend();it++){
                auto span = GetTimeSpan(it->time,tm);
                if(span < m_timeout)
                    break;
                m_map.erase(it->k);
                m_queue.erase(--it.base());
            }
            if(m_queue.size()==0){
                waikup_at = tm + milliseconds(m_timeout);
            }
            m_mutex.unlock();
            std::this_thread::sleep_until(waikup_at);
        }
    }

    //时间相关
    typedef std::chrono::steady_clock steady_clock;
    typedef std::chrono::steady_clock::time_point time_point;
    typedef std::chrono::milliseconds milliseconds;
    typedef long long time_span;
    time_span GetTimeSpan(const time_point & start,const time_point &end){
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }


protected:
    struct KVInfo{
        K k;
        V v;
        time_point time;
    };
protected:
    int m_capcity;
    long long  m_timeout;
    list<KVInfo> m_queue;
    unordered_map<K, list<KVInfo>::const_iterator > m_map;
    std::mutex m_mutex;
    std::thread m_thread_timeout;
    bool m_running;
};






#endif