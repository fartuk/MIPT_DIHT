#include<vector>
#include<iostream>
#include<string>
#include<iterator>
#include<cstdlib>
int max(int a, int b){
		if(a > b){
				return a;
		}
		else{
			   	return b;
		}
};
int min(int a, int b){
		if(a < b){
				return a;
		}
		else{
			   	return b;
		}
};

int ex(int k){
		int t = 1;
		for(int i = 0; i < k; i++){
				t *= 10;
		}
	return t;
}	

class BigInt{
	public:
		int sign;
		std::vector<int> vect;
		int getSize(){
				return vect.size();
		}
		int getCapacity(){
				return vect.capacity();
		}
		void pushBack(int a){
			   vect.push_back(a);
		}
		BigInt(const BigInt& obj){
				sign = obj.sign;
				vect = obj.vect;
		}
		BigInt(int a){
				sign = 1;
				for(int i = 0; i < a; i++){
						vect.push_back(0);
				}
		}
		BigInt(char* str_){
				sign = 1;
				std::string  str = str_;
				int tmpSizeVect;
				if((str.size() % 3) == 0){
						tmpSizeVect = (int)(str.size() / 3);
				}
				else{
						tmpSizeVect = (int)(str.size() / 3) + 1;
				}
				vect.resize(tmpSizeVect, 0);
				int firstSimb = atoi((str.substr(0, 3 - (tmpSizeVect * 3 - str.size()))).c_str());
				int k = 0;
				for(int i = str.size() - 3; i > 0; i -= 3){
						vect[k] = atoi((str.substr(i, 3)).c_str());
						k++;
				}
				vect[k] = firstSimb;
		}
		BigInt(){
			sign = 1;
		}
		

		BigInt operator+(int b){
				BigInt result(vect.size());
				for(int i = 0; i < vect.size(); i++){
						result.vect[i] = vect[i];
				}
				result.vect[0] += b;
				for(int i = 0; i < vect.size() - 1; i++){
						if((result.vect[i] > 999)&&(i != vect.size() - 1)){
								result.vect[i] = result.vect[i] % 1000;
								result.vect[i + 1]++;
						}
						if((result.vect[i] > 999)&&(i == vect.size() - 1)){
								result.vect[i] = result.vect[i] % 1000;
								result.vect.push_back(1);
						}

				}

				result.sign = 1;
				return result;
		}
	
