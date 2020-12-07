matrix g_matWorld, g_matView, g_matProj;
float g_fUV_X = 0.f, g_fUV_Y = 0.f;

vector g_vColor;


texture g_Texture;

sampler BaseSampler = sampler_state
{
    Texture = g_Texture;

    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};

texture g_FilterTexture;

sampler FilterSampler = sampler_state
{
	Texture = g_FilterTexture;

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
	float4 ProjPos : TEXCOORD2;
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
	Out.ProjPos = Out.Position;

    return Out;
}

VS_OUT VS_MAIN_SHADOW(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position, 1.f), matWVP);
	Out.TexUV = In.TexUV;	
	Out.ProjPos = Out.Position;

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
	float4 ProjPos : TEXCOORD2;
};

struct PS_OUT
{
    vector vDiffuse : COLOR0;
	vector vNormal : COLOR1;
	vector vDepth : COLOR2;
};

struct PS_OUT_SHADOW
{
	vector vDepth : COLOR0;	
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
   
    Out.vDiffuse = (tex2D(BaseSampler, In.TexUV));
    
	Out.vNormal = vector(In.Normal.xyz*0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.ProjPos.w / 1000.f, In.ProjPos.z / In.ProjPos.w, 0.f, 0.f);

    return Out;
}

PS_OUT_SHADOW PS_MAIN_SHADOW(PS_IN In)
{
	PS_OUT_SHADOW Out = (PS_OUT_SHADOW)0;

	Out.vDepth = vector(In.ProjPos.w / 1000.f, In.ProjPos.z / In.ProjPos.w, 0.f, 1.f);

	return Out;
}

PS_OUT PS_MAIN_UV(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.vDiffuse = (tex2D(BaseSampler, In.TexUV));	

	Out.vDiffuse += g_vColor;

	return Out;
}



PS_OUT PS_MAIN_FILTER(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vDiffuse = (tex2D(BaseSampler, In.TexUV));
	vector vFilter =  (tex2D(FilterSampler, In.TexUV));
	
	vDiffuse += g_vColor - vFilter*0.5f;
	vDiffuse.a = vFilter.a;
	Out.vDiffuse = vDiffuse;
	 
	Out.vNormal = vector(In.Normal.xyz*0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.ProjPos.w / 1000.f, In.ProjPos.z / In.ProjPos.w, 0.f, 0.f);

	return Out;
}

technique Default
{
    pass Default_Render
    {	
		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }

    pass Default_Render_CCW
    {
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }

    pass Default_Render_NONE
    {
        CullMode = NONE;

		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN_FILTER();
    }

    pass Default_TerrainRender
    {        
        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        ZEnable = false;
        ZWriteEnable = false;
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }

	pass Default_Render_UV
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		
		VertexShader = compile vs_3_0 VS_MAIN_UV();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_BEAM
	{
		CullMode = NONE;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN_UV();
		PixelShader = compile ps_3_0 PS_MAIN_UV();
	}

	pass Default_Render_MESH
	{
		CullMode = NONE;

		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_Shadow
	{
		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

		VertexShader = compile vs_3_0 VS_MAIN_SHADOW();
		PixelShader = compile ps_3_0 PS_MAIN_SHADOW();
	}
	
}
