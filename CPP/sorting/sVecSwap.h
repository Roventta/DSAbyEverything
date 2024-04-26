#ifndef SWAP_H
#define SWAP_H

#include <vector>

void qs_swap(std::vector<int> &vec, int a, int b){
            int temp = vec [a];
            vec[a] = vec[b];
            vec[b] = temp;
}

#endif