		BigInt operator+(BigInt& b){
				int tmpMax = max(vect.capacity(), b.getCapacity());
				int tmpMin = min(vect.capacity(), b.getCapacity());
				BigInt result(tmpMax);
				BigInt temp(tmpMin);
				if((sign == - 1)&&(b.sign == 1)){
						BigInt tmpBig;
						tmpBig = *this;
						tmpBig.sign = 1;
						return b - tmpBig;
				}
				if((sign ==  1)&&(b.sign == -1)){
						BigInt tmpBig;
						tmpBig = b;
						tmpBig.sign = 1;
						return *this - tmpBig;
				}
				if((sign == -1)&&(b.sign == -1)){
						BigInt tmpBig1;
						tmpBig1 = *this;
						tmpBig1.sign = 1;
						BigInt tmpBig2;
						tmpBig2 = b;
						tmpBig2.sign = 1;
						BigInt tmpBig3;
						tmpBig3 = tmpBig1 + tmpBig2;
						tmpBig3.sign = -1;
						return tmpBig3;
				}

				if(tmpMax == vect.size()){
						for(int i = 0; i < tmpMax; i++){
								result.vect[i] = vect[i];
						}
						for(int i = 0; i < tmpMin; i++){
								temp.vect[i] = b.vect[i];
						}
				}
				else{
						for(int i = 0; i < tmpMax; i++){
								result.vect[i] = b.vect[i];
						}
						for(int i = 0; i < tmpMin; i++){
								result.vect[i] = vect[i];
						}
				}
				int i;
				int trans = 0;
				for(i = 0; i < tmpMin; i++){
						/*if(result.vect[i] + temp.vect[i] > 999){
								trans = 1;
								result.vect[i] = (result.vect[i] + temp.vect[i]) % 1000;
								if(tmpMax - 1 == i){
										result.vect.push_back(1);
								}
								else{
										result.vect[i + 1]++;
								} 
						}
						else{
								trans = 0;
								result.vect[i] = (vect[i] + b.vect[i]);
						}
						*/
						result.vect[i] = (result.vect[i] + temp.vect[i]);

				}
				for(int i = 0; i < tmpMax; i++){
						if(result.vect[i] > 999){
								result.vect[i] = result.vect[i] % 1000;
								if(tmpMax - 1 == i){
												result.vect.push_back(1);
								}
								else{
										result.vect[i + 1]++;
								}
						}
				}
				result.sign = 1;
				return result;
		}
		BigInt operator-(BigInt& b){
				BigInt minBig;
				BigInt maxBig;
				int tmpMax = max(vect.capacity(), b.getCapacity());
				int tmpMin = min(vect.capacity(), b.getCapacity());
				if((sign == - 1)&&(b.sign == 1)){
						BigInt tmpBig1;
						tmpBig1 = *this;
						tmpBig1.sign = 1;
						BigInt tmpBig2;
						tmpBig2 = tmpBig1 + b;
						tmpBig2.sign = -1;
						return tmpBig2;
				}
				if((sign == 1)&&(b.sign == -1)){
						BigInt tmpBig1;
						tmpBig1 = b;
						tmpBig1.sign = 1;
						return *this + tmpBig1;
				}
				if((sign == -1)&&(b.sign == -1)){
						BigInt tmpBig1;
						tmpBig1 = b;
						tmpBig1.sign = 1;
						BigInt tmpBig2;
						tmpBig2 = *this;
						tmpBig2.sign = 1;
						return tmpBig1 - tmpBig2;
				}
				int who;
				if(vect.size() == b.getSize()){
						int k = getSize() - 1;
						while((vect[k] == b.vect[k])&&(k > 0)){
								k--;
						}
						if((k == 0)&&(vect[k] == b.vect[k])){
								BigInt result;
								result.vect.push_back(0);
								return result;
						}
						if(vect[k] > b.vect[k]){
								who = 1;
								maxBig = *this;
								minBig = b;
						}
						if(vect[k] < b.vect[k]){
								who = - 1;
								maxBig = b;
								minBig = *this;
						}
				}
				if(vect.size() > b.getSize()){
						who = 1;
						maxBig = *this;
						minBig = b;
				}
				if(vect.size() < b.getSize()){
						who = -1;
						maxBig = b;
						minBig = *this;
				}
				BigInt result(tmpMax);
				for(int i = 0; i < tmpMax; i++){
						result.vect[i] = maxBig.vect[i];
				}	
				for(int i = 0; i < tmpMin; i++){
						int diff;
						diff = maxBig.vect[i] - minBig.vect[i];
						if(diff >= 0){
								result.vect[i] = diff;
						}
						else{
								diff += 1000;
								result.vect[i] = diff;
								maxBig.vect[i + 1]--;
								result.vect[i + 1]--;
						}
				}
				int k;
				k = result.getSize() - 1;
				
				while(result.vect[k] == 0){
						result.vect.pop_back();
						k--;
				}
				result.sign = who;
				return result;
		}

		
		BigInt operator*(BigInt& b){
				BigInt result;
				for(int i = 0; i < vect.size() + b.getSize(); i++){
						result.vect.push_back(0);
				}
				for(int i = 0; i < vect.size(); i++){
						int trans = 0;
						for(int j = 0; j < b.vect.size() || trans; j++){
								result.vect[i + j] += vect[i] * b.vect[j] + trans;
								trans = result.vect[i + j] / 1000;
								result.vect[i + j] -= trans * 1000;
						}
				}
				int k = vect.size() + b.vect.size() - 1;
				while((k > 0)&&(result.vect[k] == 0)){
						result.vect.pop_back();
						k--;
				}
				result.sign = sign * b.sign;
				return result;
		}
		BigInt operator*(int x){
				BigInt result;
				for(int i = 0; i < vect.size() + 1; i++){
						result.vect.push_back(0);
				}
				result.sign = sign * x / abs(x);
				x = abs(x);
				int trans = 0;
				for(int i = 0; i < vect.size() || trans; i++){
						result.vect[i] = vect[i] * x + trans;
						trans = result.vect[i] / 1000;
						result.vect[i] -= trans * 1000;
				}
				int k = vect.size();
				while((k > 0)&&(result.vect[k] == 0)){
						result.vect.pop_back();
						k--;
				}
				return result;
		}
		BigInt operator/(BigInt& b){
				BigInt tmpB = b;
				BigInt redB = b;
				int k = 1;
				
				while(tmpB.getSize() == b.getSize()){
						k = k * 10;
						tmpB = tmpB * 10;
				}
				
				k = k / 10;
				redB = b * k;
				int k1 = k;
				std::cout << "######" << k1;
				BigInt redDiv;
				for(int i = 0; i < redB.getSize(); i++){
						redDiv.vect.push_back(0);
				}
				int ptNum = vect.size() - 1;
				int ptIns;
				k = 0;
				BigInt tmpDiv;
				tmpDiv = *this;
				
				while(tmpDiv.getSize() == vect.size()){
						k++;
						tmpDiv = tmpDiv * 10;
				}
				for(int i = 0; i < k1; i++){
						redDiv = redDiv + redDiv;
				}
				k--;
				k = 2 - k;
				ptIns = k;
				BigInt& redDivRf = redDiv;
				BigInt& thisRf = *this;
				int& ptNumRf = ptNum;
				int& ptInsRf = ptIns;
				BigInt otv("0");
			//	int otv = 0;
int e = 0;
				while((ptNum >= 0) && (e < 10) ){
						e++;
						int f;
						f = normalize(redDivRf, thisRf, redB.getSize(), ptNumRf, ptInsRf);
						f = normalize(redDivRf, thisRf, redB.getSize(), ptNumRf, ptInsRf);
						tmpDiv = redDiv - redB;
						otv = otv * ex(f);
						if(tmpDiv.sign == -1){
								renorm(redDivRf, thisRf, ptNumRf, ptInsRf);
								std::cout << "\nБыл ренорм ";
								redDiv.print();
								if((e != 1) && (ex(f) != 1)){
										BigInt tmpTen("10");
										otv = otv * tmpTen;
								}
						}
						int n = 0;
						tmpB = redB;

					
						int t = 1;
						while(comp(redDiv, tmpB) == 1){
								tmpB = redB * t;
								t++;
								n++;
						}
						t--;
						t--;
						tmpB = redB * t;
						n--;
						otv = otv * 10;
						otv = otv + t;
						BigInt tmpOff("0");
						std::cout << "\n \n A";
						redDiv.print();
						std::cout << "\n \n";
						std::cout << "\n \n B";
						tmpB.print();
						std::cout << "\n \n";
						tmpOff = redDiv - tmpB; 
						redDiv = tmpOff;

						std::cout << "\n \n вычитание ";
						redDiv.print();
						std::cout << "\n \n";
				std::cout << "\n i_________\n";
				//std::cout << otv;
				otv.print();
				std::cout << "\n i_________\n";
				}

		
				
				std::cout << "\n i_________\n";
				//std::cout << otv;
				otv.print();
				std::cout << "\n i_________\n";
				

				return otv;	
		}
		BigInt& operator=(BigInt other){
				int tmpSize = other.getSize();
				vect.resize(tmpSize, 0);
				sign = other.sign;
				for(int i = 0; i < tmpSize; i++){
						vect[i] = other.vect[i];
				}	
				return *this;
		}
		
