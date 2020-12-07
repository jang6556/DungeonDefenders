#pragma once

_BEGIN(Engine)
struct Vertex
{
	D3DXVECTOR3 vPosition;

	Vertex() {}
	Vertex(D3DXVECTOR3 _vPostion)
	{
		vPosition = _vPostion;
	}

};

struct VertexCol
{
	D3DXVECTOR3 vPosition;
	D3DCOLOR iColor;

	VertexCol() {}
	VertexCol(D3DXVECTOR3 _vPostion,D3DCOLOR _Color)
	{
		vPosition = _vPostion;
		iColor = _Color;
	}

};

struct VertexUV
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vTexUV;

	VertexUV() {}
	VertexUV(D3DXVECTOR3 _vPostion, D3DXVECTOR2 _UV)
	{
		vPosition = _vPostion;
		vTexUV = _UV;
	}

};

struct VertexCubeUV
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 UV;

	VertexCubeUV() {}
	VertexCubeUV(D3DXVECTOR3 _vPostion, D3DXVECTOR3 _UV)
	{
		vPosition = _vPostion;
		UV = _UV;
	}

};

struct VertexNormal
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vNormal;

	VertexNormal() {}
	VertexNormal(D3DXVECTOR3 _vPostion)
	{
		vPosition = _vPostion;		
	}

};

struct VertexScreenTex
{
	D3DXVECTOR4		vPosition; // D3DFVF_XYZRHW
	D3DXVECTOR2		vTexUV;    // D3DFVF_TEX1

	VertexScreenTex() {}

};


typedef struct tagMeshTexture
{
	enum MESHTEXTYPE { MESH_DIFFUSE, MESH_NORMAL, MESH_SPECULAR, MESH_END };

	LPDIRECT3DTEXTURE9 pTexture[MESH_END];

}MESHTEXTURE;

typedef struct tagD3DXFRame : public D3DXFRAME
{
	D3DXMATRIX CombinedMatrix;  //�޽��� ���� * ������ ����

}EXFRAME;

typedef struct tagD3DXMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPD3DXMESH		pOriginalMesh;	//�������� �޽�
	MESHTEXTURE*	pMeshTexture;   //�ؽ��� �迭
	unsigned long	dwFrameNum;		//������ ����
	D3DXMATRIX*		pRenderMatrix;	//��¿� ���
	D3DXMATRIX*		pOffsetMatrix;  //������ ���
	D3DXMATRIX**	ppCombinedMatrix;	//������

}EXMESHCONTAINER, *LPEXMESHCONTAINER;

typedef struct tagCloneData
{
	D3DXMATRIX				matWorld;
	D3DXVECTOR3				vRotation;
	int						ObjectType;

}OBJSAVEDATA,OBJLOADDATA;

typedef struct tagColliderData
{
	D3DXMATRIX				matWorld;
	TCHAR					szBoneName[MAX_PATH];
	int						iColliderType;
}OBJCOLLIDERDATA;



_END