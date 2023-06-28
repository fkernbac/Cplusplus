#pragma once

#include <string>
#include <set>

class ASpell;
class ATarget;

class Warlock {

private:
	std::string			_name;
	std::string			_title;
	std::set<ASpell*>	_spells;

	Warlock(const Warlock& other);
	Warlock&	operator=(const Warlock& other);

public:

	Warlock(const std::string& name, const std::string& title);
	~Warlock();

	const std::string&	getName() const;
	const std::string&	getTitle() const;

	void	setTitle(const std::string& title);

	void	introduce() const;
	void	learnSpell(ASpell* spell);
	void	forgetSpell(std::string& name);
	void	launchSpell(std::string& spell, ATarget& target);
};
