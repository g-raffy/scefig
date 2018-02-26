/*
 * geom.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: graffy
 */
#include <iostream>
#include "geom.hpp"

namespace scefig
{

	void Geom::cropPlaneByAabb(const scefig::Plane & plane, const scefig::AxisAlignedBoundingBox & aabb, scefig::PolyLine & polyLine)
	{
		const Vector3 & planeNormal = plane.getNormal();

		int iMostSignifAxis;
		planeNormal.maxCoeff(&iMostSignifAxis); // argmax
		/*
			# if x is the most significant axis :
			# | x1 | = |  1  1  1 | | -b | / a
			# | x2 |   | -1  1  1 | | -c |
			# | x3 |   | -1 -1  1 | | -d |
			# | x4 |   |  1 -1  1 |

			# if y is the most significant axis :
			# | y1 | = |  1  1  1 | | -c | / b
			# | y2 |   | -1  1  1 | | -d |
			# | y3 |   | -1 -1  1 | | -a |
			# | y4 |   |  1 -1  1 |

			# if z is the most significant axis :
			# | z1 | = |  1  1  1 | | -d | / c
			# | z2 |   | -1  1  1 | | -a |
			# | z3 |   | -1 -1  1 | | -b |
			# | z4 |   |  1 -1  1 |
		*/
		// Y = X A
		//MatrixXf a(2,3); a << 1, 2, 3, 4, 5, 6;
		Eigen::MatrixXf	X(4,3);
		X <<  1.0, 1.0, 1.0,
		     -1.0, 1.0, 1.0,
			 -1.0,-1.0, 1.0,
			  1.0,-1.0, 1.0;
		Vector3 A;
		int j = (iMostSignifAxis + 1) % 4;
		for( int i = 0; i<3; ++i)
		{
			A[i] = plane.getParams()[j] / plane.getParams()[iMostSignifAxis];
			j = (j + 1) % 4;
		}
		Vector4 Y = X * A;
		//print(Y)
		for( int iVertex = 0 ; iVertex < 4; ++iVertex)
		{
			Vector3 vertex;
			vertex[iMostSignifAxis] = Y[iVertex];
			for(int iAxis = 0; iAxis < 2; ++iAxis)
			{
				vertex[(iMostSignifAxis+iAxis+1)%3] = X(iVertex,iAxis);
			}
			//print(vertex)
			polyLine.appendVertex(vertex);
		}
		/*
		#if iMostSignifAxis == 0:
			# ax +by +cz +d = 0
			# x = (-d -by -cz)/a
		#elif iMostSignifAxis == 1:
			# ax +by +cz +d = 0
			# y = (-d -ax -cz)/b

		#polyLine.appendVertex( numpy.array([1.0, 2.0, 3.0]) )
		#polyLine.appendVertex( numpy.array([2.0, 3.0, 0.0]) )
		#polyLine.appendVertex( numpy.array([4.0, 5.0, 6.0]) )
		*/
		polyLine.setClosedness(true);
	}

} /* namespace scefig */
