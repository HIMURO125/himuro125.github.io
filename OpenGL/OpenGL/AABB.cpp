#include "header.h"

//ƒJƒƒ‰‚ÌAABBæ“¾
AABB GetCameraAABB(const Vector3& cameraPosition) {
	AABB cameraBox;
	cameraBox.min.x = cameraPosition.x - 0.5f;
	cameraBox.min.y = cameraPosition.y - 0.5f;
	cameraBox.min.z = cameraPosition.z - 0.5f;
	cameraBox.max.x = cameraPosition.x + 0.5f;
	cameraBox.max.y = cameraPosition.y + 0.5f;
	cameraBox.max.z = cameraPosition.z + 0.5f;
	return cameraBox;
}

//•Ç‚ÌAABBæ“¾
AABB GetCubeAABB(const Vector3& CubeCenter, float size) {
	AABB cube;
	float halfSize = size / 2.0f;
	cube.min.x = CubeCenter.x - halfSize;
	cube.min.y = CubeCenter.y - halfSize;
	cube.min.z = CubeCenter.z - halfSize;
	cube.max.x = CubeCenter.x + halfSize;
	cube.max.y = CubeCenter.y + halfSize;
	cube.max.z = CubeCenter.z + halfSize;
	return cube;
}

//Œ®‚ÌAABBæ“¾
AABB GetKeyAABB(const Vector3& KeyCenter, float size) {
	AABB key;
	float halfsize = size / 2.0f;
	key.min.x = KeyCenter.x - halfsize;
	key.min.y = KeyCenter.y - halfsize;
	key.min.z = KeyCenter.z - halfsize;
	key.max.x = KeyCenter.x + halfsize;
	key.max.y = KeyCenter.y + halfsize;
	key.max.z = KeyCenter.z + halfsize;
	return key;
}

//Õ“Ë”»’è
bool CheckCollision(const AABB Camera, const AABB Cube) {
	return (Camera.min.x <= Cube.max.x && Camera.max.x >= Cube.min.x) &&
		(Camera.min.y <= Cube.max.y && Camera.max.y >= Cube.min.y) &&
		(Camera.min.z <= Cube.max.z && Camera.max.z >= Cube.min.z);
}

//Œ®‚Ìæ“¾”»’è
bool CheckCollisionKey(const AABB Camera, const AABB Key) {
	return (Camera.min.x <= Key.max.x && Camera.max.x >= Key.min.x) &&
		(Camera.min.y <= Key.max.y && Camera.max.y >= Key.min.y) &&
		(Camera.min.z <= Key.max.z && Camera.max.z >= Key.min.z);
}

//ƒS[ƒ‹‚ÌÕ“Ë”»’è
bool CheckCollisionGate(const AABB Camera, const AABB Gate) {
	return (Camera.min.x <= Gate.max.x && Camera.max.x >= Gate.min.x) &&
		(Camera.min.y <= Gate.max.y && Camera.max.y >= Gate.min.y) &&
		(Camera.min.z <= Gate.max.z && Camera.max.z >= Gate.min.z);
}