#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"

struct Raycast;
struct BoundingBox;

class CollisionDetection
{
public:
	CollisionDetection() = delete;

	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator = (const CollisionDetection&) = delete;
	CollisionDetection& operator = (CollisionDetection&&) = delete;

	static Raycast ScreenToWorldRay(glm::vec2 mousePosition_, glm::vec2 screenSize_);
	static bool RayOBBIntersection(Raycast* ray_, BoundingBox* box_);
};

#endif // !COLLISIONDETECTION_H

