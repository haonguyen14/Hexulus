#include <GLTools.h>
#include <GLShaderManager.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

bool LoadTextures(char **textureFiles, GLuint *hTexture, GLint numTextures);
bool LoadTextures(char *textureFile, GLuint *hTexture);
