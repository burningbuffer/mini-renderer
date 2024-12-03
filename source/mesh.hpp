#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "common.hpp"

struct face
{
	int a;
	int b;
	int c;

	uint32 FaceColor;
};

static std::vector<uint32> ColorRange
{
	WHITE, 
	BLACK, 
	RED, 
	GREEN, 
	BLUE, 
	YELLOW, 
	GRAY, 
	PINK
};

class Mesh
{
public:

	std::vector<glm::vec3> mVertices;
	std::vector<face> mIndices;

	Mesh(const char* filename);
	void LoadOBJ(const char * Path);
	void PrintMeshContent();

};