		void print(){
				if(sign == -1){
						std::cout << "-";
				}
				for(int i = vect.size() - 1; i >= 0; i--){
						if((vect[i] < 10)&&(vect.size() - 1 != i)){
								std::cout  << "00" << vect[i];
						}
						else{ 
								if((vect[i] < 100)&&(vect.size() - 1 != i)){
										std::cout << "0" << vect[i];
								}
								else{
										std::cout << vect[i];
								}
						}
				}
		}
		friend void  renorm(BigInt& norm, BigInt& donor, int& num, int& ins);
		friend void  renorm1(BigInt& norm, BigInt& donor, int& num, int& ins);
		friend int normalize(BigInt& norm, BigInt& donor, int quan, int& num, int& ins);
		friend int comp(BigInt a, BigInt b);
};	

int comp(BigInt a, BigInt b){
		if(a.getSize() == b.getSize()){
				int k = a.getSize() - 1;
				while((a.vect[k] == b.vect[k])&&(k > 0)){
						k--;
				}
				if((k == 0)&&(a.vect[k] == b.vect[k])){
					return 0;
				}
				if(a.vect[k] > b.vect[k]){
						return  1;
				}
				if(a.vect[k] < b.vect[k]){
						return - 1;
				}
				
		}
		if(a.getSize() > b.getSize()){
				return 1;
		}
		if(a.getSize() < b.getSize()){
				return -1;
		}
}
		

