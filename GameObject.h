/*
* ���Ӱ�ü�� ���� ��ġ,����,ȸ����,������ ������ ����ִ�.
*/
#pragma once
#include "Mesh.h"
#include "Camera.h"
class CShader;

struct MATERIALLOADINFO
{
	XMFLOAT4						m_xmf4AlbedoColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4						m_xmf4EmissiveColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4						m_xmf4SpecularColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	float							m_fGlossiness = 0.0f;
	float							m_fSmoothness = 0.0f;
	float							m_fSpecularHighlight = 0.0f;
	float							m_fMetallic = 0.0f;
	float							m_fGlossyReflection = 0.0f;

	UINT							m_nType = 0x00;

	//char							m_pstrAlbedoMapName[64] = { '\0' };
	//char							m_pstrSpecularMapName[64] = { '\0' };
	//char							m_pstrMetallicMapName[64] = { '\0' };
	//char							m_pstrNormalMapName[64] = { '\0' };
	//char							m_pstrEmissionMapName[64] = { '\0' };
	//char							m_pstrDetailAlbedoMapName[64] = { '\0' };
	//char							m_pstrDetailNormalMapName[64] = { '\0' };
};

struct MATERIALSLOADINFO
{
	int								m_nMaterials = 0;
	MATERIALLOADINFO* m_pMaterials = NULL;
};
class CMaterialColors
{
public:
	CMaterialColors() { }
	CMaterialColors(MATERIALLOADINFO* pMaterialInfo) {};
	virtual ~CMaterialColors() { }

private:
	int								m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	XMFLOAT4						m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	XMFLOAT4						m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4						m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f); //(r,g,b,a=power)
	XMFLOAT4						m_xmf4Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
};


class CMaterial
{
public:
	CMaterial() {};
	virtual ~CMaterial();

private:
	int								m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	CShader* m_pShader = NULL;

	CMaterialColors* m_pMaterialColors = NULL;

	void SetMaterialColors(CMaterialColors* pMaterialColors);
	void SetShader(CShader* pShader);
	void SetIlluminatedShader() { SetShader(m_pIlluminatedShader); }

	void UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList);

protected:
	static CShader* m_pIlluminatedShader;

public:
	static void PrepareShaders(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature);
};




class CGameObject
{
public:
	CGameObject(int nMeshes=1);
	virtual ~CGameObject();
private:
	int m_nReferences = 0;
	//���� ��ü�� ���� ���� �޽��� �����ϴ� ��� ���� ��ü�� ������ �޽��鿡 ���� �����Ϳ� �� �����̴�. 

public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	char							m_pstrFrameName[64];
	int								m_nMaterials = 0;
	CMaterial						** m_ppMaterials = NULL;
	XMFLOAT4X4						m_xmf4x4Transform;
	CGameObject* m_pParent = NULL;
	CGameObject* m_pChild = NULL;
	CGameObject* m_pSibling = NULL;
	XMFLOAT4X4 m_xmf4x4World;
protected:
	CMesh* m_pMesh = NULL;
	CShader* m_pShader = NULL;
	CMesh **m_ppMeshes = NULL;
	int m_nMeshes = 0;

public:
	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);

