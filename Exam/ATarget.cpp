#include <iostream>
#include "ATarget.hpp"

ATarget::ATarget(const std::string& type) : _type(type) {}

ATarget::~ATarget() {}

const std::string&	ATarget::getType() const
{
	return _type;
}

void	ATarget::getHitBySpell(ASpell& spell)
{
	std::cout << _type << " has been " << spell.getEffects() << "!\n";
}
