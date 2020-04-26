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

	ComPtr<ID3D11ShaderResourceView> pipeTexture;

	unique_ptr<DirectX::SpriteBatch> spriteBatch;


	//textures
	ComPtr<ID3D11ShaderResourceView> backgroundTex;
	Vector2 backgroundTexSize;
	ComPtr<ID3D11ShaderResourceView> groundTex;
	Vector2 groundTexSize;

	//States
	std::unique_ptr<DirectX::CommonStates> states;

public:
	Renderer();
	~Renderer() = default;

	//Draw functions
	void DrawBird(Vector2 pos, float rot, int frame);
	void DrawPipe(Vector2 pos);
	void DrawBackground(Vector2 screenPos, Vector2 origin, int type);

	//Init functions
	backgroundTextureData LoadScrollingTexture(int type);

	void Init(ComPtr<ID3D11Device1> dev, ComPtr<ID3D11DeviceContext1> cont);
	void SetWindow(int w, int h);
	
	void OnDeviceLost();
	inline void BeginSpriteBatch(){ spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied()); }
	inline void EndSpriteBatch(){ spriteBatch->End(); }

	//Setters
	
	inline void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device1> dev) { device = dev; }
	inline void SetContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> cont) { context = cont; }

	//getters
	inline int GetScreenWidth() { return screenWidth; }
	inline int GetScreenHeight() { return screenHeight; }
	inline ComPtr<ID3D11ShaderResourceView> GetBirdTexture() { return birdTextures[0]; }
	inline ComPtr<ID3D11ShaderResourceView> GetPipeTexture() { return pipeTexture; }
};