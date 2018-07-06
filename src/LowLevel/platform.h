#pragma once
#if defined(__MINGW32__)
#ifdef __clang__
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(_MSC_VER)
#define GLFW_EXPOSE_NATIVE_WIN32
#endif		// end of mingw32
#elif defined(WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3native.h>

namespace wnd
{

#ifdef GLFW_EXPOSE_NATIVE_WIN32
	struct native_interface
	{
		using handle_t = HWND;
		
		handle_t get_window_handle(GLFWwindow* window) const
		{
			return glfwGetWin32Window(window);
		}
	};
	
#elif defined(GLFW_EXPOSE_NATIVE_X11)
	struct native_interface
	{
		using handle_t = Window;
		
		handle_t get_window_handle(GLFWwindow* window) const
		{
			return glfwGetX11Window(window);
		}
	};
#endif
	
}
