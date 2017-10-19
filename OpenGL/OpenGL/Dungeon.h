/*

Created by Thomas Angeland, student at Østfold University College, Norway.

Refferences:

#3	"Rooms and Mazes: A Procedural Dungeon Generator" by Bob Nystrom (21.12.2014).
Sourced 27.09.2017 from http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/.
My dungeon generator is written entirely by me, but based on Nystrom's guide.

#4	Hundreds of Stack Overflow articles. Thank God that webpage exists.

*/

#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
#include <glm.hpp>

class Dungeon
{
public:
	enum Symbols : char
	{
		EMPTY = ' ',
		END = 'E',
		PATH = 'f',
		WALL = 'w',
		CORNER = 'c',
		ROOM_WALL = 'W',
		ROOM_FLOOR = 'F',
		ROOM_CORNER = 'C',
		DOOR = '+',
		TELEPORTER = 't',
		DEAD_END = 'X',
	};

	class Cell
	{
	public:
		int ID, x, y;
		char type;
		bool deadEnd = false;
		static int numberOfRegions;

		Cell() {
			type = NULL;
		}

		Cell(char type) {
			this->type = type;
		}

		Cell(char type, int region) {
			this->type = type;
			this->ID = region;
		}

		Cell(char type, int region, int x, int y) {
			this->type = type;
			this->ID = region;
			this->x = x;
			this->y = y;
		}

		void remove() {
			type = NULL;
			deadEnd = false;
			ID = 0;
			x = 0;
			y = 0;
		}

		std::string toString() {
			if (type == NULL) return " ";
			else return std::string(1, type);
		}
	};

	struct Teleporter
	{
		int x, y, address, linkedToAddress;

		Teleporter() {};

		Teleporter(int x, int y, int address) {
			this->x = x;
			this->y = y;
			this->address = address;
		}

		void linkTo(Teleporter teleporter, bool twoWay) {
			linkedToAddress = teleporter.address;
			if (twoWay)
				teleporter.linkedToAddress = address;
		}
	};

	class Room
	{
	public:

		int roomNR, x, y, startX, endX, startY, endY, width, height;

		bool hasDoors = false;

		std::vector<int> connectedRegions;

		Room() {};

		Room(int startX, int endX, int startY, int endY, int roomNR) {
			this->x = startX + ((endX - startX) / 2);
			this->y = startY + ((endY - startY) / 2);
			this->roomNR = roomNR;
			this->startX = startX;
			this->endX = endX;
			this->startY = startY;
			this->endY = endY;
			this->width = endX - startX + 1;
			this->height = endY - startY + 1;
		}

		std::vector<int> & getConnectedRegions() {
			return connectedRegions;
		}

		int areal() {
			return width * height;
		}

		void connectWith(int region) {
			getConnectedRegions().push_back(region);
		}

		bool isConnected(int region) {
			for (int connectedRegion : getConnectedRegions()) {
				if (region == connectedRegion) {
					return true;
				}
			}
			return false;
		}

		bool connectIfNotconnected(int region) {
			if (!isConnected(region)) {
				connectWith(region);
				return true;
			}
			else return false;
		}

		std::string Room::toString() {
			return std::to_string(roomNR);
		}

		std::string Room::toStringWithDetails() {
			return "RoomNR: " + std::to_string(roomNR)
				+ "\nPosition: " + std::to_string(x) + ", " + std::to_string(y)
				+ "\nSize: " + std::to_string(width) + " x " + std::to_string(height) + " (" + std::to_string(areal()) + " cells)";
		}
	};

	class Door
	{
	public:

		int x, y, roomNR;

		char direction;

		Door() {};

		Door(int x, int y, int roomNR, char direction) {
			this->x = x;
			this->y = y;
			this->roomNR = roomNR;
			this->direction = direction;
		}
	};

private:

	// Dungeon defaults
	const std::string DEFAULT_NAME = "Dungeon";
	const int WIDTH = 50;
	const int HEIGHT = 50;
	const int ATTEMPTS = 200;
	const int MIN_ROOM_WIDTH = 6;
	const int MAX_ROOM_WIDTH = 10;
	const int MIN_ROOM_HEIGHT = 6;
	const int MAX_ROOM_HEIGHT = 10;

	std::string name;
	int width, height, attempts, minRoomWidth, maxRoomWidth, minRoomHeight, maxRoomheight, numberOfRooms = 0, numberOfRegions = 0, numberOfteleporters = 0;

	std::vector<std::vector<Cell>> blueprint;
	std::vector<Room> roomList;
	std::vector<Door> doorList;
	std::vector<std::vector<bool>> regionConnectedToRoom;

	std::mt19937 generator;
	clock_t time_begin, time_end;

public:
	Dungeon::Dungeon();
	Dungeon::Dungeon(int width, int height, int attempts);
	Dungeon::Dungeon(int width, int height, int attempts, int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomheight);
	Dungeon::Dungeon(std::string name, int width, int height, int attempts, int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomheight);
	Dungeon::~Dungeon();

	void Dungeon::generate();
	void Dungeon::fillAllEmptyWith(char fill);
	void Dungeon::insertRooms();
	void Dungeon::insertPaths();
	void Dungeon::traversePaths(int x, int y);
	bool Dungeon::findPlaceForPath(int *x, int *z);
	void Dungeon::insertDoors();
	bool Dungeon::connectIfNotconnected(int region, int room);
	void Dungeon::setRoomHasDoorTrue(int x, int y);
	void Dungeon::traverseRegion(int x, int y, int cameFrom);
	void Dungeon::removeMultipleRoutes();
	void Dungeon::removeRegion(int reg);
	bool Dungeon::removeFromDeadEnd(int x, int y, int cameFrom);
	void Dungeon::insertTeleporters();
	bool Dungeon::placeTeleporter(Dungeon::Room room, bool placeLink);
	bool Dungeon::findEmptyCell(int *x, int *y);
	bool Dungeon::cellContains(int x, int y, char type);
	bool Dungeon::isCordinatesValid(int x, int y);
	int Dungeon::numberOfEmptyCells();
	char Dungeon::getCell(int x, int y);
	int Dungeon::getWidth();
	void Dungeon::setWidth(int width);
	int Dungeon::getHeight();
	void Dungeon::setHeight(int height);
	std::vector<Dungeon::Room>& Dungeon::getRoomList();
	std::vector<Dungeon::Door>& Dungeon::getDoorList();
	int Dungeon::getNumberOfRooms();
	int Dungeon::getNumberOfRegions();
	std::string Dungeon::getName();
	int Dungeon::randomInt(int min, int max);
	double Dungeon::getBuildTime();
	std::string Dungeon::toString();
	void Dungeon::printWithDetails();
	void Dungeon::print();
};

#endif