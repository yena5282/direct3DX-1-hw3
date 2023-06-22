/* 인스턴스에 대한 메모리 생성,소멸
* < 프레임 버퍼관리 >
* 프레임 버퍼 : 모니터로 출력되어야 하는 비디오 메모리의 영역
  프레임 : 화면에 출력되는 하나의 장면
  프레임 레이트 : 1초 동안 출력되는 평균 프레임의 수 (FPS)
  60Hz -> 1.0/60.0 
*  마우스, 키보드 콜백 등을 관리
*/
#pragma once

#include "Scene.h"
#include "Timer.h"
#include "Camera.h"
#include "Player.h"

class CGameFramework
{
private:
	////다음은 게임 프레임워크에서 사용할 타이머이다. 
	CGameTimer m_GameTimer;
	////다음은 프레임 레이트를 주 윈도우의 캡션에 출력하기 위한 문자열이다. 
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

	//플레이어 객체에 대한 포인터이다
	CPlayer* m_pPlayer = NULL;

	// 마지막으로 마우스 버튼을 클릭할 때의 마우스 커서의 위치이다.
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
