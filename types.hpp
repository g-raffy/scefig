/*
 * types.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: graffy
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <Eigen/Dense>
namespace scefig
{
	/*
	class Vector3f
	{

	};
	*/

	typedef Eigen::Vector3f Vector3;
	typedef Eigen::Vector4f Vector4;

	class AxisAlignedBoundingBox
	{
	public:
		AxisAlignedBoundingBox(const Vector3 & min, const Vector3 & max)
		: m_min(min)
		, m_max(max)
		{

		}
		const Vector3 & getMin(void) const {return m_min;}
		const Vector3 & getMax(void) const {return m_max;}
	protected:
		Vector3 m_min;
		Vector3 m_max;
	};
}



#endif /* TYPES_HPP_ */
