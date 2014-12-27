#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

// Represents a vertex.
class vertex
{
	public:
		// Constructors.
		vertex(const vec3& position_arg);
		
		// Access functions.
		vec3 getPosition() const;
		
	private:
		vec3 m_position;
};

// Creates meshes.
class mesh
{
	public:
		// Constructors.
		mesh(vertex* vertices, const unsigned int& numVertices);
		
		// Destructors.
		virtual ~mesh();
		
		// Methods.
		void draw();
		
	private:
		enum
		{
			POSITION_VB,
			NUM_BUFFERS
		};
	
		GLuint m_vertexArrayObject;
		GLuint m_vertexBufferObjects[NUM_BUFFERS];
		unsigned int m_drawCount;
};

#endif 
