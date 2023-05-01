#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include "../ImGui/stb_implement.h"
#include "geometry_store/geom_store.h"
#include "menu_events.h"
#include "mouse_event_handler.h"

class app_window
{
private:
	GLFWwindow* window = nullptr;
	ImFont* imgui_font = nullptr;
	menu_events menu_click;
	// mouse_events mouse_click;
	mouse_event_handler mouse_Handler;
public:
	bool is_glwindow_success = false;
	static int window_width;
	static int window_height;
	static bool isWindowSizeChanging;
	const char* log = "";
	geom_store geom;

	// Constructor and Destructor
	app_window();
	~app_window();

	// Functions
	void app_render();
	void menu_events();
	static void framebufferSizeCallback(GLFWwindow* window, int window_width, int window_height);
	void GLFWwindow_set_icon(GLFWwindow* window);
};
