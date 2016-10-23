#include <iostream>

using namespace std;


class GameObj{
    int x;
    int y;
public:
    GameObj(int x_, int y_){
        std::cout << "Konstr class GameObj " << std::endl;
        x = x_;
        y = y_;
    }
    virtual ~GameObj(){
        std::cout << "Destr class GameObj " << std::endl;
    }
    int getx() const{
        return x;
    }
    int gety() const{
        return y;
    }
    virtual void print() const{
        std::cout << "GameObj " << getx() << " " << gety() << " " << std::endl;
    }

};

class Creature: public GameObj{
    int hp;
public:
    Creature(int x_, int y_, int hp_) : GameObj(x_, y_) {
        hp = hp_;
        std::cout << "Konstr class Creature " << std::endl;
    }
    ~Creature(){
        std::cout << "Destr class Creature " << std::endl;
    }
    int gethp() const{
        return hp;
    }
    void print() const{
        std::cout << "Creature " << getx() << " " << gety() << " " << gethp() << std::endl;
    }
};

class Mob: public Creature{
    int line;
public:
    Mob(int x_, int y_, int line_) : Creature(x_, y_, 50) {
        line = line_;
        std::cout << "Konstr class Mob " << std::endl;
    }
    ~Mob(){
        std::cout << "Destr class Mob " << std::endl;
    }
    int getline() const{
        return line;
    }
    void print() const{
        std::cout << "Mob " << getx() << " " << gety() << " " << gethp() << " " << getline() << std::endl;
    }
};

class Hero : public Creature{
    string name;
public:
    Hero(int x_, int y_,  string name_):Creature(x_, y_, 500){
        std::cout << "Konstr class Hero " << std::endl;
        name = name_;
    }
    ~Hero(){
        std::cout << "Destr class Hero " << std::endl;
    }
    string getname() const{
            return name;
    };
    void print() const{
        std::cout << "Hero " << getx() << " " << gety() << " " << gethp() << " " << getname() << std::endl;
    }
};

void print_objects(GameObj *objects[], int size){
    int i = 0;
    for(i; i < size; i++){
        objects[i]->print();
    }
}
void destroy_objects(GameObj *objects[], int size){
    int i = 0;
    for(i; i < size; i++){
        delete objects[i];
    }
}

int main() {
    GameObj *objects[] = {new Hero(10, 10,  "sdv"), new Mob(10, 10,  2)};
    print_objects(objects, 2);
    destroy_objects(objects, 2);
    return 0;
}