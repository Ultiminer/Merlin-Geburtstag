#include "readxml.h"
#include "Application.h"


int main(int argc, char* argv[])
{
	MGE_PRINT("Beginning of Main Initialization...");
	Application* app= new Application(); app->Gameloop(); delete app;
	return 0;
}