matrix g_matWorld, g_matView, g_matProj;
float g_fUV_X = 0.f, g_fUV_Y = 0.f;



texture g_Texture;

sampler BaseSampler = sampler_state
{
    Texture = g_Texture;

    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};


struct VS_IN
{
    float3 Position : POSITION;
	float3 Normal	: NORMAL;
    float2 TexUV    : TEXCOORD0;
};

struct VS_OUT
{
    float4 Position : POSITION;
	float4 Normal	: NORMAL;
    float2 TexUV : TEXCOORD0;
    float4 WorldPosition : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    matrix matWV, matWVP;

    matWV = mul(g_matWorld, g_matView);
    matWVP = mul(matWV, g_matProj);

    Out.Position = mul(float4(In.Position, 1.f), matWVP);
    Out.TexUV = In.TexUV;
    Out.Normal = normalize(mul(float4(In.Normal, 0.f), g_matWorld));
    Out.WorldPosition = mul(float4(In.Position, 1.f), g_matWorld);
    return Out;
}

VS_OUT VS_MAIN_UV(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position, 1.f), matWVP);

	Out.TexUV = In.TexUV;
	Out.TexUV.x += g_fUV_X;
	Out.TexUV.y += g_fUV_Y;

	Out.Normal = normalize(mul(float4(In.Normal, 0.f), g_matWorld));
	Out.WorldPosition = mul(float4(In.Position, 1.f), g_matWorld);
	return Out;
}


struct PS_IN
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
    float2 TexUV : TEXCOORD0;
    float4 WorldPosition : TEXCOORD1;
};

struct PS_OUT
{
    float4 Color : COLOR;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;
    
	Out.Color = tex2D(BaseSampler, In.TexUV); 

	Out.Color.a = Out.Color.r;	

    return Out;
}

technique Default
{
    pass Default_Render
    {
		CullMode = None;
	    AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
		
        VertexShader = compile vs_3_0 VS_MAIN_UV();
        PixelShader = compile ps_3_0 PS_MAIN();
    }   

	pass Default_Render_None
	{		
		CullMode = None;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN_UV();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}
