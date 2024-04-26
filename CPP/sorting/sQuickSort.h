#include <vector>
#include <array>

#include "sVecSwap.h"

// pivot chose from right most
int partition_lomuto(std::vector<int> &vec, std::array<int, 2> dope, bool (*compare) (int,int)){
    int low = dope[0];
    int high = dope[1];

    int pivot = vec [high];
    int pivotPosi = low;

    for(int i=low; i<high; i++){
        if(compare(vec[i], pivot)){
            //swap, advance pivot position
            qs_swap( vec, pivotPosi, i);
            pivotPosi++; 
        }
    }
    //end, swap the pivotPosi's value with the pivot
    qs_swap(vec, pivotPosi, high);
    return pivotPosi;
}

int partition_hoare(std::vector<int> &vec, std::array<int, 2> dope, bool (*comp) (int,int)){
    int low = dope[0];
    int high = dope[1];
    
    int pivot = vec[high];
    int leftwall = low;
    int rightwall = high-1;

    while(true){
        if(leftwall >=rightwall){goto finish;}
        while(!comp(vec[leftwall],pivot)){leftwall++;}
        while(comp(vec[rightwall],pivot)){rightwall--;}


        qs_swap(vec, leftwall, rightwall);
    }
    finish:
    qs_swap(vec, high, leftwall);
    return leftwall;
}

void quickSort(std::vector<int> &vec, int low, int high, 
                int (*part)(std::vector<int> &, std::array<int, 2>, bool (*comp) (int,int)),
                bool (*comp) (int,int)){
    if(low < high){
        std::array<int,2> dope = {low, high};
        int pivotPosi = part(vec, dope, comp);
        quickSort(vec, low, pivotPosi-1, part, comp);
        quickSort(vec, pivotPosi+1, high, part, comp);
    }

}