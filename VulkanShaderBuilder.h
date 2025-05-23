/******************************************************************************
This file is part of the Newcastle Vulkan Tutorial Series

Author:Rich Davison
Contact:richgdavison@gmail.com
License: MIT (see LICENSE file at the top of the source tree)
*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../NCLCoreClasses/Shader.h"
#include "SmartTypes.h"

namespace NCL::Rendering::Vulkan {
	class DescriptorSetLayoutBuilder;
	class VulkanShader;
	/*
	ShaderBuilder: 
	*/
	class ShaderBuilder {
	public:
		ShaderBuilder(vk::Device m_device) { m_sourceDevice = m_device; };
		~ShaderBuilder()	{};

		ShaderBuilder& WithMeshBinary(const std::string& name, const std::string& entry = "main");

		ShaderBuilder& WithVertexBinary(const std::string& name, const std::string& entry = "main");
		ShaderBuilder& WithFragmentBinary(const std::string& name, const std::string& entry = "main");
		ShaderBuilder& WithGeometryBinary(const std::string& name, const std::string& entry = "main");
		ShaderBuilder& WithTessControlBinary(const std::string& name, const std::string& entry = "main");
		ShaderBuilder& WithTessEvalBinary(const std::string& name, const std::string& entry = "main");

		ShaderBuilder& AddBinary(ShaderStages::Type stage, const std::string& name, const std::string& entry = "main");

		UniqueVulkanShader Build(const std::string& debugName = "");
	protected:
		std::string m_shaderFiles[ShaderStages::MAX_SIZE];
		std::string m_entryPoints[ShaderStages::MAX_SIZE];
		vk::Device	m_sourceDevice;
	};
}