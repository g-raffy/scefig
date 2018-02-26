/*
 * asymptoterenderer.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: graffy
 */

#include <iostream>
#include "asymptoterenderer.hpp"
#include <sstream>
#include <fstream>
#include "geom.hpp"
namespace scefig
{

	static std::string toAsymptoteString(const scefig::Vector3 & v)
	{
		std::stringstream s;
		s << "(";
		for ( int i = 0; i < v.size(); i++ )
		{
			s << v[i];
			if (i == (v.size()-1))
			{
				s << ")";
			}
			else
			{
				s << ",";
			}
		}
		return s.str();
	}

	static void drawLine(std::ofstream & file, float x1, float y1, float z1, float x2, float y2, float z2)
	{
		file << "draw(" << toAsymptoteString(Vector3(x1,y1,z1)) << "--" << toAsymptoteString(Vector3(x2,y2,z2)) << ", black);\n";
	}

	static void drawPolyLine(std::ofstream & file, const scefig::PolyLine & polyLine)
	{
		int numSegments = polyLine.getVertices().size();
		if ( ! polyLine.isClosed() )
		{
			numSegments -= 1;
		}
		for( int iSegment = 0; iSegment < numSegments; ++ iSegment)
		{
			const Vector3 & v1 = polyLine.getVertices()[iSegment];
			const Vector3 & v2 = polyLine.getVertices()[(iSegment + 1) % numSegments];
			file << "draw(" << toAsymptoteString(v1) << "--" << toAsymptoteString(v2) << ", blue);\n";
		}
	}


	class ShapeExporter : public scefig::Scene3D::IShapeVisitor
	{
	public:
		ShapeExporter(std::ofstream & file, const AxisAlignedBoundingBox & sceneAabb)
		: scefig::Scene3D::IShapeVisitor()
		, m_file(file)
		, m_sceneAabb(sceneAabb)
		{

		}

		virtual ~ShapeExporter()
		{

		}

		virtual void visitPoint( const Scene3D::PointShape & point)
		{
			m_file << "dot(";
			m_file << "\"$" << point.getLabel() << "$\"";
			m_file << ", " << toAsymptoteString(point.getPosition());
			m_file << ", S, red);\n";
		}

		virtual void visitPolyLine( const Scene3D::PolyLineShape & polyLine)
		{
			drawPolyLine( m_file, polyLine.getPolyLine() );
		}

		virtual void visitPlane( const Scene3D::PlaneShape & plane)
		{
			scefig::PolyLine polyLine;
			scefig::Geom::cropPlaneByAabb(plane.getPlane(), m_sceneAabb, polyLine);
			drawPolyLine( m_file, polyLine );
		}

	protected:
		std::ofstream & m_file;
		AxisAlignedBoundingBox m_sceneAabb;
	};

	void AsymptoteRenderer::renderDummyScene(std::ofstream & f) const
	{
		f << "// Draw blue rectangle\n";
		f << "path3 rect1=(0.5,0.5,2)--(1.5,0.5,2)--(1.5,1.5,2)--(0.5,1.5,2)--cycle;\n";
		f << "draw(rect1,blue);\n";
		f << "\n";
		f << "// Construct projection and draw red rectangle\n";
		f << "// XYplane is defined in three library\n";
		f << "transform3 proj=planeproject(Z);\n";
		f << "path3 proj=proj*rect1;\n";
		f << "draw(proj,red);\n";
	}

	void AsymptoteRenderer::renderAabb(const AxisAlignedBoundingBox & aaBB, std::ofstream & f) const
	{
		const Vector3 & min = aaBB.getMin();
		const Vector3 & max = aaBB.getMax();
		drawLine(f, min[0], min[1], min[2], min[0], min[1], max[2]);
		drawLine(f, min[0], max[1], min[2], min[0], max[1], max[2]);
		drawLine(f, max[0], min[1], min[2], max[0], min[1], max[2]);
		drawLine(f, max[0], max[1], min[2], max[0], max[1], max[2]);

		drawLine(f, min[0], min[1], min[2], min[0], max[1], min[2]);
		drawLine(f, min[0], min[1], max[2], min[0], max[1], max[2]);
		drawLine(f, max[0], min[1], min[2], max[0], max[1], min[2]);
		drawLine(f, max[0], min[1], max[2], max[0], max[1], max[2]);

		drawLine(f, min[0], min[1], min[2], max[0], min[1], min[2]);
		drawLine(f, min[0], min[1], max[2], max[0], min[1], max[2]);
		drawLine(f, min[0], max[1], min[2], max[0], max[1], min[2]);
		drawLine(f, min[0], max[1], max[2], max[0], max[1], max[2]);
	}

	void AsymptoteRenderer::renderScene(const scefig::Scene3D & scene, const std::string & filename )
	{
		std::ofstream file(filename);

		file << "import graph3;\n";
		file << "import three;\n";
		file << "settings.outformat=\"pdf\";\n";
		file << "\n";
		file << "currentprojection=orthographic(1,-2,0.5);\n";
		file << "limits((-4,-4,-0.2),(4,4,3.5));\n";
		file << "size3(8cm,8cm,4cm);\n";
		file << "\n";
		file << "// Draw axis\n";
		file << "xaxis3(\"$x$\",Arrow3);\n";
		file << "yaxis3(\"$y$\",Arrow3);\n";
		file << "zaxis3(\"$z$\",Arrow3);\n";
		file << "\n";

		scefig::AxisAlignedBoundingBox sceneAabb(Vector3(-1.0, -1.0, -1.0), Vector3(1.0, 1.0, 1.0));
		ShapeExporter shapeExporter(file, sceneAabb);
		renderAabb(sceneAabb, file);
		typedef std::vector<const scefig::Scene3D::Shape* > ShapeList;
		ShapeList shapes;
		scene.getShapes(shapes);
		for( ShapeList::const_iterator shapeIt = shapes.begin(); shapeIt != shapes.end(); ++shapeIt)
		{

			const scefig::Scene3D::Shape & shape = **shapeIt;
			// std::cout << "shape : " << shape.getLabel() << std::endl;
			shape.visit(shapeExporter);
		}
	}
		/*

		class AsymptoteRenderer(object):

			def renderScene( self, scene, filename ):
				with open(filename, 'w') as f:
					sceneAabb = Core.Aabb(numpy.array([-1.0, -1.0, -1.0]), numpy.array([1.0, 1.0, 1.0]))
					shapeVisitor = ShapeExporter(f, sceneAabb)
					f.write('import graph3;\n')
					f.write('import three;\n')
					f.write('settings.outformat="pdf";\n')
					f.write('\n')
					f.write('currentprojection=orthographic(1,-2,0.5);\n')
					f.write('limits((-4,-4,-0.2),(4,4,3.5));\n')
					f.write('size3(8cm,8cm,4cm);\n')
					f.write('\n')
					f.write('// Draw axis\n')
					f.write('xaxis3("$x$",Arrow3);\n')
					f.write('yaxis3("$y$",Arrow3);\n')
					f.write('zaxis3("$z$",Arrow3);\n')
					f.write('\n')
					self.renderAabb( sceneAabb, f )

					for shape in scene.shapes():
						shape.visit(shapeVisitor)



	*/
}



