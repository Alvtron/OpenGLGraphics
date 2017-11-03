/*

Created by Thomas Angeland, student at Østfold University College, Norway.

Refferences:

#3	"Rooms and Mazes: A Procedural Dungeon Generator" by Bob Nystrom (21.12.2014).
Sourced 27.09.2017 from http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/.
My dungeon generator is written entirely by me, but based on Nystrom's guide.

#4	Hundreds of Stack Overflow articles. Thank God that webpage exists.

*/

#include "Dungeon.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>

Dungeon::Dungeon() {
	this->name = DEFAULT_NAME;
	this->width = WIDTH;
	this->height = HEIGHT;
	this->attempts = ATTEMPTS;
	this->minRoomWidth = MIN_ROOM_WIDTH;
	this->maxRoomWidth = MAX_ROOM_WIDTH;
	this->minRoomHeight = MIN_ROOM_HEIGHT;
	this->maxRoomheight = MAX_ROOM_HEIGHT;
	this->generate();
}

Dungeon::~Dungeon()
{
	std::cout << "Dungeon destroyed!" << std::endl;
}

Dungeon::Dungeon(int width, int height, int attempts)
{
	this->name = DEFAULT_NAME;
	this->width = (width > 0) ? width : WIDTH;
	this->height = (height > 0) ? height : HEIGHT;
	this->attempts = (attempts >= 0) ? attempts : ATTEMPTS;
	this->minRoomWidth = MIN_ROOM_WIDTH;
	this->maxRoomWidth = MAX_ROOM_WIDTH;
	this->minRoomHeight = MIN_ROOM_HEIGHT;
	this->maxRoomheight = MAX_ROOM_HEIGHT;
	generate();
}

Dungeon::Dungeon(int width, int height, int attempts, int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomheight)
{
	this->name = DEFAULT_NAME;
	this->width = (width > 0) ? width : WIDTH;
	this->height = (height > 0) ? height : HEIGHT;
	this->attempts = (attempts >= 0) ? attempts : ATTEMPTS;
	this->minRoomWidth = (minRoomWidth > 0 && minRoomWidth <= maxRoomWidth) ? minRoomWidth : MIN_ROOM_WIDTH;
	this->maxRoomWidth = (maxRoomWidth > 0 && maxRoomWidth >= minRoomWidth) ? maxRoomWidth : MAX_ROOM_WIDTH;
	this->minRoomHeight = (minRoomHeight > 0 && minRoomHeight <= maxRoomheight) ? minRoomHeight : MIN_ROOM_HEIGHT;
	this->maxRoomheight = (maxRoomheight > 0 && maxRoomheight >= minRoomHeight) ? maxRoomheight : MAX_ROOM_HEIGHT;
	generate();
}

Dungeon::Dungeon(std::string name, int width, int height, int attempts, int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomheight) {
	this->name = name;
	this->width = (width > 0) ? width : WIDTH;
	this->height = (height > 0) ? height : HEIGHT;
	this->attempts = (attempts >= 0) ? attempts : ATTEMPTS;
	this->minRoomWidth = (minRoomWidth > 0 && minRoomWidth <= maxRoomWidth) ? minRoomWidth : MIN_ROOM_WIDTH;
	this->maxRoomWidth = (maxRoomWidth > 0 && maxRoomWidth >= minRoomWidth) ? maxRoomWidth : MAX_ROOM_WIDTH;
	this->minRoomHeight = (minRoomHeight > 0 && minRoomHeight <= maxRoomheight) ? minRoomHeight : MIN_ROOM_HEIGHT;
	this->maxRoomheight = (maxRoomheight > 0 && maxRoomheight >= minRoomHeight) ? maxRoomheight : MAX_ROOM_HEIGHT;
	generate();
}

std::vector<Dungeon::Room>& Dungeon::getRoomList()
{
	return roomList;
}

std::vector<Dungeon::Door>& Dungeon::getDoorList()
{
	return doorList;
}

