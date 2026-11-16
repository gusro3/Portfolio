#include "Elements.h"

#include "imgui.h"

namespace Elements
{
	void RenderUI() {
		ImGui::Begin("Console");
		ImGui::Button("Hello");
		ImGui::End();
	}
}