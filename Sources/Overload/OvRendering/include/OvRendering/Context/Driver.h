/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "OvRendering/Settings/DriverSettings.h"
#include "OvRendering/Settings/ERenderingCapability.h"
#include "OvRendering/Settings/EPrimitiveMode.h"
#include "OvRendering/Settings/ERasterizationMode.h"
#include "OvRendering/Settings/EComparaisonAlgorithm.h"
#include "OvRendering/Settings/EOperation.h"
#include "OvRendering/Settings/ECullFace.h"
#include "OvRendering/Settings/ECullingOptions.h"
#include "OvRendering/Settings/EPixelDataFormat.h"
#include "OvRendering/Settings/EPixelDataType.h"
#include "OvRendering/Settings/EPipelineStateCreationMode.h"
#include "OvRendering/Data/PipelineState.h"

namespace OvRendering::Context
{
	/**
	* Handles the lifecycle of the underlying graphics context
	*/
	class Driver
	{
	public:
		/**
		* Creates the driver
		* @param p_driverSettings
		*/
		Driver(const Settings::DriverSettings& p_driverSettings);

		/**
		* Destroy the driver
		*/
		~Driver() = default;

		/**
		* Clear the screen using the previously defined clear color (With Renderer::SetClearColor()) or by
		* using the OpenGL default one.
		* @param p_colorBuffer
		* @param p_depthBuffer
		* @param p_stencilBuffer
		*/
		void Clear(bool p_colorBuffer = true, bool p_depthBuffer = true, bool p_stencilBuffer = true) const;

		/**
		 * Read a block of pixels from the frame buffer.
		 * @param x
		 * @param y
		 * @param width
		 * @param height
		 * @param format
		 * @param type
		 * @param data
		 */
		void ReadPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Settings::EPixelDataFormat format, Settings::EPixelDataType type, void* data) const;

		/**
		* Issue a draw call command (EBO) using the given primitive mode
		* @param p_primitiveMode
		* @param p_indexCount
		*/
		void DrawElements(Settings::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount) const;

		/**
		* Issue an instanced draw call (EBO) command using the given primitive mode
		* @param p_primitiveMode
		* @param p_indexCount
		* @param p_instances
		*/
		void DrawElementsInstanced(Settings::EPrimitiveMode p_primitiveMode, uint32_t p_indexCount, uint32_t p_instances) const;

		/**
		* Issue a draw call command (VBO) using the given primitive mode
		* @param p_primitiveMode
		* @param p_indexCount
		* @note Should be avoided, prefer using DrawElements
		*/
		void DrawArrays(Settings::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount) const;

		/**
		* Issue an instanced draw call (VBO) command using the given primitive mode
		* @param p_primitiveMode
		* @param p_vertexCount
		* @param p_instances
		* @note Should be avoided, prefer using DrawElements
		*/
		void DrawArraysInstanced(Settings::EPrimitiveMode p_primitiveMode, uint32_t p_vertexCount, uint32_t p_instances) const;

		/**
		* Set the pipeline state to match the given PSO
		* @param p_state
		*/
		void SetPipelineState(const Data::PipelineState& p_state);

		/**
		* Return the current pipeline state
		*/
		const Data::PipelineState& GetPipelineState() const;

		/**
		* Create a pipeline state object from the current pipeline state
		* @param p_creationMode (Define how the pipeline state object should be initialized)
		*/
		Data::PipelineState CreatePipelineState(OvRendering::Settings::EPipelineStateCreationMode p_creationMode) const;

		/**
		* Returns the vendor
		*/
		std::string_view GetVendor() const;

		/**
		* Returns details about the current rendering hardware
		*/
		std::string_view GetHardware() const;

		/**
		* Returns the current graphics API version
		*/
		std::string_view GetVersion() const;

		/**
		* Returns the current shading language version
		*/
		std::string_view GetShadingLanguageVersion() const;

	private:
		std::string m_vendor;
		std::string m_hardware;
		std::string m_version;
		std::string m_shadingLanguageVersion;

		Data::PipelineState m_initialState;
		Data::PipelineState m_pipelineState;
	};
}