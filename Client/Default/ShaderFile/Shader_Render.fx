
float	g_fTargetRange = 0.75f;
/////////////////////////////////////////////////////////////////////////////////
texture g_DiffuseTexture;

sampler DiffuseSampler = sampler_state
{
    Texture = g_DiffuseTexture;
    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};

texture g_BlurTexture;

sampler BlurSampler = sampler_state
{
	Texture = g_BlurTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture g_DepthTexture;

sampler DepthSampler = sampler_state
{
	Texture = g_DepthTexture;
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
	vector vBlur = tex2D(BlurSampler, In.TexUV);
	vector vDepth = tex2D(DepthSampler, In.TexUV);

	float fDegree = abs(vDepth.y - g_fTargetRange);

	Out.vColor = vDiffuse*(1.f-fDegree)+ vBlur*(fDegree);

  /*  Out.vColor = lerp(vDiffuse, vBlur, fDegree);*/
    
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