#pragma once 
#include "menu.hpp"
#include "obj.hpp"
#include "snake.hpp"

class ApiDisplay
{
	public:
					ApiDisplay();
	virtual			~ApiDisplay();
	
	virtual	void	InitDisplay(unsigned height, unsigned width) = 0;
	virtual	void	ExitDisplay() = 0;
	
	virtual	void	UpdateGame(menu *interfase, std::vector<snake*> players, std::vector<obj*> foods, std::vector<obj*> bonus, std::vector<obj*> walls) = 0;
	virtual	void	UpdateMenu(menu *interfase, std::vector<snake*> players) = 0;
	
	virtual int 	DelayDisplay() = 0;
	
private:
	ApiDisplay(ApiDisplay const & ref);
	ApiDisplay & 	operator=(ApiDisplay const & ref);

};

std::ostream &	operator<<(std::ostream & os, ApiDisplay const & ref);