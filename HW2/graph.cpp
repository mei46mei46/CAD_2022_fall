
#include "graph.h"
#include "module.h"
#include <sstream>

using namespace std;

bool flag_comment;
bool flag_lineEnd;
const double dou_max = 10000000.0;

/*=====================================================================*/
/*                             < compare >                             */
/*=====================================================================*/

bool compare_out_load(const Node* a,const Node* b){
    if(a->out_load == b->out_load){
        string sub_str1, sub_str2;
        int inta, intb;
        sub_str1 = a->name.substr(1,a->name.size()-1);
        sub_str2 = b->name.substr(1,b->name.size()-1);
        inta = stoi(sub_str1);
        intb = stoi(sub_str2);
        return(inta < intb);
    }
    else{
        return(a->out_load > b->out_load);
    }
}

bool compare_delay(const Node* a,const Node* b){
    if(a->delay == b->delay){
        string sub_str1, sub_str2;
        int inta, intb;
        sub_str1 = a->name.substr(1,a->name.size()-1);
        sub_str2 = b->name.substr(1,b->name.size()-1);
        inta = stoi(sub_str1);
        intb = stoi(sub_str2);
        return(inta < intb);
    }
    else{
        return(a->delay > b->delay);
    }
}


/*=====================================================================*/
/*                             < parser >                              */
/*=====================================================================*/

void Graph::parser(ifstream &in){
    flag_comment = 0;
    flag_lineEnd = 0;
    string str,ans;
    vector<string> str_vec;
    vector<string> temp_vec;
    while(!in.eof()){
        getline(in,str);
        //cout<<str<<endl;
        ans = RemoveSpace(str);
        //cout<<ans<<endl;
        if(!ans.empty()){
            str_vec = string2vec(ans);
            temp_vec.insert(temp_vec.end(),str_vec.begin(),str_vec.end());
            if(flag_lineEnd == 1){
                if(str_vec.size() != temp_vec.size()){
                    str_vec.clear();
                    str_vec.assign(temp_vec.begin(), temp_vec.end());
                }
                temp_vec.clear();
                if(!str_vec.empty()){
                    /*for(int i=0;i<str_vec.size();i++){
                        cout<<str_vec[i]<<endl;
                    }*/
                    //cout<<endl;
                    if(str_vec[0] == "input"){
                        for(int i=1;i<str_vec.size();i++){
                            Arc* temp_arc = new Arc("input", str_vec[i]);
                            name2arc.insert(pair<string, Arc*>(temp_arc->name, temp_arc));
                            arc_list.push_back(temp_arc);   
                        }
                    }
                    else if(str_vec[0] == "output"){
                        for(int i=1;i<str_vec.size();i++){
                            Arc* temp_arc = new Arc("output", str_vec[i]);
                            name2arc.insert(pair<string, Arc*>(temp_arc->name, temp_arc));
                            arc_list.push_back(temp_arc); 
                            output_list.push_back(temp_arc);
                        }
                    }
                    else if(str_vec[0] == "wire"){
                        for(int i=1;i<str_vec.size();i++){
                            Arc* temp_arc = new Arc("wire", str_vec[i]);
                            name2arc.insert(pair<string, Arc*>(temp_arc->name, temp_arc));
                            arc_list.push_back(temp_arc);   
                        }
                    }
                    else if(str_vec[0] == "NOR2X1"){
                        Node* temp_node = new Node("NOR2X1", str_vec[1]);
                        name2node.insert(pair<string, Node*>(str_vec[1], temp_node));
                        node_list.push_back(temp_node);
                        for(int i=2;i<str_vec.size();i=i+2){
                            if(str_vec[i] == ".A1"){
                                name2arc[str_vec[i+1]]->tail.push_back(temp_node->name);
                                name2arc[str_vec[i+1]]->tail_type.push_back("A1");
                                temp_node->in1 = str_vec[i+1];
                            }
                            else if(str_vec[i] == ".A2"){
                                name2arc[str_vec[i+1]]->tail.push_back(temp_node->name);
                                name2arc[str_vec[i+1]]->tail_type.push_back("A2");
                                temp_node->in2 = str_vec[i+1];
                            }
                            else if(str_vec[i] == ".ZN"){
                                name2arc[str_vec[i+1]]->start = temp_node->name;
                                temp_node->out = str_vec[i+1];
                            }   
                        }
                    }
                    else if(str_vec[0] == "NANDX1"){
                        Node* temp_node = new Node("NANDX1", str_vec[1]);
                        name2node.insert(pair<string, Node*>(str_vec[1], temp_node));
                        node_list.push_back(temp_node);
                        for(int i=2;i<str_vec.size();i=i+2){
                            if(str_vec[i] == ".A1"){
                                name2arc[str_vec[i+1]]->tail.push_back(temp_node->name);
                                name2arc[str_vec[i+1]]->tail_type.push_back("A1");
                                temp_node->in1 = str_vec[i+1];
                            }
                            else if(str_vec[i] == ".A2"){
                                name2arc[str_vec[i+1]]->tail.push_back(temp_node->name);
                                name2arc[str_vec[i+1]]->tail_type.push_back("A2");
                                temp_node->in2 = str_vec[i+1];
                            }
                            else if(str_vec[i] == ".ZN"){
                                name2arc[str_vec[i+1]]->start = temp_node->name;
                                temp_node->out = str_vec[i+1];
                            }   
                        }
                    }
                    else if(str_vec[0] == "INVX1"){
                        Node* temp_node = new Node("INVX1", str_vec[1]);
                        name2node.insert(pair<string, Node*>(str_vec[1], temp_node));
                        node_list.push_back(temp_node);
                        for(int i=2;i<str_vec.size();i=i+2){
                            if(str_vec[i] == ".I"){
                                name2arc[str_vec[i+1]]->tail.push_back(temp_node->name);
                                name2arc[str_vec[i+1]]->tail_type.push_back("I");
                                temp_node->in1 = str_vec[i+1];
                            }
                            else if(str_vec[i] == ".ZN"){
                                name2arc[str_vec[i+1]]->start = temp_node->name;
                                temp_node->out = str_vec[i+1];
                            }   
                        }
                    }
                }
                flag_lineEnd = 0;
            }
        }
    }
    set_InOutGraph();
}

