
#include <algorithm>
#include "mythread.h"
#include <iostream>



unsigned long long facto(int n) {
if (n <= 1) {
return 1; // La factorielle de 0 et 1 est 1
}
return n * factorial(n-1);
}


//Get the kth permutaion
std::vector<int> getPermutation(std::vector<int> seq, int k)
{
    int sizeSeq = seq.size();
    std::vector<int> permutation;
    std::vector<int> seqCopy = seq;

    for(size_t i =0; i<sizeSeq;++i){
        unsigned long long fact = facto(sizeSeq-1-i);
        int index = k/fact;
        permutation.push_back(seqCopy[index])
        seqCopy.erase[index];
        k %= fact;
    }

    return seqCopy;
}


void bogosort(std::vector<int> seq, ThreadManager* pManager, int k, int seqSize){
    for(int i = k; i<facto(seqSize); i+seqSize){
        std::vector<int> perm = getPermutation(seq, i);

        if(is_sorted(perm)){
            pManager->results = perm;
        }
    }


    // Exemple de mise à jour de la barre de progression
    pManager->incrementPercentComputed((double)1);
}

