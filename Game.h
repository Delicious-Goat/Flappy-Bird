//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "Renderer.h"
#include  "ScrollingBackground.h"
#include "Bird.h"
#include "Pipe.h"
#include "pch.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game() noexcept;
    ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:
    void Input();
    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

    //keyboard and mouse
    std::unique_ptr<DirectX::Keyboard> keyboard;
    Keyboard::KeyboardStateTracker tracker;
    std::unique_ptr<DirectX::Mouse> mouse;

    //Renderer
    Renderer renderer;

    //Speed
    float speed = 500;
    bool active;

    //Background
    ScrollingBackground* background;
    ScrollingBackground* ground;

    //Bird
    Bird* bird;

    //Pipe
    Pipe* pipes[6];
};
