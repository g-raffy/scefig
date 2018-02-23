#include "polyline.hpp"

namespace scefig
{
	PolyLine::PolyLine(void)
	: m_isClosed(false)
	{

	}

	void PolyLine::appendVertex(const Vector3 & vertex)
	{
		m_vertices.push_back(vertex);
	}

	bool PolyLine::isClosed(void) const
	{
		return m_isClosed;
	}

	void PolyLine::setClosedness(bool closedness)
	{
		m_isClosed = closedness;
	}
}



