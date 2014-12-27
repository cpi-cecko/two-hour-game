#ifndef MESH_CPP_INCLUDED
#define MESH_CPP_INCLUDED

#include <GL/glew.h>

#include "mesh.h"

// VERTEX CLASS

// Constructor.
vertex::vertex(const vec3& position)
{
	m_position = position;
}

// Access functions.
vec3 vertex::getPosition() const
{
	return m_position;
}

// MESH CLASS

// Manually create a mesh from given vertices.
mesh::mesh(vertex* vertices, const unsigned int& numVertices)
{
	m_drawCount = numVertices;
	
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	
	glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);
	
	// Position buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
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
