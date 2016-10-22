#pragma once
#ifndef ROCKET_GLRENDERQUEUE_INCLUDED
#define ROCKET_GLRENDERQUEUE_INCLUDED

#include "renderqueue.h"
#include <string>
#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
		class GLRenderQueue : public RenderQueue
		{
		public:
			GLRenderQueue(const char* name, int priority);

			virtual void Draw(DrawBinding* drawBinding, Material* material);
			virtual const char* Name() const;
			virtual int Priority() const;

			virtual void SetEnabled(bool enabled);
			virtual bool IsEnabled() const;

			virtual void SetClearColorEnabled(bool enabled);
			virtual bool IsClearColorEnabled() const;
			virtual void SetClearColor(color color);

			virtual void SetClearDepthEnabled(bool enabled);
			virtual bool IsClearDepthEnabled() const;
			virtual void SetClearDepth(float depth);

			virtual void SetDepthTestEnabled(bool enabled);
			virtual bool IsDepthTestEnabled() const;
			
			void FlushQueue();

		private:
			struct QueueItem
			{
			public:
				DrawBinding* binding;
				Material* material;
			};

			std::string m_name;
			int m_priority;
			std::vector<QueueItem> m_drawQueue;
			bool m_enabled;

			bool m_clearColorEnabled;
			color m_clearColor;
			bool m_clearDepthEnabled;
			float m_clearDepth;
			bool m_depthTestEnabled;
		};
	}
}

#endif