#include "gameview.h"
#include "renderer.h"
#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "drawbinding.h"
#include "material.h"

#include "vectormath.h"

#include <thread>
#include <cassert>

using namespace Rocket;

Buffer* CreateTestBuffer(Renderer* renderer)
{
	// Create a buffer with no data
	Buffer* vertexbuffer = renderer->CreateBuffer(100, nullptr);
	assert(vertexbuffer);
	renderer->ReleaseBuffer(vertexbuffer);

	// Create a buffer with data, map it and compare with original data
	float vertexdata[] = {
		-1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	  0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.5f, 1.0f,
	};

	Buffer* vertexbuffer2 = renderer->CreateBuffer(sizeof(vertexdata), vertexdata);

	void* mappeddata = vertexbuffer2->Map(Buffer::MAP_READ_ONLY);
	if (mappeddata == nullptr) assert(false);
	assert(memcmp(vertexdata, mappeddata, sizeof(vertexdata))==0);
	vertexbuffer2->Unmap();

	return vertexbuffer2;
}

DrawBinding* CreateTestDrawBinding(Renderer* renderer, Buffer* vertexbuffer)
{
	VertexBinding vertexBindings[] =
	{
		{ 2, DB_TYPE_FLOAT, DB_COMPONENTS_2, vertexbuffer, 24, 32 },
		{ 1, DB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 12, 32 },
		{ 0, DB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 0, 32 },
	};

	DrawBindingDef bindingDef =
	{
		vertexBindings,
		3,
		nullptr,
		3
	};

	DrawBinding* binding = renderer->CreateDrawBinding(bindingDef);
	assert(binding);
	return binding;
}

Shader* CreateTestShader(Renderer* renderer)
{
	const char* vert =
		"#version 140\n"
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"uniform vec4 u_color;\n"
		"uniform mat4 u_transform;\n"
		"layout(location=0)in vec3 i_vertex;\n"
		"layout(location=1)in vec3 i_color;\n"
		"layout(location=2)in vec2 i_uv;\n"
		"out vec3 f_color;\n"
		"out vec2 f_uv;\n"
		"void main()\n"
		"{\n"
		"vec4 temp;\n"
		"temp.xyz = i_vertex.xyz;\n"
		"temp.w = 1;\n"
		"temp = u_transform * temp;\n"
		"gl_Position = temp;\n"
		"f_color = i_color * u_color.xyz;\n"
		"f_uv = i_uv;\n"
		"}";
	unsigned vertSize = sizeof(vert);

	const char* frag =
		"#version 140\n"
		"uniform vec2 u_offset;\n"
		"uniform sampler2D s_texture;\n"
		"in vec3 f_color;\n"
		"in vec2 f_uv;\n"
		"out vec4 frag;\n"
		"void main()\n"
		"{\n"
		"frag.xyz = texture(s_texture, f_uv + u_offset).xyz * f_color;\n"
		"frag.w = 1;\n"
		"}";
	unsigned fragSize = sizeof(frag);

	ShaderDef shaderSource =
	{
		vert,
		vertSize,
		frag,
		fragSize
	};

	Shader* shader = renderer->CreateShader(shaderSource);

	assert(shader);
	return shader;
}

Texture2D* CreateTestTexture2D(Renderer* renderer)
{
	const unsigned char bytes[] = {
		0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00
	};

	TextureDef2D def;
	def.sampler.widthWrap = WRAP_REPEAT;
	def.sampler.heightWrap = WRAP_REPEAT;
	def.width = 2;
	def.height = 2;
	def.data = bytes;
	def.size = sizeof(bytes);

	Texture2D* texture = renderer->CreateTexture(def);
	assert(texture);

	return texture;
}

int main(int, char**)
{
	GameView* view = GameView::Create("test application");
    assert(view);
    view->SetIsResizable(true);
    
    Renderer* renderer = view->CreateRenderer();
    assert(renderer);

	Buffer* buffer = CreateTestBuffer(renderer);
	Shader* shader = CreateTestShader(renderer);
	DrawBinding* binding = CreateTestDrawBinding(renderer, buffer);
	Texture2D* texture = CreateTestTexture2D(renderer);

	Material* material = new Material(shader);
	ShaderParameters* parameters = material->GetParameters();

	parameters->SetTexture2D("s_texture", texture);

	

	float angle = 0.0f;
	float angle2 = 0.0f;


	vec2 offset(0.0f, 0.0f);

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
		view->FlushEvents();

		vec4 random_color = vec4((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
		parameters->SetVec4("u_color", random_color);

		offset.x += 0.01f;
		offset.y += 0.0025f;

		parameters->SetVec2("u_offset", offset);
        
		angle += 0.01f;
		angle2 += 0.025f;

		ivec2 size = view->GetSize();
		float ratio = (float)size.x / (float)size.y;

		mat4 ortho = mat4::Ortho(-2 * ratio, 2 * ratio, 2, -2, -2, 2);

		mat4 transform = mat4::AxisAngle(vec3::Up(), angle);
		mat4 transform2 = transform * mat4::AxisAngle(vec3::Forward(), angle2);
		parameters->SetMat4("u_transform", transform * transform2 * ortho);

		renderer->RenderTemp(binding, material);
		renderer->Present();
	}
	
	delete material;

	renderer->ReleaseDrawBinding(binding);
	renderer->ReleaseShader(shader);
	renderer->ReleaseBuffer(buffer);
	renderer->ReleaseTexture(texture);

	view->ReleaseRenderer(renderer);
	GameView::Release(view);
	
	return 0;
}
