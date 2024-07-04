struct VertexShaderOutput{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
    float32_t4 color : COLOR0;
};

struct Particle{
    float32_t4x4 world;
    float32_t4 color;
};

struct ViewProjectionMatrix{
    float32_t4x4 viewProj;
};

struct VertexShaderInput{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

struct PixelShaderOutput{
    float32_t4 color : SV_TARGET0;
};

struct Material{
    float32_t4 color;
};