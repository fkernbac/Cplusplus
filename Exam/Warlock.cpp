#include "Warlock.hpp"
#include "ASpell.hpp"
#include <iostream>

Warlock::Warlock(const std::string& name, const std::string& title) : _name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day.\n";
}

Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!\n";
}

Warlock::Warlock(const Warlock& other)
{
	(void)other;
}

Warlock&	Warlock::operator=(const Warlock& other)
{
	(void) other;

	return *this;
}

const std::string&	Warlock::getName() const
{
	return (_name);
}

const std::string&	Warlock::getTitle() const
{
	return (_title);
}

void	Warlock::setTitle(const std::string& title)
{
	_title = title;
}

void	Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

void	Warlock::learnSpell(ASpell* spell)
{
	_spells.insert(spell);
}
void	Warlock::forgetSpell(std::string& name)
{
	std::set<ASpell*>::iterator	it = _spells.find();
}
void	Warlock::launchSpell(std::string& spell, ATarget& target);
