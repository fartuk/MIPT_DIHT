#include<sstream>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
using namespace std;

class GameObj{
private:
    int x;
    int y;
public:
	char mark;
    GameObj(int x_, int y_){
        //std::cout << "Konstr class GameObj " << std::endl;
        x = x_;
        y = y_;
		mark = '?';	
    }
    virtual ~GameObj(){
       // std::cout << "Destr class GameObj " << std::endl;
    }
	virtual char getSize(){
		int size = 1;
		return size;
	}
	char getMark() const{
		return mark;
	}

    int getx() const{
        return x;
    }
    int gety() const{
        return y;
    }
	void setx(int x_){
		x = x_;
	}
	void sety(int y_){
		y = y_;
	}
    virtual void print() {
		std::cout << "GameObj (" << getx() << ", " << gety() << ") " << std::endl;
    }

};

class Creature: public GameObj{
    int hp;
public:
    Creature(int x_, int y_, int hp_) : GameObj(x_, y_) {
        hp = hp_;
		mark = '?';
    //    std::cout << "Konstr class Creature " << std::endl;
    }
    ~Creature(){
     //   std::cout << "Destr class Creature " << std::endl;
    }
	virtual char getSize(){
		int size = 1;
		return size;
	}
    int gethp() const{
        return hp;
    }
    void print(){
		std::cout << "Creature (" << getx() << ", " << gety() << ") hp " << gethp() << std::endl;
    }
};

class Monster: public Creature{
	
public:
    Monster(int x_, int y_, int hp_) : Creature(x_, y_, hp_) {
    	mark = 'm';
	//    std::cout << "Konstr class Mob " << std::endl;
    }
    ~Monster(){
    //    std::cout << "Destr class Mob " << std::endl;
    }
    void print() {
		std::cout << "Monster (" << getx() << ", " << gety() << ") hp" << gethp() << " " << std::endl;
    }
};
class Hero : public Creature{
    string name;
public:
    Hero(int x_, int y_, int hp_, string name_) : Creature(x_, y_, hp_){
    //    std::cout << "Konstr class Hero " << std::endl;
        name = name_;
		mark = name[0];
    }
    ~Hero(){
    //    std::cout << "Destr class Hero " << std::endl;
    }
    string getname() const{
            return name;
    };
    void print(){
		std::cout << "Hero (" << getx() << ", " << gety() << ") hp" << gethp() << " " << getname() << std::endl;
    }
};

class Terrain: public GameObj{
private:
	int size;
public:
    Terrain(int x_, int y_, int size_) : GameObj(x_, y_){
		size = size_;
		mark = '?';
    //    std::cout << "Konstr class Creature " << std::endl;
    }
    ~Terrain(){
     //   std::cout << "Destr class Creature " << std::endl;
    }
	char getSize(){
		return size;
	}
    virtual void print(){
		std::cout << "Terrain (" << getx() << ", " << gety() << ") size " << getSize() << std::endl;
    }
};
class Forest: public Terrain{
public:
    Forest(int x_, int y_, int size_) : Terrain(x_, y_, size_){
		mark = 'F';
    //    std::cout << "Konstr class Creature " << std::endl;
    }
    ~Forest(){
     //   std::cout << "Destr class Creature " << std::endl;
    }
    void print(){
		std::cout << "Forest (" << getx() << ", " << gety() << ") size " << getSize() << std::endl;
    }
};


class Lake: public Terrain{
public:
    Lake(int x_, int y_, int size_) : Terrain(x_, y_, size_){
		mark = 'o';
    //    std::cout << "Konstr class Creature " << std::endl;
    }
    ~Lake(){
     //   std::cout << "Destr class Creature " << std::endl;
    }
    void print(){
		std::cout << "Lake (" << getx() << ", " << gety() << ") size " << getSize() << std::endl;
    }
};

class Mountain: public Terrain{
	int heightMountain;
public:
    Mountain(int x_, int y_, int size_, int heightMountain_) : Terrain(x_, y_, size_){
		mark = '^';
		heightMountain = heightMountain_;
    //    std::cout << "Konstr class Creature " << std::endl;
    }
    ~Mountain(){
     //   std::cout << "Destr class Creature " << std::endl;
    }
	int getMountainHeight(){
		return heightMountain;
	}
    void print(){
		std::cout << "Mountain (" << getx() << ", " << gety() << ") size " << getSize() << " height " << getMountainHeight() << std::endl;
    }
};






