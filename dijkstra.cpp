#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

int g_n;


class Node;



class Edge{
    Node *targetNode;
    int weight;
    public:
    Edge(){
        targetNode = nullptr;
        weight = 0;
    }
    Edge(Node *p,double weight){
        targetNode = p;
        this->weight = weight;
    }
    ~Edge(){}


    void setWeight(int weight){ this->weight = weight;}
    int getWeight(){ return weight;}
    void setTargetNode(Node *m){ this->targetNode = m;}
    Node *getTargetNode(){ return targetNode;}

};



class Node{
    string name = "Node ";
    bool seen = false;
    int distance;
    Edge *v = new Edge[g_n];
    static int count;

public:
    vector<string> mark;

    Node(){
        count++;
        name = name + to_string(count);
        distance = 0;
        // for (int i = 0; i < g_n; i ++){
        //     v[i]= nullptr;
        // }
    }
    Node(string name){
        count++;
        this->name = name;
        distance = 0;
        // for (int i = 0; i < g_n; i ++){
        //     v[i]= nullptr;
        // }

    }
    ~Node(){
        count--;
        mark.clear();
        // for (int i = 0; i < g_n; i ++){
        //     delete v[i];
        // }
         delete []v;
    }

    void setNodeName(string m){ this->name = m;}
    string getNodeName(){ return name;}
    void setDistance(int m){ this->distance = m;}
    int getDistance(){ return distance;}
    bool getSeen(){ return seen;}
    void setSeen(bool seen){ this->seen = seen;}
    Edge *getListEdge(){ return v;}

    // void addEdge(Node *node,int weight){
       
    //     Edge *p = new Edge(node,weight);
    //     for (int i = 0; i < g_n; i ++){
    //         if( v[i] != nullptr) v[i] = p;
    //         break;
    //     }
    // }
    
};
int Node::count = 0;

Node *readFile(const char *input){
    int n;
    ifstream f(input);
    if(f.fail()){
        cout<<"Fail!"<<endl;
        exit(0);
    }
    
    f>>g_n;
    Node *a = new Node[g_n];
    for( int i = 0; i < g_n; i++){
        Edge *p = a[i].getListEdge();
            for(int j = 0; j < g_n; j++,p++){
                f>>n;
                p->setWeight(n);
                p->setTargetNode((a+j));
            }
        }
    f.close();
    return a;
}




void Dijkstra(Node *startNode){
    startNode->setSeen(true);
    int d;
    startNode->mark.push_back(startNode->getNodeName());

    Edge *p = startNode->getListEdge();
    for(int i = 0; i < g_n; i++,p++)
    {
        if(p != nullptr)
        {
            d = startNode->getDistance()+p->getWeight();

            if(!p->getTargetNode()->getSeen())
            {
            p->getTargetNode()->setDistance(d);

            for(int j = 0 ; j < startNode->mark.size(); j++)
            {
                p->getTargetNode()->mark.push_back(startNode->mark[j]); 
            }

            Dijkstra(p->getTargetNode());    

            }
            else
            {
                if(d<p->getTargetNode()->getDistance()) 
                {
                    p->getTargetNode()->setDistance(d);
                    p->getTargetNode()->mark.clear();
                    for(int j = 0 ; j < startNode->mark.size(); j++)
                    {   
                        p->getTargetNode()->mark.push_back(startNode->mark[j]); 
                    }
                    Dijkstra(p->getTargetNode());
                }
            }
        }
    }   
}





int main(int argc, char *argv[]){
    
    Node *a = readFile("input.txt");
        //Edge *p = a->getListEdge();
    Dijkstra(a);
    for(int i = 0; i < g_n; i++){
        for (int j = 0; j < a[i].mark.size(); j++){
            cout<<a[i].mark[j]<<" ";
        }
        cout<<endl;
    }
     delete []a;
 return 0;
}