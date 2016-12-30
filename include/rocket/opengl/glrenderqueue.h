#pragma once
#ifndef ROCKET_GLRENDERQUEUE_INCLUDED
#define ROCKET_GLRENDERQUEUE_INCLUDED

#include "renderqueue.h"
#include "opengl/glshaderglobals.h"
#include <string>
#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
        class GLShaderGlobals;
        
		class GLRenderQueue : public RenderQueue, public GLShaderOverride
		{
		public:
			GLRenderQueue(const char* name, int priority, RenderTarget* defaultTarget, GLShaderGlobals* globals);

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
			
			virtual void SetTarget(RenderTarget* target);
			virtual RenderTarget* GetTarget();

			virtual void SetViewport(const ViewportRect& viewport);
			virtual ViewportRect GetViewport() const;
            
            virtual void SetShaderFloat(const char* name, float value);
            virtual void SetShaderVec2(const char* name, const vec2& value);
            virtual void SetShaderVec3(const char* name, const vec3& value);
            virtual void SetShaderVec4(const char* name, const vec4& value);
            virtual void SetShaderMat4(const char* name, const mat4& value);
            virtual void SetShaderInt(const char* name, int value);
            virtual void SetShaderIVec2(const char* name, const ivec2& value);
            virtual void SetShaderIVec3(const char* name, const ivec3& value);
            virtual void SetShaderIVec4(const char* name, const ivec4& value);
            virtual void SetShaderTexture1D(const char* name, Texture1D* texture);
            virtual void SetShaderTexture2D(const char* name, Texture2D* texture);
            virtual void SetShaderTexture3D(const char* name, Texture3D* texture);
            
            virtual void SetShaderFloat(int propertyID, float value);
            virtual void SetShaderVec2(int propertyID, const vec2& value);
            virtual void SetShaderVec3(int propertyID, const vec3& value);
            virtual void SetShaderVec4(int propertyID, const vec4& value);
            virtual void SetShaderMat4(int propertyID, const mat4& value);
            virtual void SetShaderInt(int propertyID, int value);
            virtual void SetShaderIVec2(int propertyID, const ivec2& value);
            virtual void SetShaderIVec3(int propertyID, const ivec3& value);
            virtual void SetShaderIVec4(int propertyID, const ivec4& value);
            virtual void SetShaderTexture1D(int propertyID, Texture1D* texture);
            virtual void SetShaderTexture2D(int propertyID, Texture2D* texture);
            virtual void SetShaderTexture3D(int propertyID, Texture3D* texture);
            
            virtual void ClearShaderProperty(const char* name);
            virtual void ClearShaderProperty(int propertyID);
            
            virtual const GLShaderProperty* GetProperty(int propertyID) const;
            
			void FlushQueue();

		private:
            
            void SetProperty(int propertyID, GLShaderProperty& property);
            
			struct QueueItem
			{
			public:
				DrawBinding* binding;
				Material* material;
			};

            GLShaderGlobals* m_globals;
            
			std::string m_name;
			int m_priority;
			std::vector<QueueItem> m_drawQueue;
			bool m_enabled;

			bool m_clearColorEnabled;
			color m_clearColor;
			bool m_clearDepthEnabled;
			float m_clearDepth;
			bool m_depthTestEnabled;
			RenderTarget* m_target;
			
			ViewportRect m_viewport;
            
            std::vector<int> m_propertyIDs;
            std::vector<GLShaderProperty> m_properties;
		};
	}
}

#endif
