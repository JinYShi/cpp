#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>
#include <string>

struct BucketSort {
	

	// vector of numbers
	std::vector<unsigned int> numbersToSort;

	// std::vector<std::string> changeToString(std::vector<unsigned int> numbers);
	// std::vector<std::string> radix_string_sort(std::vector<std::string> numbers, unsigned index);
	// std::vector<unsigned int> changeToInt(std::vector<std::string> numbers);
	void sort(unsigned int numCores);
	std::vector<unsigned int> radix_sort(std::vector<unsigned int> numbers, unsigned index);


};


#endif /* BUCKET_SORT_H */