void Graph::lib_parser(ifstream &in){
    flag_comment = 0;
    flag_lineEnd = 0;
    string now_cell,now_pin;
    string now_state = "none";
    bool now_value = 0;
    while(!in.eof()){
        string str,ans;
        vector<string> str_vec;
        getline(in,str);
        ans = RemoveSpace(str);
        if(!ans.empty()){
            str_vec = string2vec(ans);
            if(!str_vec.empty()){
                /*for(int i=0;i<str_vec.size();i++){
                    cout<<str_vec[i]<<endl;
                }*/
                if(str_vec[0] == "index_1"){
                    for(int i=1;i<str_vec.size();i++){
                        index_cap.push_back(stod(str_vec[i]));   
                    }
                }
                else if(str_vec[0] == "index_2"){
                    for(int i=1;i<str_vec.size();i++){
                        index_tran.push_back(stod(str_vec[i]));   
                    }
                }
                else if(str_vec[0] == "cell"){
                    now_cell = str_vec[1];
                    now_value = 0;
                    now_state = "none";
                }
                else if(str_vec[0] == "pin"){
                    now_pin = str_vec[1];
                }
                else if(str_vec[0] == "capacitance"){
                    if(now_cell == "NOR2X1"){
                        if(now_pin == "A1"){
                            NOR2X1.cap_a1 = stod(str_vec[1]);
                        }
                        else if(now_pin == "A2"){
                            NOR2X1.cap_a2 = stod(str_vec[1]);
                        }
                        else if(now_pin == "ZN"){
                            NOR2X1.cap_zn = stod(str_vec[1]);
                        }
                    }
                    else if(now_cell == "NANDX1"){
                        if(now_pin == "A1"){
                            NANDX1.cap_a1 = stod(str_vec[1]);
                        }
                        else if(now_pin == "A2"){
                            NANDX1.cap_a2 = stod(str_vec[1]);
                        }
                        else if(now_pin == "ZN"){
                            NANDX1.cap_zn = stod(str_vec[1]);
                        }
                    }
                    else if(now_cell == "INVX1"){
                        if(now_pin == "I"){
                            INVX1.cap_a1 = stod(str_vec[1]);
                            INVX1.cap_a2 = 0.0;
                        }
                        else if(now_pin == "ZN"){
                            INVX1.cap_zn = stod(str_vec[1]);
                        }
                    }
                }
                else if(str_vec[0] == "cell_rise"){
                    now_state = "cell_rise";
                    now_value = 0;
                }
                else if(str_vec[0] == "cell_fall"){
                    now_state = "cell_fall";
                    now_value = 0;
                }
                else if(str_vec[0] == "rise_transition"){
                    now_state = "rise_transition";
                    now_value = 0;
                }
                else if(str_vec[0] == "fall_transition"){
                    now_state = "fall_transition";
                    now_value = 0;
                }
                else if((str_vec[0] == "values") && (now_state != "none")){
                    now_value = 1;
                    if(now_cell == "NOR2X1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.t_fall.push_back(temp_value);
                        }
                    }
                    else if(now_cell == "NANDX1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.t_fall.push_back(temp_value);
                        }
                    }
                    else if(now_cell == "INVX1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=1;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.t_fall.push_back(temp_value);
                        }
                    }
                }
                else if(now_value == 1){
                    if(now_cell == "NOR2X1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NOR2X1.t_fall.push_back(temp_value);
                        }
                    }
                    else if(now_cell == "NANDX1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            NANDX1.t_fall.push_back(temp_value);
                        }
                    }
                    else if(now_cell == "INVX1"){
                        if(now_state == "cell_rise"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.c_rise.push_back(temp_value);
                        }
                        else if(now_state == "cell_fall"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.c_fall.push_back(temp_value);
                        }
                        else if(now_state == "rise_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.t_rise.push_back(temp_value);
                        }
                        else if(now_state == "fall_transition"){
                            vector<double> temp_value;
                            for(int i=0;i<str_vec.size();i++){
                                temp_value.push_back(stod(str_vec[i]));   
                            }
                            INVX1.t_fall.push_back(temp_value);
                        }
                    }
                }
            }
        }
    }
}

