#include <kma/kma.hpp>
#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "color_types.hpp"

struct face
{
	int a;
	int b;
	int c;

	unsigned int FaceColor;
};

static std::vector<unsigned int> ColorRange
{
  WHITE
, BLACK
, RED
, GREEN
, BLUE
, YELLOW
, GRAY
, PINK
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
