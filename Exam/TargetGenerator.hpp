#pragma once

#include <iostream>
#include <map>

class ASpell;
class ATarget;

class TargetGenerator
{
private:
	std::map<std::string, ASpell*>	_spells;

	TargetGenerator(const TargetGenerator& other);
	TargetGenerator&	operator=(const TargetGenerator& other);

public:
	TargetGenerator();
	~TargetGenerator();

	void	learnSpell(ASpell* spell);
	void	forgetSpell(const std::string& spellname);
	ASpell*	createSpell(const std::string& spellname);
};