void Graph::pat_parser(ifstream &in){
    flag_comment = 0;
    flag_lineEnd = 0;
    int count_pat = 0;
    while(!in.eof()){
        string str,ans;
        vector<string> str_vec;
        getline(in,str);
        ans = RemoveSpace(str);
        if(!ans.empty()){
            str_vec = string2vec(ans);
            if(!str_vec.empty()){
                if(str_vec[0] == "input"){
                    for(int i=1;i<str_vec.size();i++){
                        pat_order.push_back(str_vec[i]);   
                    }
                }
                else if(str_vec[0] != ".end"){
                    for(int i=0;i<pat_order.size();i++){
                        pat.push_back(stoi(str_vec[i]));   
                    }
                    count_pat++;
                }
            }     
        }
    }
    pat_num = count_pat;
}

string Graph::RemoveSpace(string str){  
    istringstream ss(str); 
    string temp;  
    string output="";
    while(ss >> temp){
        if(!output.empty()){
            output += " ";
        } 
        output += temp;
    }
    return output;
}

vector<string> Graph::string2vec(string str){  
   int current = 0;
   int next;
   vector<string> temp_vec;
   while(current <= str.length()){
        next = str.find_first_of(" ,\";{()\\}:/*" , current);
        if((str[next] == '/') && (next < str.length()-1)){
            if(str[next+1] == '/'){
                break;
            }
        }
        if((str[next] == '/') && (next < str.length()-1)){
            if(str[next+1] == '*'){
                flag_comment = 1;
            }
        }
        if(str[next] == ';'){
            flag_lineEnd = 1;
        }
		if ((next != current) && (flag_comment == 0)){
			string tmp = str.substr(current, next - current);
			if (tmp.size() != 0){
                temp_vec.push_back(tmp);
            }
		}
        if((str[next] == '*') && (next < str.length()-1)){
            if(str[next+1] == '/'){
                flag_comment = 0;
            }
        }
		if (next == string::npos) break;
		current = next + 1; 
   }
   return temp_vec;
}

/*=====================================================================*/
/*                       < initialize & recover >                      */
/*=====================================================================*/

