#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<memory>

using namespace std;

template <typename K, typename V>
class Vert{
private:
		weak_ptr<Vert> parent;
		shared_ptr<Vert> left;
		shared_ptr<Vert> right;
		pair<K, V> kvPair;
public:
		~Vert(){
				cout << this <<" дестр\n";
		}
		void setPair(pair<K, V> kvPair_){
				kvPair = kvPair_;
		}
		pair<K, V> getPair(){
				return kvPair;
		}
		void setParent(weak_ptr<Vert<K, V>> parent_){
				parent = parent_;
		}
		weak_ptr<Vert> getParent(){
				return parent;
		}
		void setLeft(shared_ptr<Vert<K, V>> left_){
				left = left_;
		}
		shared_ptr<Vert> getLeft(){
				return left;
		}
		void setRight(shared_ptr<Vert<K, V>> right_){
				right = right_;
		}
		shared_ptr<Vert> getRight(){
				return right;
		}
};


template <typename K, typename V>
class Tree{
private:
		shared_ptr< Vert<K, V> > nilPtr;
		shared_ptr< Vert<K, V> > rootPtr;
public:
		Tree(){
				nilPtr = make_shared< Vert<K, V> >();
				rootPtr = make_shared< Vert<K, V> >();
				//rootPtr->setParent(NULL);
				rootPtr->setPair(pair<K, V>(NULL, NULL));
				rootPtr->setLeft(nilPtr);
				rootPtr->setRight(nilPtr);
		}
		
		shared_ptr< Vert<K, V> > getRoot(){
				return rootPtr;
		}
		shared_ptr< Vert<K, V> > getNil(){
				return nilPtr;
		}	
		void insert(pair<K, V> kvPair_){
				if(rootPtr->getPair() == pair<K, V>(NULL, NULL)){
						rootPtr->setPair(kvPair_);
				}else{
						shared_ptr< Vert<K, V> > newVert(new(Vert<K, V>));
						newVert->setLeft(nilPtr);
						newVert->setRight(nilPtr);
						newVert->setPair(kvPair_);
						shared_ptr< Vert<K, V> > goDown;
						goDown = rootPtr;
						shared_ptr< Vert<K, V> > parentGoDown(nilPtr);
						while((goDown != nilPtr) && (goDown->getPair().first != kvPair_.first)){
								parentGoDown = goDown;
								if(newVert->getPair().first < goDown->getPair().first){
										goDown = goDown->getLeft();
								}else{
										goDown = goDown->getRight();
								}
						}
						if(goDown->getPair().first == kvPair_.first){
								goDown->setPair(kvPair_);
						}else{
								weak_ptr< Vert<K, V>> tmpW(parentGoDown);
								newVert->setParent(tmpW);
								if(newVert->getPair().first < parentGoDown->getPair().first){
										parentGoDown->setLeft(newVert);
								}else{
										if(newVert->getPair().first > parentGoDown->getPair().first){
												parentGoDown->setRight(newVert);
										}else{
												parentGoDown = newVert;
										}
								}
						}
				}
		}
		shared_ptr< Vert<K, V> > search(K key){
				shared_ptr< Vert<K, V> > x;
				x = rootPtr;
				while((x != nilPtr) && (key != x->getPair().first)){
						if(key < x->getPair().first){
								x = x->getLeft();
						}else{
								x = x->getRight();
						}
				}
				return x;
		}
		shared_ptr< Vert<K, V> > min(shared_ptr< Vert<K, V> > x){
				while(x->getLeft() != nilPtr){
						x = x->getLeft();
				}
				return x;
		}
		shared_ptr< Vert<K, V> > next(shared_ptr< Vert<K, V> > x){
				K tmp;
				tmp = x->getPair().first;
				if(x->getRight() != nilPtr){
						return min(x->getRight());
				}else{
						shared_ptr< Vert<K, V> > y;
						y = (x->getParent()).lock();
						while((x == y->getRight()) && (y != rootPtr)){
								x = y;
								y = (y->getParent()).lock();
						}
						if(y->getPair().first > tmp){
								return y;
						}else{
								return nilPtr;
						}
				}
		}
	//	void test(){

		
};


main(){
		Tree<int, int> m;
		m.insert(pair<int, int>(1, 50));
		m.insert(pair<int, int>(4, 40));
		m.insert(pair<int, int>(5, 40));
		cout << "начало программы\n";
		cout << m.getRoot() << " корень(1)\n";	
		cout << m.getNil() << " лист()\n";	
		cout << m.getRoot()->getRight() << " правый сын(4)\n";	
		cout << m.getRoot()->getRight()->getRight() << " правый внук(5)\n\n";	

		m.getRoot()->getRight()->setRight(m.getNil());
			
		cout << "Еще не конец программы\n";	
	//	cout << m.min( m.getRoot() )->getPair().first;
	
	//	cout << m.next(m.getRoot())->getPair().first;
	//	cout << m.next(m.search(1))->getPair().first;

		int y;
		y++;
}
