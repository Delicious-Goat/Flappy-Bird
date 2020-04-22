#pragma once
#include "pch.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using std::unique_ptr;

struct backgroundTextureData
{
	int textureWidth;
	int textureHeight;
	int type;
};

class Renderer 
{
private:
	//device and context
	ComPtr<ID3D11Device1> device;
	ComPtr<ID3D11DeviceContext1> context;

	//window dimensions
	int screenHeight;
	int screenWidth;

	//texture
	ComPtr<ID3D11ShaderResourceView> birdTextures[4];


	unique_ptr<DirectX::SpriteBatch> spriteBatch;

	//TODO look into this
	Vector2 origin;

	//textures
	ComPtr<ID3D11ShaderResourceView> backgroundTex;
	Vector2 backgroundTexSize;
	ComPtr<ID3D11ShaderResourceView> groundTex;
	Vector2 groundTexSize;

public:
	Renderer();
	~Renderer() = default;

	//Draw functions
	void DrawBird(Vector2 pos, float rot, int frame);
	void DrawBackground(Vector2 screenPos, Vector2 origin, int type);

	//Init functions
	backgroundTextureData LoadScrollingTexture(int type);

	void Init(ComPtr<ID3D11Device1> dev, ComPtr<ID3D11DeviceContext1> cont);
	void SetWindow(int w, int h);
	
	void OnDeviceLost();
	inline void BeginSpriteBatch(){ spriteBatch->Begin(); }
	inline void EndSpriteBatch(){ spriteBatch->End(); }

	//Setters
	
	inline void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device1> dev) { device = dev; }
	inline void SetContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> cont) { context = cont; }

	//getters
	inline int GetScreenWidth() { return screenWidth; }
	inline int GetScreenHeight() { return screenHeight; }
};