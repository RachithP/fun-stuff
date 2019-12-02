#pragma once

#include "../Maze/maze.h"
#include "../LandBasedRobot/landbasedrobot.h"
#include "../Algorithm/algorithm.h"
#include "../MinHeap/minheap.h"

namespace fp
{
/*! \class DIJKSTRAlgorithm dijkstralgorithm.h "src/DIJKSTRAlgorithm/dijkstralgorithm.h"
 * \brief DIJKSTRAlgorithm class for solving the search objective using BFS algorithm.
 *  \headerfile dijkstralgorithm.h
 */
class DIJKSTRAlgorithm : public Algorithm, public MinHeap
{
	public:
		//! Constructor
		DIJKSTRAlgorithm(fp::Maze* maze_ptr);
		
		//! Member functions
		virtual void solve(fp::Maze*, fp::LandBasedRobot*) override;
		virtual bool generatePath(fp::Maze*, fp::LandBasedRobot*) override;
		unsigned char getKey(int x, int y);
		int getX(unsigned char);
		int getY(unsigned char);
		
		//!Destructor
		virtual ~DIJKSTRAlgorithm(){}
		
	private:
		std::map<int, std::map<int, double>> cost2come_;
};
}

