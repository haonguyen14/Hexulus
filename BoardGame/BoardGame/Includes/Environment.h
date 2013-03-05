#pragma once
class Environment
{
public:
	char *mTextureFile;
	char *mEnvironmentName;
public:
	Environment();
	Environment(char *textureFile, char *environmentName);
	~Environment();
};

