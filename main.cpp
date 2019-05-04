#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <model.h>

#include <iostream>
#include <stdio.h>
#include <string>


// settings
const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

bool keys[1024];
bool keysPressed[1024];
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
			keysPressed[key] = false;
		}
	}
}

GLuint loadTexture(char const * path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL Chapter 5", NULL, NULL);	
	glfwMakeContextCurrent(window);

	// setup peripheral callback functions
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);

	Shader shader("normal_mapping_vs.glsl", "normal_mapping_fs.glsl");
	
	GLuint diffuseMap = loadTexture("brickwall.jpg");
	GLuint normalMap = loadTexture("brickwall_normal.jpg");
	
	// positions
	glm::vec3 pos1(-1.0, 1.0, 0.0);
	glm::vec3 pos2(-1.0, -1.0, 0.0);
	glm::vec3 pos3(1.0, -1.0, 0.0);
	glm::vec3 pos4(1.0, 1.0, 0.0);
	// texture coordinates
	glm::vec2 uv1(0.0, 1.0);
	glm::vec2 uv2(0.0, 0.0);
	glm::vec2 uv3(1.0, 0.0);
	glm::vec2 uv4(1.0, 1.0);
	
	GLfloat quadVertices[] = {
		// position
		pos1.x, pos1.y, pos1.z, uv1.x, uv1.y,
		pos2.x, pos2.y, pos2.z, uv2.x, uv2.y,
		pos3.x, pos3.y, pos3.z, uv3.x, uv3.y,

		pos1.x, pos1.y, pos1.z, uv1.x, uv1.y,
		pos3.x, pos3.y, pos3.z, uv3.x, uv3.y,
		pos4.x, pos4.y, pos4.z, uv4.x, uv4.y
	};

	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

	// Set texture units
	shader.use();
	shader.setInt("diffuseMap", 0);
	shader.setInt("normalMap", 1);

	// Light position
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);

	// Render loop
	while (!glfwWindowShouldClose(window)) 
	{		
		// Set frame time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		glfwPollEvents();	

		// Keyboard and mouse input
		processInput(window);
		
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// configure V P matrices
		shader.use();		
		glm::mat4 V = camera.GetViewMatrix();
		glm::mat4 P = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);	
		shader.setMat4("V", V);
		shader.setMat4("P", P);

		// render plane
		glm::mat4 M = glm::mat4(1.0f);
		M = glm::rotate(M, 45.0f, glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
		//M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
		// M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
		shader.setMat4("M", M);
		shader.setVec3("lightPos", lightPos);
		shader.setVec3("viewPos", camera.Position);	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap);

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);	
	}

	glfwTerminate();

	return 0;
}
