#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{
	// Create square with given bottom left corner, length and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float height,
							float width, glm::vec3 color, bool fill = true);

}

