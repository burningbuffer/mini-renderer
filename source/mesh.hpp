#include <kma/kma.hpp>
#include <vector>

typedef struct
{
	int a;
	int b;
	int c;
} indices;

typedef struct
{
	kma::vec2 Points[3];
} triangle;

class Mesh
{
public:

	//std::vector<kma::vec3> vertices;
	//std::vector<std::vector<kma::vec3>> indices;

	std::vector<kma::vec3>  CubeVertices =
	{
		kma::vec3{-1, -1, -1 },
		kma::vec3{-1,  1, -1 },
		kma::vec3{ 1,  1, -1 },
		kma::vec3{ 1, -1, -1 },
		kma::vec3{ 1,  1,  1 },
		kma::vec3{ 1, -1,  1 },
		kma::vec3{-1,  1,  1 },
		kma::vec3{-1, -1,  1 }
	};

	std::vector<indices>  CubeIndices =
	{
		 indices{1, 2, 3 },
		 indices{1, 3, 4 },

		 indices{4, 3, 5 },
		 indices{4, 5, 6 },

		 indices{6, 5, 7 },
		 indices{6, 7, 8 },

		 indices{8, 7, 2 },
		 indices{8, 2, 1 },

		 indices{2, 7, 5 },
		 indices{2, 5, 3 },

		 indices{6, 8, 1 },
		 indices{6, 1, 4 }
	};

	kma::vec3 rotation{0.0f, 0.0f, 0.0f};


	Mesh();

	void LoadOBJ(const char * Path);

};
