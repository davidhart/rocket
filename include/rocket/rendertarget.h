#pragma once
#ifndef ROCKET_RENDERTARGET_INCLUDED
#define ROCKET_RENDERTARGET_INCLUDED

#include "texture.h"
#include "vectormath.h"

namespace Rocket
{

	struct RenderTargetColorAttachmentDef
	{
		TextureFormat format;
		TextureSamplerDef2D sampler;
	};

	struct RenderTargetDepthAttachmentDef
	{
		TextureFormat format;
		TextureSamplerDef2D sampler;
	};

	struct RenderTargetDef
	{
		int width;
		int height;

		RenderTargetColorAttachmentDef* colorAttachments;
		unsigned numColorAttachements;

		RenderTargetDepthAttachmentDef* depthAttachement;
	};
	
	class RenderTarget
	{
	public: 
		RenderTarget();
		virtual ~RenderTarget();
		virtual ivec2 GetSize() const = 0;

		virtual Texture2D* GetColorAttachment(int index) = 0;
		virtual Texture2D* GetDepthAttachment() = 0;

	private:
		RenderTarget(const RenderTarget&);
	};
}

#endif