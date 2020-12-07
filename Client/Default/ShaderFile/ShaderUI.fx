matrix g_matWorld, g_matView, g_matProj;
float g_fUV = 0.f;
float g_fCurrUV = 0.f;
float g_fGlare = 0.f;
float g_fHP = 0.f;
float g_fStart = 0.f;

vector g_vColor=(vector)0;
float  g_fRatio = 0;
float  g_fU = 0;

float  g_fSizeX = 0, g_fSizeY = 0;

float  g_fAlpha = 0.f;



texture g_Filter;

sampler FilterSampler = sampler_state
{
	Texture = g_Filter;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_Filter_Wave;

sampler FilterSampler_Wave = sampler_state
{
    Texture = g_Filter_Wave;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_Texture;

sampler BaseSampler = sampler_state
{
    Texture = g_Texture;

    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};

texture g_Texture_One;

sampler BaseSampler_One = sampler_state
{
    Texture = g_Texture_One;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_Texture_Ten;

sampler BaseSampler_Ten = sampler_state
{
	Texture = g_Texture_Ten;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_AlphaTexture;

sampler AlphaSampler = sampler_state
{
	Texture = g_AlphaTexture;

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
	float2 WaveUV : TEXCOORD1;
	float3 LocalPos : TEXCOORD2;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;     

    matrix matWV, matWVP;

    matWV = mul(g_matWorld, g_matView);
    matWVP = mul(matWV, g_matProj);

    Out.Position = mul(float4(In.Position, 1.f), matWVP);
    Out.TexUV = In.TexUV;
	

    return Out;
}

VS_OUT VS_MAIN_HP_CURR(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position, 1.f), matWVP);
	Out.TexUV = In.TexUV;   
	Out.WaveUV = In.TexUV;

	Out.WaveUV.x *= 1.5f;
	Out.WaveUV.y *= 0.5f;

	Out.WaveUV.x += g_fCurrUV;
	Out.WaveUV.y += 0.33f;
	

	Out.LocalPos = In.Position + float3(0.5f,0.f,0.f);

	return Out;
}

VS_OUT VS_MAIN_HP_COLOR(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    matrix matWV, matWVP;

    matWV = mul(g_matWorld, g_matView);
    matWVP = mul(matWV, g_matProj);

    Out.Position = mul(float4(In.Position, 1.f), matWVP);
    Out.TexUV = In.TexUV;
    Out.WaveUV = In.TexUV;
	Out.WaveUV.x *= g_fSizeX;
	Out.WaveUV.y *= g_fSizeY;

	Out.WaveUV.x += g_fU;
		
    return Out;
}

VS_OUT VS_MAIN_HP_NUM(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position , 1.f), matWVP);
	Out.TexUV = In.TexUV;
	Out.WaveUV = In.TexUV;
	Out.WaveUV.x = (Out.WaveUV - g_fStart)*3.f;


	return Out;
}


struct PS_IN
{
    float4 Position : POSITION;   
    float2 TexUV : TEXCOORD0;
	float2 WaveUV : TEXCOORD1;
	float3 LocalPos : TEXCOORD2;
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

PS_OUT PS_MAIN_HP_CURR(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 Color = (tex2D(BaseSampler, In.TexUV));

    float4 Tile = (tex2D(FilterSampler, In.WaveUV));
	
    Color.rgb = Tile.rgb + g_fGlare;
	Color.r *= 1.5f;
	Color.gb *= 0.1f;

	if (In.LocalPos.x > g_fHP)
		Color.a = 0;

	Out.Color = Color;

	return Out;
}

PS_OUT PS_MAIN_HP_COLOR(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
	
    vector vAlpha = (tex2D(BaseSampler, In.TexUV));
	vector vFilter = (tex2D(FilterSampler, In.WaveUV));

	vector vColor = g_vColor;

	vFilter.a =vFilter.r;
	vColor.a = vAlpha.r;	
	
	if (In.TexUV.x > g_fRatio)
		vColor.a = 0;  

	vColor.rgb *= vFilter.a;
	vColor.rgb *= 5.f;
	Out.Color = vColor;

    return Out;
}

PS_OUT PS_MAIN_HP_COLOR_ALPHA(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vAlpha = (tex2D(BaseSampler, In.TexUV));
	vector vFilter = (tex2D(FilterSampler, In.WaveUV));

	vector vColor = g_vColor;

	vFilter.a = vFilter.r;
	vColor.a = vAlpha.r;

	if (In.TexUV.x > g_fRatio)
		vColor.a = 0;

	vColor.rgb *= vFilter.a;
	vColor.rgb *= 5.f;
	vColor.a *= g_fAlpha;
	Out.Color = vColor;

	return Out;
}

PS_OUT PS_MAIN_HP_Num(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;


	if (In.TexUV.x >= g_fStart && In.TexUV.x < g_fStart + 0.33f)
	{
		Out.Color = (tex2D(BaseSampler, In.WaveUV));
	}
	else
		Out.Color = float4(0, 0, 0, 0);
	
    return Out;
}

PS_OUT PS_MAIN_Alpha(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color.a *= g_fAlpha;

	return Out;
}

PS_OUT PS_MAIN_HP_FILTER_ALPHA(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));
	vector vAlpha = (tex2D(AlphaSampler, In.TexUV));

	Out.Color.a += -vAlpha.r*0.5f;

	return Out;
}

PS_OUT PS_MAIN_COLOR(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));
	
	Out.Color.r *= g_vColor.r;
	Out.Color.g *= g_vColor.g;
	Out.Color.b *= g_vColor.b;

	return Out;
}

technique Default
{
    pass Default_Render
    {	
        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;	

		zwriteenable = false;
		Zenable = false;
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_Tile
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN_HP_CURR();
		PixelShader = compile ps_3_0 PS_MAIN_HP_CURR();
	}

    pass Default_Render_Color
    {
        CullMode = CCW;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

        VertexShader = compile vs_3_0 VS_MAIN_HP_COLOR();
        PixelShader = compile ps_3_0 PS_MAIN_HP_COLOR();
    }

	pass Default_Render_Num
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN_HP_NUM();
		PixelShader = compile ps_3_0 PS_MAIN_HP_Num();
	}

	pass Default_Render_Alpha
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_Alpha();
	}

	pass Default_Render_Alpha_Color
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN_HP_COLOR();
		PixelShader = compile ps_3_0 PS_MAIN_HP_COLOR_ALPHA();
	}

	pass Default_Render_Alpha_Filter
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN_HP_COLOR();
		PixelShader = compile ps_3_0 PS_MAIN_HP_FILTER_ALPHA();
	}

	pass Default_Render_AlphaTest
	{
		CullMode = CCW;

		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 10;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_AlphaTest
	{
		CullMode = CCW;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		zwriteenable = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_COLOR();
	}
}