void Graph::set_InOutGraph(){
    for(int i=0;i<node_list.size();i++){
        Arc *temp_arc = name2arc[node_list[i]->out];
        for(int j=0;j<temp_arc->tail.size();j++){
            node_list[i]->out_graph.push_back(name2node[temp_arc->tail[j]]);
        }
        Arc *temp_arc1 = name2arc[node_list[i]->in1];
        if(temp_arc1->start != "none"){
            node_list[i]->in_graph.push_back(name2node[temp_arc1->start]);
        }
        if(node_list[i]->in2 != "none"){
            Arc *temp_arc2 = name2arc[node_list[i]->in2];
            if(temp_arc2->start != "none"){
                node_list[i]->in_graph.push_back(name2node[temp_arc2->start]);
            }
        }
        if(node_list[i]->in_graph.size() == 0){
            undo_list.push_back(node_list[i]);
        }
        node_list[i]->in_degree = node_list[i]->in_graph.size();
    }
}

void Graph::set_initial_pat(int num){
    //num = pattern num
    int num_ = num*pat_order.size();
    for(int i=0;i<pat_order.size();i++){
        name2arc[pat_order[i]]->logic = pat[num_+i];
    }
}

void Graph::recover(){
    for(int i=0;i<node_list.size();i++){
       node_list[i]->in_degree = node_list[i]->in_graph.size();
       node_list[i]->choose_path_max = "none";
       node_list[i]->logic = -1;
       node_list[i]->tran = 0.0;
       node_list[i]->total_max_delay = 0.0;
       node_list[i]->delay = 0.0;
       node_list[i]->control = "none";
    }
    for(int i=0;i<arc_list.size();i++){
       arc_list[i]->logic = -1;
       arc_list[i]->tran = 0.0;
       arc_list[i]->total_max_delay = 0.0;
    }
}

/*=====================================================================*/
/*                            < calculation >                          */
/*=====================================================================*/

void Graph::cal_OutputLoad(ofstream &out){
    for(int i=0;i<node_list.size();i++){
        Arc *temp_arc = name2arc[node_list[i]->out];
        if(temp_arc->type == "output"){
            node_list[i]->out_load += 0.03;
        }
        for(int j=0;j<temp_arc->tail.size();j++){
            if(name2node[temp_arc->tail[j]]->type == "NOR2X1"){
                if(temp_arc->tail_type[j] == "A1") node_list[i]->out_load += NOR2X1.cap_a1;
                else node_list[i]->out_load += NOR2X1.cap_a2; 
            }
            else if(name2node[temp_arc->tail[j]]->type == "NANDX1"){
                if(temp_arc->tail_type[j] == "A1") node_list[i]->out_load += NANDX1.cap_a1;
                else node_list[i]->out_load += NANDX1.cap_a2;
            }
            else if(name2node[temp_arc->tail[j]]->type == "INVX1"){
                node_list[i]->out_load += INVX1.cap_a1;
            }
        }
    }
    sort(node_list.begin(),node_list.end(),compare_out_load);
    for(int i=0;i<node_list.size();i++){
        out<<node_list[i]->name<<" "<<node_list[i]->out_load<<endl;

    }
}

void Graph::cal_logic(Node* node){
    if(node->type == "INVX1"){
        Arc* temp_arc = name2arc[node->in1];
        if(temp_arc->logic == 1) node->logic = 0;
        else node->logic = 1;
        name2arc[node->out]->logic = node->logic;
    }
    else if(node->type == "NOR2X1"){
        Arc* temp_arc1 = name2arc[node->in1];
        Arc* temp_arc2 = name2arc[node->in2];
        if((temp_arc1->logic == 0) && (temp_arc2->logic == 0)){
            node->logic = 1;
        }
        else if((temp_arc1->logic == 1) && (temp_arc2->logic == 0)){
            node->logic = 0;
            node->control = "in1";
        }
        else if((temp_arc1->logic == 0) && (temp_arc2->logic == 1)){
            node->logic = 0;
            node->control = "in2";
        }
        else {
            node->logic = 0;
            if(temp_arc1->total_max_delay <= temp_arc2->total_max_delay){
                node->control = "in1";
            }
            else{
                node->control = "in2";
            }
        }
        name2arc[node->out]->logic = node->logic;
    }
    else if(node->type == "NANDX1"){
        Arc* temp_arc1 = name2arc[node->in1];
        Arc* temp_arc2 = name2arc[node->in2];
        if((temp_arc1->logic == 1) && (temp_arc2->logic == 1)){
            node->logic = 0;
        }
        else if((temp_arc1->logic == 1) && (temp_arc2->logic == 0)){
            node->logic = 1;
            node->control = "in2";
        }
        else if((temp_arc1->logic == 0) && (temp_arc2->logic == 1)){
            node->logic = 1;
            node->control = "in1";
        }
        else {
            node->logic = 1;
            if(temp_arc1->total_max_delay <= temp_arc2->total_max_delay){
                node->control = "in1";
            }
            else{
                node->control = "in2";
            }
        }
        name2arc[node->out]->logic = node->logic;
    }
}

