#include <string>
#include <vector>

#include "scene3d.hpp"

namespace scefig
{

	// TransformNode

		void Scene3D::TransformNode::addShape(Shape* pShape)
		{
			m_shapes.push_back(pShape);
			pShape->setTransformNode(*this);
		}

		void Scene3D::TransformNode::addChildTransform(TransformNode* pChild)
		{
			m_children.push_back(pChild);
		}


		void Scene3D::TransformNode::getShapes(std::vector<Shape*> shapes) const
		{
			shapes.clear();
			for(std::vector<TransformNode*>::const_iterator childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
			{
				const TransformNode* pChildTransformNode = *childIt;
				const std::vector<Shape*> childShapes = pChildTransformNode->m_shapes;
				for(std::vector<Shape*>::const_iterator shapeIt = childShapes.begin(); shapeIt != childShapes.end(); ++shapeIt)
				{
					shapes.push_back(*shapeIt);
				}
			}
		}

	// Shape

		Scene3D::Shape::Shape(const LabelType & label, TransformNode * pTransformNode)
			: m_label(label)
			, m_pTransformNode(pTransformNode)
			{}

	// PointShape
		Scene3D::PointShape::PointShape(const LabelType & label, const Vector3 & values) : super(label), m_position(values) {}

		void Scene3D::PointShape::visit( IShapeVisitor & shapeVisitor)
		{
			shapeVisitor.visitPoint(*this);
		}

	// PolyLine

		Scene3D::PolyLineShape::PolyLineShape(const LabelType & label) : super(label), m_polyLine() {}
		void Scene3D::PolyLineShape::visit( IShapeVisitor & shapeVisitor)
		{
			shapeVisitor.visitPolyLine(*this);
		}

		void Scene3D::PolyLineShape::appendVertex(const Vector3 & vertex)
		{
			m_polyLine.appendVertex( vertex );
		}

		bool Scene3D::PolyLineShape::isClosed(void) const
		{
			return m_polyLine.isClosed();
		}

	// Line

		Scene3D::LineShape::LineShape(const LabelType & label, const Vector3 & fromPos, const Vector3 & toPos) : PolyLineShape(label)
		{
			m_polyLine.appendVertex( fromPos );
			m_polyLine.appendVertex( toPos );
		}

	// PlaneShape

		Scene3D::PlaneShape::PlaneShape(const LabelType & label, const Plane & plane)
		: Shape(label), m_plane(plane)
		{

		}

		void Scene3D::PlaneShape::visit( IShapeVisitor & shapeVisitor)
		{
			shapeVisitor.visitPlane(*this);
		}

		const Plane & Scene3D::PlaneShape::getPlane(void) const
		{
			return m_plane;
		}

		/*
		class Scene(object):

			def __init__(self):
				self.m_rootNode = TransformNode()

			def getRootNode(self):
				return self.m_rootNode

			# a generator that yields items instead of returning a list
			def shapes(self):
				return self.m_rootNode.shapes()


		 */

		//Point3D * createPoint(const LabelType & label, const Vector3f & values);

}
