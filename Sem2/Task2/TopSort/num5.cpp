#include<iostream>
#include<algorithm>
#include<stddef.h>
#include <fstream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;



class Versh{
		public:
		bool use;
		int parent;
		int num;
		int color;
		int way;
		void set(int k){
				color = k;
		}
		Versh(int i){
				use = false;
				num = i;
				color = 0;
				parent = 0;
				way = 0;
		}
/*		Versh operator<(Versh other){
				return num < other.num;
		}*/
};

main(){
		ifstream fin("in5.txt");
		int n;
		int first;
		int last;
		fin >> n;
		fin >> first;
		fin >> last;
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
		queue<int> frontVersh;
		frontVersh.push(first);
		int k = 0;
		while( (!frontVersh.empty())/* && (frontVersh.back() != last)*/ ){
				int tmp = frontVersh.front();
				frontVersh.pop();
				for(int i = 0; i < m[tmp].size(); ++i){
						if(!vert[m[tmp][i]].use){
								vert[m[tmp][i]].use = true;
								frontVersh.push(m[tmp][i]);
								vert[m[tmp][i]].parent = tmp;
								vert[m[tmp][i]].way = vert[tmp].way + 1;
								k++;
						}
				}
		}
								
		cout << "\n" << vert[last].way - 1 <<"\n"; 				
		int now = vert[last].parent;		
		while(now != first){
				cout<< now << " ";
				now = vert[now].parent;
		}


		
}
