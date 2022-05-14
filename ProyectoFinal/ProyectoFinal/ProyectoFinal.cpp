#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Functionprototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();
void animacion2();


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 6.0f, 40.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(4.5f, 0.66f, -3.5f);
glm::vec3 PosIni2(-3.0f, 0.3f, 1.5f);
bool active;
float rot = 0.0f;
float range = 0.0f;
float range2 = 0.0f;

//Luz
GLfloat direccionx = 0.0f;
GLfloat direcciony = 0.0f;
GLfloat direccionz = 0.0f;
GLfloat posicionx = 0.0f;
GLfloat posiciony = 0.0f;
GLfloat posicionz = 0.0f;

// AnimacionPuerta
float rotpuerta = 0.0f;
bool animpuerta = false;
bool animpuerta2 = false;
bool controladorpuerta = false;

// AnimacionLibrero
float movimientolibrero = 0.0f;
bool animlibrero = false;
bool animlibrero2 = false;
bool controladorlibrero = false;


// AnimacionEsfera
float movimientoEsfera = 0.0f;
float contadorEsfera = 0.0f;
bool animEsfera = false;
bool animEsfera2 = false;
bool animEsfera3 = false;
bool animEsfera4 = false;
bool animEsfera5 = false;
bool animEsfera6 = false;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Deltatime
GLfloat deltaTime2 = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame2 = 0.0f;  // Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0, rotIzq2 = 0;
float rotRodDer = 0, rotDer2 = 0, rotBraDer = 0, rotBraIzq = 0;

//Para seguna Animacion
float posX2 = PosIni2.x, posY2 = PosIni2.y, posZ2 = PosIni2.z, rot2RodIzq = 0, rot2Izq2 = 0;
float rot2RodDer = 0, rot2Der2 = 0, rot2BraDer = 0, rot2BraIzq = 0;


#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotIzq2;
	float rotInc;
	float rotInc2;

	float rotRodDer;
	float rotDer2;
	float rotInc3;
	float rotInc4;

	float rotBraDer;
	float rotBraIzq;
	float rotInc5;
	float rotInc6;


}FRAME;


int i_max_steps2 = 190;
int i_curr_steps2 = 0;
typedef struct _frame2
{
	//Variables para GUARDAR Key Frames
	float posX2;		//Variable para PosicionX
	float posY2;		//Variable para PosicionY
	float posZ2;		//Variable para PosicionZ
	float incX2;		//Variable para IncrementoX
	float incY2;		//Variable para IncrementoY
	float incZ2;		//Variable para IncrementoZ
	float rot2RodIzq;
	float rot2Izq2;
	float rot2Inc;
	float rot2Inc2;

	float rot2RodDer;
	float rot2Der2;
	float rot2Inc3;
	float rot2Inc4;

	float rot2BraDer;
	float rot2BraIzq;
	float rot2Inc5;
	float rot2Inc6;
}FRAME2;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 6;			//introducir datos
bool play = false;
int playIndex = 0;

FRAME2 KeyFrame2[MAX_FRAMES];
int FrameIndex2 = 6;			//introducir datos
bool play2 = false;
int playIndex2 = 0;



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(-2.0f,0.0f, 0.0f),
	glm::vec3(2.0f,0.0f, 0.0f),
	glm::vec3(-2.0f,0.0f, -4.0f),
	glm::vec3(2.0f,0.0f, -4.0f)
};

glm::vec3 LightP1;

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);



void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotIzq2 = rotIzq2;

	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotDer2 = rotDer2;

	KeyFrame[FrameIndex].rotBraDer = rotBraDer;
	KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotIzq2 = KeyFrame[0].rotIzq2;

	rotRodDer = KeyFrame[0].rotRodDer;
	rotDer2 = KeyFrame[0].rotDer2;

	rotBraDer = KeyFrame[0].rotBraDer;
	rotBraIzq = KeyFrame[0].rotBraIzq;
}

