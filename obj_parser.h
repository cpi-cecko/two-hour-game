#ifndef OBJ_PARSER_H_INCLUDED
#define OBJ_PARSER_H_INCLUDED

#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "mesh.h"

using namespace std;
using namespace glm;

class objLoader
{
	public:
		objLoader(const string& fileName);
		vector<vertex> getVertices() const
		{
			return expVertices;
		}
	private:
		vector<vec3> m_positions;
		vector<vec2> m_uvs;
		vector<unsigned int> posIndices;
		vector<unsigned int> uvIndices;
		vector<vertex> expVertices;
};

#endif