// Generate dungeon, fill with room, doors and corridors.
void Dungeon::generate() {

	time_begin = clock();

	// Seed random functions
	generator.seed(time(0));
	srand(time(0));

	// Setup array sizes
	blueprint.resize(width);
	regionConnectedToRoom.resize(width);
	for (int i = 0; i < width; ++i) {
		blueprint[i].resize(height);
		regionConnectedToRoom[i].resize(height);
	}

	insertRooms();
	insertPaths();
	insertDoors();

	removeMultipleRoutes();

	//insertTeleporters();

	time_end = clock();
}

void Dungeon::fillAllEmptyWith(char fill) {
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (cellContains(x, y, NULL))
				blueprint[x][y] = Cell(fill);
}

void Dungeon::insertRooms() {
	for (int a = 0; a < attempts; a++) {

		// Generate random room size
		int roomWidth = randomInt(minRoomWidth, maxRoomWidth);
		int roomHeight = randomInt(minRoomHeight, maxRoomheight);

		// generate random xz-position, but with room size in mind
		int randomX = randomInt(roomWidth + 1, width - roomWidth - 1);
		int randomY = randomInt(roomHeight + 1, height - roomHeight - 1);

		int available = true;

		// Checks if theres space for said room at xz-position.
		for (int x = randomX - roomWidth - 1; x < randomX + roomWidth + 1; x++) {
			for (int y = randomY - roomHeight - 1; y < randomY + roomHeight + 1; y++) {
				if (!cellContains(x, y, NULL)) {
					available = false;
					break;
				}
			}
			if (!available) break;
		}

		// If the place is free, place the room
		if (available) {

			// Set up variables for all four corners
			int startX = randomX - roomWidth;
			int endX = randomX + roomWidth;
			int startY = randomY - roomHeight;
			int endY = randomY + roomHeight;

			Room room = Room(startX, endX, startY, endY, numberOfRooms);
			getRoomList().push_back(room);

			// Draw room: room corners
			blueprint[startX][startY] = Cell(ROOM_CORNER, numberOfRooms);
			blueprint[startX][endY] = Cell(ROOM_CORNER, numberOfRooms);
			blueprint[endX][startY] = Cell(ROOM_CORNER, numberOfRooms);
			blueprint[endX][endY] = Cell(ROOM_CORNER, numberOfRooms);

			// Draw room: horizontal room walls
			for (int i = startX + 1; i < endX; i++) {
				blueprint[i][startY] = Cell(ROOM_WALL, numberOfRooms);
				blueprint[i][endY] = Cell(ROOM_WALL, numberOfRooms);
			}

			// Draw room: vertical room walls
			for (int i = startY + 1; i < endY; i++) {
				blueprint[startX][i] = Cell(ROOM_WALL, numberOfRooms);
				blueprint[endX][i] = Cell(ROOM_WALL, numberOfRooms);
			}

			// Draw room: set up room floor
			for (int x = startX + 1; x < endX; x++)
				for (int y = startY + 1; y < endY; y++)
					blueprint[x][y] = Cell(ROOM_FLOOR, numberOfRooms);

			numberOfRooms++;
		}
	}
}

void Dungeon::insertPaths() {

	int x = -1; int z = -1;

	while (findPlaceForPath(&x, &z)) {
		traversePaths(x, z);
		numberOfRegions++;
	}
}

void Dungeon::traversePaths(int x, int y) {

	// Draw path 
	blueprint[x][y] = Cell(PATH, numberOfRegions);

	// Try all four possible steps

	// Shuffle the order of which step to take
	int choices[4] = { 1,2,3,4 };
	std::random_shuffle(std::begin(choices), std::end(choices));

	for (int choice : choices) {
		switch (choice) {

		case 1:
			// UP
			if (cellContains(x, y + 1, NULL) && !cellContains(x + 1, y + 1, PATH) && !cellContains(x - 1, y + 1, PATH) && !cellContains(x, y + 2, PATH) && !cellContains(x + 1, y + 2, PATH) && !cellContains(x - 1, y + 2, PATH))
				traversePaths(x, y + 1);

		case 2:
			// DOWN 
			if (cellContains(x, y - 1, NULL) && !cellContains(x + 1, y - 1, PATH) && !cellContains(x - 1, y - 1, PATH) && !cellContains(x, y - 2, PATH) && !cellContains(x + 1, y - 2, PATH) && !cellContains(x - 1, y - 2, PATH))
				traversePaths(x, y - 1);

		case 3:
			// RIGHT
			if (cellContains(x + 1, y, NULL) && !cellContains(x + 1, y + 1, PATH) && !cellContains(x + 1, y - 1, PATH) && !cellContains(x + 2, y, PATH) && !cellContains(x + 2, y + 1, PATH) && !cellContains(x + 2, y - 1, PATH))
				traversePaths(x + 1, y);

		case 4:
			// LEFT
			if (cellContains(x - 1, y, NULL) && !cellContains(x - 1, y + 1, PATH) && !cellContains(x - 1, y - 1, PATH) && !cellContains(x - 2, y, PATH) && !cellContains(x - 2, y + 1, PATH) && !cellContains(x - 2, y - 1, PATH))
				traversePaths(x - 1, y);
		}
	}
}

