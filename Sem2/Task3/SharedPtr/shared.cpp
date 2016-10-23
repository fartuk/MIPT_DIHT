#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<map>
#include<set>
#include<string>

using namespace std;


template <typename T>
class shP{
private:
		class Helper{
		private:
				int countShared;
				T* ptr;
		public:
				Helper(){
						ptr = nullptr;
						countShared = 1;
				}
				Helper(T* ptr_){
						ptr = ptr_;
						countShared = 1;
				}



				void dec(){
						if(countShared == 1){
								delete ptr;
						}else{
								countShared--;
						}
				}
				void inc(){
						countShared++;
				}
				T* getPtr(){
						return ptr;
				}

	
		};
		Helper* ptHelper;
public:
		Helper* getHelper() const{
				return ptHelper;
		}
		shP(){
				Helper* ptHelper = new Helper;
		}
		shP(T* t){
				ptHelper = new Helper(t);
		}
		shP(const shP<T>& otherShP){
				ptHelper = otherShP.ptHelper;
				ptHelper->inc();
		}
		~shP(){
				ptHelper->dec();
		}
		T& operator*(){
				return *(ptHelper->getPtr());
		}
		T* get(){
				return ptHelper->getPtr();
		}
		shP<T> operator=(const shP<T>& otherShP){
				if(this == &otherShP){
				}else{
						ptHelper = otherShP.getHelper();
						ptHelper->inc();
				}
				return *this;


		}
		T* operator->(){
				return ptHelper->getPtr();
		}
};

class obj{
public:
		int y;
		obj(){
				y = 0;
		}
		obj(int y_){
				y = y_;
		}
		void set(int y_){
				y = y_;
		}
};

main(){
		shP<long long> m;
		//shP<long long> n(new foo());
		shP<obj> n(new obj);
		shP<obj> r;
		r = n;


		cout << (*n).y << "\n";
		n->set(2);	
		cout << n->y << "\n";
		cout << (*r).y << "\n";
		cout << r->y << "\n\n";
/*		
		obj* p = new obj(2);
		{
			shP<obj> e(p);
			shP<obj> w(new obj(1));
			cout << w->y;
		}

		cout << " " << p->y; // неп, т к деструктор после вызова деструктора shared 
							 // вызывается деструктор helper'а, который делает delete объекта, которым владеет 

*/
}