void resetElements2(void)
{
	posX2 = KeyFrame2[0].posX2;
	posY2 = KeyFrame2[0].posY2;
	posZ2 = KeyFrame2[0].posZ2;

	rot2RodIzq = KeyFrame2[0].rot2RodIzq;
	rot2Izq2 = KeyFrame2[0].rot2Izq2;

	rot2RodDer = KeyFrame2[0].rot2RodDer;
	rot2Der2 = KeyFrame2[0].rot2Der2;

	rot2BraDer = KeyFrame2[0].rot2BraDer;
	rot2BraIzq = KeyFrame2[0].rot2BraIzq;
}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotIzq2 - KeyFrame[playIndex].rotIzq2) / i_max_steps;

	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotDer2 - KeyFrame[playIndex].rotDer2) / i_max_steps;

	KeyFrame[playIndex].rotInc5 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;
	KeyFrame[playIndex].rotInc6 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
}

void interpolation2(void)
{

	KeyFrame2[playIndex2].incX2 = (KeyFrame2[playIndex2 + 1].posX2 - KeyFrame2[playIndex2].posX2) / i_max_steps;
	KeyFrame2[playIndex2].incY2 = (KeyFrame2[playIndex2 + 1].posY2 - KeyFrame2[playIndex2].posY2) / i_max_steps;
	KeyFrame2[playIndex2].incZ2 = (KeyFrame2[playIndex2 + 1].posZ2 - KeyFrame2[playIndex2].posZ2) / i_max_steps;
	KeyFrame2[playIndex2].rot2Inc = (KeyFrame2[playIndex2 + 1].rot2RodIzq - KeyFrame2[playIndex2].rot2RodIzq) / i_max_steps;
	KeyFrame2[playIndex2].rot2Inc2 = (KeyFrame2[playIndex2 + 1].rot2Izq2 - KeyFrame2[playIndex2].rot2Izq2) / i_max_steps;

	KeyFrame2[playIndex2].rot2Inc3 = (KeyFrame2[playIndex2 + 1].rot2RodDer - KeyFrame2[playIndex2].rot2RodDer) / i_max_steps;
	KeyFrame2[playIndex2].rot2Inc4 = (KeyFrame2[playIndex2 + 1].rot2Der2 - KeyFrame2[playIndex2].rot2Der2) / i_max_steps;
	KeyFrame2[playIndex2].rot2Inc5 = (KeyFrame2[playIndex2 + 1].rot2BraDer - KeyFrame2[playIndex2].rot2BraDer) / i_max_steps;
	KeyFrame2[playIndex2].rot2Inc6 = (KeyFrame2[playIndex2 + 1].rot2BraIzq - KeyFrame2[playIndex2].rot2BraIzq) / i_max_steps;
}

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	
	Model Piso((char*)"Models/Esfera/Piso.obj");
	Model Esfera((char*)"Models/Esfera/Esfera.obj");
	Model P2((char*)"Models/PC/P2.obj");
	Model maquina1((char*)"Models/maquina1/maquina.obj");
	Model maquina2((char*)"Models/Maquina2/Maquina2.obj");
	Model maquina3((char*)"Models/Maquina3/Maquina3.obj");
	Model maquina4((char*)"Models/Maquina4/Maquina4.obj");
	Model Casa((char*)"Models/Casa/Casa2.obj");
	Model Mesa((char*)"Models/Mesa/mesa.obj");
	Model Celda((char*)"Models/celda/celda.obj");
	Model Puerta((char*)"Models/Puerta/Puerta.obj");
	Model bola((char*)"Models/bola/bola.obj");
	Model Librero((char*)"Models/Librero/Librero2.obj");
	Model robotcuerpo((char*)"Models/robot/robotcuerpo.obj");
	Model robotfemur((char*)"Models/robot/femur.obj");
	Model fibula((char*)"Models/robot/tibia.obj");
	Model pie((char*)"Models/robot/pie.obj");
	Model BrazoDer((char*)"Models/robot/Brazo2.obj");
	Model BrazoIzq((char*)"Models/robot/Brazo.obj");

	Model robotcuerpo2((char*)"Models/robot1/robotcuerpo.obj");
	Model robotfemur2((char*)"Models/robot1/femur.obj");
	Model fibula2((char*)"Models/robot1/tibia.obj");
	Model pie2((char*)"Models/robot1/pie.obj");

	//Inicialización de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotInc = 0;
	}

	//Animacion
	KeyFrame[0].posX = posX;
	KeyFrame[0].posY = posY;
	KeyFrame[0].posZ = posZ;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].rotIzq2 = 0;
	KeyFrame[0].rotRodDer = 0;
	KeyFrame[0].rotDer2 = 0;
	KeyFrame[0].rotBraDer = 0;
	KeyFrame[0].rotBraIzq = 0;

	KeyFrame[1].posX = posX;
	KeyFrame[1].posY = posY;
	KeyFrame[1].posZ = posZ + 1;
	KeyFrame[1].rotRodIzq = -50;
	KeyFrame[1].rotIzq2 = -10;
	KeyFrame[1].rotRodDer = 50;
	KeyFrame[1].rotDer2 = 10;
	KeyFrame[1].rotBraDer = 50;
	KeyFrame[1].rotBraIzq = -50;

	KeyFrame[2].posX = posX;
	KeyFrame[2].posY = posY;
	KeyFrame[2].posZ = posZ+2;
	KeyFrame[2].rotRodIzq = 50;
	KeyFrame[2].rotIzq2 = -60;
	KeyFrame[2].rotRodDer = -50;
	KeyFrame[2].rotDer2 = -10;
	KeyFrame[2].rotBraDer = -50;
	KeyFrame[2].rotBraIzq = 50;

	KeyFrame[3].posX = posX;
	KeyFrame[3].posY = posY;
	KeyFrame[3].posZ = posZ + 4;
	KeyFrame[3].rotRodIzq = -50;
	KeyFrame[3].rotIzq2 = -10;
	KeyFrame[3].rotRodDer = 50;
	KeyFrame[3].rotDer2 = 10;
	KeyFrame[3].rotBraDer = 50;
	KeyFrame[3].rotBraIzq = -50;

	KeyFrame[4].posX = posX;
	KeyFrame[4].posY = posY;
	KeyFrame[4].posZ = posZ + 6;
	KeyFrame[4].rotRodIzq = 50;
	KeyFrame[4].rotIzq2 = -60;
	KeyFrame[4].rotRodDer = -50;
	KeyFrame[4].rotDer2 = -10;
	KeyFrame[4].rotBraDer = -50;
	KeyFrame[4].rotBraIzq = 50;

	KeyFrame[5].posX = posX;
	KeyFrame[5].posY = posY;
	KeyFrame[5].posZ = posZ + 6.5;
	KeyFrame[5].rotRodIzq = 0;
	KeyFrame[5].rotIzq2 = 0;
	KeyFrame[5].rotRodDer = 0;
	KeyFrame[5].rotDer2 = 0;
	KeyFrame[5].rotBraDer = 0;
	KeyFrame[5].rotBraIzq = 0;

	//Animacion
	KeyFrame2[0].posX2 = posX2;
	KeyFrame2[0].posY2 = posY2;
	KeyFrame2[0].posZ2 = posZ2;
	KeyFrame2[0].rot2RodIzq = 0;
	KeyFrame2[0].rot2Izq2 = 0;
	KeyFrame2[0].rot2RodDer = 0;
	KeyFrame2[0].rot2Der2 = 0;


	KeyFrame2[1].posX2 = posX2;
	KeyFrame2[1].posY2 = posY2;
	KeyFrame2[1].posZ2 = posZ2;
	KeyFrame2[1].rot2RodIzq = -10;
	KeyFrame2[1].rot2Izq2 = 0;
	KeyFrame2[1].rot2RodDer = -10;
	KeyFrame2[1].rot2Der2 = 0;

	KeyFrame2[2].posX2 = posX2;
	KeyFrame2[2].posY2 = posY2+0.5;
	KeyFrame2[2].posZ2 = posZ2+0.5;
	KeyFrame2[2].rot2RodIzq = 20;
	KeyFrame2[2].rot2Izq2 = 0;
	KeyFrame2[2].rot2RodDer = -20;
	KeyFrame2[2].rot2Der2 = 0;

	KeyFrame2[3].posX2 = posX2;
	KeyFrame2[3].posY2 = posY2+1;
	KeyFrame2[3].posZ2 = posZ2+1;
	KeyFrame2[3].rot2RodIzq = 40;
	KeyFrame2[3].rot2Izq2 = 15;
	KeyFrame2[3].rot2RodDer = -40;
	KeyFrame2[3].rot2Der2 = -15;

	KeyFrame2[4].posX2 = posX2;
	KeyFrame2[4].posY2 = posY2+0.5;
	KeyFrame2[4].posZ2 = posZ2+1.5;
	KeyFrame2[4].rot2RodIzq = -20;
	KeyFrame2[4].rot2Izq2 = 0;
	KeyFrame2[4].rot2RodDer = 20;
	KeyFrame2[4].rot2Der2 = 0;

	KeyFrame2[5].posX2 = posX2;
	KeyFrame2[5].posY2 = posY2;
	KeyFrame2[5].posZ2 = posZ2+2;
	KeyFrame2[5].rot2RodIzq = 0;
	KeyFrame2[5].rot2Izq2 = 0;
	KeyFrame2[5].rot2RodDer = 0;
	KeyFrame2[5].rot2Der2 = 0;



	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"),1);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLfloat currentFrame2 = glfwGetTime();
		deltaTime2 = currentFrame2 - lastFrame2;
		lastFrame2 = currentFrame2;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();
		animacion2();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		//Load Model
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.5f,0.5f,0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),1.0f, 1.0f, 1.0f);


		//// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),1.8f);



		// Point light 2
		glm::vec3 lightColor2;
		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = sin(glfwGetTime() * Light2.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 1.8f);

		// Point light 3
		glm::vec3 lightColor3;
		lightColor3.x = abs(sin(glfwGetTime() * Light3.x));
		lightColor3.y = abs(sin(glfwGetTime() * Light3.y));
		lightColor3.z = sin(glfwGetTime() * Light3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 1.8f);

		// Point light 4
		glm::vec3 lightColor4;
		lightColor4.x = abs(sin(glfwGetTime() * Light4.x));
		lightColor4.y = abs(sin(glfwGetTime() * Light4.y));
		lightColor4.z = sin(glfwGetTime() * Light4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 1.8f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 0.0f+posicionx,0.0f+posiciony,-2.0f+posicionz);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f+direccionx, 0.0f+direcciony, 0.0f+direccionz);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	

		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Piso.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Casa.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(7.0f, 0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		maquina2.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.5, -1.8f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		P2.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.0f, 0.6, 4.9));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		maquina1.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.6, 4.0));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Mesa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-6.0f, 0.8, 1.0));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Celda.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-6.0f, 0.4, -5.0));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		maquina3.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.5f, 0.3f, 1.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		maquina4.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.8f, 2.0f, 7.8f));
		model = glm::rotate(model, glm::radians(-rotpuerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Puerta.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, 1.82 + movimientoEsfera, -3.0));
		model = glm::scale(model, glm::vec3(1.1f + movimientoEsfera * 3, 1.1f + movimientoEsfera * 3, 1.1f + movimientoEsfera * 3));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		bola.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f,0.0f+movimientolibrero));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		Librero.Draw(lightingShader);

		//Robot

		glm::mat4 tmp = glm::mat4(1.0f); //Temp
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.1f,0.1f,0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotcuerpo.Draw(lightingShader);

		//Pierna Izq
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(-0.2f, -0.52f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotfemur.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -3.2f, -0.0f));
		model = glm::rotate(model, glm::radians(-rotIzq2), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fibula.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -3.3f, -0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pie.Draw(lightingShader);
		
		//Pierna Der
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(0.2f, -0.52f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotfemur.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -3.2f, -0.0f));
		model = glm::rotate(model, glm::radians(-rotDer2), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fibula.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -3.3f, -0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pie.Draw(lightingShader);

		//BrazoDer
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(-0.14f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotBraDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDer.Draw(lightingShader);


		//BrazoIzq
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(0.14f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotBraIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIzq.Draw(lightingShader);
	 

		//Segundo Robot
		glm::mat4 tmp2 = glm::mat4(1.0f); //Temp
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		tmp2 = model = glm::translate(model, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(posX2, posY2, posZ2));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotcuerpo2.Draw(lightingShader);

		//Pierna Izq
		view = camera.GetViewMatrix();
		model = glm::translate(tmp2, glm::vec3(-0.295f, -0.07f, 0.55f));
		model = glm::translate(model, glm::vec3(posX2, posY2, posZ2));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rot2RodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotfemur2.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(-0.02, -0.93f, 0.9f));
		model = glm::rotate(model, glm::radians(-rot2Izq2), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fibula2.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -0.85f, -0.85f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pie2.Draw(lightingShader);

		//Pierna Derecha
		view = camera.GetViewMatrix();
		model = glm::translate(tmp2, glm::vec3(0.295f, -0.07f, 0.55f));
		model = glm::translate(model, glm::vec3(posX2, posY2, posZ2));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rot2RodDer), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		robotfemur2.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0.02, -0.93f, 0.9f));
		model = glm::rotate(model, glm::radians(-rot2Der2), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fibula2.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::translate(model, glm::vec3(0, -0.85f, -0.85f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pie2.Draw(lightingShader);


		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);

		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}



void animacion()
{

	//Movimiento del personaje

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			rotIzq2 += KeyFrame[playIndex].rotInc2;

			rotRodDer += KeyFrame[playIndex].rotInc3;
			rotDer2 += KeyFrame[playIndex].rotInc4;

			rotBraDer += KeyFrame[playIndex].rotInc5;
			rotBraIzq += KeyFrame[playIndex].rotInc6;
			i_curr_steps++;
		}

	}
}

