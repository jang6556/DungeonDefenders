matrix  g_matViewInv;
matrix  g_matProjInv;

vector g_vCamPos;

/////////////////////////////////////////////////////////////////////////////////
texture g_DiffuseTexture;

sampler DiffuseSampler = sampler_state
{
	Texture = g_DiffuseTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};


texture g_NormalTexture;

sampler NormalSampler = sampler_state
{
	Texture = g_NormalTexture;
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

	Out.vColor = tex2D(DiffuseSampler, In.TexUV);
	vector vNormalInfo = tex2D(NormalSampler, In.TexUV);
	
	vector vNormal = vector(vNormalInfo.xyz * 2 - 1, 0);
	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vector vViewDir = g_vCamPos - vPosition;

	normalize(vViewDir);
	normalize(vNormal);

	float fCos = saturate(dot(vViewDir, vNormal));

	if (fCos <= 0.3f)
	{
		Out.vColor.r = 0;
		Out.vColor.g = 0;
		Out.vColor.b = 0;
	}

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
		
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN();
    }
}
/////////////////////////////////////////////////////////////////////////////////