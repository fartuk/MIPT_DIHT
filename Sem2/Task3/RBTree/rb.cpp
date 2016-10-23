#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

template <typename K, typename V>
class Vert{
private:
		Vert* parent;
		Vert* left;
		Vert* right;
		int color;
		pair<K, V> kvPair;
public:
		void setPair(pair<K, V> kvPair_){
				kvPair = kvPair_;
		}
		pair<K, V> getPair(){
				return kvPair;
		}
		void setParent(Vert* parent_){
				parent = parent_;
		}
		Vert* getParent(){
				return parent;
		}
		void setLeft(Vert<K, V>* left_){
				left = left_;
		}
		Vert* getLeft(){
				return left;
		}
		void setRight(Vert<K, V>* right_){
				right = right_;
		}
		Vert* getRight(){
				return right;
		}
		void setColor(int color_){
				color = color_;
		}
		int getColor(){
				return color;
		}
};



template <typename K, typename V>
		void print(Vert<K, V>* p, Vert<K, V>* nil, int level){
				if(p != nil){
						print(p->getRight(), nil, level + 1);
						for(int i = 0; i < level; i++){
								cout << "        ";
						}
						K key = p->getPair().first;
						cout << p->getPair().first << "|" <<  p->getColor()  << endl;
						print(p->getLeft(), nil, level + 1);
				}
		}


template <typename K, typename V>
class Tree{
private:
		Vert<K, V> root;
		Vert<K, V> nil;
		int counter;
public:
		class iterator{
		private:
				Tree* thisTree;
				Vert<K, V>* thisVert;
		public:
				iterator(Vert<K, V>* thisVert_, Tree* thisTree_){
						thisVert = thisVert_;
						thisTree = thisTree_;
				}
			
				pair<K, V> operator*(){
						return thisVert->getPair();
				}
				iterator operator++(){
						iterator it(thisTree->next(thisVert), thisTree);
						thisVert = thisTree->next(thisVert);
						iterator& tmp = it;	
						return tmp;
				}
				iterator operator--(){
						iterator it(thisTree->last(thisVert), thisTree);
						thisVert = thisTree->last(thisVert);
						iterator& tmp = it;	
						return tmp;
				}
				iterator operator+(const ptrdiff_t num){
						for(int i = 0; i < num; i++){
								thisVert = thisTree->next(thisVert);
						}
						iterator it(thisVert, thisTree);
						return it;
				}
				iterator operator-(const ptrdiff_t num){
						for(int i = 0; i < num; i++){
								thisVert = thisTree->last(thisVert);
						}
						iterator it(thisVert, thisTree);
						return it;
				}
				iterator& operator +=(const ptrdiff_t num){
						for(int i = 0; i < num; i++){
								thisVert = thisTree->next(thisVert);
						}
						iterator it(thisVert, thisTree);
						iterator& tmp = it;	
						return tmp;
				}
				iterator& operator -=(const ptrdiff_t num){
						for(int i = 0; i < num; i++){
								thisVert = thisTree->last(thisVert);
						}
						iterator it(thisVert, thisTree);
						iterator& tmp = it;	
						return tmp;
				}
				bool operator<(const iterator& another){
						return ((thisVert->getPair().first < another.thisVert->getPair().first) && (thisTree == another.thisTree));
				}
				bool operator>(const iterator& another){
						return ((thisVert->getPair().first > another.thisVert->getPair().first) && (thisTree == another.thisTree));
				}
				bool operator>=(const iterator& another){
						return ((thisVert->getPair().first >= another.thisVert->getPair().first) && (thisTree == another.thisTree));
				}
				bool operator<=(const iterator& another){
						return ((thisVert->getPair().first <= another.thisVert->getPair().first) && (thisTree == another.thisTree));
				}
				bool operator==(const iterator& another){
						return ((thisVert->getPair().first == another.thisVert->getPair().first) && (thisTree == another.thisTree));
				}
				bool operator!=(const iterator& another){
						return (thisVert->getPair().first != another.thisVert->getPair().first);
				}

		};

		friend iterator;

		iterator begin(){
				iterator it(min(&root), this);
				return it;
		}
		
		iterator end(){
				iterator it(max(&root), this);
				return it;
		}


