#include "nibbler.hpp"

#include <iostream>

nibbler::nibbler() : _time{0}, _delay{DELAY} {}

nibbler::~nibbler()
{
	_display->ExitDisplay();
	dlclose(_dl);
}

void			nibbler::Play(unsigned height, unsigned width, char *type)
{
	OpenLib(type);
	_display->InitDisplay(height, width);

	while(_interface.GetExit() == false)
	{
		_display->UpdateMenu(&_interface, _players);
		ChangeLib(_interface.GetLibNumber(), height, width);

		if (_interface.GetEnter() == true && _interface.GetChoise() == 2)
			_interface.SetExit(true);

		if (_interface.GetGame() == false)
		{
			if (_interface.GetEnter() == true && _interface.GetChoise() == 0)
			{
				_players.push_back(std::make_unique(height, width, '0'));
				_interface.SetGame(true);
				_interface.SetPause(false);
				_interface.SetEnter(false);
			}
			else if (_interface.GetEnter() == true && _interface.GetChoise() == 1)
			{
				_players.push_back(std::make_unique(height, width + 10, '0'));
				_players.push_back(std::make_unique(height, width - 10, '1'));
				_interface.SetGame(true);
				_interface.SetPause(false);
				_interface.SetEnter(false);
			}
		}
		else
		{
			if (_interface.GetEnter() == true && _interface.GetChoise() == 0)
			{
				_interface.SetPause(false);
				_interface.SetEnter(false);
			}
			else if (_interface.GetEnter() == true && _interface.GetChoise() == 1)
				ResetGame();
		}

		while(_interface.GetPause() == false)
		{
			_display->UpdateGame(&_interface, _players, _foods, _bonus, _walls);

			if (_players.size() == 1)
			{
				if (_walls.size() < _players[0]->GetScore())
					CreateWalls(height, width);
			}
			else if (_players.size() == 2)
			{
				if (_walls.size() < (_players[0]->GetScore() + _players[1]->GetScore()))
					CreateWalls(height, width);
			}

			if(_time % (5000 / SPEED) == 0 || _foods.size() == 0)
				CreateFoods(height, width);

			if (_time % (12500 / SPEED) == 0 && !_bonus.size())
				CreateBonus(height, width);
			if (_time % (17500 / SPEED) == 0 && _bonus.size())
			{
				_bonus.pop_back();
			}

			if(_time % ((26 - _players[0]->GetLevel()) / SPEED) == 0)
				_players[0]->move(_interface.GetDirectionPlayer0());
			
			if (_players.size() > 1)
				if (_time % ((26 - _players[1]->GetLevel()) / SPEED) == 0)
					_players[1]->move(_interface.GetDirectionPlayer1());

			IntersectPlayers(height, width);

			_delay = DELAY * _display->DelayDisplay();
			if (_players.size() > 1)
			{
				if (_players[0]->GetLevel() > _players[1]->GetLevel())
					_delay *= (1 - 0.001 * 50 * _players[0]->GetLevel());
				else
					_delay *= (1 - 0.001 * 50 * _players[1]->GetLevel());	
			}
			else
				_delay *= (1 - 0.001 * 50 * _players[0]->GetLevel());

			usleep(_delay);
			_time++;
		}

		_interface.SetEnter(false);
	}
}

/**************************************************************/

