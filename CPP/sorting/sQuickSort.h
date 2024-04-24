#include <vector>
#include <array>

void qs_swap(std::vector<int> * vec, int a, int b);

// pivot chose from right most
void partition(std::vector<int> *vec, std::array<int, 2> dope, bool (*compare) (int,int)){
    int low = dope[0];
    int high = dope[1];

    int pivot = (*vec) [high];
    int pivotPosi = low;

    for(int i=low; i<high; i++){
        if(compare( pivot, (*vec)[i])){
            //swap, advance pivot position
            qs_swap( vec, pivotPosi, i);
            pivotPosi++; 
        }
    }
    //end, swap the pivotPosi's value with the pivot
    qs_swap(vec, pivotPosi, high);
}

void qs_swap(std::vector<int> *vec, int a, int b){
            int temp = (*vec) [a];
            (*vec)[a] = (*vec)[b];
            (*vec)[b] = temp;
}