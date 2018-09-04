#pragma once
#include <vector>
#include "obj.hpp"

typedef struct 	s_move
{
	bool		up;
	bool		down;
	bool		left;
	bool		right;
}				t_move;

class snake
{
public:
	snake() = delete;
	snake(unsigned h, unsigned w, char n);
	snake(snake const & ref) = default;
	~snake();         // to default
	snake & operator=(snake const & ref) = default;

	void move(t_move direction);
	int  eat_foods(std::vector<obj*> foods);
	bool eat_bonus(std::vector<obj*> bonus);
	bool intersect_walls(std::vector<obj*> walls);
	
	unsigned GetLevel() const;
	unsigned GetScore() const;
	unsigned GetLen() const;

	std::vector<obj*> 	pos;

private:
	t_move		_move;
	unsigned	_score;
	char		_number;
};

std::ostream &	operator<<(std::ostream & os, snake const & ref);