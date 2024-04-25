#include "sMergeSort.h"
#include "sQuickSort.h"

#include <iostream>

int main(){
    std::vector<int> a = {11,343,2526,13,43425,6,757431,123,5,1230};

    //std::vector<int> result = mergeSort(a, [](int a,int b){return a>b;});
    std::array<int,2> dope = {0, (int)a.size()-1};
    partition_lomuto(a, dope, [](int a, int b){return a>b;});

    std::cout << "partition\n";
    for(auto ele : a){std::cout << ele<<",";}
    std::cout << std::endl;

}