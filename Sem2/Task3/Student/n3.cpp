#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<map>
#include<set>
#include<string>
using namespace std;

class Student{
private:
		int tasks;
		int balls;
		string name;
public:
		Student(string name_){
				name = name_;
				tasks = 0;
				balls = 0;
		}
		int getTasks(){
				return tasks;
		}
		void incTasks(){
				tasks++;
		}
		int getBalls(){
				return balls;
		}
		void setBalls(int balls_){
				balls = balls_;
		}
};

class Task{
private:
		int count;
		int price;
public:
		int getPrice(){
				return price;
		}
		int getCount(){
				return count;
		}
		Task(int price_){
				price = price_;
				count = 0;
		}
		void incCount(){
				count++;
		}
		bool operator<(const Task other)const{
				return price < other.price;
		}
};




class myStruct{
private:
		map<string, Student> nameMap; //хранятся студенты с поиском по именам 
		map<int, set<string>> tasksMap; //дерево по количеству задач, в вершинах  сеты студентов 
		map<int, set<string>> ballsMap; //дерево по баллам, в вершинах  сеты имен
		map<int, set<Task>> tasks; //задачи по количеству решений
		vector<set<Task>::iterator > taskArr;//отсортирован
public:
		myStruct(){
				set<Task> t;
				taskArr.push_back(t.begin());
		}
		void addTask(int price_){
				map<int, set<Task>>::iterator it = tasks.find(0);
				Task newTask(price_);
				if(it != tasks.end()){
						it->second.insert(newTask);
				}else{
						
						set<Task> newSetTask;
						newSetTask.insert(newTask);
						tasks.insert(pair<int, set<Task>>(0, newSetTask));
				}
				it = tasks.find(0);
				set<Task>::iterator it1 = it->second.find(newTask);
				taskArr.push_back(it1);
		}

		void solved(string name, int taskId){


				//заполнение tasks и обновление итератора на задачу в taskArr
				Task y = *taskArr[taskId];
				map<int, set<Task>>::iterator it = tasks.find( y.getCount() );
				Task tmp = *taskArr[taskId];
				tmp.incCount();
				it->second.erase(*taskArr[taskId]);
				map<int, set<Task>>::iterator it1 = tasks.find( tmp.getCount() );
				if(it1 != tasks.end()){
						it1->second.insert(tmp);
				}else{
						set<Task> newSetTask;
						newSetTask.insert(tmp);
						tasks.insert(pair<int, set<Task>>(tmp.getCount(), newSetTask));
				}
				it1 = tasks.find( tmp.getCount() );
				taskArr[taskId] = ( (it1->second).find(tmp) );
				/************************************************/ 
				

				//занесение студента в nameMap и обновление информации о нем
				y = *taskArr[taskId];
				int balls = y.getPrice();

				map<string, Student>::iterator it2 = nameMap.find(name);
				if(it2 != nameMap.end()){
						nameMap.find(name)->second.setBalls(nameMap.find(name)->second.getBalls() + balls);
						nameMap.find(name)->second.incTasks();
				}else{
						Student newStudent(name);
						newStudent.setBalls(balls);
						newStudent.incTasks();
						nameMap.insert(pair<string, Student>(name, newStudent));
				}
				/************************************************/

				
				//заполнение tasksMap
				int tasks = nameMap.find(name)->second.getTasks() - 1;
				map<int, set<string>>::iterator it3 = tasksMap.find(tasks);
				if(it3 != tasksMap.end()){
						it3->second.erase(name);
				}
				map<int, set<string>>::iterator it4 = tasksMap.find(tasks + 1);
				if(it4 != tasksMap.end()){
						tasksMap.find(tasks + 1)->second.insert(name);
				}else{
						set<string> newNameSet;
						newNameSet.insert(name);
						tasksMap.insert(pair<int, set<string>>(tasks + 1, newNameSet));
				}
				/************************************************/




				//заполнение ballsMap
				int ballsIn = nameMap.find(name)->second.getBalls() - balls;
				map<int, set<string>>::iterator it5 = ballsMap.find(ballsIn);
				if(it5 != ballsMap.end()){
						it5->second.erase(name);
				}
				map<int, set<string>>::iterator it6 = ballsMap.find(ballsIn + balls);
				if(it6 != ballsMap.end()){
						ballsMap.find(ballsIn + balls)->second.insert(name);
				}else{
						set<string> newNameSet1;
						newNameSet1.insert(name);
						ballsMap.insert(pair<int, set<string>>(ballsIn + balls, newNameSet1));
				}
				/************************************************/

		}

		void studStat(string name){
				cout << "Баллов: " << nameMap.find(name)->second.getBalls() << "\n";
				cout << "Задач: " << nameMap.find(name)->second.getTasks() << "\n\n";
		}

		void studByTasks(){
				for(auto it = tasksMap.rbegin(); it != tasksMap.rend(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end(); it1++){
								cout << *it1 << "\n";
						}
				}
				cout << "\n";
		}
		void studByBalls(){
				for(auto it = ballsMap.rbegin(); it != ballsMap.rend(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end(); it1++){
								cout << *it1 << "\n";
						}
				}
				cout << "\n";
		}
		void studMoreTask(int k){
				map<int, set<string>>::iterator first = tasksMap.find(k);
				for(auto it = first; it != tasksMap.end(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end(); it1++){
								cout << *it1 << "\n";
						}
				}
				cout << "\n";
		}
		void studMoreBalls(int k){
				map<int, set<string>>::iterator first = ballsMap.find(k);
				for(auto it = first; it != ballsMap.end(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end(); it1++){
								cout << *it1 << "\n";
						}
				}
				cout << "\n";
		}
		void tasksBySol(){
				for(auto it = tasks.rbegin(); it != tasks.rend(); it++){
						for(auto it1 = it->second.begin(); it1 != it->second.end(); it1++){
								Task t =  *it1;
								cout << t.getCount() << "\n";
						}
				}
				cout << "\n";
		}
};

main(){
		myStruct m;
		m.addTask(10);
		m.addTask(20);
		m.addTask(200);
	
		m.solved("ivanov", 1);		
		m.solved("petrov", 2);		
		m.solved("petrov", 1);		
		m.solved("za", 2);		
		m.solved("za", 1);		
		m.solved("a", 3);		
		
		m.studStat("petrov");
		m.studByBalls();

		m.studByTasks();

		m.studMoreTask(2);
		m.studMoreBalls(20);
		m.tasksBySol();


}