bool Dungeon::findPlaceForPath(int *x, int *z) {

	bool foundIt = false;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (cellContains(i, j, NULL)
				&& !cellContains(i, j, PATH)
				&& !cellContains(i, j + 1, PATH)
				&& !cellContains(i, j - 1, PATH)
				&& !cellContains(i + 1, j, PATH)
				&& !cellContains(i + 1, j + 1, PATH)
				&& !cellContains(i + 1, j - 1, PATH)
				&& !cellContains(i - 1, j, PATH)
				&& !cellContains(i - 1, j + 1, PATH)
				&& !cellContains(i - 1, j - 1, PATH)) {

				*x = i; *z = j;
				foundIt = true;
				break;
			}
		}
		if (foundIt) break;
	}

	return foundIt;
}

void Dungeon::insertDoors() {

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (cellContains(x, y, ROOM_WALL)) {
				if (cellContains(x + 1, y, PATH)) {
					if (!connectIfNotconnected(blueprint[x + 1][y].ID, blueprint[x][y].ID)) {
						getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'R'));
						blueprint[x][y].type = DOOR;
						setRoomHasDoorTrue(x, y);
						traverseRegion(x + 1, y, 1);
					}
				}

				else if (cellContains(x - 1, y, PATH)) {
					if (!connectIfNotconnected(blueprint[x - 1][y].ID, blueprint[x][y].ID)) {
						getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'L'));
						blueprint[x][y].type = DOOR;
						setRoomHasDoorTrue(x, y);
						traverseRegion(x - 1, y, 2);
					}
				}

				else if (cellContains(x, y + 1, PATH)) {
					if (!connectIfNotconnected(blueprint[x][y + 1].ID, blueprint[x][y].ID)) {
						getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'U'));
						blueprint[x][y].type = DOOR;
						setRoomHasDoorTrue(x, y);
						traverseRegion(x, y + 1, 3);
					}
				}

				else if (cellContains(x, y - 1, PATH)) {
					if (!connectIfNotconnected(blueprint[x][y - 1].ID, blueprint[x][y].ID)) {
						getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'D'));
						blueprint[x][y].type = DOOR;
						setRoomHasDoorTrue(x, y);
						traverseRegion(x, y - 1, 4);
					}
				}
			}
}

bool Dungeon::connectIfNotconnected(int region, int room) {
	if (region >= 0 && region < numberOfRegions && room >= 0 && room < numberOfRooms)
		if (!regionConnectedToRoom[region][room]) {
			regionConnectedToRoom[region][room] = true;
			return false;
		}

		else return true;
}

void Dungeon::setRoomHasDoorTrue(int x, int y) {
	for (int i = 0; i < getRoomList().size(); i++)
		getRoomList()[i].hasDoors = (getRoomList()[i].roomNR == blueprint[x][y].ID) ? true : false;
}

