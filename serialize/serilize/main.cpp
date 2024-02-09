#include"DataStream.h"
using namespace serialize;
using namespace std;
class test
{
public:
	test(int h, int d) :a(h), b(d) { c = 0.001; }
	test() :a(0), b(0) { c = 1.001; }
	int a;
	int b;
	double c;
	//string str;
	void show()
	{
		cout << a << "," << b << "," <<c<< endl;
	}
};
int main()
{
	DataStream ds;
	
	test t1(11,12), t2(13,14);
	//t1.str = "hello kitty";
	//t2.str = "5201314";
	t1.c = 1.256;
	t2.c = 1.368;
	ds << t1 <<t2;
	ds.save("1.out");
	DataStream ds1;
	ds1.open("1.out");
	test t3, t4;
	ds1 >> t3 >>t4;
	t3.show();
	t4.show();
	return 0;
}