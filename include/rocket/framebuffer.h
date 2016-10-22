#pragma once
#ifndef ROCKET_FRAMEBUFFER_INCLUDED
#define ROCKET_FRAMEBUFFER_INCLUDED

#include "texture.h"
#include "vectormath.h"

namespace Rocket
{

	struct FramebufferColorAttachmentDef
	{
		TextureFormat format;
		TextureSamplerDef2D sampler;
	};

	struct FramebufferDepthAttachmentDef
	{
		TextureFormat format;
		TextureSamplerDef2D sampler;
	};

	struct FramebufferDef
	{
		int width;
		int height;

		FramebufferColorAttachmentDef* colorAttachments;
		unsigned numColorAttachements;

		FramebufferDepthAttachmentDef* depthAttachement;
	};

	class Framebuffer
	{
	public:
		Framebuffer();
		virtual ~Framebuffer();

		virtual Texture2D* GetColorAttachment(int index) = 0;
		virtual Texture2D* GetDepthAttachment() = 0;
		virtual ivec2 GetSize() = 0;

	private:
		Framebuffer(const Framebuffer&);
	};
}

#endif