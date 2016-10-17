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
			GLRenderQueue(const char* name);

			virtual void Draw(DrawBinding* drawBinding, Material* material);
			virtual const char* Name() const;
			virtual void SetEnabled(bool enabled);
			virtual bool IsEnabled() const;

			void FlushQueue();

		private:
			struct QueueItem
			{
			public:
				DrawBinding* binding;
				Material* material;
			};

			std::string m_name;
			std::vector<QueueItem> m_drawQueue;
			bool m_enabled;
		};
	}
}

#endif