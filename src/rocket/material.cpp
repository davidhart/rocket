#include "material.h"
#include "shader.h"
#include <cassert>

using namespace Rocket;

Material::Material(Shader* shader) :
	m_shader(shader)
{
	assert(shader);
	m_parameters = m_shader->CreateParameters();
}

Material::Material(const Material& material) :
	m_shader(material.m_shader)
{
	m_parameters = m_shader->CreateParameters();
}

Material::~Material()
{
	m_shader->ReleaseParameters(m_parameters);
}

Shader* Material::GetShader()
{
	return m_shader;
}

ShaderParameters* Material::GetParameters()
{
	return m_parameters;
}
