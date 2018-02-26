/*
 * geom.hpp
 *
 *  Created on: Feb 26, 2018
 *      Author: graffy
 */

#ifndef GEOM_HPP_
#define GEOM_HPP_

#include "plane.hpp"
#include "types.hpp"
#include "polyline.hpp"

namespace scefig {

class Geom {
public:
	static void cropPlaneByAabb(const scefig::Plane & plane, const scefig::AxisAlignedBoundingBox & aabb, scefig::PolyLine & polyLine);

};

} /* namespace scefig */

#endif /* GEOM_HPP_ */
