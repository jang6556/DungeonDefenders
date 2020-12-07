matrix g_matWorld, g_matView, g_matProj;
float g_fUV = 0.f;
float g_fAlpha = 1.f;
float g_fHP = 0.f, g_fMP = 0.f;
texture g_Texture;
texture g_FilterTexture;

float g_fU = 0.f;
float g_fV = 0.f;

vector g_vColor = (vector)0;
vector g_vColorPng = (vector)0;

sampler FilterSampler = sampler_state
{
	Texture = g_FilterTexture;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

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

struct VS_OUT_FILTER
{
	float4 Position : POSITION;
	float2 TexUV : TEXCOORD0;
	float2 FilterUV : TEXCOORD1;
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

VS_OUT_FILTER VS_MAIN_UV_Y(VS_IN In)
{
	VS_OUT_FILTER Out = (VS_OUT_FILTER)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position+float3(0,0.5f,0), 1.f), matWVP);
	Out.TexUV = In.TexUV;
	Out.TexUV.y += g_fUV;
	Out.FilterUV = In.TexUV;

	return Out;
}

VS_OUT VS_MAIN_ALPHA(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position, 1.f), matWVP);
	Out.TexUV = In.TexUV;	
	Out.LocalPos = float4(In.Position, 1.f);

	return Out;
}

VS_OUT_FILTER VS_MAIN_UV(VS_IN In)
{
	VS_OUT_FILTER Out = (VS_OUT_FILTER)0;

	matrix matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.Position = mul(float4(In.Position, 1.f), matWVP);
	Out.TexUV = In.TexUV;
	Out.TexUV.x += g_fU;
	Out.TexUV.y += g_fV;
	Out.FilterUV = In.TexUV;
	return Out;
}


struct PS_IN
{
    float4 Position : POSITION;   
    float2 TexUV : TEXCOORD0;
	float4 LocalPos : TEXCOORD1;  
};

struct PS_IN_FILTER
{
	float4 Position : POSITION;
	float2 TexUV : TEXCOORD0;
	float2 FilterUV : TEXCOORD1;
};

struct PS_OUT
{
    float4 Color : COLOR;
};

PS_OUT PS_MAIN_RED(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
 
	Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color.a = Out.Color.r;
			
	Out.Color += g_vColor;
	
    return Out;
}

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;
 
    Out.Color = (tex2D(BaseSampler, In.TexUV));    
	return Out;
}

PS_OUT PS_MAIN_GREEN(PS_IN_FILTER In)
{
	PS_OUT Out = (PS_OUT)0;

	float4 Alpha = (tex2D(FilterSampler, In.FilterUV));
	Out.Color	 = (tex2D(BaseSampler, In.TexUV));

	Out.Color.rb    *= 0.f;

	Out.Color.a   = Alpha.a*0.7f;

	return Out;
}

PS_OUT PS_MAIN_COLOR(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color += g_vColor;

	return Out;
}

PS_OUT PS_MAIN_COLOR_ALPHA(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));
	Out.Color.a = Out.Color.r;

	Out.Color += g_vColor;

	Out.Color.a *= g_fAlpha;

	return Out;
}

PS_OUT PS_MAIN_BLUE(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));

	float fRed = Out.Color.r;

	Out.Color.r = Out.Color.b;
	Out.Color.b = fRed;

	return Out;
}

PS_OUT PS_MAIN_YELLOW(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));
	Out.Color.g = Out.Color.r;
	return Out;
}

PS_OUT PS_MAIN_PNG(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));
	Out.Color.a = Out.Color.r;

	Out.Color.r *= g_vColorPng.r;
	Out.Color.g *= g_vColorPng.g;
	Out.Color.b *= g_vColorPng.b;
	Out.Color.a *= g_vColorPng.a;

	return Out;
}

PS_OUT PS_MAIN_ALPHA_FILTER(PS_IN_FILTER In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vAlphaFilter = tex2D(FilterSampler, In.FilterUV);
	Out.Color = (tex2D(BaseSampler, In.TexUV));

	Out.Color.a *= vAlphaFilter.a*g_fAlpha;

	return Out;
}

technique Default
{
    pass Default_Render
    {	
		AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
	}

    pass Default_RED
    {
		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

		ZWRITEENABLE = false;
		
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN_RED();
    }

    pass NOT_ZENABLE_Render
    {
        CullMode = CCW;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;      

		ZWRITEENABLE = false;

        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }

	pass GREEN_UV_Y_Render
	{
		CullMode = NONE;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = compile vs_3_0 VS_MAIN_UV_Y();
		PixelShader = compile ps_3_0 PS_MAIN_GREEN();
	}

	pass Default_Render_COLOR
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_COLOR();
	}

	pass Default_Render_COLOR_ALPHA
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = compile vs_3_0 VS_MAIN_ALPHA();
		PixelShader = compile ps_3_0 PS_MAIN_COLOR_ALPHA();
	}

	pass Default_Render_COLOR_BLUE
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_BLUE();
	}

	pass Default_Render_COLOR_YELLOW
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;
		Zenable = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_YELLOW();
	}

	pass Default_Render_Png
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;		

		VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN_PNG();
    }

	pass Default_Render_Alpha_Filter
	{
		CullMode = NONE;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = compile vs_3_0 VS_MAIN_UV();
		PixelShader = compile ps_3_0 PS_MAIN_ALPHA_FILTER();
	}
}
