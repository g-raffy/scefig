#ifndef ASYMPTOTERENDERER_HPP_
#define ASYMPTOTERENDERER_HPP_

#include <string>
#include "types.hpp"
#include "scene3d.hpp"
#include <fstream>
namespace scefig
{
	class AsymptoteRenderer
	{
	public:
		void renderDummyScene(std::ofstream & f) const;

		void renderAabb(const AxisAlignedBoundingBox & aaBB, std::ofstream & f) const;

		void renderScene(const scefig::Scene3D & scene, const std::string & filename );

	protected:
	};

}



#endif /* ASYMPTOTERENDERER_HPP_ */
