#include<iostream>
#include<algorithm>
#include<stddef.h>
#include <fstream>
#include<stdio.h>
#include<vector>
#include<sstream>
using namespace std;





class Versh{
		public:
		int num;
		int color;
		void set(int k){
				color = k;
		}
		Versh(int i){
				num = i;
				color = 0;
		}
/*		Versh operator<(Versh other){
				return num < other.num;
		}*/
};

void dfs(int num, const vector< vector<int> > &graf, vector<Versh> &vectVersh, vector<int> &arr){
		vectVersh[num].color = 1;
		for(auto it = graf[num].begin(); it < graf[num].end(); ++it){
				if(vectVersh[*it].color == 0){
						dfs(*it, graf, vectVersh, arr);
				}

		}
				vectVersh[num].color = 2;
				arr.push_back(num);
				cout<< "--" << num << "--\n";
}
				
		



int main(){
		ifstream fin("in4.txt");
		int n;
		fin >> n;
		vector<Versh> vert;
	//	vert.resize(n + 1);
		Versh tmp1(0);
		vert.push_back(tmp1);
		for(int i = 1; i < n + 1; i++){
				Versh tmp(i);
				vert.push_back(tmp);
		}
		for(int i = 1; i < n + 1; i++){
				cout<< i << " : " << vert[i].color << "\n";
		}
		cout << "\n";
		vector< vector<int> > m;

		for(int i = 1; i < n + 2; i++){
				string line;
				getline( fin, line );
				vector<int> t; 
				istringstream iss( line );
				int number; 
				while(iss >> number){
						t.push_back(number);
				}
				m.push_back(t);
				
		}
		

		for(int i = 1; i < n + 1; i++){
				cout << i;
				for(auto it = m[i].begin(); it < m[i].end(); ++it){
						cout << " " << *it;
				}
				cout << "\n";
		}
		vector< vector<int> > graf;
		for(int i = 0; i < n + 1; i++){
				vector<int> t;
				graf.push_back(t);
		}
		for(int i = 1; i < n + 1; i++){
				for(auto it = m[i].begin(); it < m[i].end(); ++it){
						graf[*it].push_back(i);
				}
		}
		cout << "\n";
		for(int i = 1; i < n + 1; i++){
				cout << i;
				for(auto it = graf[i].begin(); it < graf[i].end(); ++it){
						cout << " " << *it;
				}
				cout << "\n";
		}
		
///////////////////////////////////////////////////////////////////////////////

		vector<int> arr;
		for(auto it = vert.begin(); it < vert.end(); ++it){
				if(it->color == 0){
						dfs(it->num, graf, vert, arr);
				}
		}
		for(int i = 1; i < n + 1; i++){
				cout<< i << " : " << vert[i].color << "\n";
		}
		cout << "\n";
		for(auto it = arr.end() - 2; it >= arr.begin() ; --it){
				cout<< *it << "\n";
		}
}	


