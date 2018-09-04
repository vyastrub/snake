#include "menu.hpp"

/**************************************************************/

menu::menu() :
_exit{false},
_pause{true},
_game{false},
_choise{0},
_enter{false},
_score0{0},
_score1{0},
_lib_number{-1}
{
	items_menu.push_back("1 Player");
	items_menu.push_back("2 Players");
	items_menu.push_back("Exit");
	items_game.push_back("Continue");
	items_game.push_back("Restart");
	items_game.push_back("Exit");
	SetDirectionPlayer0(0);
	SetDirectionPlayer1(0);	
}

void		menu::SetExit(bool const & ref) : _exit {ref} {}

bool		menu::GetExit() const
{
	return _exit;
}
 
void		menu::SetPause(bool const & ref) : _pause {ref} {}

bool		menu::GetPause() const
{
	return _pause;
}

void		menu::SetGame(bool const & ref) : _game{ref} {}

bool		menu::GetGame() const
{
	return _game;
}

void		menu::SetChoise(size_t const & ref) : _choise{ref} {}

size_t		menu::GetChoise() const
{
	return _choise;
}

void		menu::SetEnter(bool const & ref) : 	_enter{ref} {} 

bool		menu::GetEnter() const
{
	return _enter;
}

void		menu::SetLibNumber(size_t const & ref) : _lib_number{ref} {}

size_t		menu::GetLibNumber() const
{
	return _lib_number;
}

void		menu::SetLastScore0(unsigned const & ref) : _score0{ref} {}

unsigned	menu::GetLastScore0() const
{
	return _score0;
}

void		menu::SetLastScore1(unsigned const & ref) : _score1{ref} {}

unsigned	menu::GetLastScore1() const
{
	return _score1;
}

void		menu::SetDirectionPlayer0(unsigned const & direction)
{
	_player0.up = (direction == 0) ? true : false;
	_player0.down = (direction == 1) ? true : false;
	_player0.left = (direction == 2) ? true : false;
	_player0.right = (direction == 3) ? true : false;
}

void		menu::SetDirectionPlayer1(unsigned const & direction)
{
	_player1.up = (direction == 0) ? true : false;
	_player1.down = (direction == 1) ? true : false;
	_player1.left = (direction == 2) ? true : false;
	_player1.right = (direction == 3) ? true : false;
}

t_move		menu::GetDirectionPlayer0() const
{
	return _player0;
}

t_move		menu::GetDirectionPlayer1() const
{
	return _player1;
}

std::ostream &		operator<<(std::ostream & os, menu const & ref)
{
	os << &ref;
	return os;
}
