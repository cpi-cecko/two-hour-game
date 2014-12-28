#ifndef PERSPECTIVE_H_INCLUDED
#define PERSPECTIVE_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class camera
{
	public:
		camera(const vec3& pos, const vec3& forward, const vec3& up, const float& fov, const float& asp, const float& near, const float& far)
		{
			m_pos = pos;
			m_forward = forward;
			m_up = up;
			m_projection = glm::perspective(fov, asp, near, far);
		}
		
		mat4 getPerspective() const
		{
			return m_projection * lookAt(m_pos, m_pos + m_forward, m_up);
		}
		
	private:
		mat4 m_projection;
		vec3 m_pos;
		vec3 m_forward;
		vec3 m_up;
};

#endif
