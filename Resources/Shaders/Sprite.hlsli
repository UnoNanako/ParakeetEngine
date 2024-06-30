struct Material{
    float32_t4 color;
};

struct TransformationMatrix{
    float32_t4x4 world;
};

struct ViewProjectionMatrix{
    float32_t4x4 viewProj;
};

struct VertexShaderOutput{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};

struct PixelShaderOutput{
    float32_t4 color : SV_TARGET0;
};