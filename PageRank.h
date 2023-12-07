// Copyright 2023 <Kyle Zagers>

#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <iomanip>
using std::string;
using std::pair;
using std::vector;
using std::unordered_map;
using std::ostream;
using std::cout;
using std::endl;

class PageRank {
    private:
        int size;
        int power_iterations;
        unordered_map<string, vector<string>> adjacencyList; // List of what points to a vertice.
        unordered_map<string, double> outDegree; // Out degree of a given vertice.
        std::map<string, double> pageRank; // Sorted page rank of each vertice.
    public:
        PageRank();
        PageRank(int power_iterations);
        void addLink(string from, string to);
        void initRanks();
        void rank();
        void printRank();
};

PageRank::PageRank() {
    size = 0;
    power_iterations = 0;
}

PageRank::PageRank(int power_iterations) {
    this->size = 0;
    this->power_iterations = power_iterations;
}

void PageRank::addLink(string from, string to) {
    outDegree[from]++; // "from" points to "to," therefore its out degree goes up.
    adjacencyList[to].push_back(from); // Because of this, "from" is added to "to's" adjacency list.
    pageRank[from] = 1.0;
    pageRank[to] = 1.0; // Both page ranks are initialized to one.
}

void PageRank::initRanks() {
    size = pageRank.size();
    for (auto it = pageRank.begin(); it!=pageRank.end(); it++) {
        it->second /= size; // Each page rank is divided by the number of pages because they were previously initialized to 1.
    }
}

void PageRank::rank() {
    initRanks();

    std::map<string, double> pageRankPrev;
    pageRankPrev = pageRank; // A previous page rank is needed so the new page ranks can be stored while calculating the others.

    for (int i = 0; i < power_iterations - 1; i++) { // The initial page rank counts as a power iteration so we must -1.
        for (auto it = pageRank.begin(); it!=pageRank.end(); it++) {
            it->second = 0; // must be initialized to zero so we can sum the elements for the new page rank.
            vector<string> adjacents = adjacencyList[it->first];
            for (string k : adjacents) {
                it->second += pageRankPrev[k]/outDegree[k]; // Each element being summed is the page rank of a website that points to the current, divided by it's out degree.
            }
        }
        pageRankPrev = pageRank; // Each time a new power iteration happens the previous pagerank is set to the current one so the current can be updated.
    }
}

void PageRank::printRank() {
    rank();

    for (auto it = pageRank.begin(); it!=pageRank.end(); it++) {
        cout << it->first + " " << std::fixed << std::showpoint << std::setprecision(2) <<  it->second << "\n"; // Prints the page rank of each element.
    }
}

#endif // PAGERANK_H
