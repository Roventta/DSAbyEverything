#include <vector>
#include <array>
#include <tuple>

//pass result array with a size of a.size+b.size
void mergeTwoSorted(std::vector<int> *result, std::vector<int> a, std::vector<int> b, std::array<int, 4> dope, bool (*compare) (int,int)){
    int asize = dope[0];
    int bsize = dope[1];
    int aindex = dope[2];
    int bindex = dope[3];

    while(asize != aindex || bsize != bindex){
        if(a[aindex] > b[bindex]){(*result)[aindex + bindex] = a[aindex]; ++aindex;}
        else{ (*result)[aindex+bindex] = b[bindex]; ++bindex;}
    }
    return;
}

std::vector<int> mergeSort(std::vector<int> in, bool (*compare)(int,int)){
    std::vector<int> out;
    if(in.size() == 2){
        if(compare(in[0],in[1])){out.push_back(in[0]); out.push_back(in[1]);}
        else{out.push_back(in[1]), out.push_back(in[0]);}
        return out;
    }
    if(in.size() == 1){
        out.push_back(in[0]);
        return out;
    }

    //split
    std::vector<int> left(in.begin(), in.begin()+in.size()/2);
    std::vector<int> right(in.begin()+in.size()/2, in.begin()+in.size());
    
    std::vector<int> left_s = mergeSort(left, compare);
    std::vector<int> right_s = mergeSort(right, compare);

    std::vector<int> r(left_s.size() + right_s.size());
    std::array<int,4> dope = {(int)left_s.size(), (int)right_s.size(),0,0};
    mergeTwoSorted(&r, left_s, right_s, dope, compare);
    
    return r;
}