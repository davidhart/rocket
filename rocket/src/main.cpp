#include "gameview.h"
#include "renderer.h"
#include "vertexbuffer.h"
#include "shader.h"

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
	ShaderSource shaderSource =
	{
		nullptr,
		0,
		nullptr,
		0
	};

	Shader* shader = renderer->CreateShader(shaderSource);

	assert(shader);

	renderer->ReleaseShader(shader);
}

int main(char** argv, int argc)
{
	GameView* view = GameView::Create("test application");
	Renderer* renderer = view->CreateRenderer();
	
	view->SetIsResizable(true);

	TestVertexBuffers(renderer);

	TestShaders(renderer);

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