double Graph::calculation(double cap1, double cap2, double tran1, double tran2, double n1, double n2, double n3, double n4, double cap, double tran){
    double temp1,temp2,ans;
    if((cap >= cap1) && (cap <= cap2)){
        if((tran >= tran1) && (tran <= tran2)){
            temp1 = n1*(cap2-cap)/(cap2-cap1) + n2*(cap-cap1)/(cap2-cap1);
            temp2 = n3*(cap2-cap)/(cap2-cap1) + n4*(cap-cap1)/(cap2-cap1);
            ans = temp1*(tran2-tran)/(tran2-tran1) + temp2*(tran-tran1)/(tran2-tran1);
        }
        else if(tran < tran1){
            temp1 = n1*(cap2-cap)/(cap2-cap1) + n2*(cap-cap1)/(cap2-cap1);
            temp2 = n3*(cap2-cap)/(cap2-cap1) + n4*(cap-cap1)/(cap2-cap1);
            ans = temp2 - (temp2-temp1)*(tran2-tran)/(tran2-tran1);
        }
        else if(tran > tran2){
            temp1 = n1*(cap2-cap)/(cap2-cap1) + n2*(cap-cap1)/(cap2-cap1);
            temp2 = n3*(cap2-cap)/(cap2-cap1) + n4*(cap-cap1)/(cap2-cap1);
            ans = temp1 + (temp2-temp1)*(tran-tran1)/(tran2-tran1);
        }
    }
    else if(cap < cap1){
        if((tran >= tran1) && (tran <= tran2)){
            temp1 = n2 - (n2-n1)*(cap2-cap)/(cap2-cap1);
            temp2 = n4 - (n4-n3)*(cap2-cap)/(cap2-cap1);
            ans = temp1*(tran2-tran)/(tran2-tran1) + temp2*(tran-tran1)/(tran2-tran1);
        }
        else if(tran < tran1){
            temp1 = n2 - (n2-n1)*(cap2-cap)/(cap2-cap1);
            temp2 = n4 - (n4-n3)*(cap2-cap)/(cap2-cap1);
            ans = temp2 - (temp2-temp1)*(tran2-tran)/(tran2-tran1);
        }
        else if(tran > tran2){
            temp1 = n2 - (n2-n1)*(cap2-cap)/(cap2-cap1);
            temp2 = n4 - (n4-n3)*(cap2-cap)/(cap2-cap1);
            ans = temp1 + (temp2-temp1)*(tran-tran1)/(tran2-tran1);  
        }
    }
    else if(cap > cap2){
        if((tran >= tran1) && (tran <= tran2)){
            temp1 = n1 + (n2-n1)*(cap-cap1)/(cap2-cap1);
            temp2 = n3 + (n4-n3)*(cap-cap1)/(cap2-cap1);
            ans = temp1*(tran2-tran)/(tran2-tran1) + temp2*(tran-tran1)/(tran2-tran1);
        }
        else if(tran < tran1){
            temp1 = n1 + (n2-n1)*(cap-cap1)/(cap2-cap1);
            temp2 = n3 + (n4-n3)*(cap-cap1)/(cap2-cap1);
            ans = temp2 - (temp2-temp1)*(tran2-tran)/(tran2-tran1);
        }
        else if(tran > tran2){
            temp1 = n1 + (n2-n1)*(cap-cap1)/(cap2-cap1);
            temp2 = n3 + (n4-n3)*(cap-cap1)/(cap2-cap1);
            ans = temp1 + (temp2-temp1)*(tran-tran1)/(tran2-tran1);  
        }
    }
    return ans;
}

