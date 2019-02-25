#include<iostream>
#include <cstdlib>
#include<cassert>
using namespace std;

template <class T> // forward declaration
class SA; 

template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);

template<class T>
class SA{
	private:
		int low, high;
		T* p;
	public:
	
		// default constructor
		// allows for writing things like SA a;
		SA(){
			low=0; 
			high=-1;
			p=NULL;
		}
		

		// 2 parameter constructor lets us write
		// SA x(10,20);
		SA(int l, int h){
			if((h-l+1)<=0){
				cout << "constructor error in bounds definition" <<endl;
				exit(1);
			}
			low = l;
			high = h;
			p = new T[h-l+1];
		}
		
		
		// single parameter constructor lets us
		// create a SA almost like a "standard" one by writing
		// SA x(10); and getting an array x indexed from 0 to 9
		SA(int i){
			low = 0; 
			high = i-1;
		 	p = new T[i];
		}
		
		// copy constructor for pass by value and
		// initialization
		SA(const SA & s) {
			int size=s.high-s.low+1;
			p=new T[size];
			for(int i=0; i<size; i++)
			p[i]=s.p[i];
			low=s.low;
			high=s.high;
		}
		 
		// destructor
		~SA(){
			delete [] p;
		}
		
		//overloaded [] lets us write
		//SA x(10,20); x[15]= 100;
		T& operator[](int i){
			if(i<low || i>high){
				cout<< "index "<<i<<" out of range"<<endl;
				exit(1);
			}
			return p[i-low];
		}
		 
		// overloaded assignment lets us assign
		// one SA to another
		SA & operator=(const SA & s){
			if(this==&s)
				return *this;
			
			delete [] p;
			int size=s.high-s.low+1;
			p=new T[size];
			
			for(int i=0; i<size; i++)
				p[i]=s.p[i];
				
			low=s.low;
			high=s.high;
			
			return *this;
		}
		
		// overloads << so we can directly print SAs
		//template <class T>
		friend ostream& operator<< <T> (ostream& os, SA<T> s);
};

template <class T>
ostream& operator<<(ostream& os, SA<T> s){
	int size = s.high - s.low+1;
	for(int i=0; i<size; i++)
	cout << s.p[i] << endl;
	return os;
}



int main(){
	/*
	SA<int> a(10);
    
	int i;
	for(i=0;i<10;i++)
		a[i]=i;

	cout<<"printing using []"<<endl;

	for( i=0;i<10;i++)
		cout<<a[i]<<endl;

	cout<<"and now with overloaded <<"<<endl;
	cout<<a;
	*/
	
	//create two SA in b;
	SA<SA<int>> m1(2);
	SA<SA<int>> m2(2);
	SA<int> c1(2); 
	SA<int> c2(2);
	
	for(int i = 0; i < 2; i++){
		c1[i] = i+1;
		c2[i] = i+5;
	}
		
	m1[0] = c1;
	m1[1] = c2;
	m2[0] = c2;
	m2[1] = c1;
	
	SA<SA<int>> product = m2;
	//matrix multiplcation 
	for(int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			product[i][j] = (m1[i][j] * m2[i][j]) + (m1[i][(j+1)%2] * m2[(i+1)%2][j]);
		}
	}
	
	cout << product; 
	
	
	system("pause");
	return 0;

} 
