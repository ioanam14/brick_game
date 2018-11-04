#include <math.h>
#include "Objects.h"

#include <Core/Engine.h>

Mesh* Objects::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, 
					float height, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Objects::CreateCircle(std::string name, glm::vec3 center, float radius,
	glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color)
	};

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = { 0 };

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		for (int i = 0; i <= 300; i++) {
			double angle = 2 * M_PI * i / 300;
			double x = cos(angle) * radius;
			double y = sin(angle) * radius;

			indices.push_back(i + 1);
			vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		}
		// draw 2 triangles. Add the remaining 2 indices
		for (int i = 1; i < 300; i++) {
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + 1);
		}
	}

	circle->InitFromData(vertices, indices);
	return circle;
}