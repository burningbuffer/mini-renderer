#include <kma/kma.hpp>
#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>

struct face
{
	int a;
	int b;
	int c;
};

struct triangle
{
	kma::vec2 Points[3];

	bool isClockwise()
	{
		auto ax = Points[0].x - Points[1].x;
		auto ay = Points[0].y - Points[1].y;
		auto bx = Points[0].x - Points[2].x;
		auto by = Points[0].y - Points[2].y;
		auto order = ax * by - ay * bx;
		return order < 0;
	}

};

class Mesh
{
public:

	std::vector<kma::vec3> vertices;
	std::vector<face> indices;

	kma::vec3 rotation{0.0f, 0.0f, 0.0f};

	Mesh(const char* filename);
	void LoadOBJ(const char * Path);
	void PrintMeshContent();

};
