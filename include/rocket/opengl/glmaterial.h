#pragma once
#ifndef ROCKET_GLMATERIAL_INCLUDED
#define ROCKET_GLMATERIAL_INCLUDED

#include "material.h"
#include "shader.h"

namespace Rocket
{
    namespace OpenGL
    {
        class GLMaterial : public Material
        {
        public:
            GLMaterial(Shader* shader);
            GLMaterial(Material* material);
            virtual ~GLMaterial();
            
            virtual Shader* GetShader();
            virtual ShaderParameters* GetParameters();
            
        private:
            Shader* m_shader;
            ShaderParameters* m_parameters;
        };
    }
}

#endif
