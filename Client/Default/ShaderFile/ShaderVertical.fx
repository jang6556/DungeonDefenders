matrix g_matWorld, g_matView, g_matProj;
float g_fUV = 0.f;
float g_fHP = 0.f, g_fMP = 0.f;
bool  g_Color = false;




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
    float2 TexUV    : TEXCOORD0;
};

struct VS_OUT
{
    float4 Position : POSITION;	
    float2 TexUV : TEXCOORD0;    
	float4 LocalPos : TEXCOORD1;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;     

    matrix matWV, matWVP;

    matWV = mul(g_matWorld, g_matView);
    matWVP = mul(matWV, g_matProj);

    Out.Position = mul(float4(In.Position, 1.f), matWVP);
    Out.TexUV = In.TexUV;
    Out.TexUV.x += g_fUV;
	Out.LocalPos = float4(In.Position, 1.f);
	Out.LocalPos.y += 0.5f;
    return Out;
}


struct PS_IN
{
    float4 Position : POSITION;   
    float2 TexUV : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;  
};

struct PS_OUT
{
    float4 Color : COLOR;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
 
    Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color.a = 0.3f;

	if (!g_Color)
	{
		if (In.LocalPos.y >= g_fHP)
			Out.Color.a = 0.f;

		
	}
	else
	{
		if (In.LocalPos.y >= g_fMP)
			Out.Color.a = 0.f;

		
	}
	
	

    return Out;
}

technique Default
{
    pass Default_Render
    {	
		CullMode = NONE;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;		
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
	}
}
