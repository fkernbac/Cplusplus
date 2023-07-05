#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::TargetGenerator(const TargetGenerator& other)
{
	_targets = other._targets;
}

TargetGenerator&	TargetGenerator::operator=(const TargetGenerator& other)
{
	if (this != &other)
	{
		_targets = other._targets;
	}

	return (*this);
}

TargetGenerator::~TargetGenerator() {}

void	TargetGenerator::learnTargetType(ATarget* target)
{
	if (target)
		_targets[target->getType()] = target;
}

void	TargetGenerator::forgetTargetType(const std::string& type)
{
	std::map<std::string, ATarget*>::iterator	it = _targets.find(type);

	if (it != _targets.end())
		_targets.erase(it);
}

ATarget*	TargetGenerator::createTarget(const std::string& type)
{
	std::map<std::string, ATarget*>::iterator	it = _targets.find(type);

	if (it != _targets.end())
		return (_targets[type]->clone());
	return (NULL);
}
