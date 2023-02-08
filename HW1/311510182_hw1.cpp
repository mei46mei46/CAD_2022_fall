#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <set>
#include <limits.h> 
#include <time.h> 

using namespace std;


struct Implicant{
    string index;
    int num_of_one;
    bool choose_flag;
    bool operator==(const Implicant& lhs){ return index == lhs.index;}
};
/*=====================================================================*/
/*                               < sort >                              */
/*=====================================================================*/
bool compare_one(const Implicant a,const Implicant b){
    return(a.num_of_one < b.num_of_one);
}
bool sort_prime(const Implicant a,const Implicant b){
    for(int i=0;i<a.index.length();i++){
        if(a.index[i]=='-' && b.index[i]=='0'){
            return 1;
        }
        else if(a.index[i]=='-' && b.index[i]=='1'){
            return 1;
        }
        else if(a.index[i]=='0' && b.index[i]=='1'){
            return 1;
        }
        else if(a.index[i]=='0' && b.index[i]=='-'){
            return 0;
        }
        else if(a.index[i]=='1' && b.index[i]=='-'){
            return 0;
        }
        else if(a.index[i]=='1' && b.index[i]=='0'){
            return 0;
        }
    }
}
bool sort_mc(const string a,const string b){
    for(int i=0;i<a.length();i++){
        if(a[i]=='-' && b[i]=='0'){
            return 1;
        }
        else if(a[i]=='-' && b[i]=='1'){
            return 1;
        }
        else if(a[i]=='0' && b[i]=='1'){
            return 1;
        }
        else if(a[i]=='0' && b[i]=='-'){
            return 0;
        }
        else if(a[i]=='1' && b[i]=='-'){
            return 0;
        }
        else if(a[i]=='1' && b[i]=='0'){
            return 0;
        }
    }
}
bool compare_sop(const set<string> a, const set<string> b) {
	return ( a.size() < b.size() ) ;
}

/*=====================================================================*/
/*                         < Quine_McCluskey >                         */
/*=====================================================================*/

class Quine_McCluskey {
    friend struct Implicant;
    friend bool compare_one(const Implicant,const Implicant); 
public:
	Quine_McCluskey(){};
	~Quine_McCluskey(){};
    void set_num(int temp){num = temp;};
    void set_on_set(int temp){on_set.push_back(temp);};
    void set_dc_set(int temp){dc_set.push_back(temp);};
    void on_dc2impli();
    void run_prime_impli();
    void output_prime(ofstream &);
    vector<Implicant> & Get_impli() { return impli_cp; }
    vector<Implicant> & Get_prime_impli() { return prime_impli; }
private:
    int num;
    vector<int> on_set;
    vector<int> dc_set;
    vector<Implicant> impli;
    vector<Implicant> impli_cp; //use in PM
    vector<Implicant> prime_impli;
};

void Quine_McCluskey::on_dc2impli(){
    for(int i=0;i<on_set.size();i++){
        string temp="";
        int n=on_set[i];
        int cnt_1=0;       
        while(n != 0){
            if(n%2 == 1){
                cnt_1++;
            }
            temp += '0'+ n%2;
            n /= 2;
        }
        int x=num-temp.length();
        while(x){
            temp += '0';
            x--;
        }
        reverse( temp.begin() , temp.end() );
        Implicant temp_impl;
        temp_impl.index=temp;
        temp_impl.num_of_one=cnt_1;
        temp_impl.choose_flag=0;
        impli.push_back(temp_impl);
    }
    impli_cp.assign(impli.begin(),impli.end());
    for(int i=0;i<dc_set.size();i++){
        string temp="";
        int n=dc_set[i];
        int cnt_1=0;
        while(n != 0){
            if(n%2 == 1){
                cnt_1++;
            }
            temp += '0'+ n%2;
            n /= 2;
        }
        int x=num-temp.length();
        while(x){
            temp += '0';
            x--;
        }
        reverse( temp.begin() , temp.end() );
        Implicant temp_impl;
        temp_impl.index=temp;
        temp_impl.num_of_one=cnt_1;
        temp_impl.choose_flag=0;
        impli.push_back(temp_impl);
    }
    //sort(impli.begin(),impli.end(),compare_one);
}

void Quine_McCluskey::run_prime_impli(){
    while(!impli.empty()){
        sort(impli.begin(),impli.end(),compare_one);
        vector<Implicant> temp_impli;
        for(int i=0;i<impli.size()-1;i++){
            for(int j=i+1;j<impli.size();j++){
                if(impli[i].num_of_one == impli[j].num_of_one){
                    continue;
                }
                else{
                    int diff_num=0,diff_pos;
                    for(int s=0;s<num;s++){
                        if(impli[i].index.at(s) != impli[j].index.at(s)){
                            diff_num++;
                            diff_pos = s;
                        }
                        if(diff_num > 1){
                            break;
                        }
                    }
                    if(diff_num == 1){
                        string temp=impli[i].index;
                        temp.at(diff_pos) = '-';
                        Implicant get;
                        get.index = temp;
                        if(impli[i].index.at(diff_pos)=='1'){
                            get.num_of_one = impli[i].num_of_one-1;
                        }
                        else{
                            get.num_of_one = impli[i].num_of_one;
                        }
                        get.choose_flag=0;
                        vector<Implicant>::iterator it = std::find(temp_impli.begin(), temp_impli.end(), get);
                        if(it==temp_impli.end()){
                            temp_impli.push_back(get);
                        }
                        impli[i].choose_flag=1;
                        impli[j].choose_flag=1;
                    }
                }
            }
        }
        for(int i=0;i<impli.size();i++){
            if(impli[i].choose_flag==0){
                prime_impli.push_back(impli[i]);
            }
        }
        impli.clear();
        impli.assign(temp_impli.begin(),temp_impli.end());
    }
    sort(prime_impli.begin(),prime_impli.end(),sort_prime);
}

