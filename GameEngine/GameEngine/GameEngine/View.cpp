#include "View.h"

#include "imgui.h"

namespace View
{
	void RenderUI(int framebufferTexture) {
		ImGui::Begin("Scene");
		ImVec2 tamanio = ImGui::GetContentRegionAvail();
		ImGui::Image(
			(ImTextureID)(intptr_t)framebufferTexture, // 1. textura
			tamanio,                          // 2. tamaño en pantalla
			ImVec2(0, 1),                              // 3. uv0: esquina superior izquierda
			ImVec2(1, 0)                               // 4. uv1: esquina inferior derecha
		);

		ImGui::End(); 
	}
}