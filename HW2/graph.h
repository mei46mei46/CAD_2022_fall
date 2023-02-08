#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <deque>
#include <fstream>
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "module.h"

using namespace std;


class Graph
{
  friend bool compare_out_load(const Node* a,const Node* b);
  friend bool compare_delay(const Node* a,const Node* b);
 public:
   Graph() { }
   ~Graph(){}
   void parser(ifstream &in);
   void lib_parser(ifstream &in);
   void pat_parser(ifstream &in);
   void cal_OutputLoad(ofstream &out);
   void run(ofstream &out_delay,ofstream &out_path);
   
 private:
   double pat_num;
   vector<Node*> node_list;
   vector<Arc*> arc_list;
   vector<Arc*> output_list;
   map<string,Node*> name2node;
   map<string,Arc*> name2arc;
   Lib NOR2X1,INVX1,NANDX1;
   deque<Node*> undo_list;
   vector<int> pat;
   vector<string> pat_order;
   vector<double> index_cap;
   vector<double> index_tran;
   void set_InOutGraph();
   void set_initial_pat(int num);
   void cal_logic(Node* node);
   void recover();
   void longest_path(ofstream &out);
   string RemoveSpace(string str);
   vector<string> string2vec(string str);
   double calculation(double cap1, double cap2, double tran1, double tran2, double n1, double n2, double n3, double n4, double cap, double tran);
};

#endif 