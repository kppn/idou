#include <iostream>
#include <random>

bool is_exist(int nums[], int n, int x)
{
	for (int i = 0; i < n; i++) {
		if (nums[i] == x)
			return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	int nums[65536];
	std::random_device rnd;

	for (int i = 0; i < 65536; i++) {
		int x = rnd() % 65536;
		std::cout << i << " " << x << std::endl;
		
		if (is_exist(nums, i, x)) {
			std::cout << "exists!!!" << i << std::endl;
			exit(1);
		}
		nums[i] = x;
	}

	return 0;
}

