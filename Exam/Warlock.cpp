#include "Warlock.hpp"
#include "ASpell.hpp"
#include "ATarget.hpp"

Warlock::Warlock() {}

Warlock::Warlock(const Warlock& other)
{
	_name = other._name;
	_title = other._title;
}

Warlock&	Warlock::operator=(const Warlock& other)
{
	if (this != &other)
	{
		_name = other._name;
		_title = other._title;
	}

	return (*this);
}

Warlock::Warlock(const std::string& name, const std::string& title)
{
	_name = name;
	_title = title;

	std::cout << _name << ": This looks like another boring day.\n";

}
Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!\n";
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
	if (spell)
		_spellbook.learnSpell(spell);
}

void	Warlock::forgetSpell(std::string spellname)
{
	_spellbook.forgetSpell(spellname);
}

void	Warlock::launchSpell(std::string spellname, const ATarget& target)
{
	ASpell*	spell = _spellbook.createSpell(spellname);
	if (spell)
	{
		spell->launch(target);
		delete spell;
	}
}
