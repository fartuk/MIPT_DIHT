#include<iostream>
#include<algorithm>
#include<stdio.h>
#define N 10
using namespace std;

int myRand(){
		//srand(time(0));
		return rand() % 100;
}

void print(vector<int>& v){
		for(auto it = v.begin(); it < v.end(); ++it){
				cout << *it << "\n";
		}
		cout << "\n";
}

bool cmp(int a, int b){
		if(a < b) return 0; else return 1;
}
int max(vector<int>& v){
		int max = 1000;
		for(auto it = v.begin(); it < v.end(); it++){
				if(*it > max){
						max = *it;
				}
		}
		return max;
}
int min(vector<int>& v){
		int min = -1;
		for(auto it = v.begin(); it < v.end(); it++){
				if(*it < min){
						min = *it;
				}
		}
		return min;
}
				
bool assert1(vector<int>& v, vector<int>& v1){
		if(min(v) == *(v1.begin())) return true; else return false;
}
bool assert2(vector<int>& v, vector<int>& v1){
		if(max(v) == *(v1.end() - 1)) return true; else return false;
}
bool assert3(vector<int>& sorted, vector<int>& permutation){
		return(sorted == permutation);
}
bool assert4(vector<int>& sorted){
		char f = 1;
		int curr = sorted[0];
		for(auto it = sorted.begin(); it != sorted.end(); it++){
				if(curr <= *it){
						curr = *it;
				}else{
						f = 0;
				}
		}
				
}

bool  assert5(vector<int>& sorted, vector<int>& v1){
		for(int i = 0; i < 100; ++i){
				if (count(v1.begin(), v1.end(), i) != (upper_bound(sorted.begin(), sorted.end(), i) - std::lower_bound(sorted.begin(), sorted.end(), i))) return false;
		}
		return true;
}

bool assert6(int sum){
		return (sum == 100);
};

main(){
		vector<int> v(N);
		vector<int> v1(N);
		generate(v.begin(), v.end(), myRand);
		copy(v.begin(), v.end(), v1.begin());
		print(v1);
		random_shuffle(v1.begin(), v1.end());
		print(v1);
		sort(v1.begin(), v1.end(), cmp);
		print(v1);
		reverse(v1.begin(), v1.end());
		print(v1);
	/*	if(assert1(v, v1)){
				cout << "ww";
		}
	*/
		
		vector<int> permutation(N);
		int j = 0;
		generate(permutation.begin(), permutation.end(), [&j]{return j++;});
		print(permutation);
		sort(permutation.begin(), permutation.end(), [&v](int a, int b){return v[a] < v[b];} );
		print(permutation);


		vector<int> sorted;
		transform(permutation.begin(), permutation.end(), back_inserter(sorted), [&v1](int j){return v1[j];});

		j = 0;
		vector<int> counts(100);
		generate(counts.begin(), counts.end(), [&j, &v1, &sorted] {
				if(assert5(sorted, v1)) return count(v1.begin(), v1.end(), j++); 
		});

}
