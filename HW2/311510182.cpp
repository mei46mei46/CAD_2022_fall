#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]){

    ifstream in(argv[1]);
    ifstream in_pat(argv[3]);
    ifstream in_lib(argv[5]);

    string file_name = argv[1];
    string sub_file_name = file_name.substr(0,file_name.size()-2);
    
    ofstream out_load("311510182_"+sub_file_name+"_load.txt");
    ofstream out_delay("311510182_"+sub_file_name+"_delay.txt");
    ofstream out_path("311510182_"+sub_file_name+"_path.txt");

    Graph *gp = new Graph();
    gp->parser(in);
    gp->pat_parser(in_pat);
    gp->lib_parser(in_lib);
    gp->cal_OutputLoad(out_load);
    gp->run(out_delay, out_path);
    
    return 0;
}