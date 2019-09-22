
enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class LabyrinthTree
{
public:
    location loc;
    std::list<LabyrinthTree> children;
};

int Labyrinth(std::set<std::pair<location, location>> labyrinth, int size)
{
}

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

// int nextMove(std::set<std::pair<location, location>> walls, location &currentLocation, std::stack<location> &pathSoFar, std::list<Direction> listOfDirection, int size)
// {

// 	for (Direction direction : listOfDirection)
// 	{
// 		location possibleNextLocation = handleNextMovement(currentLocation, direction);
// 		if (!checkValidMove(currentLocation, possibleNextLocation, walls, size))
// 		{
// 			continue;
// 		}

// 		pathSoFar.push(possibleNextLocation);
// 		nextMove(walls, possibleNextLocation, pathSoFar, listOfDirection, size);
// 	}
// }

// int Labyrinth(std::set<std::pair<location, location>> labyrinth, int size)
// {

// 	std::list<Direction> listOfDirection;
// 	listOfDirection.push_back(RIGHT);
// 	listOfDirection.push_back(UP);
// 	listOfDirection.push_back(DOWN);
// 	listOfDirection.push_back(LEFT);

// 	nextMove(labyrinth, location(size - 1, size - 1), std::stack<location>(), listOfDirection, size);

// 	return 0;
// }

// bool alreadyVisited(location possibleNextLocation, std::list<location> visitedAlready)
// {
// 	for (location loc : visitedAlready)
// 	{
// 		if (loc.first == possibleNextLocation.first && loc.second == possibleNextLocation.second)
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }

// void fillTree(std::set<std::pair<location, location>> walls, LabyrinthTree &tree, location currentLocation, std::list<location> &visitedAlready, std::list<Direction> listOfDirection, int size)
// {
// 	// BASE CASE PROBABLY SHIIIT
// 	if (currentLocation.first >= size - 1 && currentLocation.second >= size - 1)
// 	{
// 		return;
// 	}

// 	for (Direction direction : listOfDirection)
// 	{
// 		location possibleNextLocation = handleNextMovement(currentLocation, direction);
// 		if (!checkValidMove(currentLocation, possibleNextLocation, walls, size) || alreadyVisited(possibleNextLocation, visitedAlready))
// 		{

// 			continue;
// 		}
// 		std::cout << "possible: (" << possibleNextLocation.first << "," << possibleNextLocation.second << ")" << std::endl;

// 		visitedAlready.push_back(possibleNextLocation);
// 		LabyrinthTree child;
// 		child.loc = possibleNextLocation;
// 		tree.children.push_back(child);
// 		fillTree(walls, child, possibleNextLocation, visitedAlready, listOfDirection, size);
// 	}
// }

// void printTree(LabyrinthTree &tree, std::string delimiter)
// {
// 	std::cout << delimiter << "(" << tree.loc.first << ", " << tree.loc.second << ")" << std::endl;
// 	if (tree.children.empty())
// 	{
// 		return;
// 	}
// 	for (LabyrinthTree child : tree.children)
// 	{
// 		printTree(child, delimiter + "--");
// 	}
// }

// int Labyrinth(std::set<std::pair<location, location>> labyrinth, int size)
// {
// 	location firstLocation;
// 	firstLocation.first = 0;
// 	firstLocation.second = 0;
// 	LabyrinthTree tree;
// 	tree.loc = firstLocation;

// 	std::list<location> visitedAlready;
// 	visitedAlready.push_back(firstLocation);

// 	std::list<Direction> listOfDirection;
// 	listOfDirection.push_back(RIGHT);
// 	listOfDirection.push_back(UP);
// 	listOfDirection.push_back(DOWN);
// 	listOfDirection.push_back(LEFT);

// 	fillTree(labyrinth, tree, firstLocation, visitedAlready, listOfDirection, size);
// 	printTree(tree, "");
// 	return 13;
// }
