#include "Particle.hlsli"

StructuredBuffer<Particle> gParticle : register(t0);
ConstantBuffer<ViewProjectionMatrix> gViewProjectionMatrix : register(b0);

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID){
    VertexShaderOutput output;
    output.position = mul(input.position, gParticle[instanceId].world);
    output.position = mul(output.position, gViewProjectionMatrix.viewProj);
    output.texcoord = input.texcoord;
    output.color = gParticle[instanceId].color;
    return output;
}