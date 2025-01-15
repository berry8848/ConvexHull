#pragma once
#include <string>
#include <vector>

class StlFile
{
private:
	
	std::vector<float> m_vertexes;
	std::vector<float> m_normals;

public:
	StlFile();
	StlFile(const std::string& filename);
	~StlFile();

	const std::vector<float>& vertexes() const { return m_vertexes; }
	const std::vector<float>& normals() const { return m_normals; }
	void setVertexes(const std::vector<float>& vertexes) { m_vertexes = vertexes; }
	void setNormals(const std::vector<float>& normals) { m_normals = normals; }
	size_t polygonCount() const { return m_normals.size() / 3; }

	void read(const std::string& filename);
	void write(const std::string& filename);

};

