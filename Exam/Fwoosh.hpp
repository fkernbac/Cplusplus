#include "ASpell.hpp"

class Fwoosh : virtual public ASpell
{
private:

public:
	Fwoosh();

	virtual Fwoosh*	clone() const;
};
