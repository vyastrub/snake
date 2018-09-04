#include "ApiDisplay.hpp"

std::ostream &		operator<<(std::ostream & os, ApiDisplay const & ref)
{
	os << &ref;
	return os;
}
