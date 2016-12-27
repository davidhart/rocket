#include "examplegame.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::Input;

Buffer* CreateTestGeometry(Renderer* renderer)
{
	// Create a buffer with data, map it and compare with original data
	float vertexdata[] = {
		-1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		1.0f, -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,

		-1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
		1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,

		-1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,   0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

		1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    0.0f, 1.0f,
		1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 1.0f,    1.0f, 0.0f,
		1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 1.0f,    0.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,   1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		1.0f, -1.0f,  1.0f,   1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,

		-1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 1.0f,    0.0f, 1.0f,
		1.0f,  1.0f,  1.0f,   1.0f, 0.0f, 1.0f,    1.0f, 1.0f,
		1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,    1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,   1.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	};

	Buffer* vertexbuffer = renderer->CreateBuffer(sizeof(vertexdata), vertexdata);
	assert(vertexbuffer);

	void* mappeddata = vertexbuffer->Map(Buffer::MAP_READ_ONLY);
	if (mappeddata == nullptr) assert(false);
	assert(memcmp(vertexdata, mappeddata, sizeof(vertexdata)) == 0);
	vertexbuffer->Unmap();

	return vertexbuffer;
}

DrawBinding* CreateTestDrawBinding(Renderer* renderer, Buffer* vertexbuffer, Buffer* indexbuffer)
{
	VertexBinding vertexBindings[] =
	{
		{ 0, VB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 0, 32 },
		{ 1, VB_TYPE_FLOAT, DB_COMPONENTS_3, vertexbuffer, 12, 32 },
		{ 2, VB_TYPE_FLOAT, DB_COMPONENTS_2, vertexbuffer, 24, 32 },
	};

	IndexBinding indexBinding =
	{
		IB_TYPE_UINT16,
		indexbuffer,
		0
	};

	DrawBindingDef bindingDef =
	{
		vertexBindings,
		3,
		&indexBinding,
		36
	};

	DrawBinding* binding = renderer->CreateDrawBinding(bindingDef);
	assert(binding);
	return binding;
}

Buffer* CreateTestIndices(Renderer* renderer)
{
	unsigned short indices[] = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,
	};

	Buffer* indexBuffer = renderer->CreateBuffer(sizeof(indices), indices);
	assert(indexBuffer);

	return indexBuffer;
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
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"uniform vec2 u_offset;\n"
		"uniform sampler2D s_texture;\n"
		"in vec3 f_color;\n"
		"in vec2 f_uv;\n"
		"layout(location = 0) out vec4 frag;\n"
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
	def.width = 2;
	def.height = 2;
	def.format = TEXFMT_RGBA_32;
	def.sampler.widthWrap = WRAP_REPEAT;
	def.sampler.heightWrap = WRAP_REPEAT;
	def.data = bytes;
	def.size = sizeof(bytes);

	Texture2D* texture = renderer->CreateTexture(def);
	assert(texture);

	return texture;
}

