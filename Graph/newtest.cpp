#include <random>
#include <vector>
#include <set>
#include <algorithm>

#include "Graph.h"

// the performance of this test heavily depends on the underlying data structure
// if sorting is happening during runtime then problems will occur.

int main() {

	unsigned int totalNumbers = 50;

	// use totalNumbers required as the seed for the random
	// number generator.
	std::mt19937 mt(totalNumbers);
	std::uniform_int_distribution<unsigned int> dist(1, totalNumbers * 5);

	// make a graph
	gdwg::Graph<unsigned int,int> g;

	std::set<unsigned int> numSet;

	// insert random numbers into the sort object
	for (unsigned int i=0; i < totalNumbers; ++i) {
		unsigned int num = dist(mt);
		numSet.insert(num);
		g.addNode(num);
	}

	// delete some random nodes.
	for (unsigned int i=0; i < (totalNumbers / 2); ++i) {
		unsigned int num = dist(mt);
		numSet.erase(num);
		g.deleteNode(num);
	}

	// insert some more random numbers
	for (unsigned int i=0; i < totalNumbers; ++i) {
		unsigned int num = dist(mt);
		numSet.insert(num);
		g.addNode(num);
	}

	// iterate over the nodes to create a set of nodes.
	std::vector<unsigned int> nodeValues;
	for (unsigned int n : numSet) {
		nodeValues.push_back(n);
	}

	// shuffle over the set
	std::shuffle(nodeValues.begin(), nodeValues.end(), std::default_random_engine(1));

	// insert some edges
	for (unsigned int i = 0; i < nodeValues.size() - 4; i += 4) {
		g.addEdge(nodeValues[i], nodeValues[i+1], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+2], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+3], dist(mt));
	}

	// print one of the edges.
	g.printEdges(nodeValues[4]);

}
