#include "Environment.h"


Environment::Environment(void)
{
}

Environment::Environment(char *textureFile, char *environmentName)
{
	mTextureFile = textureFile;
	mEnvironmentName = environmentName;
}


Environment::~Environment(void)
{
}
