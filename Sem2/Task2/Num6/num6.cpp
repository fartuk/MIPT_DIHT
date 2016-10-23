#include<iostream>
#include<map>
#include<vector>
#include<iterator>
#include<string>
using namespace std;
main(){
		int n = 0;
		cin >> n;
		vector< vector<int> > graf;
		for(int i = 0; i < 10; ++i){
				vector<int> tmp;
				graf.push_back(tmp);
		}
		graf[0].push_back(4);
		graf[0].push_back(6);
		graf[1].push_back(6);
		graf[1].push_back(8);
		graf[2].push_back(7);
		graf[2].push_back(9);
		graf[3].push_back(4);
		graf[3].push_back(8);
		graf[4].push_back(0);
		graf[4].push_back(3);
		graf[4].push_back(9);
		graf[6].push_back(1);
		graf[6].push_back(7);
		graf[6].push_back(0);
		graf[7].push_back(6);
		graf[7].push_back(2);
		graf[8].push_back(1);
		graf[8].push_back(3);
		graf[9].push_back(2);
		graf[9].push_back(4);
				
		vector< vector<long long> > arr;
		for(int i = 0; i < 10; ++i){
				vector<long long> tmp;
				arr.push_back(tmp);
				for(int j = 0; j < n + 1; ++j){
						 arr[i].push_back(0);
				}
		}
				
		for(int i = 0; i < 10; i++){
				arr[i][1] = 1;
		}	
		for(int i = 0; i < 10; i++){
				arr[i][2] = graf[i].size();;
		}
		arr[1][2]--;
		arr[3][2]--;
		arr[4][2]--;
		arr[6][2]--;
		
		for(int j = 3; j < n + 1; j++){
				for(int i = 0; i < 10; i++){
						long long sum = 0;
						for(int k = 0; k < graf[i].size(); k++){
								sum += arr[graf[i][k]][j - 1];
						}
						arr[i][j] = sum;
				}
		}
		long long sum = 0;		
		for(int i = 0; i < 10; i++){
				sum += arr[i][n];
		}
								


/*		for(int i = 0; i < 10; ++i){
				cout << i <<": ";
				for(int j = 1; j < n + 1; ++j){
						 cout << arr[i][j] << " ";
				}
				cout << "\n";
		}*/
		cout <<  sum; 

}