void Graph::run(ofstream &out_delay,ofstream &out_path){
    //for pat_num
    for(int l=0;l<pat_num;l++){
        deque<Node*> undo_list2;
        undo_list2 = undo_list;
        set_initial_pat(l);
        int j=0;
        while(!undo_list2.empty()){
            Node* current_node = undo_list2[0];
            double in_tran;
            int index_cap1, index_cap2, index_tran1, index_tran2;
            cal_logic(current_node);
            if(current_node->type == "INVX1"){
                if(current_node->in_graph.empty()){
                    current_node->choose_path_max = name2arc[current_node->in1]->name;
                    in_tran = 0;
                    index_tran1 = 0;
                    index_tran2 = 1;
                }
                else{
                    in_tran = current_node->in_graph[0]->tran;
                    current_node->total_max_delay += current_node->in_graph[0]->total_max_delay;
                    current_node->choose_path_max = name2arc[current_node->in1]->name;
                    index_tran1 = 0;
                    index_tran2 = 1;
                    for(int i=1;i<index_tran.size();i++){
                        if(in_tran > index_tran[i]){
                            index_tran1 ++;
                            index_tran2 ++;
                            if(i == index_tran.size()-1){
                                index_tran1 = index_tran.size()-2;
                                index_tran2 = index_tran.size()-1;
                            }
                        }
                        else{
                            break;
                        }
                    }
                }
                index_cap1 = 0;
                index_cap2 = 1;
                for(int i=1;i<index_cap.size();i++){
                    if(current_node->out_load > index_cap[i]){
                        index_cap1 ++;
                        index_cap2 ++;
                        if(i == index_cap.size()-1){
                            index_cap1 = index_cap.size()-2;
                            index_cap2 = index_cap.size()-1;
                        }
                    }
                    else{
                        break;
                    }
                }
                if(current_node->logic == 1){
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], INVX1.t_rise[index_tran1][index_cap1], INVX1.t_rise[index_tran1][index_cap2], INVX1.t_rise[index_tran2][index_cap1], INVX1.t_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], INVX1.c_rise[index_tran1][index_cap1], INVX1.c_rise[index_tran1][index_cap2], INVX1.c_rise[index_tran2][index_cap1], INVX1.c_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                }
                else{
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], INVX1.t_fall[index_tran1][index_cap1], INVX1.t_fall[index_tran1][index_cap2], INVX1.t_fall[index_tran2][index_cap1], INVX1.t_fall[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], INVX1.c_fall[index_tran1][index_cap1], INVX1.c_fall[index_tran1][index_cap2], INVX1.c_fall[index_tran2][index_cap1], INVX1.c_fall[index_tran2][index_cap2], current_node->out_load, in_tran);
                }
                current_node->total_max_delay += current_node->delay;
            }
            else if(current_node->type == "NOR2X1"){
                Arc* temp_in1 = name2arc[current_node->in1];
                Arc* temp_in2 = name2arc[current_node->in2];
                if(current_node->in_graph.empty()){
                    in_tran = 0;
                    index_tran1 = 0;
                    index_tran2 = 1;
                    if(current_node->control == "none"){
                        current_node->choose_path_max = temp_in2->name;
                    }
                    else if(current_node->control == "in1"){
                        current_node->choose_path_max = temp_in1->name;
                    }
                    else if(current_node->control == "in2"){
                        current_node->choose_path_max = temp_in2->name;
                    }
                }
                else{
                    if(current_node->control == "none"){
                        if(temp_in1->total_max_delay >= temp_in2->total_max_delay){
                            current_node->choose_path_max = temp_in1->name;
                            current_node->total_max_delay += temp_in1->total_max_delay;
                            in_tran = temp_in1->tran;
                        }
                        else{
                            current_node->choose_path_max = temp_in2->name;
                            current_node->total_max_delay += temp_in2->total_max_delay;
                            in_tran = temp_in2->tran;
                        }
                        
                    }
                    else if(current_node->control == "in1"){
                        current_node->choose_path_max = temp_in1->name;
                        current_node->total_max_delay += temp_in1->total_max_delay;
                        in_tran = temp_in1->tran;
                    }
                    else if(current_node->control == "in2"){
                        current_node->choose_path_max = temp_in2->name;
                        current_node->total_max_delay += temp_in2->total_max_delay;
                        in_tran = temp_in2->tran;
                    }
                    else{
                        cout<<"warning!"<<endl;
                    }
                    index_tran1 = 0;
                    index_tran2 = 1;
                    for(int i=1;i<index_tran.size();i++){
                        if(in_tran > index_tran[i]){
                            index_tran1 ++;
                            index_tran2 ++;
                            if(i == index_tran.size()-1){
                                index_tran1 = index_tran.size()-2;
                                index_tran2 = index_tran.size()-1;
                            }
                        }
                        else{
                            break;
                        }
                    }
                }
                index_cap1 = 0;
                index_cap2 = 1;
                for(int i=1;i<index_cap.size();i++){
                    if(current_node->out_load > index_cap[i]){
                        index_cap1 ++;
                        index_cap2 ++;
                        if(i == index_cap.size()-1){
                            index_cap1 = index_cap.size()-2;
                            index_cap2 = index_cap.size()-1;
                        }
                    }
                    else{
                        break;
                    }
                }
                if(current_node->logic == 1){
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NOR2X1.t_rise[index_tran1][index_cap1], NOR2X1.t_rise[index_tran1][index_cap2], NOR2X1.t_rise[index_tran2][index_cap1], NOR2X1.t_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NOR2X1.c_rise[index_tran1][index_cap1], NOR2X1.c_rise[index_tran1][index_cap2], NOR2X1.c_rise[index_tran2][index_cap1], NOR2X1.c_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                }
                else{
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NOR2X1.t_fall[index_tran1][index_cap1], NOR2X1.t_fall[index_tran1][index_cap2], NOR2X1.t_fall[index_tran2][index_cap1], NOR2X1.t_fall[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NOR2X1.c_fall[index_tran1][index_cap1], NOR2X1.c_fall[index_tran1][index_cap2], NOR2X1.c_fall[index_tran2][index_cap1], NOR2X1.c_fall[index_tran2][index_cap2], current_node->out_load, in_tran);

                }
                current_node->total_max_delay += current_node->delay;
            }
            else if(current_node->type == "NANDX1"){
                Arc* temp_in1 = name2arc[current_node->in1];
                Arc* temp_in2 = name2arc[current_node->in2];
                if(current_node->in_graph.empty()){
                    in_tran = 0;
                    index_tran1 = 0;
                    index_tran2 = 1;
                    if(current_node->control == "none"){
                        current_node->choose_path_max = temp_in2->name;
                    }
                    else if(current_node->control == "in1"){
                        current_node->choose_path_max = temp_in1->name;
                    }
                    else if(current_node->control == "in2"){
                        current_node->choose_path_max = temp_in2->name;
                    }
                }
                else{
                    if(current_node->control == "none"){
                        if(temp_in1->total_max_delay >= temp_in2->total_max_delay){
                            current_node->choose_path_max = temp_in1->name;
                            current_node->total_max_delay += temp_in1->total_max_delay;
                            in_tran = temp_in1->tran;
                        }
                        else{
                            current_node->choose_path_max = temp_in2->name;
                            current_node->total_max_delay += temp_in2->total_max_delay;
                            in_tran = temp_in2->tran;
                        }
                        
                    }
                    else if(current_node->control == "in1"){
                        current_node->choose_path_max = temp_in1->name;
                        current_node->total_max_delay += temp_in1->total_max_delay;
                        in_tran = temp_in1->tran;
                    }
                    else if(current_node->control == "in2"){
                        current_node->choose_path_max = temp_in2->name;
                        current_node->total_max_delay += temp_in2->total_max_delay;
                        in_tran = temp_in2->tran;
                    }
                    else{
                        cout<<"warning!"<<endl;
                    }
                    index_tran1 = 0;
                    index_tran2 = 1;
                    for(int i=1;i<index_tran.size();i++){
                        if(in_tran > index_tran[i]){
                            index_tran1 ++;
                            index_tran2 ++;
                            if(i == index_tran.size()-1){
                                index_tran1 = index_tran.size()-2;
                                index_tran2 = index_tran.size()-1;
                            }
                        }
                        else{
                            break;
                        }
                    }
                }
                index_cap1 = 0;
                index_cap2 = 1;
                for(int i=1;i<index_cap.size();i++){
                    if(current_node->out_load > index_cap[i]){
                        index_cap1 ++;
                        index_cap2 ++;
                        if(i == index_cap.size()-1){
                            index_cap1 = index_cap.size()-2;
                            index_cap2 = index_cap.size()-1;
                        }
                    }
                    else{
                        break;
                    }
                }
                if(current_node->logic == 1){
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NANDX1.t_rise[index_tran1][index_cap1], NANDX1.t_rise[index_tran1][index_cap2], NANDX1.t_rise[index_tran2][index_cap1], NANDX1.t_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NANDX1.c_rise[index_tran1][index_cap1], NANDX1.c_rise[index_tran1][index_cap2], NANDX1.c_rise[index_tran2][index_cap1], NANDX1.c_rise[index_tran2][index_cap2], current_node->out_load, in_tran);
                }
                else{
                    current_node->tran = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NANDX1.t_fall[index_tran1][index_cap1], NANDX1.t_fall[index_tran1][index_cap2], NANDX1.t_fall[index_tran2][index_cap1], NANDX1.t_fall[index_tran2][index_cap2], current_node->out_load, in_tran);
                    current_node->delay = calculation(index_cap[index_cap1], index_cap[index_cap2], index_tran[index_tran1], index_tran[index_tran2], NANDX1.c_fall[index_tran1][index_cap1], NANDX1.c_fall[index_tran1][index_cap2], NANDX1.c_fall[index_tran2][index_cap1], NANDX1.c_fall[index_tran2][index_cap2], current_node->out_load, in_tran);

                }
                current_node->total_max_delay += current_node->delay;
            }

            Arc* temp_out = name2arc[current_node->out];
            temp_out->total_max_delay = current_node->total_max_delay;
            temp_out->tran = current_node->tran;
            
            if(undo_list2[0]->out_graph.size() != 0){
                for(int i=0;i<undo_list2[0]->out_graph.size();i++){
                    Node* temp_out = undo_list2[0]->out_graph[i];
                    temp_out->in_degree--;
                    if(temp_out->in_degree == 0){
                        undo_list2.push_back(temp_out);
                    }
                }
            }
            undo_list2.pop_front();
        }
        sort(node_list.begin(), node_list.end(), compare_delay);
        for(int i=0;i<node_list.size();i++){
            out_delay<<node_list[i]->name<<" "<<node_list[i]->logic<<" "<<node_list[i]->delay<<" "<<node_list[i]->tran<<endl;
        }
        out_delay<<endl;
        longest_path(out_path);
        if(l != pat_num-1){
            recover();
        }
    }
}

