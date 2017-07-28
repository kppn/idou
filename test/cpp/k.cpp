#include <iostream>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

int main()
{
	stringstream ss(ios::in | ios::out | ios::binary);
	ss << "\x01\x00\x02\x00\x00\x00"s;

	short x;
	int y;
	ss.read((char *)&x, 2);
	ss.read((char *)&y, 4);

	if (x == 1)
		cout << "x yes!";
	if (y == 2)
		cout << "y yes!";

	return 0;
}
