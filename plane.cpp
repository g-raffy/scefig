#include "plane.hpp"

namespace scefig
{
	Plane::Plane(float a, float b, float c, float d)
	: m_params(a, b, c, d)
	{
	}

	Plane::Plane(const Plane & other)
	: m_params(other.m_params)
	{

	}

	Vector3 Plane::getNormal(void) const
	{
		Vector3 normal = m_params.head(3);
		normal.normalize();
		return normal;
	}
}

/*
	 class Plane(object):
	def __init__(self, a, b, c, d):
		"""
			ax + by + cz + d = 0
		"""
		self.m_params = numpy.array([a, b, c, d])
	def getNormal(self):
		normal = self.m_params[0:-1]
		normal = normal / numpy.linalg.norm(normal)
		return normal
	 */

