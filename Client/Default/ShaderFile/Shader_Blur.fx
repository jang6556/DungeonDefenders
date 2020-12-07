
float4 gaussFilterX[13] =
{
	-6.0f, 0.0f ,  0.0f, 0.002216f,
	-5.0f, 0.0f ,  0.0f, 0.008764f,
	-4.0f, 0.0f ,  0.0f, 0.026995f,
	-3.0f, 0.0f ,  0.0f, 0.064759f,
	-2.0f, 0.0f ,  0.0f, 0.120985f,
	-1.0f, 0.0f ,  0.0f, 0.176033f,
	0.0f, 0.0f  ,  0.0f, 0.199471f,
	1.0f, 0.0f  ,  0.0f, 0.176033f,
	2.0f, 0.0f  ,  0.0f, 0.120985f,
	3.0f, 0.0f  ,  0.0f, 0.064759f,
	4.0f, 0.0f ,  0.0f,  0.026995f,
	5.0f, 0.0f ,  0.0f,  0.008764f,
	6.0f, 0.0f ,  0.0f,  0.002216f,
};

float4 gaussFilterY[13] =
{
	0.0f , -6.0f,  0.0f, 0.002216f,
	0.0f , -5.0f,  0.0f, 0.008764f,
	0.0f , -4.0f,  0.0f, 0.026995f,
	0.0f , -3.0f,  0.0f, 0.064759f,
	0.0f , -2.0f,  0.0f, 0.120985f,
	0.0f , -1.0f,  0.0f, 0.176033f,
	0.0f ,  0.0f ,  0.0f, 0.199471f,
	0.0f ,  1.0f ,  0.0f, 0.176033f,
	0.0f ,  2.0f ,  0.0f, 0.120985f,
	0.0f ,  3.0f ,  0.0f, 0.064759f,
	0.0f ,  4.0f,  0.0f,  0.026995f,
	0.0f ,  5.0f,  0.0f,  0.008764f,
	0.0f ,  6.0f,  0.0f,  0.002216f,
};

float texScaler = 1.0f / 128.0f;
float texOffset = 0.0f;

/////////////////////////////////////////////////////////////////////////////////
texture g_DiffuseTexture;

sampler2D DiffuseSampler = sampler_state
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

	vector vColor = (vector)0.0f;

	int i;
	for (i = 0; i < 13; i++)
	{
		vColor += tex2D(DiffuseSampler, float2(In.TexUV.x + gaussFilterY[i].x*texScaler + texOffset, In.TexUV.y + gaussFilterY[i].y * texScaler + texOffset))*gaussFilterY[i].w;
	}

	Out.vColor = vColor;

    return Out;
}

PS_OUT PS_MAIN_X(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vColor = (vector)0.0f;

	int i;
	for (i = 0; i < 13; i++)
	{
		vColor += tex2D(DiffuseSampler, 
			      float2(In.TexUV.x + gaussFilterX[i].x*texScaler + texOffset, 
				  In.TexUV.y + gaussFilterX[i].y * texScaler + texOffset))*gaussFilterX[i].w;
	}

	Out.vColor = vColor;

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

		zwriteenable = false;
		
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN();
    }

	pass Default_Render_X
	{
		AlphaTestEnable = true;

		AlphaFunc = Greater;
		AlphaRef = 0;

		zwriteenable = false;

		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN_X();
	}
}
/////////////////////////////////////////////////////////////////////////////////