void Quine_McCluskey::output_prime(ofstream &out){
    out<<".p "<<prime_impli.size()<<endl;
    int out_num = (prime_impli.size()>15)? 15:prime_impli.size();
    for(int i=0;i<out_num;i++){
            out<<prime_impli[i].index<<endl;
    }
}

/*=====================================================================*/
/*                         < Petrick_Method >                          */
/*=====================================================================*/

class Petrick_Method {
    friend struct Implicant;
    friend bool compare_sop(const set<string> a, const set<string> b);
    friend bool sort_mc(const string a,const string b);
public:
    Petrick_Method() {};
    ~Petrick_Method() {};
    void make_POS(vector<Implicant> &prime_impli, vector<Implicant> &impli);
    void make_SOP();
    void output_mc(ofstream &);
    string setTOstring(set<string> &temp) ;
private:
    vector< vector<Implicant> > POS;
    vector< set<string> > SOP;
    vector<string> mc;
    int literal;
};

void Petrick_Method::make_POS(vector<Implicant> &prime_impli, vector<Implicant> &impli){
    for(int i=0;i<impli.size();i++){
        vector<Implicant> total;
        for(int j=0;j<prime_impli.size();j++){
             bool flag=0;
            for(int k=0;k<impli[i].index.length();k++){
                if((prime_impli[j].index[k]!='-') && (prime_impli[j].index[k]!=impli[i].index[k])){
                    flag=1;
                    break;
                }
            }
            if(flag == 0){
                total.push_back(prime_impli[j]);
            }
        }
        POS.push_back(total);
    }
}

string Petrick_Method::setTOstring(set<string> &temp) {
    set<string>::iterator iter;
	stringstream ss;
	for( iter=temp.begin() ; iter!=temp.end() ; iter++ )
		ss<< *iter ;
	string s;
	ss>> s ;
	return s ;
}

void Petrick_Method::make_SOP(){
    //1
    for(int i=0;i<POS[0].size();i++){
        set<string> temp;   
        temp.insert(POS[0][i].index);
        SOP.push_back(temp);
    }
    //others
    for(int i=1;i<POS.size();i++){
        vector< set<string> >temp_SOP;
        set<string> fastSOP;
        for(int j=0;j<SOP.size();j++){           
            for(int k=0;k<POS[i].size();k++){
                set<string> temp = SOP[j];
                temp.insert(POS[i][k].index);
                temp_SOP.push_back(temp);               
            }
        }
        SOP.clear();
        for(int i=0;i<temp_SOP.size();i++){
            string temp = setTOstring(temp_SOP[i]) ;
            if( fastSOP.find(temp)==fastSOP.end() ) {
                fastSOP.insert( temp );
                SOP.push_back( temp_SOP[i] );
            }       
        }
    }   
    sort(SOP.begin(),SOP.end(),compare_sop);
    //literal
    int count_pos=0;
    int min_it = INT_MAX;
    for(int i=0;i<SOP.size();i++){
        int count_it=0;
        if(SOP[i].size()>SOP[0].size()){
            break;
        }
        for (set<string>::iterator iter = SOP[i].begin(); iter != SOP[i].end(); iter++) {
            for(int j=0;j<(*iter).length();j++){
                if((*iter).at(j)!='-'){
                    count_it ++;
                }
            }
        }
        if(count_it <min_it ){
            min_it = count_it;
            count_pos = i;
        }
    }
    for (set<string>::iterator it = SOP[count_pos].begin(); it != SOP[count_pos].end(); it++) {
        mc.push_back(*it);
    }
    literal = min_it;
    sort(mc.begin(),mc.end(),sort_mc);
}

void Petrick_Method::output_mc(ofstream &out){
    out<<".mc "<<mc.size()<<endl;
    for(int i=0;i<mc.size();i++){
        out<<mc[i]<<endl;
    } 
    out<<"literal="<<literal;
    /*cout<<endl;
	cout<<"SOP: "<<SOP.size()<<endl;*/
}

void initial(ifstream &in,Quine_McCluskey &QUMC);

/*=====================================================================*/
/*                              < Main >                               */
/*=====================================================================*/

int main(int argc, char *argv[]){
    /*clock_t end,start;
    start = clock();*/
    ifstream in(argv[1]);
    ofstream out(argv[2]);

    Quine_McCluskey QUMC;
    Petrick_Method PEME;
    initial(in,QUMC);
    QUMC.on_dc2impli();
    QUMC.run_prime_impli();
    QUMC.output_prime(out);
    out<<endl;
    PEME.make_POS(QUMC.Get_prime_impli(),QUMC.Get_impli());
    PEME.make_SOP();
    PEME.output_mc(out);
    /*end = clock();
    cout<<double(end-start)/ CLOCKS_PER_SEC<<"s"<<endl;*/
 return 0;
}

void initial(ifstream &in,Quine_McCluskey &QUMC){
    string str;
    int temp_m,temp_d,num;
    getline(in,str);//.i
    getline(in,str);//num
    stringstream ss(str);
    ss >> num;
    QUMC.set_num(num);
    getline(in,str);//.m
    getline(in,str);
    stringstream mm(str);
    while(mm >> temp_m){
        QUMC.set_on_set(temp_m);
    }
    if(!in.eof()){
        getline(in,str);//.d
    }
    if(!in.eof()){
        getline(in,str);
        stringstream dd(str);
        while(dd >> temp_d){
            QUMC.set_dc_set(temp_d);
        }
    }
}