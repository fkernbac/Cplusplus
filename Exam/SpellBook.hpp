#pragma once

#include <iostream>
#include <map>

class ASpell;
class ATarget;

class SpellBook
{
private:
	std::map<std::string, ASpell*>	_spells;

	SpellBook(const SpellBook& other);
	SpellBook&	operator=(const SpellBook& other);

public:
	SpellBook();
	~SpellBook();

	void	learnSpell(ASpell* spell);
	void	forgetSpell(const std::string& spellname);
	ASpell*	createSpell(const std::string& spellname);
};