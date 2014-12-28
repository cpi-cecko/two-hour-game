#include <string>
#include <fstream>
#include <iostream>

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


objLoader::objLoader(const string& fileName)
{
	string line;
	
	ifstream iFile;
	iFile.open(fileName.c_str());
	
	if(iFile.is_open())
	{
		while(iFile.good())
		{
			getline(iFile, line);
			
			// If vertex.
			if(line[0] == 'v' && line[1] == ' ')
			{
				float x, y, z;
				sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
				m_positions.push_back(vec3(x, y, z));
			}
			
			// If uv.
			if(line[0] == 'v' && line[1] == 't')
			{
				float x, y;
				sscanf(line.c_str(), "vt %f %f", &x, &y);
				m_uvs.push_back(vec2(x, y));
			}
			
			// If face.
			if(line[0] == 'f' && line[1] == ' ')
			{
				float vIn[3], uIn[3];
				sscanf(line.c_str(), "f %f/%f %f/%f %f/%f", &vIn[0], &uIn[0], &vIn[1], &uIn[1], &vIn[2], &uIn[2]);
				
				// Do tyk vqrno
				for(unsigned short timesLooped = 0; timesLooped < 3; timesLooped++)
				{
					posIndices.push_back(vIn[timesLooped]);
				}
					
				for(unsigned short timesLooped = 0; timesLooped < 3; timesLooped++)
				{
					uvIndices.push_back(uIn[timesLooped]);
				}
			}
		}
		
		for(unsigned int timesLooped = 0; timesLooped < posIndices.size(); timesLooped++)
		{
			expVertices.push_back(vertex(m_positions[posIndices[timesLooped] - 1], m_uvs[uvIndices[timesLooped] - 1]));
		}
	}
	
	else
	{
		cout << "Could not open " << fileName << endl;
	}
	
	iFile.close();
}
