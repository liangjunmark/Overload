/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvRendering/Features/ARenderFeature.h"
#include "OvRendering/Core/ABaseRenderer.h"
#include "OvRendering/Core/CompositeRenderer.h"

OvRendering::Features::ARenderFeature::ARenderFeature(Core::CompositeRenderer& p_renderer)
	: m_renderer(p_renderer), m_driver(p_renderer.GetDriver())
{
}

OvRendering::Settings::ERenderPassMask OvRendering::Features::ARenderFeature::GetRenderPassMask() const
{
	return OvRendering::Settings::ERenderPassMask::NONE;
}

void OvRendering::Features::ARenderFeature::DrawPrePass(OvRendering::Settings::ERenderPass p_renderPass)
{
}

void OvRendering::Features::ARenderFeature::DrawPass(OvRendering::Settings::ERenderPass p_renderPass)
{
}

void OvRendering::Features::ARenderFeature::OnBeforeDraw(const Entities::Drawable& p_drawable)
{
}

void OvRendering::Features::ARenderFeature::OnAfterDraw(const Entities::Drawable& p_drawable)
{
}

void OvRendering::Features::ARenderFeature::OnBeginFrame(const Data::FrameDescriptor& p_frameDescriptor)
{
}

void OvRendering::Features::ARenderFeature::OnEndFrame()
{
}