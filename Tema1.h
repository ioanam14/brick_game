#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#include "Brick.h"
#include "Ball.h"
#include "Platform.h"
#include "Wall.h"
#include "GameObject.h"

using namespace std;

class Tema1 : public SimpleScene
{
public:
	struct ViewportSpace
	{
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		int x;
		int y;
		int width;
		int height;
	};

	struct LogicSpace
	{
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height) {}
		float x;
		float y;
		float width;
		float height;
	};

public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void DrawScene(glm::mat3 visMatrix);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

	// Sets the logic space and view space
	// logicSpace: { x, y, width, height }
	// viewSpace: { x, y, width, height }
	glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

	void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

	bool Tema1::isCollision(Ball ball, GameObject game_obj);

protected:
	int nr_lives;
	int nr_bricks;
	bool is_started;
	ViewportSpace viewSpace;
	LogicSpace logicSpace;
	glm::mat3 modelMatrix, visMatrix;
	vector<Brick> bricks;
	Ball ball;
	Plaform platform;
	vector<Wall> walls;
};
