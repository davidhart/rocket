#include "material.h"

using namespace Rocket;

Material::Material(Shader* shader) :
	m_shader(shader)
{
}

Material::Material(const Material& material) :
	m_shader(material.m_shader)
{
}

Material::~Material()
{
}

Shader* Material::GetShader()
{
	return m_shader;
}
