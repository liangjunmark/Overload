/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvUI/Widgets/Buttons/ButtonImage.h"
#include "OvUI/Internal/Converter.h"
#include "OvUI/ImGui/imgui_internal.h"

OvUI::Widgets::Buttons::ButtonImage::ButtonImage(uint32_t p_textureID, const OvMaths::FVector2 & p_size) :
	textureID{ p_textureID }, size(p_size)
{
}

void OvUI::Widgets::Buttons::ButtonImage::_Draw_Impl()
{
	ImVec4 bg = Internal::Converter::ToImVec4(background);
	ImVec4 tn = Internal::Converter::ToImVec4(tint);

	ImGui::BeginDisabled(disabled);
	if (ImGui::ImageButton(textureID.raw, Internal::Converter::ToImVec2(size), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f), -1, bg, tn))
		ClickedEvent.Invoke();
	ImGui::EndDisabled();
}
