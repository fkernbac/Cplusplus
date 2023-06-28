#pragma once

#include <string>

class ATarget;

class ASpell {

private:

protected:
	std::string	_name;
	std::string	_effects;

public:
	ASpell(const std::string& name, const std::string& effects);
	virtual ~ASpell();

	const std::string&	getName() const;
	const std::string&	getEffects() const;

	void	launch(const ATarget& target);

	virtual ASpell*	clone() const = 0;

};
