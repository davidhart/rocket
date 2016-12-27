#pragma once
#ifndef ROCKET_GLMATERIAL_INCLUDED
#define ROCKET_GLMATERIAL_INCLUDED

#include "material.h"
#include "opengl/rocket_opengl.h"
#include "opengl/glshaderglobals.h"
#include <vector>

namespace Rocket
{
    namespace OpenGL
    {
        class GLShader;
        
        class GLMaterial : public Material
        {
        public:
            GLMaterial(GLShader* shader);
            virtual ~GLMaterial();
            
            virtual void SetFloat(const char* name, float value);
            virtual void SetVec2(const char* name, const vec2& value);
            virtual void SetVec3(const char* name, const vec3& value);
            virtual void SetVec4(const char* name, const vec4& value);
            virtual void SetMat4(const char* name, const mat4& value);
            virtual void SetInt(const char* name, int value);
            virtual void SetIVec2(const char* name, const ivec2& value);
            virtual void SetIVec3(const char* name, const ivec3& value);
            virtual void SetIVec4(const char* name, const ivec4& value);
            virtual void SetTexture1D(const char* name, Texture1D* texture);
            virtual void SetTexture2D(const char* name, Texture2D* texture);
            virtual void SetTexture3D(const char* name, Texture3D* texture);
            
            virtual void SetFloat(int propertyID, float value);
            virtual void SetVec2(int propertyID, const vec2& value);
            virtual void SetVec3(int propertyID, const vec3& value);
            virtual void SetVec4(int propertyID, const vec4& value);
            virtual void SetMat4(int propertyID, const mat4& value);
            virtual void SetInt(int propertyID, int value);
            virtual void SetIVec2(int propertyID, const ivec2& value);
            virtual void SetIVec3(int propertyID, const ivec3& value);
            virtual void SetIVec4(int propertyID, const ivec4& value);
            virtual void SetTexture1D(int propertyID, Texture1D* texture);
            virtual void SetTexture2D(int propertyID, Texture2D* texture);
            virtual void SetTexture3D(int propertyID, Texture3D* texture);
            
            virtual void Clear(const char* name);
            virtual void Clear(int propertyID);
            
            void MakeCurrent(GLShaderGlobals* globals);
            
        private:
            
            void SetByName(const char* name, GLShaderValue value, GLShaderValueType type);
            void SetByID(int propertyID, GLShaderValue value, GLShaderValueType type);
            
            struct Parameter
            {
                const char* name;
                GLint location;
                int globalID;
                
                GLShaderValue value;
                GLShaderValueType type;
            };
            
            GLShader* m_shader;
            std::vector<Parameter> m_parameters;
        };
    }
}

#endif