		Tree(){
				nil.setColor(1);
				root.setParent(NULL);
				root.setPair(pair<K, V>(NULL, NULL));
				root.setLeft(&nil);
				root.setRight(&nil);
				counter = 0;
		}
		void incCount(){
				counter++;
		}

		void leftRotate(Vert<K, V>* x){
				Vert<K, V>* y;
				Vert<K, V> x1;
				x1 = *x;
				y = x->getRight();
				if(x != &root){
						if(y->getLeft() != &nil){
								y->getLeft()->setParent(x);
						}
						x->setRight(y->getLeft());
						y->setParent(x->getParent());
						if(x->getParent()->getLeft() == x){
								x->getParent()->setLeft(y);
						}else{
								x->getParent()->setRight(y);
						}
						y->setLeft(x);
						x->setParent(y);
				}else{
						root = *y;
						root.setParent(NULL);
						*y = x1;
						root.getLeft()->setParent(y);
						y->setRight(root.getLeft());
						root.setLeft(y);
						y->setParent(&root);
				}


		}
		void rightRotate(Vert<K, V>* x){
				Vert<K, V>* y;
				Vert<K, V> x1;
				x1 = *x;
				y = x->getLeft();
				if(x != &root){
						y->getRight()->setParent(x);
						y->setParent(x->getParent());
						x->setLeft(y->getRight());
						if(x->getParent()->getRight() == x){
								x->getParent()->setRight(y);
						}else{
								x->getParent()->setLeft(y);
						}
						y->setRight(x);
						x->setParent(y);
				}else{
						root = *y;
						root.setParent(NULL);
						*y = x1;
						root.getRight()->setParent(y);
						y->setLeft(root.getRight());
						root.setRight(y);
						y->setParent(&root);
				}


		}


						

		Vert<K, V>* insert(pair<K, V> kvPair_){
				if(root.getPair() == pair<K, V>(NULL, NULL)){
						root.setPair(kvPair_);
						root.setColor(1);
						incCount();
						return &root;
				}else{
						Vert<K, V>* newVert = new(Vert<K, V>);
						newVert->setLeft(&nil);
						newVert->setRight(&nil);
						newVert->setPair(kvPair_);
						newVert->setColor(0);
						Vert<K, V>* goDown;
						Vert<K, V>* parentGoDown;
						parentGoDown = &nil;
						goDown = &root;
						while((goDown != &nil) && (goDown->getPair().first != kvPair_.first)){
								parentGoDown = goDown;
								if(newVert->getPair().first < goDown->getPair().first){
										goDown = goDown->getLeft();
								}else{
										goDown = goDown->getRight();
								}
						}
						if(goDown->getPair().first == kvPair_.first){
								goDown->setPair(kvPair_);
								return goDown;
						}else{
								newVert->setParent(parentGoDown);
								if(newVert->getPair().first < parentGoDown->getPair().first){
										parentGoDown->setLeft(newVert);
								}else{
										if(newVert->getPair().first > parentGoDown->getPair().first){
												parentGoDown->setRight(newVert);
										}else{
												parentGoDown = newVert;
										}
								}
								incCount();
								return newVert;
						}
				}
		}
		void rbInsert(pair<K, V> kvPair_ ){
				Vert<K, V>* x = insert(kvPair_);
				Vert<K, V>* y;
				while((x != &root) && (x->getParent()->getColor() == 0)){
						if( x->getParent() == x->getParent()->getParent()->getLeft() ){
								y = x->getParent()->getParent()->getRight();
								if(y->getColor() == 0){
										x->getParent()->setColor(1);
										y->setColor(1);
										x->getParent()->getParent()->setColor(0);
										x = x->getParent()->getParent();
								}else{
										if(x == x->getParent()->getRight()){
												x = x->getParent();
												leftRotate(x);
										}
										x->getParent()->setColor(1);
										x->getParent()->getParent()->setColor(0);
										rightRotate(x->getParent()->getParent());
								}
						}else{
								y = x->getParent()->getParent()->getLeft();
								if(y->getColor() == 0){
										x->getParent()->setColor(1);
										y->setColor(1);
										x->getParent()->getParent()->setColor(0);
										x = x->getParent()->getParent();
								}else{
										if(x == x->getParent()->getLeft()){
												x = x->getParent();
												rightRotate(x);
										}
										x->getParent()->setColor(1);
										x->getParent()->getParent()->setColor(0);
										leftRotate(x->getParent()->getParent());
								}
						}
				}
				root.setColor(1);
		}

