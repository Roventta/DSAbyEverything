#include "mergeSort.h"

#include <iostream>

int main(){
    std::vector<int> a = {11,343,2526,13,43425,6,757431,123,5,1230};

    std::vector<int> result = mergeSort(a, [](int a,int b){return a>b;});

    std::cout << "merged sorted\n";
    for(auto ele : result){std::cout << ele<<",";}
    std::cout << std::endl;


}