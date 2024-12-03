#include <Unify.h>

class Editor : public Unify::Application {
public:
	Editor() = default;
	~Editor() = default;
};

Unify::Application* Unify::CreateApplication() {
	return new Editor();
}