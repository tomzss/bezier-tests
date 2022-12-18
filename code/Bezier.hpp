#pragma once

#include "utilities.hpp"
#include <glm/vec2.hpp>

glm::vec2 getBezierPointFor(glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3, glm::vec2 cref p4, float t);

glm::vec2 getTangentForBezierAt(glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3, glm::vec2 cref p4, float t);