public:
	void ReleaseUploadBuffers();
	void SetMesh(int nIndex, CMesh* pMesh);
	virtual void SetShader(CShader* pShader);
	void SetMaterial(int nMaterial, CMaterial* pMaterial) {};
	void SetChild(CGameObject* pChild, bool bReferenceUpdate = false) ;
	virtual void Animate(float fTimeElapsed);
	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent);
	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	//��� ���۸� �����Ѵ�. 
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	//��� ������ ������ �����Ѵ�. 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	// ***���� ���� ���� ��ü�� �����Ϸ��� ���� ��ü�� ��ġ�� �����ϱ� ���� �Լ��� �ʿ��ϴ�.*** //

	// ���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ���Ϳ� ����(x,y,z) ���͸� ��ȯ�Ѵ�.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	// ���� ��ü�� ��ġ�� �����Ѵ�
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	// ���� ��ü�� ���� x,y,z�� �������� �̵��Ѵ�.
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	void UpdateTransform(XMFLOAT4X4* pxmf4x4Parent = NULL);

	CGameObject* GetParent() { return(m_pParent); }
	CGameObject* FindFrame(const char* pstrFrameName);
	// ���� ��ü�� ȸ�� x,y,z
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	UINT GetMeshType() { return((m_pMesh) ? m_pMesh->GetType() : 0); }
public:
	static MATERIALSLOADINFO* LoadMaterialsInfoFromFile(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, FILE* pInFile) ;
	static CMeshLoadInfo* LoadMeshInfoFromFile(FILE* pInFile) ;

	static CGameObject* LoadFrameHierarchyFromFile(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, FILE* pInFile);
	static CGameObject* LoadGeometryFromFile(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, const char* pstrFileName);

	static void PrintFrameInfo(CGameObject* pGameObject, CGameObject* pParent);
};

class CRotatingObject :public CGameObject
{
public:
	CRotatingObject(int nMeshes=1);
	virtual ~CRotatingObject() {};

private:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;

public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) { m_xmf3RotationAxis = xmf3RotationAxis; }

	virtual void Animate(float fTimeElapsed);
};

class CHeightMapTerrain : public CGameObject
{
public:
	CHeightMapTerrain(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, LPCTSTR pFileName, int
		nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4 xmf4Color);
	virtual ~CHeightMapTerrain() { if (m_pHeightMapImage) delete m_pHeightMapImage; }
private:
	//������ ���� ������ ����� �̹����̴�. 
	CHeightMapImage* m_pHeightMapImage;
	//���� ���� ���ο� ���� ũ���̴�. 
	int m_nWidth;
	int m_nLength;
	//������ ������ �� �� Ȯ���� ���ΰ��� ��Ÿ���� ������ �����̴�. 
	XMFLOAT3 m_xmf3Scale;

public:
	//������ ���̸� ����ϴ� �Լ��̴�(���� ��ǥ��). ���� ���� ���̿� �������� y�� ���� ���̴�. 
	float GetHeight(float x, float z) { return(m_pHeightMapImage->GetHeight(x / m_xmf3Scale.x, z / m_xmf3Scale.z)* m_xmf3Scale.y);}

//������ ���� ���͸� ����ϴ� �Լ��̴�(���� ��ǥ��). ���� ���� ���� ���͸� ����Ѵ�. 
	XMFLOAT3 GetNormal(float x, float z) { return(m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z /m_xmf3Scale.z))); }
	int GetHeightMapWidth() { return(m_pHeightMapImage->GetHeightMapWidth()); }
	int GetHeightMapLength() { return(m_pHeightMapImage->GetHeightMapLength()); }
	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	//������ ũ��(����/����)�� ��ȯ�Ѵ�. ���� ���� ũ�⿡ �������� ���� ���̴�. 
	float GetWidth() { return(m_nWidth * m_xmf3Scale.x); }
	float GetLength() { return(m_nLength * m_xmf3Scale.z); }
};
class CHellicopterObject : public CGameObject
{
public:
	CHellicopterObject() {};
	virtual ~CHellicopterObject() {};

protected:
	CGameObject* m_pMainRotorFrame = NULL;
	CGameObject* m_pTailRotorFrame = NULL;

public:
	virtual void OnInitialize() {};
	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);
};
class CApacheObject : public CHellicopterObject
{
public:
	CApacheObject() {};
	virtual ~CApacheObject() {};

public:
	virtual void OnInitialize() {
		m_pMainRotorFrame = FindFrame("rotor");
		m_pTailRotorFrame = FindFrame("black_m_7");
	};
	virtual void Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent = NULL);
};