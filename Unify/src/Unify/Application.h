#pragma once

#include "Core.h"

namespace Unify {

	class UNIFY_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
	};

	// Defined in client
	Application* CreateApplication();

}
