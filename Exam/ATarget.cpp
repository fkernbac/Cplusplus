#include "ATarget.hpp"
#include "ASpell.hpp"

ATarget::ATarget() {}

ATarget::ATarget(const ATarget& other)
{
	_type = other._type;
}

ATarget&	ATarget::operator=(const ATarget& other)
{
	if (this != &other)
	{
		_type = other._type;
	}

	return (*this);
}

ATarget::ATarget(const std::string& type)
{
	_type = type;
}

ATarget::~ATarget() {}

const std::string&	ATarget::getType() const
{
	return (_type);
}

void	ATarget::getHitBySpell(const ASpell& spell) const
{
	std::cout << _type << " has been " << spell.getEffects() << "!\n";
}
