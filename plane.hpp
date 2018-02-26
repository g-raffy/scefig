/*
 * plane.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: graffy
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "types.hpp"

namespace scefig
{
	class Plane
	{
	public:
		/**
		 * ax + by + cz + d = 0
		 */
		Plane(float a, float b, float c, float d);

		Plane(const Plane & other);

		Vector3 getNormal(void) const;
		const Vector4 & getParams(void) const {return m_params;}
	protected:
		Vector4 m_params;
	};
}




#endif /* PLANE_HPP_ */
