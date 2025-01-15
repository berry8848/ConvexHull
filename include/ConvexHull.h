#pragma once

#include <vector>

class ConvexHull
{
private:

	std::vector<float> m_input_vertexes;
	std::vector<float> m_convex_vertexes;
	std::vector<float> m_convex_normals;

public:
	ConvexHull();
	ConvexHull(const std::vector<float>& vertexes);
	~ConvexHull();

	const std::vector<float>& vertexes() const { return m_input_vertexes; }
	const std::vector<float>& convexVertexes() const { return m_convex_vertexes; }
	const std::vector<float>& convexNormals() const { return m_convex_normals; }
	void setVertexes(const std::vector<float>& vertexes) { m_input_vertexes = vertexes; }

	void execute();

private:
	void calcFaceNormal();

};