void  renorm(BigInt& norm, BigInt& donor, int& num, int& ins){
		BigInt tmp("10");
		norm = norm * tmp + (donor.vect[num] % (ex(ins) * 10)) / ex(ins);
		ins--;
		if(ins == -1){
				ins = 2;
				num--;
		}
}
void  renorm1(BigInt& norm, BigInt& donor, int& num, int& ins){
		BigInt tmp("10");
		norm = norm * tmp;
		ins--;
		if(ins == -1){
				ins = 2;
				num--;
		}
}

int normalize(BigInt& norm, BigInt& donor, int quan, int& num, int& ins){
		
		
		BigInt tmp;
		tmp = norm;
		tmp.vect[0] = tmp.vect[0] / 10 * 10 + 1;
		int k = 0;
		while(tmp.getSize() <= quan){
				k++;
				tmp = tmp * 10;
		}
		k--;
		for(int i = 0; i < k; i++){
				norm = norm * 10 + (donor.vect[num] % (ex(ins) * 10)) / ex(ins);
				ins--;
				if(ins == -1){
						ins = 2;
						num--;
				}
		}
		std::cout << "\nresult ";
		norm.print();
		std::cout << "\n ";
		return k;
}
int main(){
	BigInt a;
	BigInt s;
//	BigInt c("1564521902111");
//	BigInt q( "1952");
	
	BigInt c("4643687664");
	BigInt q( "5698");
	a = c / q;
	//q = q * 8;
	//a = b - q;
/*	BigInt a1("1564521");
	std::cout << "\n----------a1\n";
	a1.print();
	std::cout << "\n";
				for(int i = 0; i < a1.getSize(); i++){
						std::cout << a1.vect[i] << "\n";
				}
	BigInt b1("1561600");
	std::cout << "\n----------b1\n";
	b1.print();
	std::cout << "\n";
				for(int i = 0; i < b1.getSize(); i++){
						std::cout << b1.vect[i] << "\n";
				}
	s = a1 - b1;
	std::cout << "\n----------a1 - b1\n";
	s.print();
	std::cout << "\n";
				for(int i = 0; i < s.getSize(); i++){
						std::cout << s.vect[i] << "\n";
				}
	//a.vect.pop_back();
	//a.print();
	//a.vect.erase(a.vect.begin()++);

*/	
}	
