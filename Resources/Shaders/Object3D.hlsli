struct Material{
    float32_t4 color;
    int32_t enableLighting;
    float32_t shininess;
    uint32_t shadeType;
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
    float32_t3 normal : NORMAL0;
    float32_t3 worldPosition : POSITION0;
};

struct VertexShaderInput{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};

struct PixelShaderOutput{
    float32_t4 color : SV_TARGET0;
};
