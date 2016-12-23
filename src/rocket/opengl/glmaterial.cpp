#include "opengl/glmaterial.h"
#include "shader.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLMaterial::GLMaterial(Shader* shader) :
    m_shader(shader)
{
    assert(shader);
    m_parameters = m_shader->CreateParameters();
}

GLMaterial::GLMaterial(Material* material) :
    m_shader(material->GetShader())
{
    assert(false); // TODO: Clone parameters
    m_parameters = m_shader->CreateParameters();
}

GLMaterial::~GLMaterial()
{
    m_shader->ReleaseParameters(m_parameters);
}

Shader* GLMaterial::GetShader()
{
    return m_shader;
}

ShaderParameters* GLMaterial::GetParameters()
{
    return m_parameters;
}
