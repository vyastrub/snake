#include "obj.hpp"

obj::obj(unsigned h, unsigned w, char s, bool rand) : _symbol{s}
{
	if (rand == true)
	{
		_pos.x = std::rand() % (w + 1) - 1;
		_pos.y = std::rand() % (h + 1) - 1;
	}
	else
	{
		_pos.x = w;
		_pos.y = h;
	}
}

void obj::SetPosition(unsigned x, unsigned y) : _pos.x{x}, _pos.y{y} {}

t_position	obj::GetPosition() const
{
	return _pos;
}

char obj::GetSymbol() const
{
	return _symbol;
}

std::ostream &	operator<<(std::ostream & os, obj const & ref)
{
	os << &ref;
	return os;
}
