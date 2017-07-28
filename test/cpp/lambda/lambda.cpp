#include <iostream>
#include <vector>

int each(auto collection, auto lambda)
{
  for (auto it = collection.begin(); it != collection.end(); ++it) {
    lambda(*it);
  }
}

int map(auto collection, auto lambda)
{
  for (auto it = collection.begin(); it != collection.end(); ++it) {
    *it = lambda(*it);
  }
}

int main()
{
  std::vector<int> vec = {1, 2};

  map(vec, [](auto v){return v*2;});
  each(vec, [](auto v){std::cout << v*2;});

  return 0;
}


