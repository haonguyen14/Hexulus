#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>

#include "HexulusBoard.h"
#include "Ultilities.h"
#include <iostream>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL\glut.h> // Windows FreeGlut equivalent
#endif


GLShaderManager shaderManger;
GLFrustum		frustum;
GLFrame			frame;
GLGeometryTransform	transformationPipeline;
GLMatrixStack		modelMatrixStack;
GLMatrixStack		projectionMatrixStack;

HexulusBoard		*hexBoard;

GLBatch				floorBatch;

GLuint				*hTexture;
GLuint				hFloorTexture;

void ChangeSize(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

	frustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
	projectionMatrixStack.LoadMatrix(frustum.GetProjectionMatrix());

	modelMatrixStack.LoadIdentity();
	transformationPipeline.SetMatrixStacks(modelMatrixStack, projectionMatrixStack);
}

void SetupRC()
{
	shaderManger.InitializeStockShaders();

	glEnable(GL_DEPTH_TEST);    
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	//initialize the board
	int initLen = 6;
	int longestLen = 11;
	GLfloat dim = 1.5f;

	char *fileNames[] = {"Texture//Black_Hex_R.tga", "Texture//Black_Hex_G.tga", "Texture//Black_Hex.tga"};
	GLfloat texCoor[8][2] = {{0.5f, 1.0 - 0.5f}, {0.731f, 1.0 - 0.00333f}, {0.272f, 1.0 - 0.00333f}, {0.0427f, 1.0 - 0.502f}, {0.272f, 1.0 - 0.997f}, {0.731f, 1.0 - 0.997f}, {0.959f, 1.0 - 0.502f}, {0.731f, 1.0 - 0.00333f}};

	//prepare the board
	hexBoard = new HexulusBoard(-10.0f, -1.0f, 0.0f, dim);
	hexBoard->PrepareTexture(fileNames, 3);
	hexBoard->PrepareBatch(texCoor);

	//prepare background
	char *sFloorTexture[] = {"Texture//floorTexture.tga"};
	if(!LoadTextures(sFloorTexture, &hFloorTexture, 1))
		std::cout << "Cannot load floor texture!!\n";

	floorBatch.Begin(GL_TRIANGLE_STRIP, 6, 1);

	floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] - 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] + 2.0f);

	floorBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] - 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] - 28.0f);

	floorBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] + 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] + 2.0f);

	floorBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] + 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] - 28.0f);
	
	floorBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] - 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] - 28.0f);
	
	floorBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
	floorBatch.Vertex3f(hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][0] + 14.0f, -1.2f, hexBoard->mHexLines[5]->mHexes[0]->mVertices[0][2] + 2.0f);

	floorBatch.End();
}

void specialFunc(int key, int mX, int mY)
{
	float linear = 0.5f;
	float angle = (float)m3dDegToRad(0.5f);

	switch (key)
	{
	case GLUT_KEY_UP:
		frame.MoveForward(linear);
		break;
	case GLUT_KEY_DOWN:
		frame.MoveForward(-linear);
		break;
	case GLUT_KEY_LEFT:
		frame.RotateWorld(angle, 0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		frame.RotateWorld(-angle, 0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_F1:
		frame.MoveUp(linear);
		break;
	case GLUT_KEY_F2:
		frame.MoveUp(-linear);
	case GLUT_KEY_F3:
		frame.RotateWorld(-angle, 1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_F4:
		frame.RotateWorld(angle, 1.0f, 0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void RenderScene()
{
	static GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 0.1f};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	M3DMatrix44f mCamera;
	frame.GetCameraMatrix(mCamera);
	modelMatrixStack.PushMatrix(mCamera);

	shaderManger.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformationPipeline.GetModelViewProjectionMatrix(), 0);
	hexBoard->DrawBoard();

	shaderManger.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformationPipeline.GetModelViewProjectionMatrix(), 0);
	glBindTexture(GL_TEXTURE_2D, hFloorTexture);
	floorBatch.Draw();

	modelMatrixStack.PopMatrix();


	glutSwapBuffers();
	glutPostRedisplay();
}

void Stop()
{
	delete hexBoard;
}

int main(int argc, char *argv[])
{
	gltSetWorkingDirectory(argv[0]);
		
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
  
    glutCreateWindow("Hexagon Sample");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(specialFunc);

	GLenum err = glewInit();
    if (GLEW_OK != err) 
	{
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

	SetupRC();
	glutMainLoop();    
	Stop();

    return 0;
}

