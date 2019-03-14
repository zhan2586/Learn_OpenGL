#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
};

class Mesh {
public:
	// mesh data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	// function
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->glad_glBindTexture = textures;

		setupMesh();
	}
	void Draw(Shader shader);
private:
	// render data
	GLuint VAO, VBO, EBO;
	// function
	void setupMesh();
};

#endif