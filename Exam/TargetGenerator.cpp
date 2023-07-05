#include "TargetGenerator.hpp"
#include "ASpell.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::TargetGenerator(const TargetGenerator& other)
{
	_spells = other._spells;
}

TargetGenerator&	TargetGenerator::operator=(const TargetGenerator& other)
{
	if (this != &other)
	{
		_spells = other._spells;
	}

	return (*this);
}

TargetGenerator::~TargetGenerator() {}

void	TargetGenerator::learnSpell(ASpell* spell)
{
	_spells[spell->getName()] = spell;
}

void	TargetGenerator::forgetSpell(const std::string& spellname)
{
	std::map<std::string, ASpell*>::iterator	it = _spells.find(spellname);

	if (it != _spells.end())
		_spells.erase(it);
}

ASpell*	TargetGenerator::createSpell(const std::string& spellname)
{
	std::map<std::string, ASpell*>::iterator	it = _spells.find(spellname);

	if (it != _spells.end())
		return (_spells[spellname].clone());
	return (NULL);
}