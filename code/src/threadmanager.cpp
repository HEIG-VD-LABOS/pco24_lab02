

#include <QRandomGenerator>
#include <iostream>

#include "mythread.h"
#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) : QObject(parent) {}

/**
 * @brief Cette fonction trie une séquence générée aléatoirement
 * @param seq séquence à trier
 * @param nbThreads le nombre de threads à lancer
 * @return séquence triée
 */
std::vector<int> ThreadManager::startSorting(std::vector<int> seq,
                                             unsigned int nbThreads) {
  finished = false;
  // TODO création des threads et du vecteur de résultats
  std::vector<PcoThread *> threads;

  // TODO lancement des threads avec la fonction Bogosort
  for (size_t i = 0; i < nbThreads; ++i) {
    threads.push_back(new PcoThread(bogosort, seq, this, i, nbThreads));
  }
  // TODO arrêt des threads et récupération du tableau trié
  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i]->join();
    delete threads[i];
  }
  // TODO retourner le tableau trié
  return results;
}

void ThreadManager::incrementPercentComputed(double percentComputed) {
  emit sig_incrementPercentComputed(percentComputed);
}

