/******************************************************************************
This file is part of the Newcastle Vulkan Tutorial Series

Author:Rich Davison
Contact:richgdavison@gmail.com
License: MIT (see LICENSE file at the top of the source tree)
*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../VulkanRendering/VulkanRenderer.h"
#include "../VulkanRendering/VulkanPipelineBuilderBase.h"
#include "VulkanRTShader.h"

namespace NCL::Rendering::Vulkan {

	class VulkanRayTracingPipelineBuilder : 
		public PipelineBuilderBase< VulkanRayTracingPipelineBuilder, vk::RayTracingPipelineCreateInfoKHR> {
	public:
		VulkanRayTracingPipelineBuilder(vk::Device m_device);
		~VulkanRayTracingPipelineBuilder();

		VulkanRayTracingPipelineBuilder& WithShader(VulkanRTShader& shader, vk::ShaderStageFlagBits stage, const string& entry = "main");

		VulkanRayTracingPipelineBuilder& WithRayGenGroup(uint32_t shaderIndex);
		VulkanRayTracingPipelineBuilder& WithMissGroup(uint32_t shaderIndex);
		VulkanRayTracingPipelineBuilder& WithTriangleHitGroup(uint32_t closestHit = VK_SHADER_UNUSED_KHR, uint32_t anyHit = VK_SHADER_UNUSED_KHR);
		VulkanRayTracingPipelineBuilder& WithProceduralHitGroup(uint32_t intersection, uint32_t closestHit = VK_SHADER_UNUSED_KHR, uint32_t anyHit = VK_SHADER_UNUSED_KHR);

		VulkanRayTracingPipelineBuilder& WithRecursionDepth(uint32_t count);

		VulkanPipeline Build(const std::string& debugName = "", vk::PipelineCache cache = {});

	protected:
		struct ShaderEntry {
			std::string				entryPoint;
			VulkanRTShader*			shader;
			vk::ShaderStageFlagBits	stage;
		};

		std::vector<ShaderEntry>							m_entries;

		std::vector<vk::PipelineShaderStageCreateInfo>		m_shaderStages;

		std::vector<vk::RayTracingShaderGroupCreateInfoKHR> m_genGroups;
		std::vector<vk::RayTracingShaderGroupCreateInfoKHR> m_missGroups;
		std::vector<vk::RayTracingShaderGroupCreateInfoKHR> m_hitGroups;
		std::vector<vk::RayTracingShaderGroupCreateInfoKHR> m_allGroups;

		vk::PipelineDynamicStateCreateInfo					m_dynamicCreate;
	};
}