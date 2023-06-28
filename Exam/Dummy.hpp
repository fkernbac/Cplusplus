#include "ATarget.hpp"

class Dummy : public virtual ATarget
{
public:
	Dummy();

	virtual Dummy*	clone() const;
};
