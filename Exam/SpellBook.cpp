#include "SpellBook.hpp"
#include "ASpell.hpp"

SpellBook::SpellBook() {}

SpellBook::SpellBook(const SpellBook& other)
{
	_spells = other._spells;
}

SpellBook&	SpellBook::operator=(const SpellBook& other)
{
	if (this != &other)
	{
		_spells = other._spells;
	}

	return (*this);
}

SpellBook::~SpellBook() {}

void	SpellBook::learnSpell(ASpell* spell)
{
	_spells[spell->getName()] = spell;
}

void	SpellBook::forgetSpell(const std::string& spellname)
{
	std::map<std::string, ASpell*>::iterator	it = _spells.find(spellname);

	if (it != _spells.end())
		_spells.erase(it);
}

ASpell*	SpellBook::createSpell(const std::string& spellname)
{
	std::map<std::string, ASpell*>::iterator	it = _spells.find(spellname);

	if (it != _spells.end())
		return (_spells[spellname].clone());
	return (NULL);
}