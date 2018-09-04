#pragma once
#include <string>
#include "snake.hpp"

class menu
{
public:
	menu();
	menu(menu const & ref) = default;
	~menu() = default;
	menu &	operator=(menu const & ref) = default;
	
	void	SetExit(bool const & ref);
	bool	GetExit() const;
	
	void	SetPause(bool const & ref);
	bool	GetPause() const;
	
	void	SetGame(bool const & ref);
	bool	GetGame() const;
	
	std::vector<std::string>	items_menu;
	std::vector<std::string>	items_game;
	
	void	 SetChoise(size_t const & ref);
	size_t	 GetChoise() const;
	
	void	 SetEnter(bool const & ref);
	bool	 GetEnter() const;
	
	void	 SetLibNumber(size_t const & ref);
	size_t	 GetLibNumber() const;
	
	void	 SetDirectionPlayer0(unsigned const & direction);
	t_move	 GetDirectionPlayer0() const;
	
	void	 SetDirectionPlayer1(unsigned const & direction);
	t_move	 GetDirectionPlayer1() const;
	
	void	 SetLastScore0(unsigned const & ref);
	unsigned GetLastScore0() const;
	
	void	 SetLastScore1(unsigned const & ref);
	unsigned GetLastScore1() const;
	
private:
	bool	 _exit;
	bool	 _pause;
	bool	 _game;
	
	size_t	 _choise;
	bool	 _enter;
	
	t_move	 _player0;
	t_move	 _player1;
	
	unsigned _score0;
	unsigned _score1;
	
	size_t	 _lib_number;

};

std::ostream &	operator<<(std::ostream & os, menu const & ref);