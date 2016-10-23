#include<iostream>
#include<algorithm>
#include<stddef.h>
template <typename T>
class Vector{
	private:
		ptrdiff_t size;
		ptrdiff_t capacity;
		T *arr;
	public:
		class iterator{
				ptrdiff_t idx;
				Vector *thisVector;
				public:
					typedef T value_type;
					typedef T* pointer;
					typedef T& reference;
					typedef ptrdiff_t difference_type;
					typedef std::random_access_iterator_tag iterator_category;
				
				iterator(Vector* _thisVector, ptrdiff_t _idx){
						thisVector = _thisVector;
						idx = _idx;
				}
				
				iterator& operator++(){
						++idx;
						iterator& tmp = *this;
						return tmp;
				}
				iterator& operator--(){
						--idx;
						iterator& tmp = *this;
						return tmp;
				}
				T& operator*(){
						T s = thisVector->arr[idx];
						T& ref = s;	
						return ref;
				}
				bool operator>(const iterator& another){
						if(this->idx > another.idx){
								return true;
						}
						else{
								return false;
						}
				}
				bool operator<(const iterator& another){
						if(this->idx < another.idx){
								return true;
						}
						else{
								return false;
						}
				}

				bool operator!=(const iterator& another) const{
						if(this->idx != another.idx){
								return true;
						}
						else{
								return false;
						}
				}
				bool operator==(const iterator& another) const{
						if(this->idx == another.idx){
								return true;
						}
						else{
//		std::cout << "fwewwefewf" << std::endl;
								return false;
						}
				}
				bool operator>(const iterator& another) const{
						if(this->idx > another.idx){
								return true;
						}
						else{
								return false;
						}
				}
				bool operator<(const iterator& another) const{
						if(this->idx < another.idx){
								return true;
						}
						else{
								return false;
						}
				}
				bool operator>=(const iterator& another) const{
						if(this->idx >= another.idx){
		std::cout << "aaaaaaaaaaaaa" << std::endl;
								return true;
						}
						else{
								return false;
						}
				}
				bool operator<=(const iterator& another) const{
						if(this->idx <= another.idx){
								return true;
						}
						else{
								return false;
						}
				}
				iterator& operator+=(const ptrdiff_t num){
						idx += num;
						iterator& tmp = *this;
						return tmp;
				}
				iterator& operator-=(const ptrdiff_t num){
						idx -= num;
						iterator& tmp = *this;
						return tmp;
				}
				iterator operator+(const ptrdiff_t num){
						Vector<T>::iterator tmp  = *this;
						tmp.idx = idx + num;
						return tmp;
				}
				iterator operator-(const ptrdiff_t num){
						Vector<T>::iterator tmp = *this;
						tmp.idx = idx - num;
						return tmp;
				}
				ptrdiff_t operator-(const iterator& another) const{
						return (this->idx - another.idx);
				}
				
		};
		
		friend iterator;

		iterator begin(){
				iterator it(this, 0);
				return it;
		}
		iterator end(){
				iterator it(this, size);
				return it;
		};
		Vector(const Vector& obj){
				capacity = obj.capacity;
				size = obj.size;
				arr = new T[capacity];
				for(int i = 0; i < capacity; i++){
					arr[i] = obj.arr[i];
				}
		}

			
		Vector(ptrdiff_t firstSize){
			arr = new T[firstSize];
			capacity = firstSize;
			size = firstSize;
		}
		~Vector(){
			delete[] arr;
		}
//		int Get(ptrdiff_t i);
//		void Set(ptrdiff_t i, int x);
		void PushBack(T x);
		//ptrdiff_t Size();
		//ptrdiff_t Capacity();
		void Resize();

		const T& operator[](ptrdiff_t index) const{

			if(index <= size){
				return arr[index];
			}
		}

		T& operator[](ptrdiff_t index){

			return arr[index];
		}

		Vector& operator=(Vector& other){
			if(this != &other){
					size = other.size;
					free(arr);
					capacity = other.capacity;
					arr = new T[capacity];
					for(int i = 0; i < capacity; i++){
							arr[i] = other.arr[i];
					}
			}
			return *this;
		}
};

template <typename T>
void Vector<T>::Resize(){
	T *arrTemp = new T[capacity * 2];
	for(int i = 0; i < capacity; i++){
		arrTemp[i] = arr[i];
	}
	capacity *= 2;
	arr = arrTemp;
//	delete[] arrTemp;
}
/*
void Vector::Set(ptrdiff_t i, int x){
	if(i <= size){
		arr[i] = x;
	}
}

int Vector::Get(ptrdiff_t i){
	if(i <= size){
		return arr[i];
	}
}
*/
template <typename T>
void Vector<T>::PushBack(T x){
	if(size == capacity){
		Resize();
		arr[size] = x;
		size++;

	}else{
		arr[size] = x;
		size++;
	}

}

template <typename T>
class TLessCmp{
public:
	bool operator() (const T& a, const T& b){
		if(a < b){
			return true;
		}else{
			return false;
		}
	}
};
main(){
	Vector<double> my(2);
	Vector<double> my1(6);
	my[0] = 5;
	my[1] = 2;
	my.PushBack(777);
	my.PushBack(778);
	my.PushBack(178);
	my.PushBack(4378);
	my1 = my;
//	my[1] = 334;
	for(int i = 0; i < 6; i++){
		std::cout << my[i] << std::endl;
	}
	//std::cout << my.Get(2) << std::endl;
	double sum = 0;

	Vector<double>::iterator it = my.begin();
	Vector<double>::iterator it1 = my.begin();
/*	for(it; it != my.end(); ++it){
			sum = sum + (*it);
	}
*/	
	TLessCmp<double> cmp;
	std::sort(my.begin(), my.end(), cmp);
	
	std::cout << "\n _______________\n" << std::endl;
	for(int i = 0; i < 6; i++){
		std::cout << my[i] << std::endl;
	}

	//std::cout << *it << std::endl;
	//std::cout << it - it1  << std::endl;
	std::cout << "\n _______________\n" << std::endl;
	it = my.begin();
	it1 = my.begin();
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	it = it + 2;
	std::cout << *it << std::endl;
	//istd::cout << *it1 << std::endl;
			/*
	if(it1 == it){
		std::cout << "yes" << std::endl;
	}*/
}