Buffer* CreateScreenSpaceQuad(Renderer* renderer)
{
	float vertData[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	Buffer* buffer = renderer->CreateBuffer(sizeof(vertData), vertData);
	assert(buffer);
	return buffer;
}

Buffer* CreateScreenSpaceQuadIndices(Renderer* renderer)
{
	short indices[] =
	{
		0, 1, 2,
		0, 2, 3,
	};

	Buffer* buffer = renderer->CreateBuffer(sizeof(indices), indices);
	assert(buffer);
	return buffer;
}

DrawBinding* CreateScreenSpaceQuadBinding(Renderer* renderer, Buffer* vertexbuffer, Buffer* indexbuffer)
{
	VertexBinding vertexBindings[] =
	{
		{ 0, VB_TYPE_FLOAT, DB_COMPONENTS_2, vertexbuffer, 0, 8 },
	};

	IndexBinding indexBinding =
	{
		IB_TYPE_UINT16,
		indexbuffer,
		0
	};

	DrawBindingDef bindingDef =
	{
		vertexBindings,
		1,
		&indexBinding,
		6
	};

	DrawBinding* binding = renderer->CreateDrawBinding(bindingDef);
	assert(binding);
	return binding;
}

Shader* CreateBlitShader(Renderer* renderer)
{
	const char* vert =
		"#version 140\n"
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"layout(location=0)in vec2 i_vertex;\n"
		"out vec2 f_uv;\n"
		"void main()\n"
		"{\n"
		"vec2 temp = i_vertex * vec2(2, 2) - vec2(1.0, 1.0);\n"
		"gl_Position = vec4(temp.x, temp.y, 0, 1.0);\n"
		"f_uv = i_vertex;\n"
		"}";
	unsigned vertSize = sizeof(vert);

	const char* frag =
		"#version 140\n"
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"uniform sampler2D s_texture;\n"
		"uniform sampler2D s_displace;\n"
		"in vec2 f_uv;\n"
		"layout(location = 0) out vec4 frag;\n"
		"void main()\n"
		"{\n"
		"vec2 displace = texture(s_displace, f_uv * 20.0).xy * 0.01;"
		"frag.xyz = texture(s_texture, f_uv + displace).xyz;\n"
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

RenderTarget* CreateTestRenderTarget(Renderer* renderer)
{
	ivec2 viewSize = renderer->GetPrimaryRenderTarget()->GetSize();

	TextureSamplerDef2D sampler;

	RenderTargetColorAttachmentDef colorAttachments[] =
	{
		{ TEXFMT_RGBA_32, sampler },
	};

	RenderTargetDepthAttachmentDef depthAttachment =
	{
		TEXFMT_DEPTH_16,
		sampler
	};

	RenderTargetDef def;
	def.width = viewSize.x;
	def.height = viewSize.y;
	def.colorAttachments = colorAttachments;
	def.numColorAttachements = 1;
	def.depthAttachement = &depthAttachment;

	RenderTarget* target = renderer->CreateRenderTarget(def);
	assert(target);
	return target;
}

vec4 RandomColor()
{
	return vec4((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
}



void ExampleGame::Startup(GameServices* services)
{
    // Setup input
    GameView* view = services->GameView();

    IControlScheme* controlScheme = view->AddControlScheme("controls");
    controlScheme->AddButton("bump");
    controlScheme->AddButtonKeyboardMapping("bump", KeyCode::KEY_SPACE);

    controlScheme->AddAxis("spinX");
    controlScheme->AddAxisKeyboardMapping("spinX", KeyCode::KEY_A, KeyCode::KEY_D);
    controlScheme->AddAxisKeyboardMapping("spinX", KeyCode::KEY_LEFT, KeyCode::KEY_RIGHT);
    controlScheme->AddAxis("spinY");
    controlScheme->AddAxisKeyboardMapping("spinY", KeyCode::KEY_S, KeyCode::KEY_W);
    controlScheme->AddAxisKeyboardMapping("spinY", KeyCode::KEY_DOWN, KeyCode::KEY_UP);

    IRuntimeControls* controls = view->ActivateControlScheme("controls");
    m_bumpButton = controls->GetButton("bump");
    m_spinAxisX = controls->GetAxis("spinX");
    m_spinAxisY = controls->GetAxis("spinY");

    // Setup graphics
    Renderer* renderer = services->Renderer();

    m_primaryTarget = renderer->GetPrimaryRenderTarget();

	m_vertbuffer = CreateTestGeometry(renderer);
	m_indexbuffer = CreateTestIndices(renderer);
	m_binding = CreateTestDrawBinding(renderer, m_vertbuffer, m_indexbuffer);
	m_shader = CreateTestShader(renderer);
	m_texture = CreateTestTexture2D(renderer);

	m_material = renderer->CreateMaterial(m_shader);
	m_material->SetTexture2D("s_texture", m_texture);

	m_renderTarget = CreateTestRenderTarget(renderer);

	m_framebufferQueue = renderer->CreateRenderQueue("framebuffer", 0);
	m_framebufferQueue->SetClearColorEnabled(true);
	m_framebufferQueue->SetClearColor(color(0, 0, 0, 0));
	m_framebufferQueue->SetClearDepthEnabled(true);
	m_framebufferQueue->SetTarget(m_renderTarget);

	m_quadverts = CreateScreenSpaceQuad(renderer);
	m_quadindices = CreateScreenSpaceQuadIndices(renderer);
	m_quadbinding = CreateScreenSpaceQuadBinding(renderer, m_quadverts, m_quadindices);
	m_blitshader = CreateBlitShader(renderer);
	m_blitMaterial = renderer->CreateMaterial(m_blitshader);
    
	m_blitMaterial->SetTexture2D("s_texture", m_renderTarget->GetColorAttachment(0));
    m_blitMaterial->SetTexture2D("s_displace", m_texture);
    
	m_mainQueue = renderer->CreateRenderQueue("composite", 1);
	m_mainQueue->SetClearColorEnabled(true);
	m_mainQueue->SetClearColor(color(1, 0, 0, 1));
	m_mainQueue->SetClearDepthEnabled(true);

	m_angle = 0.0f;
	m_angle2 = 0.0f;
	m_offset = vec2(0.0f, 0.0f);
}

void ExampleGame::Shutdown(GameServices* services)
{
    GameView* view = services->GameView();
    view->DeactivateControlScheme("controls");

    Renderer* renderer = services->Renderer();
	renderer->ReleaseRenderQueue(m_mainQueue);
	renderer->ReleaseRenderQueue(m_framebufferQueue);

	renderer->ReleaseMaterial(m_material);
	renderer->ReleaseMaterial(m_blitMaterial);

	renderer->ReleaseShader(m_shader);
	renderer->ReleaseShader(m_blitshader);

	renderer->ReleaseDrawBinding(m_binding);
	renderer->ReleaseDrawBinding(m_quadbinding);

	renderer->ReleaseBuffer(m_indexbuffer);
	renderer->ReleaseBuffer(m_vertbuffer);
	renderer->ReleaseBuffer(m_quadverts);
	renderer->ReleaseBuffer(m_quadindices);

	renderer->ReleaseTexture(m_texture);
}

void ExampleGame::Update(float dt)
{
	m_offset.x += 144.0f * 0.01f * dt;
	m_offset.y += 144.0f * 0.0025f * dt;
	m_angle += m_spinAxisX->Value() * dt * 10.0f;
	m_angle2 += m_spinAxisY->Value() * dt * 10.0f;

    if (m_bumpButton->WasJustPressed())
        m_bump = 2;

    m_bump -= 10 * dt;
    if (m_bump < 1) m_bump = 1;

	ivec2 size = m_primaryTarget->GetSize();
	float ratio = (float)size.x / (float)size.y;

	mat4 projectionmat = mat4::Frustum(-1.0f * ratio, 1.0f * ratio, -1.0f, 1.0f, 1.5f, 1000.0f);
	mat4 viewmat = mat4::Translate(vec3(0.0f, 0.0f, -5.5f));
	mat4 transform = mat4::AxisAngle(vec3::Up(), m_angle);
	mat4 transform2 = mat4::AxisAngle(vec3::Right(), m_angle2);
    mat4 scale = mat4::Scale(vec3(m_bump, m_bump, m_bump));
    mat4 modelmat = transform * transform2 * scale;;

	m_material->SetVec4("u_color", RandomColor());
	m_material->SetVec2("u_offset", m_offset);
	m_material->SetMat4("u_transform", projectionmat * viewmat * modelmat);

	m_framebufferQueue->Draw(m_binding, m_material);
	m_mainQueue->Draw(m_quadbinding, m_blitMaterial);
}
