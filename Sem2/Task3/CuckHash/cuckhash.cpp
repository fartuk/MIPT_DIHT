#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<map>
#include<set>
#include<string>
#define P 1097
using namespace std;

template <typename K, typename V>
class Cuck{
private:
		vector<K> arrK;
		vector<int> arrA1;
		vector<int> arrA2;
		vector<pair<V, K>> arrVal;
		vector<char> arrValBool;
		int currM;
		int m;

public:
		int untiLoop;
		int loopFlag;
		int loop1;
		Cuck(){
				for(int i = 0; i < sizeof(K); i++){
						arrA1.push_back(3);
						arrA2.push_back(2);
				}
				currM = 0;
				m = 12;
				loop1 = 0;
				pair<V, K> nul;

				for(int i = 0; i < m; i++){
						arrVal.push_back(nul);
						arrValBool.push_back(0);
				}
				loopFlag = 0;
				untiLoop = -1;
		}
		class iterator{
		private:
				Cuck* thisCuck;
				int num;
		public:
				int getNum(){
						return num;
				}
				Cuck* getCuck(){
						return thisCuck;
				}
				iterator(Cuck* thisCuck_, int num_){
						thisCuck = thisCuck_;
						num = num_;
				}
				pair<K, V> operator*(){

						pair<K, V> tmp = pair<K, V>(thisCuck->arrK[num], thisCuck->at(thisCuck->arrK[num]));
						return tmp;
				}
				iterator& operator++(){
						num++;
						return *this;
				}
				iterator& operator--(){
						num--;
						return *this;
				}
		};
		
		friend iterator;
		int h1(K k){
				char tmp;
				int sum = 0;

				for(int i = 0; i < sizeof(K); i++){
						tmp = k  % 256;
						sum += tmp * arrA1[i];
						k = k >> 8;
				}
				return abs((sum % P) % m);
		}
		int h2(K k){
				char tmp;
				int sum = 0;

				for(int i = 0; i < sizeof(K); i++){
						tmp = k  % 256;
						sum += tmp * arrA2[i];
						k = k >> 8;
				}
				return abs((sum % P) % m);
		}
		V at(K k){
				if(arrValBool[h1(k)] != 0){
						return arrVal[h1(k)].first;
				}else{
						if(arrValBool[h2(k)] != 0){
								return arrVal[h2(k)].first;
						}else{

						}
				}
		}
		V& operator[](K k){
				if(arrValBool[h1(k)] != 0){
						return arrVal[h1(k)].first;
				}else{
						if(arrValBool[h2(k)] != 0){
								return arrVal[h2(k)].first;
						}else{
			//					insert<>
						}
				}
		}
		const V& operator[](K k)const{
				if(arrValBool[h1(k)] != 0){
						return arrVal[h1(k)].first;
				}else{
						if(arrValBool[h2(k)] != 0){
								return arrVal[h2(k)].first;
						}else{
			//					insert<>
						}
				}
		}
//		void remove(V v){
//

