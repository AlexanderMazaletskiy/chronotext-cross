
#pragma once

#define GLM_SWIZZLE
#include <glm/glm.hpp>

namespace chr
{
	struct TouchEvent
	{
		glm::vec2 pos;
		glm::vec2 prevPos;
		uint32_t id;
		double time;

		TouchEvent(const glm::vec2 &pos, const glm::vec2 &prevPos, uint32_t id, double time)
		:
		pos(pos),
		prevPos(prevPos),
		id(id),
		time(time)
		{}
	};
}