		Vert<K, V>* min(Vert<K, V>* x){
				while(x->getLeft() != &nil){
						x = x->getLeft();
				}
				return x;
		}

		Vert<K, V>* max(Vert<K, V>* x){
				while(x->getRight() != &nil){
						x = x->getRight();
				}
				return x;
		}
		Vert<K, V>* search(K key){
				Vert<K, V>* x;
				x = &root;
				while((x != &nil) && (key != x->getPair().first)){
						if(key < x->getPair().first){
								x = x->getLeft();
						}else{
								x = x->getRight();
						}
				}
				return x;
		}
		Vert<K, V>* next(Vert<K, V>* x){
				K tmp;
				tmp = x->getPair().first;
				if(x->getRight() != &nil){
						return min(x->getRight());
				}else{
						Vert<K, V>* y;
						y = x->getParent();
						while((x == y->getRight()) && (y != &root)){
								x = y;
								y = y->getParent();
						}
						if(y->getPair().first > tmp){
								return y;
						}else{
								return &nil;
						}
				}
		}
		Vert<K, V>* last(Vert<K, V>* x){
				K tmp;
				tmp = x->getPair().first;
				if(x->getRight() != &nil){
						return min(x->getLeft());
				}else{
						Vert<K, V>* y;
						y = x->getParent();
						while((x == y->getLeft()) && (y != &root)){
								x = y;
								y = y->getParent();
						}
						if(y->getPair().first > tmp){
								return y;
						}else{
								return &nil;
						}
				}
		}



		void fix(Vert<K, V>* x){
				Vert<K, V>* y;
				while((x != &root) && (x->getColor() == 1)){
						if(x == x->getParent()->getLeft()){
								y  = x->getParent()->getRight();
								if(y->getColor() == 0){
										y->setColor(1);
										x->getParent()->setColor(1);
										leftRotate(x->getParent());
										y = x->getParent()->getRight();
								}
								if((y->getLeft()->getColor() == 1) && (y->getRight()->getColor() == 1)){
										y->setColor(0);
										x = x->getParent();
								}else{
										if(y->getRight()->getColor() == 1){
												y->getLeft()->setColor(1);
												y->setColor(0);
												rightRotate(y);
												y = x->getParent()->getRight();
										}
										y->setColor(x->getParent()->getColor());
										x->getParent()->setColor(1);
										y->getRight()->setColor(1);
										leftRotate(x->getParent());
										x = &root;
								}
						}else{
								y  = x->getParent()->getLeft();
								if(y->getColor() == 0){
										y->setColor(1);
										x->getParent()->setColor(1);
										rightRotate(x->getParent());
										y = x->getParent()->getLeft();
								}
								if((y->getRight()->getColor() == 1) && (y->getLeft()->getColor() == 1)){
										y->setColor(0);
										x = x->getParent();
								}else{
										if(y->getLeft()->getColor() == 1){
												y->getRight()->setColor(1);
												y->setColor(0);
												leftRotate(y);
												y = x->getParent()->getLeft();
										}
										y->setColor(x->getParent()->getColor());
										x->getParent()->setColor(1);
										y->getLeft()->setColor(1);
										rightRotate(x->getParent());
										x = &root;
								}
						}
				}
				x->setColor(1);
		}

		void rbDelete(Vert<K, V>* z){
				Vert<K, V>* y;
				Vert<K, V>* x;
				if((z->getLeft() == &nil) || (z->getRight() == &nil)){
						y = z;
				}else{
						y = next(z);
				}
				if(y->getLeft() != &nil){
						x = y->getLeft();
				}else{
						x = y->getRight();
				}
				x->setParent(y->getParent());
				if(y->getParent() == NULL){
						root = *x;
						root.setParent(NULL);
				}else{
						if(y == y->getParent()->getLeft()){
								y->getParent()->setLeft(x);
						}else{
								y->getParent()->setRight(x);
						}
				}
				if(y != z){
						z->setPair(y->getPair());
				}
				if(y->getColor() == 1){
						fix(x);
				}

		}

