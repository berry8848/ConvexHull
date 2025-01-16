// QhullTest.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <iostream>
#include <string>
#include "StlFile.h"
#include "ConvexHull.h"

#include <libqhullcpp\Qhull.h>
#include <libqhullcpp\QhullError.h>

int main()
{
    // サンプルとして3次元空間の入力頂点を追加
    std::vector<float> m_input_vertexes = {
        1.0, 2.0, 3.0,  // Vertex 1 (x0, y0, z0)
        4.0, 5.0, 6.0,  // Vertex 2 (x1, y1, z1)
        7.0, 8.0, 9.0,  // Vertex 3 (x2, y2, z2)
        2.0, 3.0, 4.0,  // Vertex 4 (x3, y3, z3)
        5.0, 6.0, 7.0   // Vertex 5 (x4, y4, z4)
    };

	std::string outputFile = "C:/myFolder/ConvexHull/data/Output.stl";

	// if (argc < 1) {
	// 	std::cerr << "QhullTest INPUT_STL_FILE" << std::endl;
	// 	return 1;
	// }

	StlFile stl("C:/myFolder/ConvexHull/data/Nut.stl");

	ConvexHull convex;
	convex.setVertexes(stl.vertexes());
    // convex.setVertexes(m_input_vertexes);
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
	
    return 0;
}