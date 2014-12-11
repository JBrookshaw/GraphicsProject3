
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>


#include <GLFW/glfw3.h>
GLFWwindow* window;



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "utils/shader.hpp"
#include "utils/texture.hpp"
#include "utils/objloader.hpp"
#include "utils/vboindexer.hpp"
#include "utils/p1controls.hpp"
#include "utils/p2controls.hpp"
#include "utils/text2D.hpp"



//Freetype Variables






GLuint Texture;
GLuint Texture2;
GLuint Texture3;
GLuint Texture4;
GLuint Texture5;



GLuint VertexArrayID;

GLuint programID;

GLuint MatrixID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;

GLuint TextureID;


std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;
std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;

std::vector<glm::vec3> vertices2;
std::vector<glm::vec2> uvs2;
std::vector<glm::vec3> normals2;
std::vector<unsigned short> indices2;
std::vector<glm::vec3> indexed_vertices2;
std::vector<glm::vec2> indexed_uvs2;
std::vector<glm::vec3> indexed_normals2;

GLuint vertexbuffer;
GLuint uvbuffer;
GLuint normalbuffer;
GLuint elementbuffer;

GLuint vertexbuffer2;
GLuint uvbuffer2;
GLuint normalbuffer2;
GLuint elementbuffer2;

glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;

glm::mat4 ModelMatrix1 = glm::mat4(1.0);

glm::mat4 P2CARD3m = glm::mat4(1.0);
glm::mat4 P2CARD2m = glm::mat4(1.0);
glm::mat4 P2CARD1m = glm::mat4(1.0);

glm::mat4 P1CARD3m = glm::mat4(1.0);
glm::mat4 P1CARD2m = glm::mat4(1.0);
glm::mat4 P1CARD1m = glm::mat4(1.0);

glm::mat4 MVP1;
glm::mat4 MVP2;
glm::mat4 MVP3;
glm::mat4 MVP4;
glm::mat4 MVP5;
glm::mat4 MVP6;
glm::mat4 MVP7;

glm::mat4 setUpCard(glm::mat4 MODEL, glm::mat4 MVP, glm::vec3 TRANS, glm::mat4 SCALE, glm::mat4 ROTA){
	MODEL = glm::translate(MODEL, TRANS);
	MODEL = MODEL * SCALE * ROTA;
	MVP = ProjectionMatrix * ViewMatrix * MODEL;
	return MODEL;
}



void drawText(const char *text, int length, int x, int y){
 glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
 double matrix[16]; // 16 doubles in stack memory
 glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
 glLoadIdentity(); // reset PROJECTION matrix to identity matrix
 glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
 glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
 glLoadIdentity(); // reset it to identity matrix
 glPushMatrix(); // push current state of MODELVIEW matrix to stack
 glLoadIdentity(); // reset it again. (may not be required, but it my convention)
 glRasterPos2i(x, y); // raster position in 2D
 for(int i=0; i<length; i++){
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
 }
 glPopMatrix(); // get MODELVIEW matrix value from stack
 glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
 glLoadMatrixd(matrix); // reset
 glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}
 




