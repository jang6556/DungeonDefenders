
matrix  g_matViewInv;
matrix  g_matProjInv;
matrix  g_matBoxWorldInv;

bool	g_bFlag = false;

vector g_vColor= (vector)1;
/////////////////////////////////////////////////////////////////////////////////
texture g_DecalTexture;

sampler DecalSampler = sampler_state
{
    Texture = g_DecalTexture;

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

texture g_DepthTexture;

sampler DepthSampler = sampler_state
{
	Texture = g_DepthTexture;
};

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
struct PS_IN
{
    float4 Position : POSITION; 
    float2 TexUV : TEXCOORD0;   
};

struct PS_OUT
{
	vector		vColor	  : COLOR;
};
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;
	
	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vPosition = mul(vPosition, g_matBoxWorldInv);

	clip(0.5f - abs(vPosition.xyz));

	float2	TexUV = 0.5f + vPosition.xz;

	Out.vColor = tex2D(DecalSampler, TexUV);

    return Out;
}

PS_OUT PS_MAIN_FILTER(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;
 
	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vPosition = mul(vPosition, g_matBoxWorldInv);

	clip(0.5f - abs(vPosition.xyz));

	float2	TexUV = 0.5f + vPosition.xz;

	Out.vColor = tex2D(DecalSampler, TexUV);

	if (g_bFlag == false)
	{
		float fColor = Out.vColor.g;
		Out.vColor.g = Out.vColor.r;
		Out.vColor.r = fColor;
	}

	Out.vColor.b = 0.f;

	//float4 vColor= tex2D(FilterSampler, TexUV);
	//Out.vColor.g = vColor.g;

	return Out;
}

PS_OUT PS_MAIN_COLOR_ALPHA(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vPosition = mul(vPosition, g_matBoxWorldInv);

	clip(0.5f - abs(vPosition.xyz));

	float2	TexUV = 0.5f + vPosition.xz;

	Out.vColor = tex2D(DecalSampler, TexUV);

	Out.vColor.r *= g_vColor.r;
	Out.vColor.g *= g_vColor.g;
	Out.vColor.b *= g_vColor.b;
	Out.vColor.a *= g_vColor.a;
	//float4 vColor= tex2D(FilterSampler, TexUV);
	//Out.vColor.g = vColor.g;

	return Out;
}

PS_OUT PS_MAIN_CIRCLE(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vPosition = mul(vPosition, g_matBoxWorldInv);

	clip(0.5f - abs(vPosition.xyz));

	float2	TexUV = 0.5f + vPosition.xz;

	Out.vColor = tex2D(DecalSampler, TexUV);

	
	Out.vColor.g = Out.vColor.r;
	
	return Out;
}


/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
technique Default
{
    pass Default_Render
    {	
		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

		ZWRITEENABLE = false;
		
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN();
    }

	pass Default_Render_Filter
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;	

		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN_FILTER();
	}

	pass Default_Render_Alpha_Color
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN_COLOR_ALPHA();
	}

	pass Default_Render_Alpha_Circle
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		ZWRITEENABLE = false;

		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN_CIRCLE();
	}
}
/////////////////////////////////////////////////////////////////////////////////