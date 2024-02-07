#include"DataStream.h"
using namespace serialize;
using namespace std;
int main()
{
	DataStream ds;
	ds << 123 << 1.23 << true << "hello world";
	ds.open("1.out");
	ds.show();
	/*int a;
	double b;
	bool c;
	string s;
	ds >> a >> b >> c >> s;
	cout << a << "," << b << "," << c << "," << s << endl;
	ds.save("1.out");*/
	
	return 0;
}