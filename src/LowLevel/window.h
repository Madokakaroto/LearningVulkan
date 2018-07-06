#pragma once
#include <GLFW/glfw3.h>
#include <algorithm>
#include <string>
#include <stdexcept>

#include "platform.h"

class window_t : protected wnd::native_interface
{
protected:
	friend class application_t;
	
	GLFWwindow* window_;
	window_t(GLFWwindow* window)
		: window_(window) {
	}

public:
	using native_handle_t = wnd::native_interface::handle_t;
	
	~window_t() noexcept
	{
		destroy();
	}
	
	window_t(window_t const&) = delete;
	window_t& operator=(window_t const&) = delete;
	
	window_t(window_t&& other) noexcept
	{
		swap(other);
	}
	
	window_t& operator=(window_t&& other) noexcept
	{
		swap(other);
		other.destroy();
		return *this;
	}
	
	native_handle_t get_native_handle() const
	{
		return this->get_window_handle(window_);
	}

private:
	void swap(window_t& other) noexcept
	{
		std::swap(window_, other.window_);
	}
	
	void destroy() noexcept
	{
		if(window_)
		{
			glfwDestroyWindow(window_);
			window_ = nullptr;
		}
	}
};

class managed_window_t : protected wnd::native_interface
{
	friend class application_t;

protected:
	GLFWwindow* window_;
	managed_window_t(GLFWwindow* window)
		: window_(window)
	{ }

public:
	using native_handle_t = wnd::native_interface::handle_t;
	
	managed_window_t(managed_window_t const&) = default;
	managed_window_t& operator=(managed_window_t const&) = default;
	managed_window_t(managed_window_t&&) = default;
	managed_window_t& operator=(managed_window_t&&) = default;
	
	native_handle_t get_native_handle() const
	{
		return this->get_window_handle(window_);
	}
};

class application_t
{
protected:
	application_t()
	{
		glfwInit();
		
		// we create vulkan API ourselves
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

public:
	~application_t()
	{
		glfwTerminate();
	}
	
	application_t(application_t const&) = delete;
	application_t& operator=(application_t const&) = delete;
	application_t(application_t&&) = delete;
	application_t& operator=(application_t&&) = delete;
	
	static application_t& get() noexcept
	{
		static application_t app{};
		return app;
	}
	
	window_t create_window(size_t w, size_t h, std::string name) const
	{
		return { create_window_impl(w, h, name) };
	}
	
	managed_window_t create_managed_window(size_t w, size_t h, std::string name) const
	{
		return { create_window_impl(w, h, name) };
	}

private:
	GLFWwindow* create_window_impl(size_t width, size_t height, std::string const& name) const
	{
		auto window = glfwCreateWindow(
			static_cast<int>(width),
			static_cast<int>(height),
			name.c_str(), nullptr, nullptr);
		
		if(nullptr == window)
			throw std::runtime_error{ "Failed to create window_t" };
		
		return window;
	}
};