#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects.h"
#include "GameObject.h"
#include "Brick.h"
#include "Ball.h"
#include "Platform.h"
#include "Wall.h"

using namespace std;

Tema1::Tema1() {}

Tema1::~Tema1() {}

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
	nr_lives = 3;
	nr_bricks = 12 * 7;
	is_started = false;

	// Create the bricks
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			Brick brick = Brick(0.55f + i * 0.25f, 3.4f - j * 0.25f);
			bricks.push_back(brick);
		}
	}

	// Create ball
	ball = Ball(0.03f, 2.0f, 0.35f);

	// Create platform
	platform = Plaform(1.725f, 0.2f, 0.6f);

	// Create walls
	walls.push_back(Wall(0.0f, 0.3f, 0.6f, 24.0f));
	walls.push_back(Wall(-0.1f, 3.85f, 40.0f, 1.0f));
	walls.push_back(Wall(3.9f, 0.3f, 0.6f, 24.0f));

	// Add meshes for objects
	Mesh* rectangle = Objects::CreateRectangle("rectangle", corner, Brick::HEIGHT, Brick::WIDTH, glm::vec3(0.2f, 0.7f, 0.1f));
	AddMeshToList(rectangle);

	Mesh* circle = Objects::CreateCircle("circle", corner, ball.radius, glm::vec3(1.0f, 1.0f, 1.0f));
	AddMeshToList(circle);
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

	// Decrease nr of lives
	if (ball.y < 0 && is_started == true) {
		nr_lives--;
		is_started = false;
	}

	// Start moving the ball
	if (is_started == true) {
		ball.x += deltaTimeSeconds * cos(ball.angle) * ball.direction_x;
		ball.y += deltaTimeSeconds * sin(ball.angle) * ball.direction_y;

		// Search for collision with walls
		for (int i = 0; i < 3; i++) {
			Wall wall = walls.at(i);
			if (i == 0) {
				if (ball.x + ball.radius >= wall.x + wall.scale_x * Brick::WIDTH + 0.05f) {
					ball.direction_x *= -1;
				}
			}
			else {
				if (ball.x + ball.radius >= wall.x) {
					ball.direction_x *= -1;
				}
			}

			if (ball.y + ball.radius >= wall.y) {
				ball.direction_y *= -1;
			}
		}

		// Search for collision with platform 
		if (platform.y >= ball.y - ball.radius) {
			if (ball.x - ball.radius >= platform.x && ball.x - ball.radius <= platform.x + platform.lenght) {
				ball.direction_y *= -1;
				ball.y = 0.35f;
				float diff = ball.x * (platform.lenght / 2);
				if (ball.x < platform.x + platform.lenght / 2) {
					ball.angle = acos(-1 + diff);
				}
				else {
					ball.angle = acos(diff);
				}
			}
		}

		// Search for collision with bricks
		for (Brick brick : bricks) {
			if (brick.y >= ball.y - ball.radius && brick.y + Brick::WIDTH <= ball.y - ball.radius) {
				if (ball.x - ball.radius >= brick.x && ball.x - ball.radius <= ball.x + Brick::HEIGHT) {
					brick.visible -= 0.1f;
					ball.direction_y *= -1;
					/*float diff = ball.x * (platform.lenght / 2);
					if (ball.x < platform.x + platform.lenght / 2) {
						ball.angle = acos(-1 + diff);
					}
					else {
						ball.angle = acos(diff);
					}*/
				}
			}
		}

	}
	else {
		ball.x = platform.x + platform.lenght / 2;
		ball.y = 0.35f;
		ball.direction_x = 1;
		ball.direction_y = 1;
		ball.angle = acos(0);
	}


	DrawScene(visMatrix);
}

void Tema1::FrameEnd() {}

void Tema1::DrawScene(glm::mat3 visMatrix)
{
	// Draw bricks
	for (int i = 0; i < nr_bricks; i++) {
		Brick brick = bricks.at(i);
		if (brick.visible == 1) {
			modelMatrix = visMatrix * Transform2D::Translate(brick.x, brick.y);
		}
		else if (brick.visible >= 0) {
			modelMatrix = visMatrix * Transform2D::Translate(brick.x, brick.y) * Transform2D::Scale(brick.visible, brick.visible);
			brick.visible -= 0.1f;
		}
		
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
	}

	// Draw walls
	for (Wall wall : walls) {
		modelMatrix = visMatrix * Transform2D::Translate(wall.x, wall.y)
			* Transform2D::Scale(wall.scale_x, wall.scale_y);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
	}

	// Draw platform
	modelMatrix = visMatrix * Transform2D::Translate(platform.x, platform.y) * 
		Transform2D::Scale(platform.lenght / Brick::WIDTH, platform.height / Brick::HEIGHT);
	RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

	// Draw ball
	if (nr_lives >= 0) {
		modelMatrix = visMatrix * Transform2D::Translate(ball.x, ball.y);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
	}

	// Draw lives
	for (int i = 0; i < nr_lives; i++) {
		modelMatrix = visMatrix * Transform2D::Translate(0.1f + i * 0.1f, 0.15f);
		RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::OnInputUpdate(float deltaTime, int mods) {}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Move platform
	if (window->GetSpecialKeyState() == 0) {
		platform.x += deltaX * 0.0025f;
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Launch the ball
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		is_started = true;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

bool Tema1::isCollision(Ball ball, GameObject game_obj) {

	return false;
}