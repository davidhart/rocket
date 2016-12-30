#pragma once
#ifndef ROCKET_GLSHADERPROPERTYCACHE_INCLUDED
#define ROCKET_GLSHADERPROPERTYCACHE_INCLUDED

#include <vector>
#include <map>
#include <string>
#include "vectormath.h"

namespace Rocket
{
    class Texture1D;
    class Texture2D;
    class Texture3D;
    
    namespace OpenGL
    {
        union GLShaderValue
        {
            float f;
            vec2 v2;
            vec3 v3;
            vec4 v4;
            
            int i;
            ivec2 iv2;
            ivec3 iv3;
            ivec4 iv4;
            
            mat4 mat4;
            
            Texture1D* t1d;
            Texture2D* t2d;
            Texture3D* t3d;
            
            GLShaderValue();
        };
        
        enum GLShaderValueType
        {
            VT_FLOAT,
            VT_VEC2,
            VT_VEC3,
            VT_VEC4,
            VT_MAT4,
            
            VT_INT,
            VT_IVEC2,
            VT_IVEC3,
            VT_IVEC4,
            
            VT_TEXTURE1D,
            VT_TEXTURE2D,
            VT_TEXTURE3D,
            
            VT_UNSET
        };
        
        struct GLShaderProperty
        {
            GLShaderValue value;
            GLShaderValueType type;
        };
        
        class GLShaderOverride
        {
        public:
            virtual const GLShaderProperty* GetProperty(int propertyID) const = 0;
        };
        
        class GLShaderGlobals : public GLShaderOverride
        {
        public:
            
            int AddProperty(const char* name);
            int GetPropertyID(const char* name);
            
            void SetValue(const char* name, float value);
            void SetValue(const char* name, const vec2& value);
            void SetValue(const char* name, const vec3& value);
            void SetValue(const char* name, const vec4& value);
            void SetValue(const char* name, const mat4& value);
            void SetValue(const char* name, int value);
            void SetValue(const char* name, const ivec2& value);
            void SetValue(const char* name, const ivec3& value);
            void SetValue(const char* name, const ivec4& value);
            void SetValue(const char* name, Texture1D* texture);
            void SetValue(const char* name, Texture2D* texture);
            void SetValue(const char* name, Texture3D* texture);
            
            void SetValue(int propertyID, float value);
            void SetValue(int propertyID, const vec2& value);
            void SetValue(int propertyID, const vec3& value);
            void SetValue(int propertyID, const vec4& value);
            void SetValue(int propertyID, const mat4& value);
            void SetValue(int propertyID, int value);
            void SetValue(int propertyID, const ivec2& value);
            void SetValue(int propertyID, const ivec3& value);
            void SetValue(int propertyID, const ivec4& value);
            void SetValue(int propertyID, Texture1D* texture);
            void SetValue(int propertyID, Texture2D* texture);
            void SetValue(int propertyID, Texture3D* texture);
            
            const GLShaderProperty* GetProperty(int propertyID) const;
            
        private:
            
            std::vector<GLShaderProperty> m_properties;
            std::map<std::string, int> m_nameToIndex;
        };
    }
}

#endif
