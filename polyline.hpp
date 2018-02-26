/*
 * polyline.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: graffy
 */

#ifndef POLYLINE_HPP_
#define POLYLINE_HPP_
#include <vector>
#include "types.hpp"

namespace scefig
{
	class PolyLine
	{
	public:
		PolyLine( void );

		void appendVertex(const Vector3 & vertex);
		const std::vector<Vector3> & getVertices(void) const {return m_vertices;}

		bool isClosed(void) const;

		void setClosedness(bool closedness);
	protected:
		std::vector<Vector3> m_vertices;
		bool m_isClosed;
	};
}



#endif /* POLYLINE_HPP_ */
