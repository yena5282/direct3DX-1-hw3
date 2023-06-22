/* �ν��Ͻ��� ���� �޸� ����,�Ҹ�
* < ������ ���۰��� >
* ������ ���� : ����ͷ� ��µǾ�� �ϴ� ���� �޸��� ����
  ������ : ȭ�鿡 ��µǴ� �ϳ��� ���
  ������ ����Ʈ : 1�� ���� ��µǴ� ��� �������� �� (FPS)
  60Hz -> 1.0/60.0 
*  ���콺, Ű���� �ݹ� ���� ����
*/
#pragma once

#include "Scene.h"
#include "Timer.h"
#include "Camera.h"
#include "Player.h"

class CGameFramework
{
private:
	////������ ���� �����ӿ�ũ���� ����� Ÿ�̸��̴�. 
	CGameTimer m_GameTimer;
	////������ ������ ����Ʈ�� �� �������� ĸ�ǿ� ����ϱ� ���� ���ڿ��̴�. 
	_TCHAR m_pszFrameRate[50];
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;
	IDXGISwapChain3* m_pdxgiSwapChain;
	ID3D12Device* m_pd3dDevice;

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;

	static const UINT m_nSwapChainBuffers = 2;
	UINT m_nSwapChainBufferIndex;
	ID3D12Resource* m_ppd3dSwapChainBackBuffers[m_nSwapChainBuffers];
	
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT m_nDsvDescriptorIncrementSize;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];

	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	ID3D12PipelineState* m_pd3dPipelineState;

	ID3D12Fence* m_pd3dFence;
	UINT64 m_nFenceValue;
	HANDLE m_hFenceEvent;

	CScene* m_pScene;

public:
	CCamera* m_pCamera = NULL;

	//�÷��̾� ��ü�� ���� �������̴�
	CPlayer* m_pPlayer = NULL;

	// ���������� ���콺 ��ư�� Ŭ���� ���� ���콺 Ŀ���� ��ġ�̴�.
	POINT m_ptOldCursorPos;

public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();
	
	void CreateSwapChain();
	void ChangeSwapChainState();

	void CreateRtvAndDsvDescriptorHeaps();
	void CreateDirect3DDevice();
	void CreateCommandQueueAndList();

	void CreateRenderTargetViews();
	void CreateDepthStencilView();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void MoveToNextFrame();
	void FrameAdvance();
	void WaitForGpuComplete();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);

};
