#include "mesh.hpp"
#include <array>

//std::vector<unsigned int> ColorRange


Mesh::Mesh(const char* filename)
{
	srand((unsigned)time(NULL));


	LoadOBJ(filename);
}

void Mesh::LoadOBJ(const char* filename)
{
	std::ifstream Reader;

	Reader.open(filename);

	if (Reader.fail())
	{
		std::cerr << "failed to open " << filename << std::endl;
	}

	std::string line;
	glm::vec3 vertex;
	std::vector<int> inputFace;
	inputFace.resize(9);

	while (std::getline(Reader, line)) {
		if (line.size() >= 2) {
			std::string firstTwoChars = line.substr(0, 2);

			if (firstTwoChars == "v ")
			{
				auto res = sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				if (!res) break;
				vertex.y = -vertex.y;
				//std::cout << "vertex " << std::setprecision(6) << std::fixed <<  vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
				vertices.push_back(vertex);
			}

			if (firstTwoChars == "f ")
			{
				auto res2 = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &inputFace[0], &inputFace[1], &inputFace[2], &inputFace[3], &inputFace[4], &inputFace[5], &inputFace[6], &inputFace[7], &inputFace[8]);
				if (!res2) break;

				int random = 1 + (rand() % 7);

				face face_t;

				face_t.FaceColor = ColorRange[random];

				face_t.a = inputFace[0];
				face_t.b = inputFace[3];
				face_t.c = inputFace[6];
				indices.push_back(face_t);
			}


		}
	}

	Reader.close();

}

void Mesh::PrintMeshContent()
{

	std::cout << "=============VERTICES==============" << std::endl;
	for (auto i : vertices)
	{
		std::cout << "vertex " << std::setprecision(6) << std::fixed << i.x << " " << i.y << " " << i.z << "\n";
	}

}
