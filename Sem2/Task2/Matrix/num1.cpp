#include<iostream>
#include<map>
#include<vector>
#include<iterator>
#include<string>

using namespace std;


template<typename T>
class Matr{
private:
		int r;
		int c;
		vector< vector<T> > arr;
public:
		class Row{
				friend class Matr;
		private:
				Matr& fromM;
				int rM;
		public:
				Row(Matr& fromM_, int rM_) : fromM(fromM_), rM(rM_){
				}
				T& operator[](int i){
						return fromM.arr[rM][i];
				}
				const T& operator[](int i) const{
						return fromM.arr[rM][i];
				}
		};

		Matr(int r_, int c_){
				r = r_;
				c = c_;
				vector< vector<T> > tmp(r);
				for(int i = 0; i < r; ++i){
						for(int j = 0; j < c; j++){
								tmp[i].push_back(0);
						}
				}
				arr = tmp;
		}
		Row operator[](int rM_){
				return Row(*this, rM_);
		}

		friend ostream& operator<<(ostream& mout, Matr& m){
				for(int i = 0; i < m.r; i++){
						for(int j = 0; j < m.c; j++){
								mout << m[i][j] << " ";
						}
						mout << "\n";
				}
		}
								
		int get_c(){
				return c;
		}
		int get_r(){
				return r;
		}

		T tr(){
				if(r != c){
						cout << "no";
					//	T tmp = 0;
						return 0;
				}else{
						T sum = 0;
						for(int i = 0; i < r; i++){
								sum += arr[i][i];
						}
						return sum;
				}
		}
		T det(){
				if(c != r){
						cout << "no";
						return 0;
				}else{
						if(r == 1){
								return arr[0][0];
						}else{
								T sum = 0;
								for(int i = 0; i < r; i++){
										Matr tmp(r - 1, c - 1);
										for(int i1 = 0; i1 < r - 1; i1++){
												for(int j1 = 0; j1 < c - 1; j1++){
												if(j1 < i)tmp.arr[i1][j1] = arr[i1 + 1][j1];
												else tmp.arr[i1][j1] = arr[i1 + 1][j1 + 1];
												}
										}
										sum += arr[0][i] * tmp.det() * (1 - 2 * (i % 2));
								}
								return sum;
						}
				}
		}

		
		//T operator[](int i){


		Matr trans(){
				Matr<T> tmp(this-> c, this -> r);
				for(int i = 0; i < c; i++){
						for(int j = 0; j < r; j++){
								tmp[i][j] = this->arr[j][i];
						}
				}
				return tmp;
		}

		Matr operator+(Matr& other){
				if( (this->r != other.r) || (this->c != other.c) ){

						cout << "no";
						Matr<T> tmp(r, c);
						return tmp;
				}else{
						Matr<T> tmp(r, c);
						for(int i = 0; i < r; i++){
								for(int j = 0; j < c; j++){
										tmp.arr[i][j] = this->arr[i][j] + other.arr[i][j];
								}
						}
						return tmp; 
				}

		}
										
		Matr operator*(Matr& other){
				if(this->c != other.r){
						Matr<T> tmp(1, 1);
						cout << "no";
						return tmp;
				}else{
						Matr<T> tmp(this->r, other.c);
						for(int i = 0; i < this->r; i++){
								for(int j = 0; j < other.c; j++){
										T sum = 0;
										for(int k = 0; k < this->r; k++){
												sum += this->arr[i][k] * other[k][j];
										}
										tmp.arr[i][j] = sum;
								}
						}
						return tmp;
				}
		}
												


};


main(){
		Matr<int> m(2, 2);
		Matr<int> m1(1, 1);
		Matr<int> m3(2, 2);
		m[1][1] = 2;
		m[0][0] = 1;
		m1 = m.trans();
		m3 = m1 * m;
		cout << m;
		cout << m1;
		cout << m3;
		cout << m1.det();
}
