#include "Console.h"

#include "imgui.h"

namespace Console
{
	void RenderUI() {
		ImGui::Begin("Console");
		ImGui::Button("Hello");
		ImGui::End();
	}
}