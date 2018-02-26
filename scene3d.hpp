/*
 * scene3d.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: graffy
 */

#ifndef SCENE3D_HPP_
#define SCENE3D_HPP_


#include <string>
#include <vector>
#include "types.hpp"
#include "polyline.hpp"
#include "plane.hpp"
#include "transform.hpp"

namespace scefig
{
	typedef std::string LabelType;

	class Scene3D
	{
	public:
		class Shape;
		class PointShape;
		class PolyLineShape;
		class PlaneShape;

		class IShapeVisitor
		{
		public:
			virtual void visitPoint( const PointShape & point) = 0;
			virtual void visitPolyLine( const PolyLineShape & polyLine) = 0;
			virtual void visitPlane( const PlaneShape & plane) = 0;
		};

		class TransformNode
		{
		public:
			TransformNode() : m_transform() {}

			void addShape(Shape* pShape);

			void addChildTransform(TransformNode* pChild);

			void getShapes(std::vector<const Shape*> & shapes) const;

		protected:
			Transform m_transform;
			std::vector<TransformNode*> m_children;
			std::vector<Shape*> m_shapes; ///< a transform node owns its shapes
		};

		class Shape
		{
		public:
			Shape(const LabelType & label, TransformNode * pTransformNode=0);

			const LabelType & getLabel(void) const {return m_label;}
			void setTransformNode(TransformNode & transformNode) { m_pTransformNode = &transformNode; }

			virtual void visit( IShapeVisitor & shapeVisitor) const = 0;
		private:
			LabelType m_label;
			TransformNode* m_pTransformNode;
		};

		class PointShape : public scefig::Scene3D::Shape
		{
		public:
			typedef scefig::Scene3D::Shape super;
			PointShape(const LabelType & label, const Vector3 & values);

			virtual void visit( IShapeVisitor & shapeVisitor) const;

			const Vector3 & getPosition(void) const {return m_position;}
		private:
			Vector3 m_position;
		};

		class PolyLineShape : public scefig::Scene3D::Shape
		{
		public:
			typedef scefig::Scene3D::Shape super;
			PolyLineShape(const LabelType & label);
			virtual void visit( IShapeVisitor & shapeVisitor) const;
			const scefig::PolyLine & getPolyLine(void) const {return m_polyLine;}

			void appendVertex(const Vector3 & vertex);

			bool isClosed(void) const;
		protected:
			scefig::PolyLine m_polyLine;
		};

		class LineShape : public PolyLineShape
		{
			LineShape(const LabelType & label, const Vector3 & fromPos, const Vector3 & toPos);
		};


		class PlaneShape : public Shape
		{
		public:
			PlaneShape(const LabelType & label, const Plane & plane);
			virtual void visit( IShapeVisitor & shapeVisitor) const;
			const Plane & getPlane(void) const;
		protected:
			Plane m_plane;
		};

		Scene3D(void) {}

		TransformNode & getRootNode(void) {return m_rootNode;}

		void getShapes(std::vector<const Shape*> & shapes) const { m_rootNode.getShapes(shapes); }

		//Point3D * createPoint(const LabelType & label, const Vector3f & values);
	protected:
		TransformNode m_rootNode;
	};

};


#endif /* SCENE3D_HPP_ */
