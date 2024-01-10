#include "renderer.hpp"
#include <stdexcept>

int main(int argsc, char* argv[])
{
	Renderer renderer{};

	try
	{
		renderer.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
