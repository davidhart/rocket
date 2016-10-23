#pragma once
#ifndef ROCKET_RENDERQUEUE_INCLUDED
#define ROCKET_RENDERQUEUE_INCLUDED

#include "vectormath.h"

namespace Rocket
{
	class DrawBinding;
	class Material;
	class RenderTarget;

	struct ViewportRect
	{
		vec2 origin;
		vec2 size;
	};

	class RenderQueue
	{
	public:
		virtual ~RenderQueue();
		
		virtual void Draw(DrawBinding* drawBinding, Material* material) = 0;
		virtual const char* Name() const = 0;
		virtual int Priority() const = 0;

		virtual void SetEnabled(bool enabled) = 0;
		virtual bool IsEnabled() const = 0;

		virtual void SetClearColorEnabled(bool enabled) = 0;
		virtual bool IsClearColorEnabled() const = 0;
		virtual void SetClearColor(color color) = 0;

		virtual void SetClearDepthEnabled(bool enabled) = 0;
		virtual bool IsClearDepthEnabled() const = 0;
		virtual void SetClearDepth(float depth) = 0;

		virtual void SetDepthTestEnabled(bool enabled) = 0;
		virtual bool IsDepthTestEnabled() const = 0;

		virtual void SetTarget(RenderTarget* surface) = 0;
		virtual RenderTarget* GetTarget() = 0;

		virtual void SetViewport(const ViewportRect& viewport) = 0;
		virtual ViewportRect GetViewport() const = 0;

	protected:
		RenderQueue();

	private:
		RenderQueue(const RenderQueue&);
	};
}

#endif