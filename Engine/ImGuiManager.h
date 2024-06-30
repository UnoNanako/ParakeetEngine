#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <memory>
#include "Externals/imgui/imgui.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"
#include "Externals/imgui/imgui_stdlib.h"
#include "Externals/magic_enum/magic_enum.hpp"

class WinApp;
class DirectXCommon;

class ImGuiManager {
public:
	void Initialize(std::shared_ptr<WinApp> winApp, std::shared_ptr<DirectXCommon> dxCommon);
	void Finalize();
	void Begin();
	void End();
	void Draw(std::shared_ptr<DirectXCommon> dxCommon);
};

template <class T>
bool Combo(const char* name, T& curr) {
	bool isChanged = false;
	if (ImGui::BeginCombo(name, magic_enum::enum_name(curr).data())) {
		for (size_t i = 0; i < magic_enum::enum_count<T>(); ++i) {
			bool isSelected = false;
			if (ImGui::Selectable(magic_enum::enum_name(T(i)).data(), isSelected)) {
				curr = T(i);
				isChanged = true;
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	return isChanged;
}
