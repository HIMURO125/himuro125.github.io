/*******************************************************
* �t�@�C�����FAABB.cpp
* �T�v�@�@�@�F�J�����A�`�悵���I�u�W�F�N�g��AABB��t�^����
* �@�@�@�@�@�@����AABB���m�̏Փ˂����m����
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* �J������AABB��ݒ肷��֐�
* ���݂̃J�����̍��W����AABB��ݒ肷��
* ����
* cameraPosition:���݂̃J�����̍��W
********************************************************/
AABB GetCameraAABB(const Vector3& cameraPosition) {
	AABB cameraBox;                             //�J������AABB
	cameraBox.min.x = cameraPosition.x - 0.5f;  //x�̍ŏ����W
	cameraBox.min.y = cameraPosition.y - 0.5f;  //y�̍ŏ����W
	cameraBox.min.z = cameraPosition.z - 0.5f;  //z�̍ŏ����W
	cameraBox.max.x = cameraPosition.x + 0.5f;  //x�̍ő���W
	cameraBox.max.y = cameraPosition.y + 0.5f;  //y�̍ő���W
	cameraBox.max.z = cameraPosition.z + 0.5f;  //z�̍ő���W
	return cameraBox;
}

/*******************************************************
* �ǂ�AABB��ݒ肷��֐�
* �ǂ̒��S���W�Ǝw��T�C�Y����AABB��ݒ肷��
* ����
* CubeCenter:�`�悵���ǂ̒��S���W
* size      :AABB�̑傫��
********************************************************/
AABB GetCubeAABB(const Vector3& CubeCenter, float size) {
	AABB cube;                             //�ǂ�AABB
	float halfSize = size / 2.0f;
	cube.min.x = CubeCenter.x - halfSize;  //x�̍ŏ����W
	cube.min.y = CubeCenter.y - halfSize;  //y�̍ŏ����W
	cube.min.z = CubeCenter.z - halfSize;  //z�̍ŏ����W
	cube.max.x = CubeCenter.x + halfSize;  //x�̍ő���W
	cube.max.y = CubeCenter.y + halfSize;  //y�̍ő���W
	cube.max.z = CubeCenter.z + halfSize;  //z�̍ő���W
	return cube;
}

/*******************************************************
* ����AABB��ݒ肷��֐�
* ���̒��S���W�Ǝw��T�C�Y����AABB��ݒ肷��
* ����
* KeyCenter:�`�悵�����̒��S���W
* size     :AABB�̑傫��
********************************************************/
AABB GetKeyAABB(const Vector3& KeyCenter, float size) {
	AABB key;                            //����AABB
	float halfsize = size / 2.0f;
	key.min.x = KeyCenter.x - halfsize;  //x�̍ŏ����W
	key.min.y = KeyCenter.y - halfsize;  //y�̍ŏ����W
	key.min.z = KeyCenter.z - halfsize;  //z�̍ŏ����W
	key.max.x = KeyCenter.x + halfsize;  //x�̍ő���W
	key.max.y = KeyCenter.y + halfsize;  //y�̍ő���W
	key.max.z = KeyCenter.z + halfsize;  //z�̍ő���W
	return key;
}

/*******************************************************
* �J�����Ƒ��̃I�u�W�F�N�g�̏Փ˂𔻒肷��֐�
* �����ɃJ������AABB�Ƒ��̃I�u�W�F�N�g��AABB��n���A�Փ˂��Ă��邩�𔻒肷��
* �Փ˂��Ă�����true��Ԃ�
* ����
* Camera:�J������AABB
* Obj   :���̃I�u�W�F�N�g��AABB
********************************************************/
bool CheckCollision(const AABB Camera, const AABB Obj) {
	//AABB���m���G�ꂽ��true��Ԃ�
	return (Camera.min.x <= Obj.max.x && Camera.max.x >= Obj.min.x) &&
		(Camera.min.y <= Obj.max.y && Camera.max.y >= Obj.min.y) &&
		(Camera.min.z <= Obj.max.z && Camera.max.z >= Obj.min.z);
}