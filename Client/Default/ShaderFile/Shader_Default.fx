matrix g_matWorld, g_matView, g_matProj;
texture g_Texture;
float	 g_fAlpha = 0.f;

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
	Out.LocalPos = float4(In.Position, 1.f);

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
	

    return Out;
}

PS_OUT PS_MAIN_ALPHA(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color.r = 0.8f;
	Out.Color.g = 0.4f;
	Out.Color.b = 0.0f;
		
	if (In.TexUV.x > g_fAlpha)
		Out.Color.a = 0.f;

	return Out;
}

technique Default
{
    pass Default_Render
    {	
		CullMode = CCW;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;		
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_Alpha
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_ALPHA();
	}
}