		V operator[](K key){
				return search(key)->getPair().second;
		}
		int count(){
				return counter;
		}

		Vert<K, V>* getRoot(){
				return &root;
		}
		Vert<K, V>* getNil(){
				return &nil;
		}

/************************************************/

		





};



main(){
		Tree<int, int> m;
		m.rbInsert(pair<int, int>(10, 20));
		m.rbInsert(pair<int, int>(13, 25));
		m.rbInsert(pair<int, int>(6, 25));
		m.rbInsert(pair<int, int>(11, 25));
		m.rbInsert(pair<int, int>(8, 25));
		m.rbInsert(pair<int, int>(15, 25));
		m.rbInsert(pair<int, int>(30, 25));
		m.rbInsert(pair<int, int>(3, 25));
/*		
		m.rbInsert(pair<int, int>(2, 25));
		m.rbInsert(pair<int, int>(3, 25));
		m.rbInsert(pair<int, int>(1, 25));
		m.rbInsert(pair<int, int>(4, 25));
		m.rbInsert(pair<int, int>(40, 25));
		m.rbInsert(pair<int, int>(50, 26));
		m.rbInsert(pair<int, int>(60, 25));
		m.rbInsert(pair<int, int>(4, 25));

	*/
		int y;
		y = y + 2;
	
		print(m.getRoot(), m.getNil(), 0);	
//		m.rbDelete(m.search(2));
		print(m.getRoot(), m.getNil(), 0);	
	//	cout << m.last(m.getRoot()->getRight())->getPair().first;
		Tree<int, int>::iterator it = m.begin();
		Tree<int, int>::iterator it1 = m.end();
		cout << "\n---------------" << (*it).first;
		if(it < it1){
				cout << "www";
		}
		++it;
		it = it + 2;
		it += 2;
		cout << "\n---------------" << (*it).first;
		cout << "\n" << m[50];
		cout << "\n" << m.count();
/*		
		cout << "           " << m.getRoot()->getPair().first << "|" << m.getRoot()->getColor() << "\n";
		cout << "     " << m.getRoot()->getLeft()->getPair().first << "|" << m.getRoot()->getLeft()->getColor() << "         ";
		cout << m.getRoot()->getRight()->getPair().first << "|" << m.getRoot()->getRight()->getColor() << "\n";
		cout << "        " <<m.getRoot()->getLeft()->getRight()->getPair().first << "|" << m.getRoot()->getLeft()->getLeft()->getColor() << "    ";
		cout << m.getRoot()->getRight()->getLeft()->getPair().first << "|" << m.getRoot()->getRight()->getLeft()->getColor() <<"    ";
		cout << m.getRoot()->getRight()->getRight()->getPair().first << "|" << m.getRoot()->getRight()->getRight()->getColor() << "\n";
		cout << "--------------------------------\n";
//		print(m.getRoot(), m.getNil(), 0);	

		
		cout << "           " << m.getRoot()->getPair().first << "\n";
		cout << "     " << m.getRoot()->getLeft()->getPair().first << "         ";
		cout << m.getRoot()->getRight()->getPair().first << "\n";
		cout << " " <<m.getRoot()->getLeft()->getLeft()->getPair().first << "    ";
		cout << m.getRoot()->getLeft()->getRight()->getPair().first << "  \n  ";
		cout << m.getRoot()->getLeft()->getLeft()->getRight()->getPair().first << "\n";
		cout << "--------------------------------\n";
		m.rightRotate(m.getRoot());
		
		cout << "           " << m.getRoot()->getPair().first << "\n";
		cout << "     " << m.getRoot()->getLeft()->getPair().first << "         ";
		cout << m.getRoot()->getRight()->getPair().first << "\n";
		cout << "        " <<m.getRoot()->getLeft()->getRight()->getPair().first << "    ";
		cout << m.getRoot()->getRight()->getLeft()->getPair().first << "    ";
		cout << m.getRoot()->getRight()->getRight()->getPair().first << "\n";
		cout << "--------------------------------\n";
*/	
} 
