#pragma once

#ifdef UN_PLATFORM_WINDOWS

extern Unify::Application* Unify::CreateApplication();

int main(int argc, char** argv) {

	auto app = Unify::CreateApplication();
	app->Run();
	delete app;

}

#endif