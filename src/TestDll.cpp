#include <iostream>
#include <string>
#include "StlFile.h"
#include "ConvexHull.h"
#include "TestDll.h"

#include <libqhullcpp\Qhull.h>
#include <libqhullcpp\QhullError.h>

extern "C" EXPORT void TestDll()
{
	std::string outputFile = "C:/myFolder/ConvexHull/data/Output.stl";

	StlFile stl("C:/myFolder/ConvexHull/data/Nut.stl");

	ConvexHull convex;
	convex.setVertexes(stl.vertexes());
	try {
		convex.execute();
	}
	catch(orgQhull::QhullError &e){
		std::cerr << e.what() << std::endl;
	}

	StlFile outStl;
	outStl.setVertexes(convex.convexVertexes());
	outStl.setNormals(convex.convexNormals());
	outStl.write(outputFile.c_str());
}