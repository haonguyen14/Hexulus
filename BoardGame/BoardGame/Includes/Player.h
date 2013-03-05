#include "Environment.h"

class Player
{
public:
	Environment *mEnvironemt;
	Environment *mOppEnvironemt;
public:
	Player();
	Player(Environment *environment, Environment *oppEnvironment);
}