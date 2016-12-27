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
        
        virtual void SetFloat(const char* name, float value) = 0;
        virtual void SetVec2(const char* name, const vec2& value) = 0;
        virtual void SetVec3(const char* name, const vec3& value) = 0;
        virtual void SetVec4(const char* name, const vec4& value) = 0;
        virtual void SetMat4(const char* name, const mat4& value) = 0;
        virtual void SetInt(const char* name, int value) = 0;
        virtual void SetIVec2(const char* name, const ivec2& value) = 0;
        virtual void SetIVec3(const char* name, const ivec3& value) = 0;
        virtual void SetIVec4(const char* name, const ivec4& value) = 0;
        virtual void SetTexture1D(const char* name, Texture1D* texture) = 0;
        virtual void SetTexture2D(const char* name, Texture2D* texture) = 0;
        virtual void SetTexture3D(const char* name, Texture3D* texture) = 0;
        
        virtual void SetFloat(int propertyID, float value) = 0;
        virtual void SetVec2(int propertyID, const vec2& value) = 0;
        virtual void SetVec3(int propertyID, const vec3& value) = 0;
        virtual void SetVec4(int propertyID, const vec4& value) = 0;
        virtual void SetMat4(int propertyID, const mat4& value) = 0;
        virtual void SetInt(int propertyID, int value) = 0;
        virtual void SetIVec2(int propertyID, const ivec2& value) = 0;
        virtual void SetIVec3(int propertyID, const ivec3& value) = 0;
        virtual void SetIVec4(int propertyID, const ivec4& value) = 0;
        virtual void SetTexture1D(int propertyID, Texture1D* texture) = 0;
        virtual void SetTexture2D(int propertyID, Texture2D* texture) = 0;
        virtual void SetTexture3D(int propertyID, Texture3D* texture) = 0;
        
        virtual void Clear(const char* name) = 0;
        virtual void Clear(int propertyID) = 0;
	};
}

#endif
