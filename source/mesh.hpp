#include <kma/kma.hpp>
#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>

typedef struct
{
	int a;
	int b;
	int c;
} face;

typedef struct
{
	kma::vec2 Points[3];
} triangle;

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
