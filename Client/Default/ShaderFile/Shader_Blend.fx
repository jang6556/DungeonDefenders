matrix  g_matViewInv;
matrix  g_matProjInv;

matrix  g_matLightView;
matrix  g_matProj;

/////////////////////////////////////////////////////////////////////////////////
texture g_DiffuseTexture;

sampler DiffuseSampler = sampler_state
{
    Texture = g_DiffuseTexture;
    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};

texture g_DepthTexture;

sampler DepthSampler = sampler_state
{
	Texture = g_DepthTexture;
};

texture g_DepthShadowTexture;

sampler DepthShadowSampler = sampler_state
{
	Texture = g_DepthShadowTexture;
};

texture g_DecalTexture;

sampler DecalSampler = sampler_state
{
	Texture = g_DecalTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_ShadeTexture;

sampler ShadeSampler = sampler_state
{
    Texture = g_ShadeTexture;
};
texture g_SpecularTexture;

sampler SpecularhSampler = sampler_state
{
    Texture = g_SpecularTexture;

    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
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
    vector vColor : COLOR0;
};
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
   
    vector vDiffuse = tex2D(DiffuseSampler, In.TexUV);	
	vector vDecal = tex2D(DecalSampler, In.TexUV);

    vector vShade = tex2D(ShadeSampler, In.TexUV);

	vector vShadowColor = (vector)0.0f;
	vShadowColor.a = 0.2f;

	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;
	
	vector vLightPosition;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vLightPosition = mul(vPosition, g_matLightView);
	vLightPosition = mul(vLightPosition, g_matProj);

	float  fLightDepth = vLightPosition.z;

	float2 fUV = vLightPosition.xy / vLightPosition.w;
	fUV.y = -fUV.y;
	fUV = fUV*0.5f + 0.5f;

	vector vDepthShadowInfo = tex2D(DepthShadowSampler, fUV);
	float fLightViewZ = vDepthShadowInfo.x *1000.f;

	if (fLightDepth > vDepthShadowInfo.y*fLightViewZ)
	{
		vDiffuse = vDiffuse*(1 - vShadowColor.a) + vShadowColor*vShadowColor.a;
	}

	vDiffuse = vDiffuse*(1 - vDecal.a) + vDecal*vDecal.a;    

    Out.vColor = vDiffuse * vShade;
    
    return Out;
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
technique Default
{
    pass Default_Render
    {	
        AlphaTestEnable = true;

        AlphaRef = 0;
        AlphaFunc = Greater;

        ZWriteEnable = false;
		
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN();
    }	
}
/////////////////////////////////////////////////////////////////////////////////