#include<iostream>
#include<list>
#include<string>
#include<unordered_map>
using namespace std;


//Node to store to the data
class Node{
    public: 
        string key;
        int value;
        Node(string k,int val){
            key=k;
            value=val;
        }
};

//LRU cache data structure
class LRUCache{
    public:
        int maxSize;
        list<Node> l;
        unordered_map<string,list<Node>::iterator> m;

        LRUCache(int maxSize){
            this->maxSize= maxSize >1? maxSize : 1;
        }

        // We will implement three operations 

        void InsertKeYValue(string key,int value){

            //two cases whther the key value that is to be accssed is present in cache or not
            //present in cache
            if(m.count(key)!=0){
                
                auto it=m[key];//this will give the address of the key
                it->value=value;//updating the old value to new one
            }
            else{
                //if that key is not present in cache then we need to get it insertedin cache
                //Check if cahe is full or not 
                //if yes then remove least recently used key
                if(l.size()==maxSize){
                    Node last=l.back();
                    m.erase(last.key);
                    l.pop_back();
                    
                }

                Node n(key,value);
                l.push_front(n);
                m[key]=l.begin();
            }

        }

        int* getValue(string key){
            if(m.count(key)!=0){
                auto it=m[key];

                int value=it->value;
                l.push_front(*it);
                l.erase(it);
                m[key]=l.begin();
                return &l.begin()->value;
            }

            return NULL;
        }

        string MostRecentKey(){
            return l.front().key;
        }
};


int main(){
    LRUCache lru(3);
    lru.InsertKeYValue("Mango",10);
    lru.InsertKeYValue("apple",20);
    lru.InsertKeYValue("guava",30);
    cout<<lru.l.front().value<<endl;
    cout<<lru.MostRecentKey()<<endl;//This will give the most recent inserted in the cache
    cout<<*(lru.getValue("Mango"))<<endl;
    cout<<lru.MostRecentKey()<<endl;// As mango is the lastest updated so this will most recent key

    lru.InsertKeYValue("Mango",40);
    cout<<*(lru.getValue("Mango"))<<endl;//The value with Mango will be updated

    lru.InsertKeYValue("Banana",20);

    lru.InsertKeYValue("Starwberry",50);//As the size of cache is so the least recent used ill be popped

    if(lru.getValue("apple")==NULL){
        cout<<"apple does not exist"<<endl;
    }
    if(lru.getValue("guava")==NULL){
        cout<<"guava does not exist"<<endl;
    }
    if(lru.getValue("banana")==NULL){
        cout<<"banana does not exist"<<endl;
    }
    if(lru.getValue("Mango")==NULL){
        cout<<"Mango does not exist"<<endl;
    }

}
