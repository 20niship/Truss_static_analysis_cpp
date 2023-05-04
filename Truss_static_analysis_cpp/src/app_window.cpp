#include "app_window.h"
#include "geometry_store/buffers/IndexBuffer.h"
#include "geometry_store/buffers/VertexArray.h"
#include "geometry_store/buffers/VertexBuffer.h"
#include "geometry_store/buffers/VertexBufferLayout.h"

int app_window::window_width = 800;
int app_window::window_height = 600;
bool app_window::isWindowSizeChanging = false;

app_window::app_window()
	:geom()
{
	// Main constructor
	// Initialize GLFW
	is_glwindow_success = false;
	if (!glfwInit()) {
		// ShowWindow(GetConsoleWindow(), SW_RESTORE);
		log = "Failed to initialize GLFW";
		// std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Create a window
	window = glfwCreateWindow(window_width, window_height, "Plane Truss Finite Element Solver", nullptr, nullptr);

	if (!window) {
		log = "Failed to create GLFW window";
		// std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		log = "Failed to initialize GLEW";
		// std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}

	//// Maximize the window
	//glfwMaximizeWindow(window);

	// Set viewport size and register framebuffer resize callback
	glfwGetFramebufferSize(window, &window_width, &window_height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	geom.updateWindowDimension(window_width, window_height);

	// Set the icon for the window
	GLFWwindow_set_icon(window);

	// Window initialize success
	is_glwindow_success = true;

	// Set the mouse button callback function with the user pointer pointing to the mouseHandler object
	glfwSetWindowUserPointer(window, &mouse_Handler);

	// Passing the address of geom and window dimensions 
	mouse_Handler.add_geometry_ptr(&geom, &window_width, &window_height);

	glfwSetMouseButtonCallback(window, mouse_event_handler::mouseButtonCallback);

	// Set the mouse move callback function with the user pointer pointing to the mouseHandler object
	glfwSetCursorPosCallback(window, mouse_event_handler::mouseMoveCallback);

	// Set the mouse scroll callback function with the user pointer pointing to the mouseHandler object
	glfwSetScrollCallback(window, mouse_event_handler::mouseScrollCallback);

	// Set key input callback function with the user pointer pointing to the mouseHandler object
	glfwSetKeyCallback(window, mouse_event_handler::keyDownCallback);


	// Setup ImGui context
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	framebufferSizeCallback(window, window_width, window_height);
}

app_window::~app_window()
{
	// Destructor
	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Terminate GLFW
	glfwTerminate();
}

void app_window::app_render()
{
	// Create a custom font for the menu bar
	ImGuiIO& io = ImGui::GetIO();
	imgui_font = io.Fonts->AddFontFromFileTTF("./Images/font/FreeSans.ttf", 18);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// menu events
		menu_events();

		// Render OpenGL graphics here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the clear color to black
		glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

		// Window size change event
		if (isWindowSizeChanging == true)
		{
			geom.updateWindowDimension(window_width, window_height);
			mouse_Handler.zoom_to_fit();
		}
		isWindowSizeChanging = false;

		// Paint the geometry
		geom.paint_geometry();


		// Render ImGui UI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}
}

void app_window::menu_events()
{
	// Control the menu events
	// Change the font for the menu bar
	ImGui::PushFont(imgui_font);

	// Create a menu bar
	if (ImGui::BeginMainMenuBar(), ImGuiWindowFlags_MenuBar)
	{
		// File menu item
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Import varai2D"))
			{
				// Handle menu Import varai2D
				menu_click.update_event(import_varai2d, geom);
				isWindowSizeChanging = true;
			}
			if (ImGui::MenuItem("Import raw data"))
			{
				// Handle menu Import raw data
				menu_click.update_event(import_raw_data, geom);
			}
			if (ImGui::MenuItem("Export raw data"))
			{
				// Handle menu Export raw data
				menu_click.update_event(export_raw_data, geom);
			}
			if (ImGui::MenuItem("Exit"))
			{
				// Handle menu Exit
				menu_click.update_event(exit_p, geom);
			}
			ImGui::EndMenu();
		}
		// Constraint menu item
		if (ImGui::BeginMenu("Constraints"))
		{
			// render your GUI
			ImGui::Begin("Demo window");
			ImGui::Button("Hello!");
			ImGui::End();

			//if (ImGui::MenuItem("Add Constraint"))
			//{
			//	// Handle menu Add constraint
			//	menu_click.update_event(Add_Constraint, geom);
			//}
			//if (ImGui::MenuItem("Delete Constraint"))
			//{
			//	// Handle menu Delete constraint
			//	menu_click.update_event(Delete_Constraint, geom);
			//}
			//if (ImGui::MenuItem("Edit Constraint"))
			//{
			//	// Handle menu Edit Constraint
			//	menu_click.update_event(Edit_Constraint, geom);
			//}
			ImGui::EndMenu();
		}
		// Load menu item
		if (ImGui::BeginMenu("Loads"))
		{
			if (ImGui::MenuItem("Add Load"))
			{
				// Handle menu Add Load
				menu_click.update_event(Add_Load, geom);
			}
			if (ImGui::MenuItem("Delete Load"))
			{
				// Handle menu Delete Load
				menu_click.update_event(Delete_Load, geom);
			}
			if (ImGui::MenuItem("Edit Load"))
			{
				// Handle menu Edit Load
				menu_click.update_event(Edit_Load, geom);
			}
			ImGui::EndMenu();
		}
		// Solve menu item
		if (ImGui::BeginMenu("Solve"))
		{
			if (ImGui::MenuItem("FE Solve"))
			{
				// Handle menu FE Solve
				menu_click.update_event(FE_Solve, geom);
			}
			if (ImGui::MenuItem("Displacement"))
			{
				// Handle menu Displacement
				menu_click.update_event(Displacement, geom);
			}
			if (ImGui::MenuItem("Member force"))
			{
				// Handle menu Member force
				menu_click.update_event(Member_force, geom);
			}
			ImGui::EndMenu();
		}
		// Add more menu items here as needed
		ImGui::EndMainMenuBar();
	}

	// Pop the custom font after using it
	ImGui::PopFont();
}

// Static callback function for framebuffer size changes
// static keyword makes the function a class-level function rather than an instance-level function
// allows it to be used as a callback function for the GLFW library
void app_window::framebufferSizeCallback(GLFWwindow* window, int window_width, int window_height)
{
	// Triggers when the openGL window is resized
	app_window::window_width = window_width;
	app_window::window_height = window_height;

	int max_dim = window_width > window_height ? window_width : window_height;
	int x_offset = (max_dim - window_width) / 2; // Calculate x offset to center the viewport
	int y_offset = (max_dim - window_height) / 2; // Calculate y offset to center the viewport

	// Set the viewport to the maximum dimension and center it at (0, 0)
	glViewport(-x_offset, -y_offset, max_dim, max_dim);

	isWindowSizeChanging = true;
	// glViewport(0, 0, max_size, max_size);
}

void app_window::GLFWwindow_set_icon(GLFWwindow* window)
{
	// Get the image
	stb_implement stb("./Images/innx_icon.png");

	// Set the window icon using GLFW's API for Windows
	GLFWimage icon;
	icon.width = stb.image_width;
	icon.height = stb.image_height;
	icon.pixels = stb.image;
	glfwSetWindowIcon(window, 1, &icon);

	// Image memory is released at the end
}
