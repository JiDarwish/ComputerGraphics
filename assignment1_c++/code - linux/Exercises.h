#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <numeric>
#include <vector>
#include <algorithm>
#include <stack>

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(const std::list<float> &values)
{
	float average = std::accumulate(std::begin(values), std::end(values), 0.f) / values.size();
	float squaredDifference = 0.f;
	for (float val : values)
	{
		squaredDifference += pow(val - average, 2);
	}

	float standardDeviation = sqrt(squaredDifference / values.size());
	return std::pair<float, float>(average, standardDeviation);
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor
{
private:
	static float calcSum(const Tree &tree, bool countOnlyEvenLevels)
	{
		float sum;

		if (countOnlyEvenLevels)
		{
			sum = tree.value;
		}

		else
		{
			sum = 0;
		}

		if (!tree.children.empty())
		{
			for (Tree child : tree.children)
			{
				sum += TreeVisitor::calcSum(child, !countOnlyEvenLevels);
			}
		}

		return sum;
	}

public:
	float visitTree(const Tree &tree, bool countOnlyEvenLevels)
	{
		if (countOnlyEvenLevels)
		{
			return TreeVisitor::calcSum(tree, countOnlyEvenLevels);
		}

		else
		{
			return TreeVisitor::calcSum(tree, countOnlyEvenLevels) + TreeVisitor::calcSum(tree, !countOnlyEvenLevels);
		}
	}
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex
{
public:
	Complex(float real, float imaginary)
	{
		this->real = real;
		this->im = imaginary;
	};
	float real, im;

	Complex operator+(Complex const &numberTwo)
	{
		Complex result((real + numberTwo.real), (im + numberTwo.im));
		return result;
	}
	Complex operator-(Complex const &numberTwo)
	{
		Complex result((real - numberTwo.real), (im - numberTwo.im));
		return result;
	}

	Complex operator*(Complex const &numberTwo)
	{
		Complex result((real * numberTwo.real - im * numberTwo.im), (im * numberTwo.real + real * numberTwo.im));
		return result;
	}
};
//////////////////////////////////////////////////////////////////
////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::list<float> heights)
{
	std::vector<float> fromLeft;
	std::vector<float> fromRight;
	float heighest = 0.f;

	for (float val : heights)
	{
		if (val > heighest)
		{
			heighest = val;
		}
		fromLeft.push_back(heighest);
	}

	heighest = 0.f;

	std::list<float>::reverse_iterator iter = heights.rbegin();
	for (; iter != heights.rend(); ++iter)
	{
		float val = *iter;
		if (val > heighest)
		{
			heighest = val;
		}
		fromRight.push_back(heighest);
	}

	std::reverse(fromRight.begin(), fromRight.end());

	int index = 0;
	float sum = 0.f;
	for (float val : heights)
	{
		sum += std::min(fromLeft.at(index), fromRight.at(index)) - val;
		index++;
	}
	return sum;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
typedef std::pair<int, int> location;

class LabyrinthTree
{
public:
	location loc;
	std::list<LabyrinthTree> children;
	LabyrinthTree *parentTree;
};

enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};
location handleNextMovement(location currentLocation, Direction direction)
{
	switch (direction)
	{
	case UP:
		return location(currentLocation.first, currentLocation.second - 1);
	case DOWN:
		return location(currentLocation.first, currentLocation.second + 1);
	case RIGHT:
		return location(currentLocation.first + 1, currentLocation.second);
	case LEFT:
		return location(currentLocation.first - 1, currentLocation.second);
	default:
		std::cout << "Weird it reached default case for handleMovement what did you do?" << std::endl;
	}
}

bool checkValidMove(location currentLocation, location possibleNextLocation, std::set<std::pair<location, location>> walls, int size)
{
	if (possibleNextLocation.first >= size || possibleNextLocation.second >= size || possibleNextLocation.first < 0 || possibleNextLocation.second < 0)
	{
		return false;
	}

	for (std::set<std::pair<location, location>>::iterator it = walls.begin(); it != walls.end(); it++)
	{
		std::pair<location, location> thisWall = *it;
		if ((thisWall.first.first == currentLocation.first && thisWall.first.second == currentLocation.second && thisWall.second.first == possibleNextLocation.first && thisWall.second.second == possibleNextLocation.second) || (thisWall.first.first == possibleNextLocation.first && thisWall.first.second == possibleNextLocation.second && thisWall.second.first == currentLocation.first && thisWall.second.second == currentLocation.second))
		{
			return false;
		}
	}
	return true;
}

bool isAlreadyVisited(location loc, std::list<location> alreadyVisited)
{
	for (location visitedOne : alreadyVisited)
	{
		if (loc.first == visitedOne.first && loc.second == visitedOne.second)
		{
			return true;
		}
	}
	return false;
}

void fillLabyrinthTree(std::set<std::pair<location, location>> walls, int size, LabyrinthTree &parent, std::list<Direction> directions, int &count, std::list<location> alreadyVisited)
{
	// MEANS WE FOUND IT COUNT UP THE TREE TO (0,0)
	if (parent.loc.first == size - 1 && parent.loc.second == size - 1)
	{
		// LOOP AND COUNT THE PARENTS
		LabyrinthTree trav = parent;
		while (true)
		{
			count++;
			if (trav.loc.first == 0 && trav.loc.second == 0)
			{
				break;
			}
			trav = *trav.parentTree;
		}

		return;
	}

	location possibleNextLocation;
	for (Direction direction : directions)
	{

		possibleNextLocation = handleNextMovement(parent.loc, direction);
		if (!checkValidMove(parent.loc, possibleNextLocation, walls, size) || isAlreadyVisited(possibleNextLocation, alreadyVisited))
		{

			continue;
		}
		// std::cout << "parent: (" << parent.loc.first << ", " << parent.loc.second << ") nextChild: (" << possibleNextLocation.first << ", " << possibleNextLocation.second << ")" << std::endl;

		LabyrinthTree childTree;
		childTree.parentTree = &parent;
		childTree.loc = possibleNextLocation;
		parent.children.push_back(childTree);
		alreadyVisited.push_back(possibleNextLocation);
		fillLabyrinthTree(walls, size, childTree, directions, count, alreadyVisited);
	}
}

int Labyrinth(std::set<std::pair<location, location>> labyrinth, int size)
{
	LabyrinthTree root;
	location rootLoc = location();
	rootLoc.first = 0;
	rootLoc.second = 0;
	root.loc = rootLoc;

	std::list<location> alreadyVisited = {root.loc};
	std::list<Direction> directions = {UP, DOWN, RIGHT, LEFT};

	int count = 0;
	fillLabyrinthTree(labyrinth, size, root, directions, count, alreadyVisited);
	return count;
}
//////////////////////////////////////////////////////////////////

#endif
