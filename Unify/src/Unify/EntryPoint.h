#pragma once

#ifdef UN_PLATFORM_WINDOWS

extern Unify::Application* Unify::CreateApplication();

int main(int argc, char** argv) {

	Unify::Log::Init();
	UN_CORE_WARN("Initialized Log!");
	UN_INFO("Hello Unify!");

	auto app = Unify::CreateApplication();
	app->Run();
	delete app;

}

#endif