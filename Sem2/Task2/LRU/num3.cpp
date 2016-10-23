#include<iostream>
#include<unordered_map>
#include<set>
#include<list>
#include<iterator>
using namespace std;


int func(int k){
		return k*2;
}

int funcHash(int k, list<int> &q, unordered_map<int, list<int>::iterator> &h){
		if(h.find(k)!=h.end()){
				int tmp = *(h[k]);
				q.erase(h[k]);
				q.push_front(tmp);
				h.insert(pair<int, list<int>::iterator>( k, q.begin() ));
				cout << "Из кэша \n";
				return *(h[k]);
		}
		int ans = func(k);
		if(q.size() == 3){
			q.pop_back();
	//		h.erase(h.find())
		}
		q.push_front(ans);
		h.insert(pair<int, list<int>::iterator>( k, q.begin() ));
		cout << "вычисленное \n";
		return ans;
}

main(){
		list<int> q;
		unordered_map<int, list<int>::iterator> h;
		int k = 0;
		while(k != -1){
				cin >> k;
				cout << funcHash(k, q, h) << "\n\n";
		}

}
