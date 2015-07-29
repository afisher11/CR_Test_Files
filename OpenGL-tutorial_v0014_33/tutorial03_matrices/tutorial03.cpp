// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
///////////////////////#include <common/texture.hpp>

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
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	// Enable depth test
//	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
//	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,15), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Load the texture using any two methods
	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	//////////////////////////////////////////////////////GLuint Texture = loadBMP_custom("TextureSource.bmp");
	//GLuint Texture = loadDDS("uvtemplate.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	//////////////////////////////////////////////GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// static const GLfloat g_vertex_buffer_data[] = {
	GLfloat g_vertex_buffer_data[] = {
		 // Primary Triangle 1
		 //-1.0f, -1.0f, 0.0f,
		 //1.0f, 1.0f, 0.0f,
		 //-1.0f,  1.0f, 0.0f,

		 // Primary Triangle 2
		 //-1.0f, -1.0f, 0.0f,
		 //1.0f, -1.0f, 0.0f,
		 //1.0f, 1.0f, 0.0f

		// TRIANGLES
		
		

		


		// Back
		-1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		// end Back



		// Bottom
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		// end Bottom

		// Left
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		// end Left

		//Right
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		// end Right

		// Top
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		// end Top

		// Front
		-1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
		// end Front
	};

	//static const GLushort g_element_buffer_data[] = { 0, 1, 2 };
	//static const GLfloat g_uv_buffer_data[] = {
		// One color for each vertex. They were generated randomly.
	//static const GLfloat g_color_buffer_data[] = {
		GLfloat g_color_buffer_data[] = {
		// Primary Triangle 1
		//0.0f, 0.0f,
		//1.0f, 1.0f,
		//0.0f, 1.0f,

		// Primary Triangle 2
		//0.0f, 0.0f,
		//1.0f, 0.0f,
		//1.0f, 1.0f

		// TEXTURES

		

		// Back
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,

		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		// end Back

		

		// Bottom
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,

		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		// end Bottom

		// Left
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,

		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		// end Left

		// Right
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,

		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		// end Right

		// Top
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,

		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		// end Top

		// Front
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,

		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f
		// end Front
	};


	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	///////////////////////////
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	///////////////////////////

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);


	glm::mat4 moveIn = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0375f));
	glm::mat4 moveOut = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.0375f));
	glm::mat4 moveLeft = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0375f, 0.0f, 0.0f));
	glm::mat4 moveRight = glm::translate(glm::mat4(1.0f), glm::vec3(0.0375f, 0.0f, 0.0f));

	double currentTime = glfwGetTime();

	do{
		/*
		// Move car left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			
		}

		// Move car right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			// CAR - 20 Triangles
			for (int i = 0; i < 20; i++)
			{
				// Move right on X axis
				g_vertex_buffer_data[((i*9) + (0 + (49*3*3)))] += 0.25f;
				g_vertex_buffer_data[((i*9) + (3 + (49*3*3)))] += 0.25f;
				g_vertex_buffer_data[((i*9) + (6 + (49*3*3)))] += 0.25f;
			}

			// WHEELS - 40 Triangles
			for (int i = 0; i < 40; i++)
			{									// 69 Previous Triangles
				// Move on X axis
				g_vertex_buffer_data[((i*9) + (0 + ((69)*3*3)))] += 0.25f;
				g_vertex_buffer_data[((i*9) + (3 + ((69)*3*3)))] += 0.25f;
				g_vertex_buffer_data[((i*9) + (6 + ((69)*3*3)))] += 0.25f;

				leftAxle += glm::vec3(0.25f, 0.0f, 0.0f);
				rightAxle += glm::vec3(0.25f, 0.0f, 0.0f);

				if (((i >= 0) && (i < 16)) || ((i >= 32) && (i < 40)))
				{
					// Rotate Left Wheel & Rim CounterClockwise
				}
				else
				{
					// Rotate Right Wheel & Rim CounterClockwise
				}
			}

			carDistRight++;
			carDistLeft--;
			if (carDistRight > 0)
			{
				// Move Sky Up - 30 Triangles
				for (int i = 0; i < 30; i++)
				{
					// Move right on X axis
					g_vertex_buffer_data[((i*9) + (1 + (0*3*3)))] += 0.12f;
					g_vertex_buffer_data[((i*9) + (4 + (0*3*3)))] += 0.12f;
					g_vertex_buffer_data[((i*9) + (7 + (0*3*3)))] += 0.12f;
				}
			}
			else
			{
				// Move Sky Down - 30 Triangles
				for (int i = 0; i < 30; i++)
				{
					// Move right on X axis
					g_vertex_buffer_data[((i*9) + (1 + (0*3*3)))] -= 0.12f;
					g_vertex_buffer_data[((i*9) + (4 + (0*3*3)))] -= 0.12f;
					g_vertex_buffer_data[((i*9) + (7 + (0*3*3)))] -= 0.12f;
				}
			}
		}
		*/

		/////////////////// TEST ROTATE //////////////////////
		// Rotate left by pushing A key
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			// Rotate
		}

		// Zoom in
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			View = View * moveIn;
		}

		// Zoom out
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			View = View * moveOut;
		}

		// Move left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			View = View * moveLeft;
		}

		// Move left
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			View = View * moveRight;
		}

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//////////////////////////////////////////////
		// Bind our texture in Texture Unit 0
//		glActiveTexture(GL_TEXTURE0); ///////////////////////////////////////////////////////////////////// was NOT commented out
//		glBindTexture(GL_TEXTURE_2D, Texture); //////////////////////////////////////////////////////////// was NOT commented out
		// Set our "myTextureSampler" sampler to user Texture Unit 0
//		glUniform1i(TextureID, 0); //////////////////////////////////////////////////////////////////////// was NOT commented out
		//////////////////////////////////////////////

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// UV Buffer for Textures:
		//////////////////////////////////////////////////
		// 2nd attribute buffer : UVs
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//		glVertexAttribPointer(
//			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
//			2,                                // size : U+V => 2
//			GL_FLOAT,                         // type
//			GL_FALSE,                         // normalized?
//			0,                                // stride
//			(void*)0                          // array buffer offset
//		);
		//////////////////////////////////////////////////
		// END UV Buffer for Textures stuff

		MVP = Projection * View * Model;

		// Draw the triangle !		Moon10 + Sky4 + Sun16 + Ground2 + Road2 + House15 (Chimney2, Siding2, Roof3, Door2, Doorknob2, WindowTrim2,
		//																		WindowPane2) + Car20 (Body12, Bumpers4, Windows4)
		//																			+ LeftWheel16 + RightWheel16 + LRim4 + RRim4
		glDrawArrays(GL_TRIANGLES, 0, (12)*3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1); ///////////////////////////

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	////////////////////////glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	////////////////////////glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

