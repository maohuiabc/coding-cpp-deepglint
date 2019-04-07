实现一个键值存储工具类，要求如下：
a.  有两个接口，其中K和V都是字符串，如果:
typedef string K;
typedef string V;
class KV {
public:
    V Get(K);
     void Set(K, V);
}
b.  Set会把对应的键值存储下来，如果K值已经存在，则会覆盖V值；
c.  Get会返回与K对应的V值，如果不存在则会返回空串；
d.  最多存储N条记录，如果超过N，则会删除最早的数据（以数据被修改的时间为准）；
e.  数据超过T时间没有被修改，就会被自动删除；
f.  需要尽可能高读写，且线程安全。

