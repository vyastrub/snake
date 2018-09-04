#pragma once
#include <iostream>

typedef struct  s_position
{
	int			x;
	int			y;
}				t_position;

class obj
{
public:
	obj() = default;
	obj(unsigned h, unsigned w, char s, bool rand);
	obj(obj const & ref) = default;
	~obj() = default;
	obj& operator=(obj const & ref) = default;

	void SetPosition(unsigned x, unsigned y);

	t_position	GetPosition() const;
	char		GetSymbol() const;

private:
	obj();
	t_position	_pos;
	char		_symbol;
};

std::ostream &	operator<<(std::ostream & os, obj const & ref);