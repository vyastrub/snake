#include "snake.hpp"

snake::snake(unsigned h, unsigned w, char n) :
_number{n}, 
_score{0},
_move.up{true},
_move.down{false},
_move.left{false},
_move.right{false}
{
	pos.push_back(new obj( h / 2 + 0, w / 2, _number, false));
	pos.push_back(new obj( h / 2 + 1, w / 2, _number, false));
	pos.push_back(new obj( h / 2 + 2, w / 2, _number, false));
	pos.push_back(new obj( h / 2 + 3, w / 2, _number, false));
}

snake::~snake()
{
	obj* buff;

	while (pos.size() > 0)
	{
		buff = pos[pos.size() - 1];
		delete buff;
		pos.pop_back();
	}
}

void snake::move(t_move direction)
{
	if (direction.up == true && _move.down == false)
	{
		_move.up = true;
		_move.down = false;
		_move.left = false;
		_move.right = false;
	}
	else if (direction.down == true && _move.up == false)
	{
		_move.up = false;
		_move.down = true;
		_move.left = false;
		_move.right = false;
	}
	else if (direction.left == true && _move.right == false)
	{
		_move.up = false;
		_move.down = false;
		_move.left = true;
		_move.right = false;
	}
	else if (direction.right == true && _move.left == false)
	{
		_move.up = false;
		_move.down = false;
		_move.left = false;
		_move.right = true;
	}

	for (size_t i = pos.size() - 1; i > 0; i--)
		pos[i]->SetPosition(pos[i - 1]->GetPosition().x, pos[i - 1]->GetPosition().y);

	if (_move.up == true)
		pos[0]->SetPosition(pos[0]->GetPosition().x, pos[0]->GetPosition().y - 1);
	else if (_move.down == true)
		pos[0]->SetPosition(pos[0]->GetPosition().x, pos[0]->GetPosition().y + 1);
	else if (_move.left == true)
		pos[0]->SetPosition(pos[0]->GetPosition().x - 1, pos[0]->GetPosition().y);
	else if (_move.right == true)
		pos[0]->SetPosition(pos[0]->GetPosition().x + 1, pos[0]->GetPosition().y);
}

int	snake::eat_foods(std::vector<obj*> foods)
{
	for (size_t i = 0; i < foods.size(); i++)
	{
	 	if (foods[i]->GetPosition().x == pos[0]->GetPosition().x
	 			&& foods[i]->GetPosition().y == pos[0]->GetPosition().y)
	 	{
 			pos.push_back(new obj(pos[pos.size() - 1]->GetPosition().y, pos[pos.size() - 1]->GetPosition().x, _number, false));
	 		_score++;
	 		return i;
	 	}
	}
	return -1;
}

bool snake::eat_bonus(std::vector<obj*> bonus)
{
	if (bonus[0]->GetPosition().x == pos[0]->GetPosition().x
			&& bonus[0]->GetPosition().y == pos[0]->GetPosition().y)
	{
		while (pos.size() > 3)
		{
			obj* buff = pos.back();
			delete buff;
			pos.pop_back();
		}
		_score += 10;
		return true;
	}
	return false;
}

bool snake::intersect_walls(std::vector<obj*> walls)
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		if (walls[i]->GetPosition().x == pos[0]->GetPosition().x
			&& walls[i]->GetPosition().y == pos[0]->GetPosition().y)
			return true;
	}
	return false;
}

unsigned	snake::GetLevel() const
{
	unsigned level = ((_score / 10) < 25) ? _score / 10 : 25;
	return level;
}

unsigned	snake::GetScore() const
{
	return _score;
}

unsigned	snake::GetLen()	const
{
	return pos.size();
}

std::ostream &		operator<<(std::ostream & os, snake const & ref)
{
	os << &ref;
	return os;
}
