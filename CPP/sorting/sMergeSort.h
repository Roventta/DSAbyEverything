#include <vector>
#include <array>
#include <tuple>

#include "sVecSwap.h"

//use it when the sorted are adjacent, a is at b's left
//dope has astart, aend, bstart, bend
//dope in inclusive style
void mergeTwoSorted(std::vector<int> &soil, std::array<int, 4> dope, bool (*comp) (int,int)){
    int astart = dope[0], aend = dope[1], bstart = dope[2], bend = dope[3];
    int asize = aend-astart+1, bsize = bend-bstart+1;
    int aiter = 0, biter = 0;

    std::vector<int> temp(asize+bsize);

    while((aiter<asize) && (biter<bsize)){
        if(comp(soil[astart+aiter], soil[bstart+biter])){
            temp[aiter+biter] = soil[astart+aiter];
            aiter++;
        }
        else{
            temp[aiter+biter] = soil[bstart+biter];
            biter++;
        }
    }

    for(int i=aiter; i<asize; i++){
        temp[i+biter] = soil[astart+i];
    }
    for(int i=biter; i<bsize; i++){
        temp[aiter+i] = soil[bstart+i];
    }

    for(int i=0; i<bsize+asize; i++){
        soil[astart + i] = temp[i];
    }

}


// soil and vec must have same size
void mergeSort(std::vector<int> &vec, std::array<int, 2> dope, bool (*comp) (int,int)){
    int low = dope[0];
    int high = dope[1];
    int size = high-low+1;

    if(size <= 1){return;}
    if(size == 2){
        if(!comp(vec[low], vec[high])){qs_swap(vec, low, high);}
        return;
    }

    int pivot = size/2 + low;
    printf("pivot %i low %i high %i\n", pivot, low, high);
    std::array<int, 2> dope_left = {low, pivot};
    std::array<int, 2> dope_right = {pivot+1, high};
    std::array<int, 4> dope_merge = {low, pivot, pivot+1, high};

    mergeSort(vec, dope_left, comp);
    mergeSort(vec, dope_right, comp);   

    mergeTwoSorted(vec, dope_merge, comp);

    return;
}
