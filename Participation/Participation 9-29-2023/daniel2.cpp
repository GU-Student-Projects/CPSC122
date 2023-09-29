#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

int main()
{
vector<int> vec_assign = {};
vector<int> vec_compare = {};

int num_ops = 1000000;

int loops = 10000;
int count_comp = 0;
double assign_time = 0.0;
double compare_time = 0.0;

auto start = chrono::high_resolution_clock::now();
auto mid = chrono::high_resolution_clock::now();
auto end = chrono::high_resolution_clock::now();
double time_taken_assign, time_taken_compare;

for (int i = 0; i < num_ops; i++)
{
vec_assign.push_back(i);
vec_compare.push_back(i);
}

for (int l = 0; l < loops; l++)
{

start = chrono::high_resolution_clock::now();

for (int i = 0; i < num_ops; i++)
{
vec_compare[0]<0;
}

mid = chrono::high_resolution_clock::now();

for (int i = 0; i < num_ops; i++)
{
vec_assign[i] = 10000;
}

end = chrono::high_resolution_clock::now();

time_taken_assign = chrono::duration_cast<std::chrono::nanoseconds>(end - mid).count();
time_taken_compare = chrono::duration_cast<std::chrono::nanoseconds>(mid - start).count();

//printf("Time taken for %i operation of assignment in loop is %.4f ms.\n", num_ops, time_taken_assign * 1e-6);
//printf("Time taken for %i operation of comparison in loop is %.4f ms.\n", num_ops, time_taken_compare * 1e-6);

assign_time += time_taken_assign * 1e-6;
compare_time += time_taken_compare * 1e-6;

if (time_taken_assign >= time_taken_compare)
{
count_comp++;
}

}

printf("Out of %d test runs of %d ops, comparison operation is faster in %d runs, that's %.4f %%.\n", loops, num_ops, count_comp, ((double)count_comp)*100/loops);
printf("Average time for comparison operations is %.4f ms.\n", compare_time/loops);
printf("Average time for assignment operations is %.4f ms.\n", assign_time/loops);
}