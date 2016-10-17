#pragma once
#ifndef ROCKET_RENDERQUEUE_INCLUDED
#define ROCKET_RENDERQUEUE_INCLUDED

namespace Rocket
{
	class DrawBinding;
	class Material;

	class RenderQueue
	{
	public:
		virtual ~RenderQueue();
		
		virtual void Draw(DrawBinding* drawBinding, Material* material) = 0;
		virtual const char* Name() const = 0;
		
		virtual void SetEnabled(bool enabled) = 0;
		virtual bool IsEnabled() const = 0;

	protected:
		RenderQueue();

	private:
		RenderQueue(const RenderQueue&);
	};
}

#endif