void			nibbler::CreateWalls(unsigned h, unsigned w)
{
	bool coincidence = true;

	while (coincidence == true)
	{
		coincidence = false;
		_walls.push_back(std::make_unique(h, w, ' ', true));

		/*with himself*/
		for (size_t k = 0; k < _walls.size() - 1; k++)
		{
			if (_walls.back()->GetPosition().x == _walls[k]->GetPosition().x
				&&	_walls.back()->GetPosition().y == _walls[k]->GetPosition().y)
			{
				_walls.pop_back();
				coincidence = true;
				break ;
			}
		}

		/*with foods*/
		for (size_t k = 0; k < _foods.size(); k++)
		{
			if (_walls.back()->GetPosition().x == _foods[k]->GetPosition().x
				&&	_walls.back()->GetPosition().y == _foods[k]->GetPosition().y)
			{
				_walls.pop_back();
				coincidence = true;
				break ;
			}
		}

		/*with players*/
		for (size_t i = 0; i < _players.size(); i++)
		{
			for (size_t j = 0; j < _players[i]->pos.size(); j++)
			{
				if (_walls.back()->GetPosition().x == _players[i]->pos[j]->GetPosition().x
					&& _walls.back()->GetPosition().y == _players[i]->pos[j]->GetPosition().y)
				{
					_walls.pop_back();
					coincidence = true;
					break ;
				}
			}
			if (coincidence == true)
				break ;
		}
	}		
}

void			nibbler::CreateFoods(unsigned h, unsigned w)
{
	bool coincidence = true;

	unsigned len = _players[0]->pos.size();
	if (_players.size() > 1)
		len += _players[1]->pos.size();

	if ( _foods.size() < ((h + 1) * (w + 1) - len + 1) )
	{
		while (coincidence == true)
		{
			coincidence = false;
			_foods.push_back(std::make_unique(h, w, '*', true));

			/*with himself*/
			for (size_t k = 0; k < _foods.size() - 1; k++)
			{
				if (_foods.back()->GetPosition().x == _foods[k]->GetPosition().x
					&&	_foods.back()->GetPosition().y == _foods[k]->GetPosition().y)
				{
					_foods.pop_back();
					coincidence = true;
					break ;
				}
			}

			/*with players*/
			for (size_t i = 0; i < _players.size(); i++)
			{
				for (size_t j = 0; j < _players[i]->pos.size(); j++)
				{
					if (_foods.back()->GetPosition().x == _players[i]->pos[j]->GetPosition().x
						&& _foods.back()->GetPosition().y == _players[i]->pos[j]->GetPosition().y)
					{
						_foods.pop_back();
						coincidence = true;
						break ;
					}
				}
				if (coincidence == true)
					break ;
			}

			/*with walls*/
			for (size_t k = 0; k < _walls.size(); k++)
			{
				if (_foods.back()->GetPosition().x == _walls[k]->GetPosition().x
					&&	_foods.back()->GetPosition().y == _walls[k]->GetPosition().y)
				{
					_foods.pop_back();
					coincidence = true;
					break ;
				}
			}

		}
	}
}

void			nibbler::CreateBonus(unsigned h, unsigned w)
{
	bool coincidence = true;

	while (coincidence == true)
	{
		coincidence = false;
		_bonus.push_back(std::make_unique(h, w, '+', true));

		/*with players*/
		for (size_t i = 0; i < _players.size(); ++i)
		{
			for (size_t j = 0; j < _players[i]->pos.size(); ++j)
			{
				if (_bonus.back()->GetPosition().x == _players[i]->pos[j]->GetPosition().x
					&& _bonus.back()->GetPosition().y == _players[i]->pos[j]->GetPosition().y)
				{
					_bonus.pop_back();
					coincidence = true;
					break ;
				}
			}
			if (coincidence == true)
				break ;
		}

		/*with walls*/
		for (size_t k = 0; k < _walls.size(); ++k)
		{
			if (_foods.back()->GetPosition().x == _walls[k]->GetPosition().x
				&&	_foods.back()->GetPosition().y == _walls[k]->GetPosition().y)
			{
				_foods.pop_back();
				coincidence = true;
				break ;
			}
		}

	}
}

