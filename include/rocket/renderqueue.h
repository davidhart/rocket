#pragma once
#ifndef ROCKET_RENDERQUEUE_INCLUDED
#define ROCKET_RENDERQUEUE_INCLUDED

#include "vectormath.h"

namespace Rocket
{
	class DrawBinding;
	class Material;
	class RenderTarget;
    class Texture1D;
    class Texture2D;
    class Texture3D;

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
        
        
        virtual void SetShaderFloat(const char* name, float value) = 0;
        virtual void SetShaderVec2(const char* name, const vec2& value) = 0;
        virtual void SetShaderVec3(const char* name, const vec3& value) = 0;
        virtual void SetShaderVec4(const char* name, const vec4& value) = 0;
        virtual void SetShaderMat4(const char* name, const mat4& value) = 0;
        virtual void SetShaderInt(const char* name, int value) = 0;
        virtual void SetShaderIVec2(const char* name, const ivec2& value) = 0;
        virtual void SetShaderIVec3(const char* name, const ivec3& value) = 0;
        virtual void SetShaderIVec4(const char* name, const ivec4& value) = 0;
        virtual void SetShaderTexture1D(const char* name, Texture1D* texture) = 0;
        virtual void SetShaderTexture2D(const char* name, Texture2D* texture) = 0;
        virtual void SetShaderTexture3D(const char* name, Texture3D* texture) = 0;
        
        virtual void SetShaderFloat(int propertyID, float value) = 0;
        virtual void SetShaderVec2(int propertyID, const vec2& value) = 0;
        virtual void SetShaderVec3(int propertyID, const vec3& value) = 0;
        virtual void SetShaderVec4(int propertyID, const vec4& value) = 0;
        virtual void SetShaderMat4(int propertyID, const mat4& value) = 0;
        virtual void SetShaderInt(int propertyID, int value) = 0;
        virtual void SetShaderIVec2(int propertyID, const ivec2& value) = 0;
        virtual void SetShaderIVec3(int propertyID, const ivec3& value) = 0;
        virtual void SetShaderIVec4(int propertyID, const ivec4& value) = 0;
        virtual void SetShaderTexture1D(int propertyID, Texture1D* texture) = 0;
        virtual void SetShaderTexture2D(int propertyID, Texture2D* texture) = 0;
        virtual void SetShaderTexture3D(int propertyID, Texture3D* texture) = 0;
        
        virtual void ClearShaderProperty(const char* name) = 0;
        virtual void ClearShaderProperty(int propertyID) = 0;

	protected:
		RenderQueue();

	private:
		RenderQueue(const RenderQueue&);
	};
}

#endif
