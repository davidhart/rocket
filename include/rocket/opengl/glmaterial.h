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
            
            void MakeCurrent(GLShaderOverride* overrides);
            
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