void Dungeon::traverseRegion(int x, int y, int cameFrom) {

	// Check for room walls not equal to roomNR
	if (cellContains(x + 1, y, ROOM_WALL))
		if (!connectIfNotconnected(blueprint[x + 1][y].ID, blueprint[x][y].ID)) {
			getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'R'));
			blueprint[x + 1][y].type = DOOR;
			setRoomHasDoorTrue(x + 1, y);
		}

	if (cellContains(x - 1, y, ROOM_WALL))
		if (!connectIfNotconnected(blueprint[x - 1][y].ID, blueprint[x][y].ID)) {
			getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'L'));
			blueprint[x - 1][y].type = DOOR;
			setRoomHasDoorTrue(x - 1, y);
		}

	if (cellContains(x, y + 1, ROOM_WALL))
		if (!connectIfNotconnected(blueprint[x][y + 1].ID, blueprint[x][y].ID)) {
			getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'U'));
			blueprint[x][y + 1].type = DOOR;
			setRoomHasDoorTrue(x, y + 1);
		}

	if (cellContains(x, y - 1, ROOM_WALL))
		if (!connectIfNotconnected(blueprint[x][y - 1].ID, blueprint[x][y].ID)) {
			getDoorList().push_back(Door(x, y, blueprint[x][y].ID, 'D'));
			blueprint[x][y - 1].type = DOOR;
			setRoomHasDoorTrue(x, y - 1);
		}

	// Check for new ways to traverse
	bool way = false;

	// 1: Right
	if (cellContains(x + 1, y, PATH) && cameFrom != 2) {
		traverseRegion(x + 1, y, 1); way = true;
	}

	// 2: Left
	if (cellContains(x - 1, y, PATH) && cameFrom != 1) {
		traverseRegion(x - 1, y, 2); way = true;
	}

	// 3: Up
	if (cellContains(x, y + 1, PATH) && cameFrom != 4) {
		traverseRegion(x, y + 1, 3); way = true;
	}

	// 4: Down
	if (cellContains(x, y - 1, PATH) && cameFrom != 3) {
		traverseRegion(x, y - 1, 4); way = true;
	}

	// If there is no way, set it as a 'dead end'
	if (!way && !(cellContains(x + 1, y, DOOR) || cellContains(x - 1, y, DOOR) || cellContains(x, y + 1, DOOR) || cellContains(x, y - 1, DOOR))) {
		blueprint[x][y].deadEnd = true;
	}
}

void Dungeon::removeMultipleRoutes() {

	// Remove regions that are connected to less that 2 rooms
	for (int region = 0; region < numberOfRegions; region++) {
		int roomsConnectedTo = 0;
		for (int room = 0; room < numberOfRooms; room++)
			if (regionConnectedToRoom[region][room]) {
				roomsConnectedTo++;
			}
		if (roomsConnectedTo < 2)
			removeRegion(region); ;
	}

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (cellContains(x, y, PATH) && blueprint[x][y].deadEnd)
				removeFromDeadEnd(x, y, 0);

	// Remove doors that are not connected
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (cellContains(x, y, DOOR) && !(cellContains(x + 1, y, PATH) || cellContains(x - 1, y, PATH) || cellContains(x, y + 1, PATH) || cellContains(x, y - 1, PATH)))
				blueprint[x][y].type = ROOM_WALL;
}

void Dungeon::removeRegion(int reg) {
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (blueprint[x][y].ID == reg) {
				blueprint[x][y].remove();
			}
	numberOfRegions--;
}

bool Dungeon::removeFromDeadEnd(int x, int y, int cameFrom) {

	if (cellContains(x + 1, y, DOOR) || cellContains(x - 1, y, DOOR) || cellContains(x, y + 1, DOOR) || cellContains(x, y - 1, DOOR))
		return false;

	int ways = 0;

	// 1: Right

	int newX, newY, newCameFrom;

	if (cellContains(x + 1, y, PATH) && cameFrom != 2) {
		newX = x + 1; newY = y; newCameFrom = 1;
		ways++;
	}

	// 2: Left
	if (cellContains(x - 1, y, PATH) && cameFrom != 1) {
		newX = x - 1; newY = y; newCameFrom = 2;
		ways++;
	}

	// 3: Up
	if (cellContains(x, y + 1, PATH) && cameFrom != 4) {
		newX = x; newY = y + 1; newCameFrom = 3;
		ways++;
	}

	// 4: Down
	if (cellContains(x, y - 1, PATH) && cameFrom != 3) {
		newX = x; newY = y - 1; newCameFrom = 4;
		ways++;
	}

	// More ways that 1? --> This isn't a dead end
	if (ways > 1)
		return false;

	// Just one way? Check it out, but remove this path first
	else if (ways == 1) {
		blueprint[x][y].remove();
		removeFromDeadEnd(newX, newY, newCameFrom);
		return true;
	}
	// No ways. This is a dead end.
	else {
		blueprint[x][y].remove();
		return true;
	}

}