void drawCard(glm::mat4 model, glm::mat4 mvp, GLuint tex){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(TextureID, 0);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer2);

	glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_SHORT, (void*)0);
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
	

	
	

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1400, 900, "Card Game", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);

	programID = LoadShaders( "shaders/TransformVertexShader.vertexshader", "shaders/TextureFragmentShader.fragmentshader" );

	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");

	TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	Texture = loadDDS("tex/cardbg2.DDS");
	Texture2 = loadDDS("tex/ecat.DDS");
	Texture3 = loadDDS("tex/gauto.DDS");
	Texture4 = loadDDS("tex/dfsen.DDS");
	Texture5 = loadDDS("tex/aceace.DDS");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Read our .obj file
	bool res = loadOBJ("obj/cardbg.obj", vertices, uvs, normals);

	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

	// Read our .obj file
	bool res2 = loadOBJ("obj/card.obj", vertices2, uvs2, normals2);

	indexVBO(vertices2, uvs2, normals2, indices2, indexed_vertices2, indexed_uvs2, indexed_normals2);

	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices2.size() * sizeof(glm::vec3), &indexed_vertices2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs2.size() * sizeof(glm::vec2), &indexed_uvs2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals2.size() * sizeof(glm::vec3), &indexed_normals2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned short), &indices2[0] , GL_STATIC_DRAW);

	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	glm::mat4 myScalingMatrix = glm::scale(2.3f, 1.0f , 3.5f);
	glm::mat4 cardSize = glm::scale(0.8f, 1.0f ,0.8f);
	glm::mat4 myScalingMatrix3 = glm::scale(0.95f, 1.0f ,0.95f);

	glm::mat4 myMatrix = glm::translate(0.0f, 0.0f, -0.05f);
	glm::mat4 select = glm::translate(0.0f, 0.005f, 0.0f);

	mat4 rotation = mat4(
		vec4( cos(3.14), 0.0,  sin(3.14),  0.0),
		vec4(0.0,  1.0, 0.0, 0.0),
		vec4(-sin(3.14), 0.0,  cos(3.14),  0.0),
		vec4( 0.0, 0.0, 0.0, 1.0)
		);

	mat4 rotation2 = mat4(
		vec4( cos(0.2), 0.0,  sin(0.2),  0.0),
		vec4(0.0,  1.0, 0.0, 0.0),
		vec4(-sin(0.2), 0.0,  cos(0.2),  0.0),
		vec4( 0.0, 0.0, 0.0, 1.0)
		);

	mat4 dieAnimation = myScalingMatrix3*rotation2;

	ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// ProjectionMatrix = ProjectionMatrix * myScalingMatrix;
	// Camera matrix

	ViewMatrix       = glm::lookAt(
		glm::vec3(0,17,0.001f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

	ModelMatrix1 = ModelMatrix1 * myScalingMatrix;
	MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;

	/*P2CARD3m = glm::translate(P2CARD3m, glm::vec3(-4.0f, 0.1f, -3.3f));
	P2CARD3m = P2CARD3m * cardSize * rotation;
	MVP2 = ProjectionMatrix * ViewMatrix * P2CARD3m;*/

	glm::mat4 temp = setUpCard(P2CARD3m, MVP2, glm::vec3(-4.0f, 0.1f, -3.3f), cardSize, rotation);
	setP2Card3(temp);
	setP2_Card3(temp);
	
	P2CARD2m = glm::translate(P2CARD2m, glm::vec3(-0.0f, 0.1f, -3.3f));
	P2CARD2m = P2CARD2m * cardSize * rotation;
	MVP6 = ProjectionMatrix * ViewMatrix * P2CARD2m;

	setP2Card2(P2CARD2m);
	setP2_Card2(P2CARD2m);

	P2CARD1m = glm::translate(P2CARD1m, glm::vec3(4.0f, 0.1f, -3.3f));
	P2CARD1m = P2CARD1m * cardSize * rotation;
	MVP3 = ProjectionMatrix * ViewMatrix * P2CARD1m;

	setP2Card1(P2CARD1m);
	setP2_Card1(P2CARD1m);

	P1CARD3m = glm::translate(P1CARD3m, glm::vec3(4.0f, 0.1f, 3.3f));
	P1CARD3m = P1CARD3m * cardSize;
	MVP4 = ProjectionMatrix * ViewMatrix * P1CARD3m;

	setP1Card3(P1CARD3m);
	setP1_Card3(P1CARD3m);

	P1CARD2m = glm::translate(P1CARD2m, glm::vec3(0.0f, 0.1f, 3.3f));
	P1CARD2m = P1CARD2m * cardSize;
	MVP7 = ProjectionMatrix * ViewMatrix * P1CARD2m;

	setP1Card2(P1CARD2m);
	setP1_Card2(P1CARD2m);

	P1CARD1m = glm::translate(P1CARD1m, glm::vec3(-4.0f, 0.1f, 3.3f));
	P1CARD1m = P1CARD1m * cardSize;
	MVP5 = ProjectionMatrix * ViewMatrix * P1CARD1m;

	setP1Card1(P1CARD1m);
	setP1_Card1(P1CARD1m);

	initText2D( "tex/Holstein.DDS" );

	//creates copys of original positions of cards to rturn to after animations
	createCopys();
	createCopys_();

	bool playerturn =false;

	do{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		//Used for changing player perspective
		if (glfwGetKey( window, GLFW_KEY_0 ) == GLFW_PRESS){
		ViewMatrix       = glm::lookAt(
		glm::vec3(0,17,0.001f), 
		glm::vec3(0,0,0), 
		glm::vec3(0,1,0)  
		);
		playerturn =false;
	}

		if (glfwGetKey( window, GLFW_KEY_9 ) == GLFW_PRESS){
		ViewMatrix       = glm::lookAt(
		glm::vec3(0,17,0.001f), 
		glm::vec3(0,0,0), 
		glm::vec3(0,-1,0)  
		);
		playerturn =true;
	}

		if(!playerturn)
		{
		player1Inputs();

		P1CARD1m = getP1Card1();
		P1CARD2m = getP1Card2();
		P1CARD3m = getP1Card3();

		P2CARD1m = getP2Card1();
		P2CARD2m = getP2Card2();
		P2CARD3m = getP2Card3();
		}
		else{
			player2Inputs();
		P1CARD1m = getP1_Card1();
		P1CARD2m = getP1_Card2();
		P1CARD3m = getP1_Card3();

		P2CARD1m = getP2_Card1();
		P2CARD2m = getP2_Card2();
		P2CARD3m = getP2_Card3();
		}
		MVP2 = ProjectionMatrix * ViewMatrix * P2CARD3m;
		MVP3 = ProjectionMatrix * ViewMatrix * P2CARD1m;
		MVP4 = ProjectionMatrix * ViewMatrix * P1CARD3m;
		MVP5 = ProjectionMatrix * ViewMatrix * P1CARD1m;
		MVP6 = ProjectionMatrix * ViewMatrix * P2CARD2m;
		MVP7 = ProjectionMatrix * ViewMatrix * P1CARD2m;

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]); // This one doesn't change between objects, so this can be done once for all objects that use "programID"

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
			);

		drawCard(P2CARD3m,MVP2,Texture2);
		drawCard(P2CARD1m,MVP3,Texture3);
		drawCard(P1CARD3m,MVP4,Texture4);
		drawCard(P1CARD1m,MVP5,Texture5);
		drawCard(P2CARD2m,MVP6,Texture5);
		drawCard(P1CARD2m,MVP7,Texture4);

		////// End of rendering of the second object //////

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		char text[256];
		sprintf(text,"Test", glfwGetTime() );
		printText2D(text, 10, 500, 60);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);



	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}