class World{
private:
	GameObj* arrObj[100];
	int width;
	int height;
	int objCount;
	char*  map;
	void render(){
		int parity = 1;
		for(int i = 1; i < height * (width * 2 + 1) + 1; i++){
			if((i + width * 2 + 1) % (width * 2 + 1) != 0 ){
				if(i % 2 == parity){
					map[i] =  '_';
				}else{
					map[i] = '.';
				}
			}else{
				map[i] = '\n';
				if(parity == 0){
					parity = 1;
				}else{
					parity = 0;
				}
			}
		}
		map[0] = '\n';
		int j = 0; int k = 0; int i = 0;
		if(objCount > 0){
			for(int i = 0; i < objCount; i++){
				for(int j = 0; j < arrObj[i]->getSize(); j++){
					for(int k = 0; k < arrObj[i]->getSize(); k++){
						map[(width * 2 + 1) * (arrObj[i]->gety() - 1 + j ) + arrObj[i]->getx() * 2 + k * 2 ] = arrObj[i]->getMark();
					}
				}
			}
		}
	}

public:
	~World(){
		for(int i; i < objCount; i++){
			delete arrObj[i];
		}

	}
	World(int width_, int height_){
		width = width_;
		height = height_;
		objCount = 0;
		map = (char*)malloc(sizeof(char)*(height * (width * 2 + 1) + 2));
		map[height * (width * 2 + 1) + 1] = '\0';
		render();
	}		
	void show() const{
	//	char e = arrObj[0]->getMark();
		std::cout << map << std::endl;
	}
	void addObj(GameObj* newObj){
		arrObj[objCount] = newObj;
		objCount++;
		render();
	}
	void dump(){
		for(int i = 0;  i < objCount; i++){
			printf("%d. ", i);
			arrObj[i]->print();
		}
	}
	void move(int num, int x_, int  y_){
		arrObj[num]->setx(x_);		
		arrObj[num]->sety(y_);
		render();
	}		
};


int main(){
	bool q = true;
	printf(">");
//	World userWorld(5, 5);			
		string str;
		std::getline(std::cin, str);
		str = str + ' ';
		printf(">");
		int i = 0;
		string currStr;
		while(str[i] != ' '){
			currStr = currStr + str[i];
			i++;
		}
		i++;
		currStr = "";
		while(str[i] != ' '){
			currStr = currStr + str[i];
			i++;
		}
		i++;
		int x = atoi(currStr.c_str());
		currStr = "";
		while(str[i] != ' '){
			currStr = currStr + str[i];
			i++;
		}
		i++;
		int y = atoi(currStr.c_str());
		World userWorld(x, y);

	
	while(q){
		str = "";
		std::getline(std::cin, str);
		str = str + ' ';
		int i = 0;
		currStr = "";
		while(str[i] != ' '){
			currStr = currStr + str[i];
			i++;
		}
		i++;
		if(currStr == "q"){
			q = false;
			printf("ok");
		}else
			if(currStr == "create"){
					currStr = "";
					while(str[i] != ' '){
						currStr = currStr + str[i];
						i++;
					}
					i++;
					if(currStr == "monster"){
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int x = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int y = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int hp = atoi(currStr.c_str());
							Monster* pMonster = new Monster(x, y, hp);
							userWorld.addObj(pMonster);
				
					}else
						if(currStr == "hero"){
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							string name = currStr;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int x = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int y = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int hp = atoi(currStr.c_str());
							Hero * pHero = new Hero(x, y, hp, name);
							userWorld.addObj(pHero);
				
					}else
						if(currStr == "forest"){
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							int x = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int y = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int size = atoi(currStr.c_str());
							Forest * pForest = new Forest(x, y, size);
							userWorld.addObj(pForest);
				
					}else
						if(currStr == "lake"){
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							int x = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int y = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int size = atoi(currStr.c_str());
							Lake * pLake = new Lake(x, y, size);
							userWorld.addObj(pLake);
				
					}else
						if(currStr == "mountain"){
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;	
							int height = atoi(currStr.c_str());	
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							int x = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int y = atoi(currStr.c_str());
							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;

							currStr = "";
							while(str[i] != ' '){
								currStr = currStr + str[i];
								i++;
							}
							i++;
							int size = atoi(currStr.c_str());
							Mountain * pMountain = new Mountain(x, y, size, height);
							userWorld.addObj(pMountain);
				
					}
			}else
				if(currStr == "map"){
						std::string currStr;
					while(str[i] != ' '){
						currStr = currStr + str[i];
						i++;
					}
					i++;
					int x = atoi(currStr.c_str());
					std::cout << x << std::endl;
					currStr = "";
					while(str[i] != ' '){
						currStr = currStr + str[i];
						i++;
					}
					i++;
					int y = atoi(currStr.c_str());
					//World userWorld(x, y);				
				}else 
					if(currStr == "dump"){
						userWorld.dump();
					}else 
						if(currStr == "show"){
							userWorld.show();
						}else
							if(currStr == "move"){
								currStr = "";
								while(str[i] != ' '){
									currStr = currStr + str[i];
									i++;
								}
								i++;
								int num = atoi(currStr.c_str());
								currStr = "";
								while(str[i] != ' '){
									currStr = currStr + str[i];
									i++;
								}
								i++;
								int x = atoi(currStr.c_str());
								currStr = "";
								while(str[i] != ' '){
									currStr = currStr + str[i];
									i++;
								}
								i++;
								int y = atoi(currStr.c_str());
								userWorld.move(num, x, y);
							}
	printf(">");			
	}
/*	
	World myWorld(20, 10);
	GameObj a(1, 1);
	Monster b(2, 4, 12);
	Hero c(10, 5, 500, "Axe");
	Lake d(7, 7, 3);
	Mountain f(15, 7, 2, 100);
	myWorld.addObj(&a);
	myWorld.addObj(&b);
	myWorld.addObj(&c);
	myWorld.addObj(&d);
	myWorld.addObj(&f);
	myWorld.dump();
	myWorld.show();		
	myWorld.move(0, 20, 10);	
	myWorld.show();		
*/	
}	
