#include<iostream>
#include<map>
#include<set>
#include<iterator>
#include<string>

class Student{
		public:
				int k;
				std::map <std::string, int> stMap;
				std::string name;
				void addSubj(std::string s, int k){
						stMap.insert(std::pair <std::string, int>(s, k));
				}
				void print(){
						for(auto it = stMap.begin(); it != stMap.end(); ++it){
								std::cout << it->first << " " << it->second << "\n";
						}
				}
				bool operator<(const Student &another)const{
					return k < another.k;
					
				}
				Student& operator=(Student& another){
						stMap = another.stMap;
				}
				Student(std::string name_){
						name = name_;
				}


};


class Group{
		public:
				std::set <Student> grSet;
				void addSt(Student st){
						grSet.insert(st);
				}
				void peresda(std::string subj){
						for(auto it = grSet.begin(); it != grSet.end(); it++){
								auto itMap = it->stMap.find(subj);
								if(itMap->second < 3 ){
										std::cout<< it->name << "\n";
								}
						}
				}
				void del(int k){
						for(auto it = grSet.begin(); it != grSet.end(); it++){
								int count = 0;
								for(auto itMap = it->stMap.begin(); itMap != it->stMap.end(); itMap++){
										if(itMap->second < 3 ){
												count++;
										}
								}
								if(count >= k){
										std::cout<< it->name << "\n";
										grSet.erase(it->name);
								}
						}
				}

		friend Student;
};


int main(){

		Student m("Иванов");
		m.addSubj("матан", 2);
		m.addSubj("физ", 1);
		m.print();
		Student m1("Петров");
		m1.addSubj("матан", 1);
		m1.addSubj("физ", 31);
		m1.print();
		Group g;
		g.addSt(m);
		g.addSt(m1);
		g.peresda("матан");
		g.del(2);

}	
