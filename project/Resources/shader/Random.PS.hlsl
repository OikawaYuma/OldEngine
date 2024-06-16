#include "Fullscreen.hlsli"

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};


float32_t rand2dTo1d(float32_t2 input)
{
    float32_t2 smallValue = sin(3.0f);
    float32_t random = dot(smallValue, input);
    random = frac(sin(random) * 143758.5453f);
    return random;
}

float32_t rand(float32_t3 vec)
{
    float32_t random = dot(vec, float32_t3(12.9898, 78.233, 37.719));
    random = frac(random * 143758.5453);
    return random;
}

PixelShaderOutput main(VertexShaderOutput input)
{
	PixelShaderOutput output;
	// 乱数生成。引数にtexcoordを和刺している
    float32_t random = rand(float32_t3(input.texcoord.x, input.texcoord.y,1.0f));
	// 色にする
        output.color = float32_t4(random, random, random, 1.0f);
        return output;

    };