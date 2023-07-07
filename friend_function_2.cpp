#include<iostream>
#include<string>
using namespace std;
class mango;
class apple{
private:
	int a,b;
public:
	apple( int A, int B ){
		a=A;
		b=B;
	}
	friend void compare(apple , mango );
};
class mango{
private:
	int x,y;
public:	
	mango( int X, int Y ){
		x=X;
		y=Y;
	};
		friend void compare(apple,mango );
};
	void compare(apple a1, mango x1)
	{
		if (a1.a+a1.b > x1.x+x1.y){
		cout<< a1.a+a1.b <<" is greater than "<< x1.x+x1.y<<endl;
		}
		else if(a1.a+a1.b < x1.x+x1.y){
			cout<<x1.x+x1.y<<" is greater than "<<a1.a+a1.b<<endl;
		}
		else{
		cout<<x1.x+x1.y<<" and "<<a1.a+a1.b<<" are both equal "<<endl;
		}	
	}
int main()
{
	apple a1(5,7);
	mango x1(5,6);
	compare(a1,x1);	
}