#include <stdio.h>
#include <iostream>
#include <utility>

/**

	======= PROBLEM =======
	you have these like two base classes
	ghost room and ghost maze or something
	and you have to extend the class to do something else
	but have a templatized version of maze that can accept ghost rooms and other kinds of rooms and doors and shit
	it's basically seeing if you learned about templates and virtual inheritence from life

	sorry that was probably confusing
	you have a maze class, a room class and a door class
	a maze is composed of rooms and doors
	there are different kinds of rooms and doors that correspond to different mazes
	i think his example was ghost doors/rooms and some other kind of rooms and doors
	and he hard coded the maze types
	GhostMaze and OtherMaze
	your goal is to make a templatized maze class that can accept both ghost rooms/doors and the other rooms/doors

	There is no abstract Maze class
	there are two concrete types
	called GhostMaze and OtherMaze
	It's your job to make Maze<T>
	that can accept both ghostrooms/ghostdoors and otherrooms/otherdoors
	I think pretty much everyone made an abstract door and room type
	then you can use that in the methods and can recieve GhostDoor* and OtherDoor*
	using AbstractDoor*
	and it might not have been Maze<T> just Maze
	where the constructor takes an AbstractDoor* and an AbstractRoom*
	and depending on what you pass as you construct the maze objects determines what it is
	sorry it's been a while

	you cant change the code of GhostRoom and stuff to inhert from abstract room -> wth am I supposed to do then?...

**/

class Maze {

	AbstractRoom* room;
	AbstractDoor* door;

	Maze& operator=(const Maze& rhs) {
		delete room;
		delete door;
		room = rhs.room;
		(*room)(*(rhs.room));
		// (*door)(*rhs.door);
		return *this;
	}

public:
	Maze(AbstractRoom* r, AbstractDoor* d) : room(r), door(d) {}
	Maze(const Maze& m) :
		room(m.room),
		door(m.door) {}
	~Maze() {
		delete room;
		delete door;
	}
};

// alternatively using templates
/*
template<typename R, typename D>
class Maze {

	R* room;
	D* door;

	Maze& operator=(const Maze& rhs) {
		room = rhs.room; // will this just use pointer equality? Do I need to dereference like this -> [    *(lhs.room) = *(rhs.room);     ] ?
		door = rhs.door;
	}

public:
	Maze(R* r, D* d) : room(r), door(d) {}
	Maze(const Maze& m) :
		room(m.room),
		door(m.door) {}
	~Maze() {
		delete room;
		delete door;
	}
};*/

class AbstractRoom {
protected:
	size_t volume;
	size_t height = 4;

public:
	virtual AbstractRoom* create()	const = 0; // essentially the default cstr
	virtual AbstractRoom* clone()	const = 0; // essentially the copy cstr
	virtual ~AbstractRoom() = 0;

	// TODO: help why is this error happening?
	// virtual AbstractRoom& operator=(const AbstractRoom& rhs) = 0; 
	// IntelliSense: object of abstract class type "GhostRoom" is not allowed:
	// pure virtual function "AbstractRoom::operator=" has no overrider

	// should there bea protected cstr, copy cstr?

	void increase_volume(size_t amount) { // now it's not an interface
		volume += amount;
	}

	void increase_height(size_t amount) {
		height += amount;
	}

	size_t get_area() {
		return volume / height;
	}
};

class GhostRoom : AbstractRoom {
	size_t num_ghosts;

	// TODO: error:operator= must be a member function
	// why is this error happening?
	/*friend GhostRoom& operator=(const GhostRoom& lhs, const GhostRoom& rhs) {
		lhs.num_ghosts = rhs.num_ghosts;
	}*/

public:

	GhostRoom() : num_ghosts(42) {}
	GhostRoom(const GhostRoom& rhs) : num_ghosts(rhs.num_ghosts) {}
	~GhostRoom() = default;
	GhostRoom& operator=(const GhostRoom& rhs) {
		num_ghosts = rhs.num_ghosts; // should this use initialization list?
	}

	GhostRoom* create() const {
		return new GhostRoom();
	}

	GhostRoom* clone() const {
		return new GhostRoom(*this);
	}
};

class OtherRoom : AbstractRoom {
	size_t num_people;

public:
	OtherRoom() : num_people(69) {}
	OtherRoom(const OtherRoom& rhs) : num_people(rhs.num_people) {}
	~OtherRoom() = default;
	OtherRoom& operator=(const OtherRoom& rhs) {
		num_people = rhs.num_people; // should this use initialization list?
	}

	OtherRoom* create() const {
		return new OtherRoom();
	}

	OtherRoom* clone() const {
		return new OtherRoom(*this);
	}
};

class AbstractDoor {
	// same shit as Room
};

class GhostDoor : AbstractDoor {
	size_t temp;
};

class OtherDoor : AbstractDoor {
	size_t num_opens;
};