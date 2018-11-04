#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{
	// Create rectangle with given bottom left corner, height, weight and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float height,
							float width, glm::vec3 color, bool fill = true);

	// Create circle with given centre, radius and color
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius,
		glm::vec3 color, bool fill = true);
}

