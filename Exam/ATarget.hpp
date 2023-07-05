#pragma once

#include <iostream>

class ASpell;

class ATarget
{
protected:
	std::string	_type;

	ATarget();
	ATarget(const ATarget& other);
	ATarget&	operator=(const ATarget& other);

public:
	ATarget(const std::string& type);
	virtual ~ATarget();

	const std::string&	getType() const;

	void	getHitBySpell(const ASpell& spell) const;

	virtual ATarget*	clone() = 0;
};