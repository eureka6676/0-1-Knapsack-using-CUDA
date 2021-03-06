#include "dp_cuda.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void print_solution(const value_t best, char* taken_indices)
{
    cout << best << " " << 1 << endl;
    cout << taken_indices << endl;
}

void parse_input(const char* filename,
                 index_t& num_items, weight_t& capacity,
                 weight_t*& weights, value_t*& values)
{
    ifstream input_file(filename);
    
    if (!(input_file >> num_items >> capacity)) {
        cerr << "Bad file format." << endl;
        exit(1);
    }
    
    weights = new weight_t[num_items];
    values = new value_t[num_items];
    
    weight_t weight;
    value_t value;
    
    for (index_t i = 0; i < num_items; ++i) {
        input_file >> value >> weight;
        weights[i] = weight;
        values[i] = value;
    }
}

int main(int argc, char *argv[])
{
    value_t best;
    index_t num_items;
    weight_t capacity;
    weight_t* weights;
    value_t* values;
    parse_input(argv[1],
                num_items, capacity,
                weights, values);
    
    char* taken_indices = new char[2*num_items];
    memset(taken_indices, ' ', 2*num_items);
    taken_indices[2*num_items-1] = '\0';
    for (index_t i = 0; i < num_items; ++i) {
        taken_indices[2*i] = '0';
    }

    best = gpu_knapsack(capacity, weights, values, num_items, taken_indices);

    print_solution(best, taken_indices);
    
    delete[] weights;
    delete[] values;
    delete[] taken_indices;
    
    return 0;
}