#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<map>
#include<set>
#include<string>

using namespace std;


class myStruct{
private:
		map<int,  set<string> > memVote;//участницы в порядке голосов, одинаковые - в порядке  фамилий
		map<string,  int> memName;//участницы по фамилиям, второе поле голоса
		map<string, pair<bool, int> > phone;


public:
		myStruct(){
				set<string> mem;
				memVote.insert(pair<int, set<string> >(0, mem));
				memName.insert(pair<string, int>("qqw", 0));
		}
		void reg(string name){
				map<string, int>::iterator it = memName.find(name);
				if(it == memName.end()){
						memName.insert(pair<string, int>(name, 0));
						map<int, set<string> >::iterator it1 = memVote.find(0);
						it1->second.insert(name);
						cout << "OK\n";
				}else{
						cout << "Уже зарегистрирована\n";
				}
		}

		void kick(string name){
				map<string, int>::iterator it = memName.find(name);
				if(it != memName.end()){
						map<int, set<string> >::iterator it1 = memVote.find(it->second);
						it1->second.erase(it1->second.find(name));
						memName.erase(memName.find(name));
						cout << "OK\n";
				}else{
						cout << "Не зарегистрирована\n";
				}
		}

		void vote(string name, string phoneNumber){
				map<string, int>::iterator it = memName.find(name);
				if(it == memName.end()){
						cout << "Не зарегистрирована\n";
				}else{
						map<string, pair<bool, int> >::iterator it1 = phone.find(phoneNumber);
						if( (it1 == phone.end()) | ( it1->second.first == 1 & it1->second.second < 3 )){
								if(it1 == phone.end()){
										pair<bool, int> tmp = pair<bool, int>(0, 1);
										phone.insert(pair<string, pair<bool, int>>(phoneNumber, tmp));
								}else{
										it1->second.second++;
								}
								map<int, set<string> >::iterator it2 = memVote.find(it->second);
								it2->second.erase(it2->second.find(name));
								it->second++;
								map<int, set<string> >::iterator it3 = memVote.find(it->second);
								if(it3 != memVote.end()){
										it3->second.insert(name);
								}else{
										set<string> tmp;
										tmp.insert(name);
										memVote.insert(pair<int, set<string> >(it->second, tmp));
								}
								cout << it->second << "\n";
						}else{
								cout << "Больше нельзя голосовать\n";
						}
				}
		}
		
		void vip(string phoneNumber){
				map<string, pair<bool, int> >::iterator it = phone.find(phoneNumber);
				if(it != phone.end()){
						if(it->second.first == 0){
								it->second.first = 1;
								cout << "OK\n";
						}else{
								cout << "Уже VIP\n";
						}
				}else{
						pair<bool, int> tmp = pair<bool, int>(1, 0);
						phone.insert(pair<string, pair<bool, int> >(phoneNumber, tmp) );
				}
		}


		void top(int k){
				int i = 0;
				for(auto it = memVote.rbegin(); it != memVote.rend(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end() & i < k; it1++, i++){
								cout << *it1 << " " << memName.find(*it1)->second << "\n";
						}
				}
		}


};


main(){
		myStruct m;
		m.reg("mary");
		m.reg("mary");
		m.reg("ola");
		m.top(10);
		m.vote("mary", "7987");
		m.vote("mary", "7987");
		m.vip("7987");
		m.vote("mary", "7987");
		m.vote("ola", "7999");
		m.top(10);
		m.kick("ola");
		m.top(10);
		

}


