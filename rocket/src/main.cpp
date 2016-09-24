#include "gameview.h"
#include "renderer.h"
#include "vertexbuffer.h"
#include "shader.h"
#include "texture.h"

#include <thread>
#include <cassert>

using namespace Rocket;

void TestVertexBuffers(Renderer* renderer)
{
	// Create a buffer with no data
	VertexBuffer* vertexbuffer = renderer->CreateVertexBuffer(100, nullptr);
	assert(vertexbuffer);
	renderer->ReleaseVertexBuffer(vertexbuffer);

	// Create a buffer with data, map it and compare with original data
	float vertexdata[] = {
		0.5f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	VertexBuffer* vertexbuffer2 = renderer->CreateVertexBuffer(sizeof(vertexdata), vertexdata);

	void* mappeddata = vertexbuffer2->Map(VertexBuffer::MAP_READ_ONLY);
	assert(mappeddata);
	int test = memcmp(vertexdata, mappeddata, sizeof(vertexdata));
	assert(test == 0);
	vertexbuffer2->Unmap();

	renderer->ReleaseVertexBuffer(vertexbuffer2);
}

void TestShaders(Renderer* renderer)
{
	const char* vert =
		"#version 130\n"
		"in vec4 vertex;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vertex;\n"
		"}";
	size_t vertSize = sizeof(vert);

	const char* frag =
		"#version 130\n"
		"out vec4 frag;\n"
		"void main()\n"
		"{\n"
		"frag = vec4(1,1,1,1);\n"
		"}";
	size_t fragSize = sizeof(frag);

	ShaderSource shaderSource =
	{
		vert,
		vertSize,
		frag,
		fragSize
	};

	Shader* shader = renderer->CreateShader(shaderSource);

	assert(shader);

	renderer->ReleaseShader(shader);
}

void TestTextures(Renderer* renderer)
{
	const unsigned char bytes[] = {
		0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00
	};

	TextureData textureData;
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

int main(char** argv, int argc)
{
	GameView* view = GameView::Create("test application");
	Renderer* renderer = view->CreateRenderer();
	
	view->SetIsResizable(true);

	TestVertexBuffers(renderer);
	TestShaders(renderer);
	TestTextures(renderer);

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
		view->FlushEvents();

		renderer->Present();
	}
	
	view->ReleaseRenderer(renderer);
	GameView::Release(view);
	
	return 0;
}
