#pragma once

#include <dlfcn.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include "ApiDisplay.hpp"
#include "menu.hpp"
#include "snake.hpp"
#include "obj.hpp"

#define	DELAY 1000
#define SPEED 4

typedef std::unique_ptr<ApiDisplay*> displayPtr;

class nibbler
{
public:
	nibbler();
	nibbler(const nibbler &) = default;
	nibbler & operator=(const nibbler &) = default;
	~nibbler();

	void Play(unsigned height, unsigned width, char *type);

private:

	menu				_interface;
	
	unsigned long int	_time;
	unsigned			_delay;
	
	void*				_dl;
	size_t				_dl_number;
	displayPtr			_display;
	
	objectsVector	_walls;
	objectsVector 	_foods;
	objectsVector	_bonus;
	
	objectsVector	_players;
	
	void				OpenLib(const char *name);
	void				ChangeLib(size_t number, unsigned h, unsigned w);
	
	void				CreateWalls(unsigned h, unsigned w);
	void				CreateFoods(unsigned h, unsigned w);
	void 				CreateBonus(unsigned h, unsigned w);
	void				IntersectPlayers(unsigned h, unsigned w);
	
	void				ResetGame();
};

std::ostream &	operator<<(std::ostream & os, nibbler const & ref);