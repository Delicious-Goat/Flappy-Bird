#include "pch.h"
#include "Renderer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

Renderer::Renderer() :
	screenHeight(0),
	screenWidth(0)
{
}

void Renderer::DrawBird(Vector2 pos, float rot)
{


	spriteBatch->Draw(birdTexture.Get(), pos, nullptr, Colors::White, rot, origin, 3.5);	
}

void Renderer::DrawBackground(Vector2 screenPos, Vector2 origin, int type)
{
	ComPtr<ID3D11ShaderResourceView> texture;
	if (type == 0)
		texture = backgroundTex;
	else if (type == 1)
		texture = groundTex;

	spriteBatch->Draw(texture.Get(), screenPos, nullptr,
		Colors::White, 0.f, origin, g_XMOne,
		SpriteEffects_None, 0);
}

backgroundTextureData Renderer::LoadScrollingTexture(int type)
{
	backgroundTextureData texData;

	if (backgroundTex)
	{
		Microsoft::WRL::ComPtr<ID3D11Resource> resource;
		if(type == 0)
			backgroundTex->GetResource(resource.GetAddressOf());
		else
			groundTex->GetResource(resource.GetAddressOf());

		D3D11_RESOURCE_DIMENSION dim;
		resource->GetType(&dim);

		if (dim != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
			throw std::exception("ScrollingBackground expects a Texture2D");

		Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
		resource.As(&tex2D);

		D3D11_TEXTURE2D_DESC desc;
		tex2D->GetDesc(&desc);

		texData.textureWidth = desc.Width;
		texData.textureHeight = desc.Height;
		
		texData.type = type;	

		return texData;
	}	
}


void Renderer::OnDeviceLost()
{
	birdTexture.Reset();
	backgroundTex.Reset();
	groundTex.Reset();
	spriteBatch.reset();
}



void Renderer::Init(Microsoft::WRL::ComPtr<ID3D11Device1> dev, Microsoft::WRL::ComPtr<ID3D11DeviceContext1> cont)
{
	//Init device and context
	device = dev;
	context = cont;

	//Init sprite batch
	spriteBatch = std::make_unique<SpriteBatch>(context.Get());

	//Init Bird Texture
	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(device.Get(), L"Art/Bird.png",
			resource.GetAddressOf(),
			birdTexture.ReleaseAndGetAddressOf()));

	ComPtr<ID3D11Texture2D> birdTex;
	DX::ThrowIfFailed(resource.As(&birdTex));

	CD3D11_TEXTURE2D_DESC birdDesc;
	birdTex->GetDesc(&birdDesc);

	origin.x = float(birdDesc.Width / 2);
	origin.y = float(birdDesc.Height / 2);

	//background
	DX::ThrowIfFailed(CreateWICTextureFromFile(device.Get(), L"Art/Background.png",
		nullptr, backgroundTex.ReleaseAndGetAddressOf()));

	//background
	DX::ThrowIfFailed(CreateWICTextureFromFile(device.Get(), L"Art/ground.png",
		nullptr, groundTex.ReleaseAndGetAddressOf()));
}

void Renderer::SetWindow(int w, int h)
{
	screenHeight = h; 
	screenWidth = w;
}
