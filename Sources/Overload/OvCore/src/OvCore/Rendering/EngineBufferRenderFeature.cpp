/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <OvRendering/Core/CompositeRenderer.h>

#include "OvCore/Rendering/EngineBufferRenderFeature.h"

OvCore::Rendering::EngineBufferRenderFeature::EngineBufferRenderFeature(OvRendering::Core::CompositeRenderer& p_renderer)
	: ARenderFeature(p_renderer)
{
	m_engineBuffer = std::make_unique<OvRendering::Buffers::UniformBuffer>(
		/* UBO Data Layout */
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FVector3) +
		sizeof(float) +
		sizeof(OvMaths::FMatrix4),
		0, 0,
		OvRendering::Buffers::EAccessSpecifier::STREAM_DRAW
	);

	m_startTime = std::chrono::high_resolution_clock::now();
}

void OvCore::Rendering::EngineBufferRenderFeature::OnBeginFrame(const OvRendering::Data::FrameDescriptor& p_frameDescriptor)
{
	OVASSERT(m_renderer.HasDescriptor<EngineBufferDescriptor>(), "Cannot find EngineBufferDescriptor attached to this renderer");

	auto& descriptor = m_renderer.GetDescriptor<EngineBufferDescriptor>();

	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - m_startTime);

	size_t offset = sizeof(OvMaths::FMatrix4);
	m_engineBuffer->SetSubData(OvMaths::FMatrix4::Transpose(descriptor.camera.GetViewMatrix()), std::ref(offset));
	m_engineBuffer->SetSubData(OvMaths::FMatrix4::Transpose(descriptor.camera.GetProjectionMatrix()), std::ref(offset));
	m_engineBuffer->SetSubData(descriptor.camera.GetPosition(), std::ref(offset));
	m_engineBuffer->SetSubData(elapsedTime.count(), std::ref(offset));
	m_engineBuffer->Bind(0);
}

void OvCore::Rendering::EngineBufferRenderFeature::OnEndFrame()
{
	m_engineBuffer->Unbind();
}

void OvCore::Rendering::EngineBufferRenderFeature::OnBeforeDraw(const OvRendering::Entities::Drawable& p_drawable)
{
	m_engineBuffer->SetSubData(OvMaths::FMatrix4::Transpose(p_drawable.modelMatrix), 0);
	m_engineBuffer->SetSubData
	(
		p_drawable.userMatrix,

		// UBO layout offset
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FMatrix4) +
		sizeof(OvMaths::FVector3) +
		sizeof(float)
	);
}