void			nibbler::IntersectPlayers(unsigned h, unsigned w)
{
	for (size_t i = 0; i < _players.size(); i++)
	{
		int del = _players[i]->eat_foods(_foods);
		if (del != -1)
		{
			_foods.erase(_foods.begin() + del);
		}

		if (_bonus.size() != 0 && _players[i]->eat_bonus(_bonus))
		{
			_bonus.pop_back();
		}

		if (_players[i]->intersect_walls(_walls))
		{
			ResetGame();
			break;
		}

		if (_players[i]->pos[0]->GetPosition().x < (0 - 1)
			|| _players[i]->pos[0]->GetPosition().y < (0 - 1)
			|| _players[i]->pos[0]->GetPosition().x > ((int)w - 1)
			|| _players[i]->pos[0]->GetPosition().y > ((int)h - 1))
		{
			ResetGame();
			break;
		}

		for (size_t j = 2; j < _players[i]->pos.size(); j++)
		{
			if (_players[i]->pos[0]->GetPosition().x == _players[i]->pos[j]->GetPosition().x
				&& _players[i]->pos[0]->GetPosition().y == _players[i]->pos[j]->GetPosition().y)
			{
				ResetGame();
				break;
			}
		}

		if (_players.size() > 1)
		{
			size_t k = (i == 0) ? 1 : 0;
			for (size_t j = 0; j < _players[k]->pos.size(); j++)
			{
				if (_players[i]->pos[0]->GetPosition().x == _players[k]->pos[j]->GetPosition().x
					&& _players[i]->pos[0]->GetPosition().y == _players[k]->pos[j]->GetPosition().y)
				{
					ResetGame();
					break;
				}
			}
		}
	}
}

void			nibbler::ResetGame()
{
	_time = 0;
	_delay = DELAY;

	_interface.SetLastScore0(_players[0]->GetScore());
	if (_players.size() > 1)
		_interface.SetLastScore1(_players[1]->GetScore());

	_walls.clear();
	_foods.clear();
	_bonus.clear();
	_players.clear();

	_interface.SetEnter(false);
	_interface.SetPause(true);
	_interface.SetGame(false);
	_interface.SetChoise(0);
	_interface.SetDirectionPlayer0(0);
	_interface.SetDirectionPlayer1(0);
}

void			nibbler::OpenLib(const char *name)
{
	ApiDisplay	*(*create)();


	if (strcmp("-ncurses", name) == 0)
	{
		_dl_number = 0;
		_dl = dlopen("./lib_ncurses/lib_ncurses.so", RTLD_LAZY | RTLD_LOCAL);
	}
	else if (strcmp("-sdl", name) == 0)
	{
		_dl_number = 1;
		_dl = dlopen("./lib_sdl/lib_sdl.so", RTLD_LAZY | RTLD_LOCAL);
	}
	else if (strcmp("-sfml", name) == 0)
	{
		_dl_number = 2;
		_dl = dlopen("./lib_sfml/lib_sfml.so", RTLD_LAZY | RTLD_LOCAL);
	}

	_interface.SetLibNumber(_dl_number);

	if (_dl == NULL)
	{
		std::cerr << "open_lib: dlopen : "<< dlerror() << std::endl;
		throw std::exception();
	}

	if (( create = reinterpret_cast<ApiDisplay* (*)()>(dlsym(_dl, "NewDisplay")) ) == NULL)
	{
		std::cerr << "open_lib: dlsym : " << dlerror() << std::endl;
		throw std::exception();
	}
	_display = create();
}

void 			nibbler::ChangeLib(size_t number, unsigned h, unsigned w)
{
	std::string name;

	if (_dl_number == number)
	{
		return ;
	}

	_display->ExitDisplay();
	delete _display; ///release 
	dlclose(_dl);
	switch (number)
	{
		case (0):
			name = "-ncurses";
		case (1):
			name = "-sdl";
		case (2):
			name = "-sfml";
		default:
			break;
	}
	
	OpenLib(name.c_str());
	_display->InitDisplay(h, w);
}

std::ostream &		operator<<(std::ostream & os, nibbler const & ref)
{
	os << &ref;
	return os;
}
