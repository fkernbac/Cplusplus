#pragma once

#include <string>

class ASpell;

class ATarget {

private:

protected:
	std::string	_type;

public:
	ATarget(const std::string& type);
	virtual ~ATarget();

	const std::string&	getType() const;

	void				getHitBySpell(ASpell& spell);
	virtual ATarget*	clone() const = 0;

};
