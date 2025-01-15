// #include "stdafx.h"
#include "StlFile.h"
#include <iostream>
#include <fstream>

StlFile::StlFile()
{
}

StlFile::StlFile(const std::string& filename) {
	read(filename);
}


StlFile::~StlFile()
{
}

void StlFile::read(const std::string& filename) {
	std::ifstream fin;
	fin.open(filename.c_str(), std::ios::in | std::ios::binary);
	if (fin.fail()) {
		std::cerr << "can not open " << filename << std::endl;
		return;
	}

	size_t polygonCount = 0;
	fin.seekg(80, std::ios::cur);
	fin.read((char *)&polygonCount, 4);

	m_vertexes = std::vector<float>(polygonCount * 9);
	m_normals = std::vector<float>(polygonCount * 3);

	float* vertexes = m_vertexes.data();
	float* normals = m_normals.data();

	size_t index3 = 0;
	size_t index9 = 0;

	for (size_t i = 0; i < polygonCount; i++, index3 += 3, index9 += 9) {
		fin.read((char *)(normals + index3), 4 * 3);
		fin.read((char *)(vertexes + index9), 4 * 3 * 3);
		fin.seekg(2, std::ios::cur);
	}
	std::cout << "Stl file read complete" << std::endl;
	std::cout << "vertex num " << m_vertexes.size() / 3 << std::endl;
	std::cout << "face num " << m_normals.size() / 3 << std::endl;
}

void StlFile::write(const std::string& filename) {
	std::ofstream fout;
	fout.open(filename.c_str(), std::ios::out | std::ios::binary);
	if (fout.fail()) {
		std::cerr << "can not write " << filename << std::endl;
		return;
	}

	char header[80] = "create by shimomuuu";
	char span[2] = { 0, 0 };

	fout.write(header, 80);
	size_t count = polygonCount();
	fout.write((char*)&count, 4);

	float* vertexes = m_vertexes.data();
	float* normals = m_normals.data();
	
	size_t index3 = 0;
	size_t index9 = 0;
	for (size_t i = 0; i < polygonCount(); i++, index3 += 3, index9 += 9) {
		fout.write((char *)(normals + index3), 4 * 3);
		fout.write((char *)(vertexes + index9), 4 * 3 * 3);
		fout.write((char *)span, 2);
	}
	std::cout << "Stl file write complete" << std::endl;
}
