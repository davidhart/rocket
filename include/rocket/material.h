#pragma once
#ifndef ROCKET_MATERIAL_INCLUDED
#define ROCKET_MATERIAL_INCLUDED

#include "vectormath.h"

namespace Rocket
{
	class Shader;
    
    class Texture1D;
    class Texture2D;
    class Texture3D;

	class Material
	{
	public:
        virtual ~Material();
        
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
	};
}

#endif
