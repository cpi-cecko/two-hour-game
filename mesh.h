#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

using namespace std;
using namespace glm;

// Represents a vertex.
class vertex
{
	public:
		// Constructors.
		vertex(const vec3& position_arg, const vec2& uv_arg);
		
		// Access functions.
		vec3 getPosition() const;
		vec2 getUV() const;
		
	private:
		vec3 m_position;
		vec2 m_uv;
};

// Creates meshes.
class mesh
{
	public:
		// Constructors.
		mesh(vertex* vertices, const unsigned int& numVertices);
		mesh(const string& fileName);
		
		// Destructors.
		virtual ~mesh();
		
		// Methods.
		void draw();
		
	private:
		enum
		{
			POSITION_VB,
			POSITION_UB,
			NUM_BUFFERS
		};
	
		GLuint m_vertexArrayObject;
		GLuint m_vertexBufferObjects[NUM_BUFFERS];
		unsigned int m_drawCount;
};

#endif 
