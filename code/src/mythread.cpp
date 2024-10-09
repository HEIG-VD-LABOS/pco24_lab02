
#include "mythread.h"
#include <algorithm>
#include <iostream>

unsigned long long facto(int n) {
  if (n <= 1) {
    return 1; // La factorielle de 0 et 1 est 1
  }
  return n * facto(n - 1);
}

// Get the kth permutaion
std::vector<int> getPermutation(std::vector<int> seq, int k) {
  int sizeSeq = seq.size();
  std::vector<int> permutation;
  std::vector<int> seqCopy = seq;

  for (size_t i = 0; i < sizeSeq; ++i) {
    unsigned long long fact = facto(sizeSeq - 1 - i);
    int index = k / fact;
    permutation.push_back(seqCopy[index]);
    seqCopy.erase(seqCopy.begin() + index);
    k %= fact;
  }

  return permutation;
}

// Manage the threads stop in the startSorting function, here just set the flag
// finished to true so it's triggered in the startSorting function
void bogosort(std::vector<int> seq, ThreadManager *pManager, int k, int seqSize,
              int nbThreads) {
  // TODO
  long long fact = facto(seqSize);
  for (long long i = k; i < fact; i += nbThreads) {
    if (PcoThread::thisThread()->stopRequested()) {
      return;
    }
    std::vector<int> perm = getPermutation(seq, i);

    // Est-ce que le pourcentage doit être à 100 s'il finit ou pas ?
    // Probablement problème de précision quand la valeur est trop petite
    pManager->incrementPercentComputed((double)1. / fact);

    if (is_sorted(perm.begin(), perm.end())) {
      // Comment implémenter pour que la barre affiche les 100% une fois la perm
      // trouvée ?
      pManager->results = perm;
      pManager->finished = true;
      return;
    }
  }

  pManager->results = std::vector<int>();
  pManager->finished = true;
  return;
  // Exemple de mise à jour de la barre de progression
}
