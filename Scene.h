#pragma once
/*
* Scene�� �������ϴ� ��ü�� �Ӽ����� �ο��ϰ�, ��ü���� ���� ������ (���)
* 
*/
#include "Shader.h"
#include "Camera.h"
class CScene 
{
public:
	CScene() {};
	~CScene() {};
	//������ ���콺�� Ű���� �޽����� ó���Ѵ�. 
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM 
	lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();
	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList,CCamera *pCamera);
	
	void ReleaseUploadBuffers();

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

	CCamera* pCamera = NULL;
	CHeightMapTerrain* GetTerrain() {return(m_pTerrain);}

	CGameObject** m_ppGameObjects = NULL;
	int							m_nGameObjects = 0;
	float						m_fElapsedTime = 0.0f;

	CPlayer* m_pPlayer = NULL;
	CGameObject* m_pCGObjcet= NULL;
protected:
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�. 
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	CHeightMapTerrain* m_pTerrain = NULL;

};

