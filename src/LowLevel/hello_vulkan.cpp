#include "window.h"

int main(void)
{
	auto& app = application_t::get();
	auto window = app.create_window(800, 600, "hello");
	
	return 0;
}