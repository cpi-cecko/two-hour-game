#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/glew.h>

#include <string>

using namespace std;

class texture
{
	public:
		texture(const string& fileName);
		void useTexture(unsigned short textureUnit);
		virtual ~texture();
	private:
		GLuint m_texture;
};

#endif