void animacion2()
{

	//Movimiento del personaje

	if (play2)
	{
		if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
		{
			playIndex2++;
			if (playIndex2 > FrameIndex2 - 2)	//end of total animation?
			{
				printf("termina anim2\n");
				playIndex2 = 0;
				play2 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps2 = 0; //Reset counter
								  //Interpolation
				interpolation2();
			}
		}
		else
		{
			//Draw animation
			posX2 += KeyFrame2[playIndex2].incX2;
			posY2 += KeyFrame2[playIndex2].incY2;
			posZ2 += KeyFrame2[playIndex2].incZ2;

			rot2RodIzq += KeyFrame2[playIndex2].rot2Inc;
			rot2Izq2 += KeyFrame2[playIndex2].rot2Inc2;

			rot2RodDer += KeyFrame2[playIndex2].rot2Inc3;
			rot2Der2 += KeyFrame2[playIndex2].rot2Inc4;

			rot2BraDer += KeyFrame2[playIndex2].rot2Inc5;
			rot2BraIzq += KeyFrame2[playIndex2].rot2Inc6;
			i_curr_steps2++;
		}

	}
}




// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}	

	if (animpuerta == true)
	{
		if (rotpuerta < 50.0f) { rotpuerta += 0.2f; }
		else if (rotpuerta > 50.0f)
		{
			animpuerta = false;
			controladorpuerta = true;
		}

	}

	if (animpuerta2 == true)
	{
		if (rotpuerta > 0.0f) { rotpuerta -= 0.2f; }
		else if (rotpuerta < 0.0f)
		{
			animpuerta2 = false;
			controladorpuerta = false;
		}
	}


	if (animlibrero == true)
	{
		if (movimientolibrero < 3.0f) { movimientolibrero += 0.1f; }
		else if (movimientolibrero > 3.0f)
		{
			animlibrero = false;	
			controladorlibrero = true;
		}

	}

	if (animlibrero2 == true)
	{
		if (movimientolibrero > 0.0f) { movimientolibrero -= 0.1f; }
		else if (movimientolibrero < 0.0f)
		{
			controladorlibrero = false;
			animlibrero2 = false;
				
		}

	}


	if (animEsfera == true)
	{
		if (movimientoEsfera < 0.1f) { movimientoEsfera += 0.005f; }
		else if (movimientoEsfera > 0.1f)
		{
			animEsfera = false;
			animEsfera2 = true;
		}
	}

	if (animEsfera2 == true)
	{
		if (movimientoEsfera > -0.08f) { movimientoEsfera -= 0.005f; }
		else if (movimientoEsfera < 0.1f)
		{
			animEsfera2 = false;
			animEsfera3 = true;
		}
	}

	if (animEsfera3 == true)
	{
		if (movimientoEsfera < 0.0f) { movimientoEsfera += 0.005f; }
		else if (movimientoEsfera > 0.0f)
		{
			animEsfera3 = false;

		}
	}	
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_1])
	{
		if (controladorpuerta == false)
			animpuerta = true;
		else if (controladorpuerta == true)
			animpuerta2 = true;
	}

	if (keys[GLFW_KEY_3])
	{
		movimientoEsfera = 0.0f;
		animEsfera = true;

	}

	if (keys[GLFW_KEY_2])
	{
		if (controladorlibrero == false) 
			animlibrero = true;
		else
			animlibrero2 = true;
	}

	if (keys[GLFW_KEY_4])
	{
		if (play == false)
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_5])
	{
		if (play2 == false)
		{

			resetElements2();
			//First Interpolation				
			interpolation2();

			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
		}
		else
		{
			play2 = false;
		}

	}

}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}