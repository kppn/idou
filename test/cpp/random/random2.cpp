#include <iostream>
#include <random>


int main(int argc, char* argv[])
{
	double kaku = 1.0;
	double kei = 65535.0 / 65536.0;

	for (int i = 0; i < 200; i++) {
		std::cout << kaku << std::endl;
		kaku *= kei;
	}

	return 0;
}

