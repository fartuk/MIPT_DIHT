#include<iostream>
#include<algorithm>
#include<stddef.h>
#include<stdio.h>
char gl;
class BitRef{
	public:
		char* byteRef;
		int idx;
		BitRef& operator=(bool other){
		//		std::cout << "oper";
				if(other){
						*byteRef = *byteRef | (1 << idx);
				}
				else{
						*byteRef = *byteRef | (1 << idx);
						*byteRef = *byteRef ^ (1 << idx);
				}
				return *this;			
		}
		BitRef& operator=(BitRef other){
				idx = other.idx;
				byteRef = other.byteRef;
				return *this;	
		}
		bool operator==(bool other){
				bool tmp;
				if( (*byteRef | (1 << idx) ) ==  *byteRef){
						tmp = true;
				}else{
						tmp = false;
				}
				return tmp == other;
		}

		BitRef(char* byteRef_, int idx_){
				byteRef = byteRef_;
				idx = idx_;
		}
	 	void print(){
				int n = 0;
				//arr[1] = arr[1] | (1 << 1);
				for(n = 0; n < 8; n++){
						printf("%d ", ( *byteRef & (1 << n) ) >> n );
				}
				std::cout << "\n";
		}
		BitRef(const BitRef& other){
				idx = other.idx;
				byteRef = other.byteRef;
		}
					
};
class BoolVect{
	private:
		ptrdiff_t boolSize;
		ptrdiff_t size;
		ptrdiff_t capacity;
	public:
		char* arr;
		BoolVect(ptrdiff_t firstSize){
				boolSize = firstSize;
				firstSize /= 8;
				if(firstSize % 8 != 0){
						firstSize++;
				}
	//			std::cout << firstSize;
				arr = new char[firstSize];
				capacity = firstSize;
				size = firstSize;
				for(int i = 0; i < size; i++){
						arr[i] = 0;
				}
		}
		void print(){
				for(int i = 0; i < size; i++){
						int n = 0;
						for(n = 0; n < 8; n++){
								printf("%d ", ( arr[i] & (1 << n)) >> n );
						};	
						std::cout  << "\n";
				}
		}
		BitRef operator[](ptrdiff_t i){
				int index = i % 8;
				i /= 8;
			//	std::cout << "\n*" << i << "*\n";	
			//	std::cout << "\n*" << index << "*\n";	
				std::cout << "\n*" << i << "*\n";	
				std::cout << "\n*" << index << "*\n";	
				BitRef tmp(&(arr[i]), index);
			//	BitRef& tmpRef = tmp;
				return tmp;
		}
		const BitRef& operator[](ptrdiff_t i) const{
				int index = i % 8;
				i /= 8;
				std::cout << "\n*" << i << "*\n";	
				std::cout << "\n*" << index << "*\n";	

				BitRef tmp(&(arr[i]), index);
				const BitRef& tmpRef = tmp;
				return tmpRef;
		}
		void resize(){
				char* arrTemp = new char[capacity * 2];
				for(int i = 0; i < capacity; i++){
						arrTemp[i] = arr[i];
				}
				capacity *= 2;
				arr = arrTemp;
			//	delete[] arrTemp;
		}
		void pushBack(bool x){
				if(size == capacity){
						resize();
						if(x){
								arr[boolSize / 8] = arr[boolSize / 8] | (1 << (boolSize % 8));
						}else{
								arr[boolSize / 8] = arr[boolSize / 8] | (1 << (boolSize % 8));
								arr[boolSize / 8] = arr[boolSize / 8] ^ (1 << (boolSize % 8));
						}
						if(boolSize % 8 == 0){
								size++;
						}
						boolSize++;		
	
				}else{
						if(x){
								arr[boolSize / 8] = arr[boolSize / 8] | (1 << (boolSize % 8));
						}else{
								arr[boolSize / 8] = arr[boolSize / 8] | (1 << (boolSize % 8));
								arr[boolSize / 8] = arr[boolSize / 8] ^ (1 << (boolSize % 8));
						}
						if(boolSize % 8 == 0){
								size++;
						}
						boolSize++;
				}

		}





};
main(){
		BoolVect q(100);
		q.print();
		char* tmp = &(q.arr[2]);
		BitRef a(tmp, 2);
		//q[i] = true;
		std::cout << "-------------------------\n";
		a.print();	
		a = q[0];
		a = true;	
		//q[0] = true;
		q[7] = true;
		q[9] = true;
		q[20] = false;
		q.pushBack(true);
		q.pushBack(true);
		q.pushBack(true);
		q.pushBack(true);
		q[102] = false;
		q[101] = false;
		std::cout << "-------------------------\n";
	q.print();	
		std::cout << "-------------------------\n";
		if(q[101] == true){
				std::cout << "true";
		}else{
				std::cout << "false";
		}
		//q[51].print();	
}
