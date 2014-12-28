#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class transform
{
	public:
		transform(const vec3& translation = vec3(), const vec3& rotation = vec3(), const vec3& scalation = vec3(1.0, 1.0, 1.0))
		{
			m_translation = translation;
			m_rotation = rotation;
			m_scalation = scalation;
			setMatrix();
			savedMatrix = getMatrix();
		}
		
		void setMatrix() 
		{
			mat4 transMatrix = translate(m_translation);
			mat4 rotatMatrixX = rotate(m_rotation.x, vec3(1.0, 0.0, 0.0));
			mat4 rotatMatrixY = rotate(m_rotation.y, vec3(0.0, 1.0, 0.0));
			mat4 rotatMatrixZ = rotate(m_rotation.z, vec3(0.0, 0.0, 1.0));
			mat4 rotatMatrix = rotatMatrixX * rotatMatrixY * rotatMatrixZ;
			mat4 scalaMatrix = scale(m_scalation);
			
			originalMatrix = transMatrix * rotatMatrix * scalaMatrix;
		}
		
		mat4 getMatrix() const
		{
			return originalMatrix;
		}
		
		// DAFUQ? should save matrix and then pop it... not working?
		void pushMatrix()
		{
			savedMatrix = originalMatrix;
		}
		
		void popMatrix()
		{
			originalMatrix = savedMatrix;
		}
		//
		
		void setTranslation(const vec3& trans)
		{
			m_translation = trans;
		}
		
		void setRotationX(const float& rot)
		{
			m_rotation.x = rot;
		}
		
		void setRotationY(const float& rot)
		{
			m_rotation.y = rot;
		}
		
		void setRotationZ(const float& rot)
		{
			m_rotation.z = rot;
		}
		
		void setScalation(const vec3& scla)
		{
			m_scalation = scla;
		}
		
	private:
		vec3 m_translation;
		vec3 m_rotation;
		vec3 m_scalation;
		mat4 originalMatrix;
		mat4 savedMatrix;
};

#endif
