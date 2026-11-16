#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include "imgui.h"
#include "Console.h"
#include "View.h"
#include "Elements.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <glut.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



using namespace std;

void processKeyboardInput ();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool spirit_loose = false;

bool oasis = false;

int phase = 0;

int width = 800;
int height = 800;

char* phase0 = "The crash still rings in your head. \"How long was I out for?\" You contemplate no furder, the thirst shuts you up and you beging looking for an oasis";
char* phase1 = "You found the oasis but you are not safe yet. You have to find the srap of your plane to fix it and scape. You remember a few important details a catus a well and nothingness. ";
char* phase2 = "Find the rest of the scrap and be quick! 1/3";
char* phase3 = "The spirits of the dessert chase you. Watch your feet. Run or die. 2/3";
char* phase4 = "Go back to the plain and survive! 3/3";

string music1 = "";
string music2 = "";

Window window("Game Engine", 800, 800);
Camera camera;
glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);

float wellc=0;
bool welled = false;
// cactus positions


std::vector<glm::vec3> cactus_positions = {
	glm::vec3(70.0f, -15.0f, 30.0f),


	glm::vec3(120.0f, -15.0f, -190.0f),
	glm::vec3(110.0f, -15.0f, -190.0f),
	glm::vec3(130.0f, -15.0f, -190.0f),
	glm::vec3(140.0f, -15.0f, -190.0f),
	glm::vec3(150.0f, -15.0f, -190.0f),
	glm::vec3(160.0f, -15.0f, -190.0f),
	glm::vec3(170.0f, -15.0f, -190.0f),

	glm::vec3(110.0f, -15.0f, -270.0f),
	glm::vec3(120.0f, -15.0f, -270.0f),
	glm::vec3(130.0f, -15.0f, -270.0f),
	glm::vec3(140.0f, -15.0f, -270.0f),
	glm::vec3(150.0f, -15.0f, -270.0f),
	glm::vec3(160.0f, -15.0f, -270.0f),
	glm::vec3(170.0f, -15.0f, -270.0f),

	glm::vec3(180.0f, -15.0f, -200.0f),
	glm::vec3(180.0f, -15.0f, -210.0f),
	glm::vec3(180.0f, -15.0f, -220.0f),
	glm::vec3(180.0f, -15.0f, -230.0f),
	glm::vec3(180.0f, -15.0f, -240.0f),
	glm::vec3(180.0f, -15.0f, -250.0f),
	glm::vec3(180.0f, -15.0f, -260.0f),
	glm::vec3(180.0f, -15.0f, -270.0f),



	

	glm::vec3(120.0f, -15.0f, -215.0f),
	glm::vec3(110.0f, -15.0f, -215.0f),
	glm::vec3(130.0f, -15.0f, -215.0f),
	glm::vec3(140.0f, -15.0f, -215.0f),
	glm::vec3(150.0f, -15.0f, -215.0f),
	glm::vec3(160.0f, -15.0f, -215.0f),
	glm::vec3(160.0f, -15.0f, -225.0f),
	glm::vec3(160.0f, -15.0f, -235.0f),
	glm::vec3(160.0f, -15.0f, -245.0f),

	glm::vec3(100.0f, -15.0f, -190.0f),
	glm::vec3(100.0f, -15.0f, -200.0f),
	glm::vec3(100.0f, -15.0f, -210.0f),
	glm::vec3(100.0f, -15.0f, -220.0f),
	glm::vec3(100.0f, -15.0f, -230.0f),
	glm::vec3(100.0f, -15.0f, -240.0f),
	glm::vec3(100.0f, -15.0f, -260.0f),
	glm::vec3(100.0f, -15.0f, -270.0f),


	glm::vec3(120.0f, -15.0f, -270.0f),
	glm::vec3(120.0f, -15.0f, -260.0f),
	glm::vec3(120.0f, -15.0f, -250.0f),

	glm::vec3(140.0f, -15.0f, -250.0f),
	glm::vec3(140.0f, -15.0f, -240.0f),
	
	glm::vec3(150.0f, -15.0f, -240.0f),

	
};


