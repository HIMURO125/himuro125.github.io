/*******************************************************
* ファイル名：AABB.cpp
* 概要　　　：カメラ、描画したオブジェクトにAABBを付与する
* 　　　　　　他のAABB同士の衝突を検知する
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* カメラのAABBを設定する関数
* 現在のカメラの座標からAABBを設定する
* 引数
* cameraPosition:現在のカメラの座標
********************************************************/
AABB GetCameraAABB(const Vector3& cameraPosition) {
	AABB cameraBox;                             //カメラのAABB
	cameraBox.min.x = cameraPosition.x - 0.5f;  //xの最小座標
	cameraBox.min.y = cameraPosition.y - 0.5f;  //yの最小座標
	cameraBox.min.z = cameraPosition.z - 0.5f;  //zの最小座標
	cameraBox.max.x = cameraPosition.x + 0.5f;  //xの最大座標
	cameraBox.max.y = cameraPosition.y + 0.5f;  //yの最大座標
	cameraBox.max.z = cameraPosition.z + 0.5f;  //zの最大座標
	return cameraBox;
}

/*******************************************************
* 壁のAABBを設定する関数
* 壁の中心座標と指定サイズからAABBを設定する
* 引数
* CubeCenter:描画した壁の中心座標
* size      :AABBの大きさ
********************************************************/
AABB GetCubeAABB(const Vector3& CubeCenter, float size) {
	AABB cube;                             //壁のAABB
	float halfSize = size / 2.0f;
	cube.min.x = CubeCenter.x - halfSize;  //xの最小座標
	cube.min.y = CubeCenter.y - halfSize;  //yの最小座標
	cube.min.z = CubeCenter.z - halfSize;  //zの最小座標
	cube.max.x = CubeCenter.x + halfSize;  //xの最大座標
	cube.max.y = CubeCenter.y + halfSize;  //yの最大座標
	cube.max.z = CubeCenter.z + halfSize;  //zの最大座標
	return cube;
}

/*******************************************************
* 鍵のAABBを設定する関数
* 鍵の中心座標と指定サイズからAABBを設定する
* 引数
* KeyCenter:描画した鍵の中心座標
* size     :AABBの大きさ
********************************************************/
AABB GetKeyAABB(const Vector3& KeyCenter, float size) {
	AABB key;                            //鍵のAABB
	float halfsize = size / 2.0f;
	key.min.x = KeyCenter.x - halfsize;  //xの最小座標
	key.min.y = KeyCenter.y - halfsize;  //yの最小座標
	key.min.z = KeyCenter.z - halfsize;  //zの最小座標
	key.max.x = KeyCenter.x + halfsize;  //xの最大座標
	key.max.y = KeyCenter.y + halfsize;  //yの最大座標
	key.max.z = KeyCenter.z + halfsize;  //zの最大座標
	return key;
}

/*******************************************************
* カメラと他のオブジェクトの衝突を判定する関数
* 引数にカメラのAABBと他のオブジェクトのAABBを渡し、衝突しているかを判定する
* 衝突していたらtrueを返す
* 引数
* Camera:カメラのAABB
* Obj   :他のオブジェクトのAABB
********************************************************/
bool CheckCollision(const AABB Camera, const AABB Obj) {
	//AABB同士が触れたらtrueを返す
	return (Camera.min.x <= Obj.max.x && Camera.max.x >= Obj.min.x) &&
		(Camera.min.y <= Obj.max.y && Camera.max.y >= Obj.min.y) &&
		(Camera.min.z <= Obj.max.z && Camera.max.z >= Obj.min.z);
}