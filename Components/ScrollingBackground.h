class ScrollingBackground
{
public:
    ScrollingBackground() :
        mScreenHeight(0),
        mScreenWidth(0),
        mTextureWidth(1600),
        mTextureHeight(),
        mScreenPos{},
        mTextureSize{},
        mOrigin{0,0},
        texLoaded(false)
    {
    }

    void SetWindow(int screenWidth, int screenHeight, int type)
    {
        mScreenWidth = screenWidth;

        mScreenPos.x = 0;
        if (type == 0)
            mScreenPos.y = 0;
        else
            mScreenPos.y = 800;
    }

    void Update(float deltaX)
    {
       if (!texLoaded)
           return;
       mScreenPos.x -= deltaX;
       mScreenPos.x = fmodf(mScreenPos.x, float(mTextureWidth)); 
    }

    void Draw(Renderer& renderer, int type)
    {
        
        if (!texLoaded)
        {
            backgroundTextureData data = renderer.LoadScrollingTexture(type);
            mTextureHeight = data.textureHeight;
            mTextureWidth = data.textureWidth;
            texLoaded = true;
        }
        
        //This still is a little bizarre
        
        mScreenPos.x += mTextureWidth;
        
        renderer.DrawBackground(mScreenPos, mOrigin, type);

        mScreenPos.x -= mTextureWidth;

        if (mScreenPos.x < mScreenWidth)
        {
            //DRAW
            renderer.DrawBackground(mScreenPos, mOrigin, type);
        }
        
    }

private:
    int                                                 mScreenHeight;
    int                                                 mScreenWidth;
    int                                                 mTextureWidth;
    int                                                 mTextureHeight;
    bool                                                texLoaded;
    DirectX::SimpleMath::Vector2                        mScreenPos;
    DirectX::SimpleMath::Vector2                        mTextureSize;
    DirectX::SimpleMath::Vector2                        mOrigin;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    mTexture;
};