void Graph::longest_path(ofstream &out){
    vector<string> path_max;
    vector<string> path_min;
    int pos_max,pos_min;
    double max_delay = 0.0;
    double min_delay = dou_max;
    for(int i=0;i<output_list.size();i++){
        if(output_list[i]->total_max_delay > max_delay){
            pos_max = i;
            max_delay = output_list[i]->total_max_delay;
        }
        if(output_list[i]->total_max_delay < min_delay){
            pos_min = i;
            min_delay = output_list[i]->total_max_delay;
        }
    }
    
    //max
    Node* current_n_max = name2node[output_list[pos_max]->start];
    Arc* current_a_max = output_list[pos_max];
    path_max.push_back(current_a_max->name);
    bool input_flag = 0;
    while(1){
        current_a_max = name2arc[current_n_max->choose_path_max];
        path_max.push_back(current_a_max->name);
        if(current_a_max->type == "input"){
            input_flag = 1;
            break;
        }
        current_n_max = name2node[current_a_max->start];
    }

    //min
    Node* current_n_min = name2node[output_list[pos_min]->start];
    Arc* current_a_min = output_list[pos_min];
    path_min.push_back(current_a_min->name);
    input_flag = 0;
    while(1){
        current_a_min = name2arc[current_n_min->choose_path_max];
        path_min.push_back(current_a_min->name);
        if(current_a_min->type == "input"){
            input_flag = 1;
            break;
        }
        current_n_min = name2node[current_a_min->start];
    }

    out<<"Longest delay = "<<max_delay<<", the path is: ";
    for(int i=path_max.size()-1; i>0; i--){
       out<<path_max[i]<<" -> ";
    }
    out<<path_max[0]<<endl;

    out<<"Shortest delay = "<<min_delay<<", the path is: ";
    for(int i=path_min.size()-1; i>0; i--){
       out<<path_min[i]<<" -> ";
    }
    out<<path_min[0]<<endl;
    out<<endl;

}