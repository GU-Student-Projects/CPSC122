#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main()
{
vector<int> vec_assign = {};
vector<int> vec_compare = {};

int num_ops = 1000000;

for (int i = 0; i < num_ops; i++)
{
vec_assign.push_back(i);
vec_compare.push_back(i);
}

auto start = chrono::high_resolution_clock::now();

for (int i = 0; i < num_ops; i++)
{
vec_compare[i]<0;
}
auto mid = chrono::high_resolution_clock::now();

for (int i = 0; i < num_ops; i++)
{
vec_assign[i] = 10000;
}

auto end = chrono::high_resolution_clock::now();

double time_taken_assign = std::chrono::duration_cast<std::chrono::nanoseconds>(end - mid).count();
double time_taken_compare = std::chrono::duration_cast<std::chrono::nanoseconds>(mid - start).count();

printf("Time taken for %i operation of assignment in loop is %.4f ms.\n", num_ops, time_taken_assign * 1e-6);
printf("Time taken for %i operation of comparison in loop is %.4f ms.\n", num_ops, time_taken_compare * 1e-6);

return 0;
}