std::vector<glm::vec3> scrap_positions = {

	glm::vec3(110.0f, 0.0f, -200.0f),
	glm::vec3(-50.0f, 0.0f, 250.0f),
	glm::vec3(-50.0f, -50.0f, 250.0f)

};

int collected_scraps = 0;

// SANDSTORM POSITIONS AND SPEED

std::vector<glm::vec3> sandstorm_positions = {
	glm::vec3(50.0f, -50.0f, 50.0f),
	glm::vec3(-50.0f, -50.0f, 50.0f),
	glm::vec3(50.0f, -50.0f, -50.0f),
	glm::vec3(-50.0f, -50.0f, -50.0f)
};

glm::vec3 sandstorm_velocity = glm::vec3(-20.0f, -100.0f, -20.0f);

float timer = 80.0f; // Tiempo inicial del contador
float timeSinceLastPrint = 0.0f; // Tracks time since last console print

int cactusImmunityTimer = 1000;  // Tiempo de inmunidad



int main()
{
	glClearColor(0.2f, 0.8f, 1.0f, 1.0f);

	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader skyboxShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader doorShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader terrainShader("Shaders/terrain_shader.glsl", "Shaders / sun_fragment_shader.glsl");
	Shader waterShader("Shaders/water_vertex_shader.glsl", "Shaders/water_fragment_shader.glsl");
	//Textures
	GLuint tex = loadBMP("Resources/Textures/skyboxbq(1).bmp");
	GLuint tex2 = loadBMP("Resources/Textures/palm.bmp");
	GLuint tex3 = loadBMP("Resources/Textures/burnt_metal.bmp");
	GLuint tex4 = loadBMP("Resources/Textures/sand2(1).bmp");
	GLuint tex5 = loadBMP("Resources/Textures/cactus2.bmp");
	GLuint tex6 = loadBMP("Resources/Textures/red.bmp");
	GLuint tex7 = loadBMP("Resources/Textures/water.bmp");

	glEnable(GL_DEPTH_TEST);

	//Test custom mesh loading
	std::vector<Vertex> vert;
	vert.push_back(Vertex());
	vert[0].pos = glm::vec3(10.5f, 10.5f, 0.0f);
	vert[0].textureCoords = glm::vec2(1.0f, 1.0f);

	vert.push_back(Vertex());
	vert[1].pos = glm::vec3(10.5f, -10.5f, 0.0f);
	vert[1].textureCoords = glm::vec2(1.0f, 0.0f);

	vert.push_back(Vertex());
	vert[2].pos = glm::vec3(-10.5f, -10.5f, 0.0f);
	vert[2].textureCoords = glm::vec2(0.0f, 0.0f);

	vert.push_back(Vertex());
	vert[3].pos = glm::vec3(-10.5f, 10.5f, 0.0f);
	vert[3].textureCoords = glm::vec2(0.0f, 1.0f);

	vert[0].normals = glm::normalize(glm::cross(vert[1].pos - vert[0].pos, vert[3].pos - vert[0].pos));
	vert[1].normals = glm::normalize(glm::cross(vert[2].pos - vert[1].pos, vert[0].pos - vert[1].pos));
	vert[2].normals = glm::normalize(glm::cross(vert[3].pos - vert[2].pos, vert[1].pos - vert[2].pos));
	vert[3].normals = glm::normalize(glm::cross(vert[0].pos - vert[3].pos, vert[2].pos - vert[3].pos));

	std::vector<int> ind = { 0, 1, 3,   
		1, 2, 3 };

	std::vector<Texture> textures;
	textures.push_back(Texture());
	textures[0].id = tex;
	textures[0].type = "texture_diffuse";

	std::vector<Texture> textures2;
	textures2.push_back(Texture());
	textures2[0].id = tex2;
	textures2[0].type = "texture_diffuse";

	std::vector<Texture> textures3;
	textures3.push_back(Texture());
	textures3[0].id = tex3;
	textures3[0].type = "texture_diffuse";

	std::vector<Texture> textures4;
	textures4.push_back(Texture());
	textures4[0].id = tex4;
	textures4[0].type = "texture_diffuse";

	std::vector<Texture> textures5;
	textures5.push_back(Texture());
	textures5[0].id = tex5;
	textures5[0].type = "texture_diffuse";

	std::vector<Texture> textures6;
	textures6.push_back(Texture());
	textures6[0].id = tex6;
	textures6[0].type = "texture_diffuse";

	std::vector<Texture> textures7;
	textures7.push_back(Texture());
	textures7[0].id = tex7;
	textures7[0].type = "texture_diffuse";



	Mesh mesh(vert, ind, textures4);

	// Create Obj files - easier :)
	// we can add here our textures :)
	MeshLoaderObj loader;
	Mesh light = loader.loadObj("Resources/Models/sphere.obj", textures);
	Mesh skybox = loader.loadObj("Resources/Models/sphere.obj", textures);
	Mesh box = loader.loadObj("Resources/Models/sphere.obj", textures);
	Mesh plane = loader.loadObj("Resources/Models/plane.obj", textures4);
	Mesh water = loader.loadObj("Resources/Models/plane1.obj", textures7);
	Mesh wrek= loader.loadObj("Resources/Models/wrek.obj", textures3);
	Mesh heart = loader.loadObj("Resources/Models/sphere.obj", textures6);
	Mesh well = loader.loadObj("Resources/Models/well.obj", textures2);
	// add cactus
	Mesh cactus = loader.loadObj("Resources/Models/cactus6.obj", textures5);

	// add sandstorm
	Mesh sandstorm = loader.loadObj("Resources/Models/sphere.obj", textures4);

	// add scrap
	Mesh scrap = loader.loadObj("Resources/Models/cube.obj", textures3); 

	//GUI stuff:
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 400");

	/*
	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));*/




	// Create Frame Buffer Object
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create Framebuffer Texture
	unsigned int framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);


	

	// Create Render Buffer Object
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


	// Error checking framebuffer
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << fboStatus << std::endl;

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// MAIN LOOP
	bool showHistory = false;
	bool setting = true;
	/*PlaySound("Cocteau-Twins-Heaven-Or-Las-Vegas-_Official-Video_.wav", NULL, SND_FILENAME | SND_ASYNC);*/
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		if (setting == true) {
			if (lightColor.x > 0.1) { lightColor.x = lightColor.x - 0.00002; }
			lightColor.z = lightColor.z - 0.00001;
			if (lightColor.y > 0.1)lightColor.y = lightColor.y - 0.00004;
			if (lightColor.z < 0.1) { setting = false;std::cout << "amanece" << std::endl; }
		}
		else {
			if (lightColor.x <= 1) { lightColor.x = lightColor.x + 0.00004; }
			if (lightColor.z <= 1)lightColor.z = lightColor.z + 0.00001;
			if (lightColor.y <= 1)lightColor.y = lightColor.y + 0.00002;
			if (lightColor.y >= 1 && lightColor.x >= 1 && lightColor.z >= 1) { setting = true; }
		}
		window.clear();

		glColor3f(1.0f, 1.0f, 0.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Game info:");

		Console::RenderUI();
		Elements::RenderUI();
		View::RenderUI(framebufferTexture);
		
		//if (ImGui::Button("Show history")) {
		//	showHistory = !showHistory;
		//}


	//	float currentFrame = glfwGetTime();


	//	deltaTime = currentFrame - lastFrame;
	//	lastFrame = currentFrame;

	//	// COUNTER
	//	// Update timer
	//	timer -= deltaTime;
	//	timeSinceLastPrint += deltaTime;
	//	if (glm::length(camera.getCameraPosition() - glm::vec3(-200.0f, -15.0f, 50.0f)) < 100.0f && !oasis) {
	//		oasis = true;
	//		std::cout << phase1 << std::endl;
	//		timer = 200;
	//		phase++;
	//	}
	//if(!oasis){
	//	if (timer <= 0.0f) {
	//		std::cout << "You have weakened. You have lost the game!" << std::endl;
	//		glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
	//	}
	//	else if (timeSinceLastPrint >= 5.0f) {
	//		std::cout << "Time remaining: " << (int)timer << " seconds. You are very weak! Try to find the oasis to survive." << std::endl;
	//		timeSinceLastPrint = 0.0f;
	//	}
	//}
	//if (timer <= 0.0f) {
	//	std::cout << "You are dead! GAME OVER" << std::endl;
	//	glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
	//}
		processKeyboardInput();
		

		if (camera.getCameraPosition().x < 320.0f && camera.getCameraPosition().x > 280.0f && camera.getCameraPosition().z < 120.0f && camera.getCameraPosition().z > 80.0f && !welled) {
			if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				wellc++;
				if (wellc >= 500.0f) {
					scrap_positions[2] = camera.getCameraPosition();
					welled = true;
				}
				
			}
			else {
				wellc = 0.0f;
			}
			
		}
		else {
			wellc = 0.0f;
		}
		//test mouse input
		/*if (window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			std::cout << "Pressing mouse button" << std::endl;
			timer = 200.0f;
		}*/
		 //// Code for the light ////

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glViewport(0, 0, width, height);
		glClearColor(0.8f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skyboxShader.use();


		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());
		GLuint MatrixID = glGetUniformLocation(skyboxShader.getId(), "MVP");

		

		//Test for one Obj loading = light source
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);



		/*glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);*/

		//light.draw(skyboxShader);

		//// End code for the light ////




		//////////////////////////////////////////////
		// SCRAP
		shader.use();

		static float rotationAngle = 0.0f;
		rotationAngle += 1000.0f * deltaTime;

		for (auto& pos : scrap_positions) {
			glm::mat4 ModelMatrix = glm::mat4(1.0);

			ModelMatrix = glm::translate(ModelMatrix, pos);
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));


			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

			GLuint MatrixID = glGetUniformLocation(shader.getId(), "MVP");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

			scrap.draw(shader);


			// Check Scrap Collection
			if (glm::length(camera.getCameraPosition() - pos) < 4.0f) {
				pos = glm::vec3(0.0f, 200.0f, 0.0f); // Move out of view
				collected_scraps++;
				phase++;
				std::cout << "Scrap collected! Total: " << collected_scraps << std::endl;

				if (collected_scraps == 3) {
					std::cout << phase4 << std::endl;
					collected_scraps++;
				}
			}
		}
		if (glm::length(camera.getCameraPosition() - glm::vec3(0.0f, -5.0f, 0.0f)) < 70.0f && collected_scraps == 4) {
			glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
		}
		//////////////////////////////////////////
		// SANDSTORM

		bool gameOver = false;



		//int i = 0;
		//for (auto& pos : sandstorm_positions) {
		//	// Calcular el vector de dirección hacia la cámara
		//	glm::vec3 direction = pos - camera.getCameraPosition();
		//	glm::vec3 direction_normalizada = glm::normalize(direction);

		//	if (collected_scraps >= 2 && !spirit_loose) {
		//		pos += (sandstorm_velocity * deltaTime) * direction_normalizada;
		//		std::cout << "The spirits of the dessert chase you. Run or die." << std::endl;
		//	}
		//	// Transformación y renderizado
		//	glm::mat4 ModelMatrix = glm::mat4(1.0f);
		//	ModelMatrix = glm::translate(ModelMatrix, pos);
		//	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.3f, 0.3f, 0.3f));
		//	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//	GLuint MatrixID = glGetUniformLocation(shader.getId(), "MVP");
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

		//	sandstorm.draw(shader);

		//	// Comprobar si la tormenta atrapa al jugador
		//	if (glm::length(camera.getCameraPosition() - pos) < 5.0f && !gameOver) {
		//		std::cout << "The spirits catched you. GAME OVER" << std::endl;
		//		gameOver = true;
		//		glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
		//	}
		//	i++;
		//}


		///////////////////////////////////////////
		//// CACTUS

		//for (const auto& pos : cactus_positions) {
		//	glm::mat4 ModelMatrix = glm::mat4(1.0f);
		//	ModelMatrix = glm::translate(ModelMatrix, pos);


		//	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.8f, 0.8f, 0.8f));

		//	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		//	GLuint MatrixID = glGetUniformLocation(shader.getId(), "MVP");
		//	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

		//	cactus.draw(shader);

		//	if (cactusImmunityTimer == 0 && glm::length(camera.getCameraPosition() - pos) < 17.0f) {

		//		timer -= 10.0f;
		//		cactusImmunityTimer = 1000; // esto es porque como chequea la colision en todos frames
		//		// si tocabas cactus te morias del tiron. esto te da unos segundos de 
		//		// inmunidad mientras de sales del cactus

		//		//std::cout << "You got hurt by the cactus! You now have " << (int)timer << " seconds left before you weaken." << std::endl;
		//		ImGui::Text("You got hurt by the cactus!You now have (int)timerseconds left before you weaken.");

		//	}
		//	else if(cactusImmunityTimer > 0){
		//		cactusImmunityTimer --;
		//	}
		//}

		//
		////////////////////////////////////////////


		/////// Test Obj files for box ////

		//GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		//GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");

		//ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -4.0f, 0.0f));
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(350.0f, 350.0f, 350.0f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//box.draw(shader);

		/////// Test plane Obj file //////

		//GLuint MatrixID3 = glGetUniformLocation(terrainShader.getId(), "MVP");
		//GLuint ModelMatrixID1 = glGetUniformLocation(terrainShader.getId(), "model");

		//ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -15.0f, 0.0f));
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID3, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID1, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(terrainShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(terrainShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(terrainShader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//plane.draw(terrainShader);

		//// Water

		//waterShader.use();
		//GLuint MatrixID4 = glGetUniformLocation(waterShader.getId(), "MVP");
		//GLuint ModelMatrixID2 = glGetUniformLocation(waterShader.getId(), "model");

		//float time = glfwGetTime();

		//ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-200.0f, -14.0f, 50.0f));
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID3, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID1, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(waterShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(waterShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(waterShader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//glUniform1f(glGetUniformLocation(waterShader.getId(), "time"), time);

		//water.draw(waterShader);

		/////////// WREK////////

		//shader.use();

		//ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -5.0f, 0.0f));
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		////ModelMatrix = glm::rotate(ModelMatrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//wrek.draw(shader);

		/////////// HEART////////

		//ModelMatrix = glm::mat4(1.0);
		//glm::vec3 vector = glm::vec3((camera.getCameraPosition() +
		//	0.8f *camera.getCameraViewDirection() +
		//	1.0f * camera.getCameraRight() + -0.5f  * camera.getCameraUp()));
		//ModelMatrix = glm::translate(ModelMatrix, vector);
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.00003f, 0.00003f, 0.00003f)*timer);
		////ModelMatrix = glm::rotate(ModelMatrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//heart.draw(shader);

		/////////// HEART////////

		//ModelMatrix = glm::mat4(1.0);
		//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(300.0f, -20.0f, 100.0f));
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(15.0f, 15.0f, 15.0f));
		////ModelMatrix = glm::rotate(ModelMatrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//well.draw(shader);

		///*if (showHistory) {
		//	if (phase == 0) {
		//		ImGui::Text(phase0);
		//	}else if(phase == 1) {
		//		ImGui::Text(phase1);
		//	}
		//	else if(phase == 2) {
		//		ImGui::Text(phase2);
		//	}
		//	else if(phase == 3){
		//		ImGui::Text(phase3);
		//	}
		//	else {
		//		ImGui::Text(phase4);
		//	}
		//}*/


		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window.getWidth(), window.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}
	
	/*ImGui::DestroyContext();*/
	}


void processKeyboardInput()
{
	float cameraSpeed = 30 * deltaTime;

	//translation
	if (window.isPressed(GLFW_KEY_W))
		camera.keyboardMoveFront(cameraSpeed);
	if (window.isPressed(GLFW_KEY_S))
		camera.keyboardMoveBack(cameraSpeed);
	if (window.isPressed(GLFW_KEY_A))
		camera.keyboardMoveLeft(cameraSpeed);
	if (window.isPressed(GLFW_KEY_D))
		camera.keyboardMoveRight(cameraSpeed);

	//rotation
	if (window.isPressed(GLFW_KEY_LEFT))
		camera.rotateOy(cameraSpeed*2);
	if (window.isPressed(GLFW_KEY_RIGHT))
		camera.rotateOy(-cameraSpeed*2);
	if (window.isPressed(GLFW_KEY_UP))
		camera.rotateOx(cameraSpeed*2);
	if (window.isPressed(GLFW_KEY_DOWN))
		camera.rotateOx(-cameraSpeed*2);
}


