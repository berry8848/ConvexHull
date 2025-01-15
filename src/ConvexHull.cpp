// #include "stdafx.h"
#include "ConvexHull.h"

#include <iostream>
#include <array>

#include <libqhullcpp\Qhull.h>
#include <libqhullcpp\PointCoordinates.h>
#include <libqhullcpp\QhullFacet.h>
#include <libqhullcpp\QhullFacetList.h>
#include <libqhullcpp\QhullVertexSet.h>


ConvexHull::ConvexHull()
{
}

ConvexHull::ConvexHull(const std::vector<float>& vertexes) {
	setVertexes(vertexes);
}


ConvexHull::~ConvexHull()
{
}

void ConvexHull::execute() {

	std::cout << "Start Convex hull" << std::endl;

	orgQhull::Qhull qhull;
	
	orgQhull::PointCoordinates points;
	
	points.setDimension(3);

	
	std::vector<coordT> allpoint;
	for (auto v : m_input_vertexes) {
		allpoint.push_back(v);
	}
	points.append( allpoint);
	
	qhull.runQhull(points.comment().c_str(), points.dimension(), points.count(), points.coordinates(), "Qt");
	
	orgQhull::QhullFacetList faceList = qhull.facetList();
	for (auto itr = faceList.begin(); itr != faceList.end(); itr++) {

		orgQhull::QhullVertexSet vset = (*itr).vertices();
		for (auto vitr = vset.begin(); vitr != vset.end(); vitr++) {
			orgQhull::QhullPoint p = (*vitr).point();
			double * coords = p.coordinates();
			m_convex_vertexes.push_back(coords[0]);
			m_convex_vertexes.push_back(coords[1]);
			m_convex_vertexes.push_back(coords[2]);
		}

	}

	calcFaceNormal();
	std::cout << "end convex hull" << std::endl;
}

void ConvexHull::calcFaceNormal() {
	for (size_t i = 0; i < m_convex_vertexes.size() / 9; i++) {

		std::array<float, 3> v0 = { m_convex_vertexes[i * 9 + 0], m_convex_vertexes[i * 9 + 1], m_convex_vertexes[i * 9 + 2] };
		std::array<float, 3> v1 = { m_convex_vertexes[i * 9 + 3], m_convex_vertexes[i * 9 + 4], m_convex_vertexes[i * 9 + 5] };
		std::array<float, 3> v2 = { m_convex_vertexes[i * 9 + 6], m_convex_vertexes[i * 9 + 7], m_convex_vertexes[i * 9 + 8] };
		std::array<float, 3> va = { v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2] };
		std::array<float, 3> vb = { v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2] };

		std::array<float, 3> normal;
		normal[0] = va[1] * vb[2] - va[2] * vb[1];
		normal[1] = va[2] * vb[0] - va[0] * vb[2];
		normal[2] = va[0] * vb[1] - va[1] * vb[0];

		float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
		for (int i = 0; i < normal.size(); i++) {
			normal[i] /= length;
		}
		m_convex_normals.push_back(normal[0]);
		m_convex_normals.push_back(normal[1]);
		m_convex_normals.push_back(normal[2]);
	}
}