		void insertH(pair<K, pair<V, K>> kvPair, int from){
				loop1++;
				if(from == 1){
						if( arrValBool[h1(kvPair.first)] == 0 ){
								arrVal[h1(kvPair.first)] = kvPair.second;
								arrValBool[h1(kvPair.first)] = 1;
								currM++;
								loop1 = 1;
								arrK.push_back(kvPair.first);
								if( currM == m){
										arrVal.resize(m * 2);
										arrValBool.resize(m * 2);
										m = m * 2;
								}
						}else{
								if( arrValBool[h2(kvPair.first)] == 0 ){
										arrVal[h2(kvPair.first)] = kvPair.second;
										arrValBool[h2(kvPair.first)] = 1;
										currM++;
										arrK.push_back(kvPair.first);
								}else{
										if(loopFlag == 0){
												untiLoop = h1(kvPair.first);
												loopFlag = 1;
												pair<V, K> tmp = arrVal[h1(kvPair.first)];
												arrVal[h1(kvPair.first)] = kvPair.second;
												if(h1(tmp.second) == h1(kvPair.first)){
														insertH(pair<K, pair<V, K>>(tmp.second, tmp), 2);
												}else{
														insertH(pair<K, pair<V, K>>(tmp.second, tmp), 1);
												}
										}else{
												if( (untiLoop != h1(kvPair.first)) & (loop1 < m) ) {
														pair<V, K> tmp = arrVal[h1(kvPair.first)];
														arrVal[h1(kvPair.first)] = kvPair.second;
														if(h1(tmp.second) == h1(kvPair.first)){
																insertH(pair<K, pair<V, K>>(tmp.second, tmp), 2);
														}else{
																insertH(pair<K, pair<V, K>>(tmp.second, tmp), 1);
														}
												}else{
														loopFlag = 0;
														untiLoop = -1;
														loop1 = 1;
														for(int i = 0; i < sizeof(K); i++){
																srand(time(0));
																arrA1[i] = rand() % P;
																arrA2[i] = rand() % P;
														}
														vector<pair<V, K>>* newV = new vector<pair<V, K>>();
														vector<char>* newVBool = new vector<char>;
														for(int i = 0; i < m; i++){
																(*newV).push_back(arrVal[i]);
																(*newVBool).push_back(arrValBool[i]);
														}
														for(int i = 0; i < m; i++){
																arrValBool[i] = 0;
														}
														currM = 0;
														for(int i = 0; i < m; i++){
																if((*newVBool)[i] != 0){
																		insertH(pair<K, pair<V, K>>( (*newV)[i].second, (*newV)[i]), 1);
																}
														}
														pair<V, K> t = pair<V, K>(kvPair.second.first, kvPair.second.second);
														insertH(pair<K, pair<V, K>>( t.second, t), 1);
												}
										}
								}
						}
				}else{
						if( arrValBool[h2(kvPair.first)] == 0 ){
								arrVal[h2(kvPair.first)] = kvPair.second;
								arrValBool[h2(kvPair.first)] = 1;
								currM++;
								loop1 = 1;
								arrK.push_back(kvPair.first);
								if( currM == m){
										arrVal.resize(m * 2);
										arrValBool.resize(m * 2);
										m = m * 2;
								}
						}else{
								if( arrValBool[h1(kvPair.first)] == 0 ){
										arrVal[h1(kvPair.first)] = kvPair.second;
										arrValBool[h1(kvPair.first)] = 1;
										currM++;
										arrK.push_back(kvPair.first);
								}else{
										if(loopFlag == 0){
												untiLoop = h2(kvPair.first);
												loopFlag = 1;
												pair<V, K> tmp = arrVal[h2(kvPair.first)];
												arrVal[h2(kvPair.first)] = kvPair.second;
												if(h1(tmp.second) == h2(kvPair.first)){
														insertH(pair<K, pair<V, K>>(tmp.second, tmp), 2);
												}else{
														insertH(pair<K, pair<V, K>>(tmp.second, tmp), 1);
												}
										}else{
												if( (untiLoop != h2(kvPair.first)) & (loop1 < m) ){
														pair<V, K> tmp = arrVal[h2(kvPair.first)];
														arrVal[h2(kvPair.first)] = kvPair.second;
														if(h1(tmp.second) == h2(kvPair.first)){
																insertH(pair<K, pair<V, K>>(tmp.second, tmp), 2);
														}else{
																insertH(pair<K, pair<V, K>>(tmp.second, tmp), 1);
														}
												}else{
														loopFlag = 0;
														untiLoop = -1;
														loop1 = 1;
														for(int i = 0; i < sizeof(K); i++){
																srand(time(0));
																arrA1[i] = rand() % P;
																arrA2[i] = rand() % P;
														}
														vector<pair<V, K>>* newV = new vector<pair<V, K>>;
														vector<char>* newVBool = new vector<char>;
														for(int i = 0; i < m; i++){
																(*newV).push_back(arrVal[i]);
																(*newVBool).push_back(arrValBool[i]);
														}
														for(int i = 0; i < m; i++){
																arrValBool[i] = 0;
														}
														currM = 0;
														for(int i = 0; i < m; i++){
																if((*newVBool)[i] != 0){
																		insertH(pair<K, pair<V, K>>( (*newV)[i].second, (*newV)[i]), 1);
																}
														}
														pair<V, K> t = pair<V, K>(kvPair.second.first, kvPair.second.second);
														insertH(pair<K, pair<V, K>>( t.second, t), 1);
												}
										}
								}
						}
				}
		}
		iterator begin(){
				iterator tmp(this, 0);
				return tmp;
		}
		iterator end(){
				iterator tmp(this, currM + 1);
				return tmp;
		}
		void insert(pair<K, V> kvPair){
				pair<int, int> tmp = pair<int, int>(kvPair.second, kvPair.first);
				insertH(pair<int, pair<int, int>>(kvPair.first, tmp), 1);
		}

		void erase(Cuck<K, V>::iterator it){
				it.getCuck()->remove((*it).first );
		}
		void remove(K k){
				if(arrValBool[h1(k)] != 0){
						arrValBool[h1(k)] = 0;
						auto it = arrK.begin();
						for( it = arrK.begin(); it != arrK.end() & *it != k; it++){}
						arrK.erase(it);
				}else{
						if(arrValBool[h2(k)] != 0){
								arrValBool[h2(k)] = 0;
								auto it = arrK.begin();
								for( it = arrK.begin(); it != arrK.end() & *it != k; it++){}
								arrK.erase(it);
						}
				}
		}
};
						

		

main(){

		Cuck<int, int> q;

		q.insert(pair<int, int>(1, 25));
		q.insert(pair<int, int>(2, 23));
		q.insert(pair<int, int>(3, 245));
		q.insert(pair<int, int>(4, 452));
		q.insert(pair<int, int>(5, 21));
		q.insert(pair<int, int>(60, 22));
	


			
		Cuck<int, int>::iterator it(&q, 1);	
		int tmp = q[6];
		q[2] = 13;
		cout << q[2] << "  " << tmp << "  \n";	
		++it;
		cout <<	(*it).second;

		q.erase(it);
		
		cout <<  "\n" << (*it).second;
	
		it = q.end();
		cout << "\n" << (*it).second;


//		tmp = pair<int, int>(250, 22);
//		q.insert(pair<int, pair<int, int>>(22, tmp), 1);


		int o;
		o++;
/*		vector<int> r;
		for(int i = 0; i < 10; i++){
				r.push_back(0);
		}
		for(int i = 0; i < 1000000; i++){
				r[q.h(i)]++;
		}
		for(int i = 0; i < 10; i++){
				cout << r[i] << "\n";
		}

*/


/*		for(int n = 0; n < 8; n++){
				printf("%d ", ( c & (1 << n) ) >> n );
		}
		cout << f;
*/
		

}