void Dungeon::insertTeleporters() {

	// find rooms without doors
	for (Room room : getRoomList()) {

		bool hasDoor = false;

		for (int x = room.startX; x <= room.endX; x++) {
			for (int y = room.startY; y <= room.endY; y++) {
				if ((x > room.startX && x < room.endX && (y == room.startY || y == room.endY)) || (y > room.startY && y < room.endY && (x == room.startX || x == room.endX)))
					if (cellContains(x, y, DOOR))
						hasDoor = true;
			}
		}

		// Room contains no doors, find spot for teleporter
		if (!hasDoor) {
			placeTeleporter(room, true);
		}
	}
}

bool Dungeon::placeTeleporter(Dungeon::Room room, bool placeLink) {
	int x, y;
	bool foundSpot = false;
	Teleporter teleporter, secondTeleporter;

	int corners[4] = { 1,2,3,4 };
	std::random_shuffle(std::begin(corners), std::end(corners));

	for (int corner : corners)
		switch (corner) {
		case 1:
			if (cellContains(room.startX + 1, room.startY, ROOM_WALL) && cellContains(room.startX, room.startY + 1, ROOM_WALL) && !foundSpot) {
				x = room.startX + 1; y = room.startY + 1;
				foundSpot = true;
			}
		case 2:
			if (cellContains(room.startX + 1, room.endY, ROOM_WALL) && cellContains(room.startX, room.endY - 1, ROOM_WALL) && !foundSpot) {
				x = room.startX + 1; y = room.endY - 1;
				foundSpot = true;
			}
		case 3:
			if (cellContains(room.endX - 1, room.startY, ROOM_WALL) && cellContains(room.endX, room.startY + 1, ROOM_WALL) && !foundSpot) {
				x = room.endX - 1; y = room.startY + 1;
				foundSpot = true;
			}
		case 4:
			if (cellContains(room.endX - 1, room.endY, ROOM_WALL) && cellContains(room.endX, room.endY - 1, ROOM_WALL) && !foundSpot) {
				x = room.endX - 1; y = room.endY - 1;
				foundSpot = true;
			}
		}

	// Spot found, --> place teleporter
	if (foundSpot) {
		std::cout << "Placing first door at " + std::to_string(x) + ", " + std::to_string(y) << std::endl;
		blueprint[x][y] = TELEPORTER;
		teleporter = Teleporter(x, y, numberOfteleporters);
		numberOfteleporters++;
	}

	// Place a second teleporter in a different room (with doors)
	if (foundSpot && placeLink) {

		for (Room secondRoom : getRoomList()) {
			bool secondHasDoor = false;

			for (int x = secondRoom.startX; x <= secondRoom.endX; x++) {
				for (int y = secondRoom.startY; y <= secondRoom.endY; y++) {
					if (cellContains(x, y, DOOR)) {
						secondHasDoor = true;
						break;
					}
				}
				if (secondHasDoor) break;
			}

			// Room has door, find spot for teleporter
			if (secondHasDoor) {
				int secondX, secondY;
				bool foundSecondSpot = false;

				std::random_shuffle(std::begin(corners), std::end(corners));

				for (int corner : corners)
					switch (corner) {
					case 1:
						if (cellContains(secondRoom.startX + 1, secondRoom.startY, ROOM_WALL) && cellContains(secondRoom.startX, secondRoom.startY + 1, ROOM_WALL) && !foundSecondSpot) {
							secondX = secondRoom.startX + 1; secondY = secondRoom.startY + 1;
							foundSecondSpot = true;
						}
					case 2:
						if (cellContains(secondRoom.startX + 1, secondRoom.endY, ROOM_WALL) && cellContains(secondRoom.startX, secondRoom.endY - 1, ROOM_WALL) && !foundSecondSpot) {
							secondX = secondRoom.startX + 1; secondY = secondRoom.endY - 1;
							foundSecondSpot = true;
						}
					case 3:
						if (cellContains(secondRoom.endX - 1, secondRoom.startY, ROOM_WALL) && cellContains(secondRoom.endX, secondRoom.startY + 1, ROOM_WALL) && !foundSecondSpot) {
							secondX = secondRoom.endX - 1; secondY = secondRoom.startY + 1;
							foundSecondSpot = true;
						}
					case 4:
						if (cellContains(secondRoom.endX - 1, secondRoom.endY, ROOM_WALL) && cellContains(secondRoom.endX, secondRoom.endY - 1, ROOM_WALL) && !foundSecondSpot) {
							secondX = secondRoom.endX - 1; secondY = secondRoom.endY - 1;
							foundSecondSpot = true;
						}
					}

				if (foundSecondSpot) {
					std::cout << "Placing second door at " + std::to_string(secondX) + ", " + std::to_string(secondY) << std::endl;
					blueprint[secondX][secondY] = TELEPORTER;
					secondTeleporter = Teleporter(secondX, secondY, numberOfteleporters);
					secondTeleporter.linkTo(teleporter, true);
					numberOfteleporters++;
					return true;
				}
				else continue;
			}
		}
	}
	return false;
}

