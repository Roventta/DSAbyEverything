#include <vector>
#include <array>

void qs_swap(std::vector<int> & vec, int a, int b);

// pivot chose from right most
void partition_lomuto(std::vector<int> &vec, std::array<int, 2> dope, bool (*compare) (int,int)){
    int low = dope[0];
    int high = dope[1];

    int pivot = vec [high];
    int pivotPosi = low;

    for(int i=low; i<high; i++){
        if(compare( pivot, vec[i])){
            //swap, advance pivot position
            qs_swap( vec, pivotPosi, i);
            pivotPosi++; 
        }
    }
    //end, swap the pivotPosi's value with the pivot
    qs_swap(vec, pivotPosi, high);
}

void partition_hoare(std::vector<int> &vec, std::array<int, 2> dope, bool (*comp) (int,int)){
    int low = dope[0];
    int high = dope[1];
    
    int pivot = vec[high];
    int leftwall = low;
    int rightwall = high-1;

    while(true){
        while(!comp(vec[leftwall],pivot)){leftwall++;}
        while(comp(vec[rightwall],pivot)){rightwall--;}

        if(leftwall >=rightwall){goto finish;}

        qs_swap(vec, leftwall, rightwall);
    }
    finish:
    qs_swap(vec, high, leftwall);
    return;
}

void qs_swap(std::vector<int> &vec, int a, int b){
            int temp = vec [a];
            vec[a] = vec[b];
            vec[b] = temp;
}