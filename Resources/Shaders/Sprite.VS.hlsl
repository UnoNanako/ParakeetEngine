#include "Sprite.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMatrix : register(b1);

struct VertexShaderInput{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input){
    VertexShaderOutput output;
    output.position = mul(input.position, gTransformationMatrix.world);
    output.position = mul(output.position, gViewProjectionMatrix.viewProj);
    output.texcoord = input.texcoord;
    return output;
}