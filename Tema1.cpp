#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = 0;		// logic x
	logicSpace.y = 0;		// logic y
	logicSpace.width = 4;	// logic width
	logicSpace.height = 4;	// logic height

	glm::vec3 corner = glm::vec3(0.001, 0.001, 0);
	height = 0.15f;
	width = 0.2f;
	platform_pos = 0.7f;

	Mesh* rectangle = Objects::CreateRectangle("rectangle", corner, height, width, glm::vec3(0.7f, 0.2f, 0.0f));
	AddMeshToList(rectangle);

	Mesh* platform = Objects::CreateRectangle("platform", corner, height, width, glm::vec3(0.1f, 0.8f, 0.1f));
	AddMeshToList(platform);
}

glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
		(float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Sets the screen area where to draw
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	// Compute uniform 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);
	DrawScene(visMatrix);
}

void Tema1::FrameEnd()
{

}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			modelMatrix = visMatrix * Transform2D::Translate(0.55 + i * 0.25, 3.5 - j * 0.25);
			RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
		}
	}

	modelMatrix = visMatrix * Transform2D::Scale(0.6f, 25.0f) * Transform2D::Translate(0, 0.01f);
	RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * Transform2D::Scale(40.0f, 1) * Transform2D::Translate(-0.1, 3.85f);
	RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * Transform2D::Scale(0.6f, 25.0f) * Transform2D::Translate(6.47f, 0.01f);
	RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

	modelMatrix = visMatrix * Transform2D::Scale(2.5f, 0.4f) * Transform2D::Translate(platform_pos, 0.2f);
	RenderMesh2D(meshes["platform"], shaders["VertexColor"], modelMatrix);
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->GetSpecialKeyState() == 0) {
		platform_pos += deltaX * 0.001f; 
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}