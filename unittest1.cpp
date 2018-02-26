#include "scene3d.hpp"
#include "polyline.hpp"
#include "plane.hpp"
#include "asymptoterenderer.hpp"

using scefig::Scene3D;
typedef scefig::Scene3D::PointShape PointShape;
typedef scefig::Scene3D::PolyLineShape PolyLineShape;
typedef scefig::Plane Plane;
typedef scefig::Scene3D::PlaneShape PlaneShape;
typedef scefig::Scene3D::TransformNode TransformNode;
using scefig::Vector3;

void makeFigure1(void)
{
	scefig::Scene3D scene;
	PointShape* pOrigin = new PointShape("Origin", Vector3(0.0, 0.0, 0.0));
	scene.getRootNode().addShape(pOrigin);

	PointShape* pP1 = new PointShape("P1", Vector3(1.0, 2.0, 3.0));
	TransformNode* pT1 = new TransformNode();
	pT1->addShape(pP1);
	scene.getRootNode().addChildTransform(pT1);

	PolyLineShape* pL1 = new PolyLineShape("dummyLine");
	pL1->appendVertex( Vector3(2.0, 3.0, 1.0) );
	pL1->appendVertex( Vector3(3.0, 1.0, 2.0) );
	TransformNode* pT2 = new TransformNode();
	pT2->addShape(pL1);
	scene.getRootNode().addChildTransform(pT2);

	PlaneShape* pPlane = new PlaneShape("dummyPlane", Plane(1.0, 0.9, 0.0, 0.0));
	TransformNode* pT3 = new TransformNode();
	pT3->addShape(pPlane);
	scene.getRootNode().addChildTransform(pT3);

	scefig::AsymptoteRenderer renderer;
	renderer.renderScene(scene, "Figure1.asy" );

}

int main(int argc, char* argv[])
{
	makeFigure1();
}
