#ifndef MESH_CPP_INCLUDED
#define MESH_CPP_INCLUDED

#include <GL/glew.h>

#include <string>
#include <vector>
#include <iostream>

#include "mesh.h"
#include "obj_parser.h"

using namespace std;

static void printVec3(const vec3& dsa)
{
	cout << dsa.x << " " << dsa.y << " " << dsa.z << endl;
}

static void printVec2(const vec2& dsa)
{
	cout << dsa.x << " " << dsa.y << endl;
}

// VERTEX CLASS

// Constructor.
vertex::vertex(const vec3& position, const vec2& uv_arg)
{
	m_position = position;
	m_uv = uv_arg;
}

// Access functions.
vec3 vertex::getPosition() const
{
	return m_position;
}

vec2 vertex::getUV() const
{
	return m_uv;
}

// MESH CLASS

// Manually create a mesh from given vertices.
mesh::mesh(vertex* vertices, const unsigned int& numVertices)
{
	m_drawCount = numVertices;
	
	vector<vec3> positions;
	vector<vec2> uvs;
	positions.reserve(numVertices);
	uvs.reserve(numVertices);
	
	for(unsigned int timesLooped = 0; timesLooped < numVertices; timesLooped++)
	{
		positions.push_back(vertices[timesLooped].getPosition());
		uvs.push_back(vertices[timesLooped].getUV());
	}
	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	
	glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);
	
	// Position buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// UV buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_UB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

// Create a mesh from a file.
mesh::mesh(const string& fileName)
{
	objLoader object(fileName);
	vector<vertex> vertices = object.getVertices();
	
	vector<vec3> positions;
	vector<vec2> uvs;
	
	for(unsigned int timesLooped = 0; timesLooped < vertices.size(); timesLooped++)
	{
		positions.push_back(vertices[timesLooped].getPosition());
		uvs.push_back(vertices[timesLooped].getUV());
	}
	
	m_drawCount = vertices.size();
	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	
	glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);
	
	// Position buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER,  m_drawCount * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// UV buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_UB]);
	glBufferData(GL_ARRAY_BUFFER, m_drawCount * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

// Draws the mesh using triangles.
void mesh::draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
}

// Destructor.
mesh::~mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

#endif
