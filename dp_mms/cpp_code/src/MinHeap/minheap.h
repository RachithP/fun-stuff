#pragma once

#include <vector>

namespace fp
{

	class MinHeap
	{
		public:

			//! Constructor
			MinHeap(){}
			
			//! Member Functions
			bool empty();
			std::size_t size();
			void push(std::pair<unsigned char, double> element);
			std::pair<unsigned char, double> top();
			void sort();
			void pop();
			bool isPresent(std::pair<unsigned char, double>& element);

			//! Destructor
			~MinHeap(){}
		
		protected:
			std::vector<std::pair<unsigned char, double> > heap_;
		
	};

	class myComparator
	{
		public:
			bool operator()(const std::pair<unsigned char, double>& a, const std::pair<unsigned char, double>& b )
			{
				return (a.second > b.second);
			}
	};
	
	class isEqual
	{
		public:
			bool operator()(const std::pair<unsigned char, double>& a, const std::pair<unsigned char, double>& b )
			{
				return (a.first==b.first);
			}
	};
}

