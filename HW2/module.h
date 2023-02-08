#ifndef MODULE_H
#define MODULE_H

#include <vector>

using namespace std;

class Node{
 public:
    Node(string type_="",string name_="") : type(type_), name(name_), in1("none"), in2("none"), out("none"), out_load(0.0), logic(-1), in_degree(0), control("none"), choose_path_max("none"), total_max_delay(0.0){ }
    ~Node() { }
    string type,name;
    string in1,in2,out;
    double out_load;
    int logic; //
    vector<Node*> in_graph;
    vector<Node*> out_graph;
    int in_degree; //
    string control; //
    double total_max_delay; //
    double tran; //
    double delay; //
    string choose_path_max; //
};

class Arc{
 public:
    Arc(string type_="",string name_="") : type(type_), name(name_), start("none"),  logic(-1), total_max_delay(0.0), tran(0.0){ }
    ~Arc() { }
    int logic; //
    string type,name;
    string start;
    vector<string> tail;
    vector<string> tail_type;
    //map<string,string> nodeName2pin;
    double total_max_delay; //
    double tran; //
    //double delay;
};


struct Lib{
    string type;
    double cap_a1,cap_a2,cap_zn;
    vector<vector<double> > c_rise;
    vector<vector<double> > c_fall;
    vector<vector<double> > t_rise;
    vector<vector<double> > t_fall;
};



#endif 