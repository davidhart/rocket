#include "gameview.h"
#include "renderer.h"
#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "drawbinding.h"
#include "material.h"

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
		-1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,	  0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 1.0f
	};

	Buffer* vertexbuffer2 = renderer->CreateBuffer(sizeof(vertexdata), vertexdata);

	void* mappeddata = vertexbuffer2->Map(Buffer::MAP_READ_ONLY);
	assert(mappeddata);
	int test = memcmp(vertexdata, mappeddata, sizeof(vertexdata));
	assert(test == 0);
	vertexbuffer2->Unmap();

	return vertexbuffer2;
}

DrawBinding* CreateTestDrawBinding(Renderer* renderer, Buffer* vertexbuffer)
{
	VertexBinding vertexBindings[] =
	{
		{ 1, DB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 12, 24 },
		{ 0, DB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 0, 24 },
	};

	DrawBindingDef bindingDef =
	{
		vertexBindings,
		2,
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
		"layout(location=0)in vec3 vertex;\n"
		"layout(location=1)in vec3 i_color;\n"
		"out vec3 f_color;\n"
		"void main()\n"
		"{\n"
		"gl_Position.xyz = vertex;\n"
		"gl_Position.w = 1;\n"
		"f_color = i_color;\n"
		"}";
	unsigned vertSize = sizeof(vert);

	const char* frag =
		"#version 140\n"
		"in vec3 f_color;\n"
		"out vec4 frag;\n"
		"void main()\n"
		"{\n"
		"frag.xyz = f_color.xyz;\n"
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

void TestTextures(Renderer* renderer)
{
	const unsigned char bytes[] = {
		0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00
	};

	TextureDef textureData;
	textureData.type = TEXTURE_2D;
	textureData.width = 2;
	textureData.height = 2;
	textureData.depth = 0;
	textureData.data = bytes;
	textureData.size = sizeof(bytes);

	Texture* texture = renderer->CreateTexture(textureData);
	assert(texture);

	renderer->ReleaseTexture(texture);
}

int main(int argc, char** argv)
{
	GameView* view = GameView::Create("test application");
    assert(view);
    view->SetIsResizable(true);
    
    Renderer* renderer = view->CreateRenderer();
    assert(renderer);

	Buffer* buffer = CreateTestBuffer(renderer);
	Shader* shader = CreateTestShader(renderer);
	DrawBinding* binding = CreateTestDrawBinding(renderer, buffer);
	TestTextures(renderer);

	Material* material = new Material(shader);

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
		view->FlushEvents();
        
		renderer->RenderTemp(binding, material);
		renderer->Present();
	}
	
	delete material;

	renderer->ReleaseDrawBinding(binding);
	renderer->ReleaseShader(shader);
	renderer->ReleaseBuffer(buffer);

	view->ReleaseRenderer(renderer);
	GameView::Release(view);
	
	return 0;
}
