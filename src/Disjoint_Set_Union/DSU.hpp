using namespace std;
namespace DSU{
    template<class Data>
    class dsu{
    public:
        vector<Data> data;                              //数据
        vector<int> parent;                             //父节点
        vector<int> rank;                               //秩，即树的高度
        Data& operator[](int i){return data[i];}

        dsu(vector<Data> &d){                           //初始化所有结点为孤立结点
            data = d;
            parent.resize(d.size());
            rank.resize(d.size());
            for(int i = 0; i < d.size(); i++){
                parent[i] = i;
                rank[i] = 0;
            }
            size = d.size();
        }
        dsu(Data d){insert(d);}                         //初始化一个孤立结点，有数据
        int find(int i){
            if(parent[i] != i){
                parent[i] = find(parent[i]);             //路径压缩
            }
            return parent[i];
        }
        void merge(int i, int j){                       //合并两结点所在的集合
            int root_i = find(i);
            int root_j = find(j);
            if(root_i != root_j){                        //两结点不在同一集合，需要合并
                if(rank[root_i] > rank[root_j]){         //如果i的秩大于j的秩
                    parent[root_j] = root_i;
                }else if(rank[root_i] < rank[root_j]){   //如果i的秩小于j的秩
                    parent[root_i] = root_j;
                }else{                                   //如果i的秩等于j的秩
                    parent[root_j] = root_i;
                    rank[root_i]++;
                }
            }
        }
        void insert(Data i){                            //插入结点i（位于新集合）
            data.push_back(i);
            parent.push_back(data.size()-1);            //将新结点的父节点设为自己
            rank.push_back(0);                          //将新结点的秩设为0
        }
        /*void del(int i){                              //删除结点i,并清除其占用的空间
            data.erase(data.begin()+i);
            parent.erase(parent.begin()+i);
            rank.erase(rank.begin()+i);
            for(int j = 0; j < parent.size(); j++)
                if(parent[j] > i)
                    parent[j]--;
        }*/
        void del(int i){                                //删除结点i,但不清除其占用的空间（size不会改变）
            parent[i] = i;
            rank[i] = 0;
        }
        void del(Data i){del(find(i));}                 //删除内容为i的结点,并清除其占用的空间
        bool share(int i, int j){return find(i) == find(j);}//判断两结点是否在同一集合
        int size(){return data.size();}//返回集合大小

        void print(){
            cout << "data: ";
            for(int i = 0; i < data.size(); i++)
                cout << data[i] << " ";
            cout << endl;
            cout << "parent: ";
            for(int i = 0; i < parent.size(); i++)
                cout << parent[i] << " ";
            cout << endl;
            cout << "rank: ";
            for(int i = 0; i < rank.size(); i++)
                cout << rank[i] << " ";
            cout << endl;
            cout << "size: " << size() << endl;
        }

    };
}