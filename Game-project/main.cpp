//  main.cpp
//  GameProject
//
//  Aatina and Roys project :D
//

#include <iostream>
#include <vector>
#include <memory>

#include "SDL.h"
#include "SDL_opengl.h"
#include "Dependancies/imgui/imgui.h"
#include "Dependancies/imgui/imgui_impl_sdl.h"

#include "WindowManager.h"
#include "World.h"
#include "EventManager.h"
#include "PhysicsEngine.h"
#include "RenderingEngine.h"
#include "Algorithms/PathFinding.h" // TEMPORARY
#include "Utility/FileHelper.h" // TEMPORARY
#include "LevelManager.h" // TEMPORARY

#include "Entities/Character.h"

using namespace game;
using namespace entities;
using namespace algorithms; // TEMPORARY
using namespace utilities; // TEMPORARY

const int fps = 40;
const int minframetime = 1000 / fps;

int main(int argc, char * argv[]) {

	// Setup window
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//SDL_DisplayMode current;
	//SDL_GetCurrentDisplayMode(0, &current);

	std::shared_ptr<WindowManager> windowManager(new WindowManager());
	if (!windowManager->init()) {
		std::cout << "Failed to initialize!" << std::endl;
		return EXIT_FAILURE;
	}

	// Setup ImGui binding
	ImGui_ImplSdlGL2_Init(windowManager->window);

	// Manages all the entities
	std::shared_ptr<game::World> world(new World());

	// Call setup on all entities
	world->setup();

	// TEMPORARY
	std::shared_ptr<PathFinding> pathFinding(new PathFinding());

	if (FileHelper::fileExists("navMesh.txt")) {
		// Use the previously made nav mesh
		std::vector<std::vector<char>> navMesh;
		FileHelper::readDataFromFile(navMesh, "navMesh.txt");

		pathFinding->setCurrentNavMesh(navMesh);

		// Calculate the resolution by comparing the level dimensions with the matrix
		// Mat.size = Level::width / resolution.x -> resolution.x = Level::width / Mat.size 
		int resolution = LevelManager::DIMENSIONS.w / (int)navMesh.size();
		pathFinding->setResolution(resolution);
	}
	else {
		// Create the nav mesh
		pathFinding->setResolution(Character::movementSpeed);
		std::vector<std::vector<char>> navMesh = pathFinding->createNavMesh();
		pathFinding->setCurrentNavMesh(navMesh);

		// Save nav mesh to file
		FileHelper::writeDataToFile(navMesh, "navMesh.txt");
	}

	// Handles any event that occurs in app
	SDL_Event window_event;
	std::unique_ptr<EventManager> eventManager(new EventManager(world));

	// Physics engine is responsible for detecting and reacting to collisions
	std::unique_ptr<PhysicsEngine> physicsEngine(new PhysicsEngine(world));

	// Rendering engine is responsible for drawing appropriate entities to screen
	std::unique_ptr<RenderingEngine> renderingEngine(new RenderingEngine(world));
	
	unsigned int frametime;

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 144, 154);

    while (true) {
		frametime = SDL_GetTicks();

#pragma message("Maybe pass in some delta time into these update functions? like how unity does it")
#pragma message("Double check update() order")
		// Handle inputs
#ifdef DEBUG_TIME
		auto t1 = Clock::now();
#endif
		eventManager->update(&window_event);

		//ImGui_ImplSdlGL2_NewFrame(windowManager->window);
		//// 1. Show a simple window
		//// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		//{
		//	static float f = 0.0f;
		//	ImGui::Text("Hello, world!");
		//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//	ImGui::ColorEdit3("clear color", (float*)&clear_color);
		//	if (ImGui::Button("Test Window")) show_test_window ^= 1;
		//	if (ImGui::Button("Another Window")) show_another_window ^= 1;
		//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//}

#ifdef DEBUG_TIME
		auto t2 = Clock::now();
		std::cout << "Event Manager Update: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
			<< " milliseconds" << std::endl;
#endif;
		// 2. Show another simple window, this time using an explicit Begin/End pair
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			ImGui::End();
		}

#ifdef DEBUG_TIME
		auto t3 = Clock::now();
#endif;

		// Logic
		world->update();

#ifdef DEBUG_TIME
		auto t4 = Clock::now();
		std::cout << "World Update: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count()
			<< " milliseconds" << std::endl;
#endif;

		// Physics Engine
		physicsEngine->update();

#ifdef DEBUG_TIME
		auto t5 = Clock::now();
		std::cout << "Physics Engine Update: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4).count()
			<< " milliseconds" << std::endl;
#endif;
		// Render
		renderingEngine->update();

#ifdef DEBUG_TIME
		auto t6 = Clock::now();
		std::cout << "Rendering Engine Update: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count()
			<< " milliseconds" << std::endl;

		std::cout << "Total frame time: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t1).count()
			<< " milliseconds" << std::endl;
			//<< 1 / std::chrono::duration_cast<std::chrono::seconds>(t6 - t1).count()
			//<< " FPS";

#endif;

		// Rendering
		//glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		//glClear(GL_COLOR_BUFFER_BIT);
		////glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		//ImGui::Render();
		//SDL_GL_SwapWindow(windowManager->window);

		// Wait until the next frame
		// This ensures the game runs at the same
		// speed on all computers
		if (SDL_GetTicks() - frametime < minframetime) {
			SDL_Delay(minframetime - (SDL_GetTicks() - frametime));
		}
    }
    
	// Delete renderer, window
	windowManager->close();
    
    return EXIT_SUCCESS;
}
