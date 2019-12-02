#include "minheap.h"
#include <algorithm>
#include <iostream>

bool fp::MinHeap::empty()
{
	return heap_.empty();
}

std::size_t fp::MinHeap::size()
{
	return heap_.size();
}

void fp::MinHeap::push(std::pair<unsigned char, double> element)
{
	if( isPresent(element) ){
		auto it = std::find(heap_.begin(), heap_.end(), element);
		it->second = element.second;
	}
	else heap_.push_back(element);
}

std::pair<unsigned char, double> fp::MinHeap::top()
{
	sort();
	return heap_.back();
}

void fp::MinHeap::pop()
{
	return heap_.pop_back();
}

void fp::MinHeap::sort()
{
	std::sort(heap_.begin(), heap_.end(), myComparator());
}

bool fp::MinHeap::isPresent(std::pair<unsigned char, double>& value)
{
	return std::binary_search(heap_.begin(), heap_.end(), value, isEqual());
}