bool Dungeon::findEmptyCell(int *x, int *y) {

	bool foundIt = false;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if ((cellContains(i, j, NULL))) {
				*x = i; *y = j;
				foundIt = true;
				break;
			}
		}
		if (foundIt)
			break;
	}

	return foundIt;
}

bool Dungeon::cellContains(int x, int y, char type) {
	if (isCordinatesValid(x, y))
		return (blueprint[x][y].type == type);
	else
		return false;
}

bool Dungeon::isCordinatesValid(int x, int y) {
	return (x >= 0 && x < width && y >= 0 && y < height);
}

int Dungeon::numberOfEmptyCells() {
	int num = 0;
	for (int x = 0; x < width; x++)
		for (int z = 0; z < height; z++) {
			if (cellContains(x, z, NULL))
				num++;
		}

	return num;
}

char Dungeon::getCell(int x, int y) {
	if (isCordinatesValid(x, y)) {
		return blueprint[x][y].type;
	}
	else {
		std::cout << x << ", " << y << "is out of bounds!" << std::endl;
		return ' ';
	}
}

int Dungeon::getWidth() {
	return width;
}

void Dungeon::setWidth(int width) {
	this->width = width;
}

int Dungeon::getHeight() {
	return height;
}

void Dungeon::setHeight(int height) {
	this->height = height;
}

int Dungeon::getNumberOfRooms() {
	return numberOfRooms;
}

int Dungeon::getNumberOfRegions() {
	return numberOfRegions;
}

std::string Dungeon::getName() {
	return name;
}

int Dungeon::randomInt(int min, int max) {

	std::uniform_int_distribution<uint32_t> random(min, max);
	return random(generator);
}

double Dungeon::getBuildTime() {
	return double(time_end - time_begin) / CLOCKS_PER_SEC;
}

std::string Dungeon::toString() {
	std::string s = "";
	for (int i = width - 1; i >= 0; i--) {
		for (int j = 0; j < height; j++)
			s += std::string(1, blueprint[j][i].type);
		if (i > 0)
			s += "\n";
	}
	return s;
}

void Dungeon::printWithDetails() {

	std::string blueprintString = "";

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (blueprint[j][i].deadEnd)
				blueprintString += DEAD_END;
			else if (cellContains(j, i, PATH))
				blueprintString += std::to_string(blueprint[j][i].ID);
			else if (cellContains(j, i, ROOM_FLOOR))
				blueprintString += std::to_string(blueprint[j][i].ID);
			else
				blueprintString += blueprint[j][i].toString();
		}
		blueprintString += "\n";
	}

	std::cout << blueprintString << std::endl;
}

void Dungeon::print() {

	std::string breakline = "";
	std::string horizontalSymbol = ".";
	std::string verticalSymbol = ":";

	std::string blueprintString = "";

	for (int i = 0; i < height; i++) {
		blueprintString += verticalSymbol;
		for (int j = 0; j < width; j++)
			blueprintString += blueprint[j][i].toString();
		if (i == height - 1)
			blueprintString += verticalSymbol;
		else
			blueprintString += verticalSymbol + "\n";
	}

	for (int i = 0; i < width + 2; i++)
		breakline += horizontalSymbol;
	std::cout << breakline << std::endl << blueprintString << std::endl << breakline << std::endl;
}