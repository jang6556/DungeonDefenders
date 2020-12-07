

vector	g_vLightDir;

vector	g_vLightPos;
float	g_fRange;

vector  g_vCamPos;

matrix  g_matViewInv;
matrix  g_matProjInv;

vector  g_vLightDiffuse;
vector  g_vLightSpecular;
vector  g_vLightAmbient;

vector  g_vMaterialDiffuse =(vector)1.f;
vector  g_vMaterialSpecular = (vector)1.f;
vector  g_vMaterialAmbient = (vector)1.f;
float   g_fPower = 30.f;


/////////////////////////////////////////////////////////////////////////////////
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
	vector		vShade	  : COLOR0;
	vector		vSpecular : COLOR1;
};
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
PS_OUT PS_MAIN_DIRECTION(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;    
   
	vector vNormalInfo = tex2D(NormalSampler, In.TexUV);
	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	vector vNormal = vector(vNormalInfo.xyz * 2 - 1, 0);

	Out.vShade = saturate((g_vLightDiffuse*g_vMaterialDiffuse)*max(dot(normalize(g_vLightDir)*-1.f, vNormal), 0.f) + (g_vLightAmbient*g_vMaterialAmbient));
	Out.vShade.a = 1.f;
    
    return Out;
}

PS_OUT PS_MAIN_POINT(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	vector vNormalInfo = tex2D(NormalSampler, In.TexUV);
	vector vDepthInfo = tex2D(DepthSampler, In.TexUV);

	vector vNormal = vector(vNormalInfo.xyz * 2 - 1, 0);

	float  fViewZ = vDepthInfo.x * 1000.f;

	vector vPosition;

	vPosition.x = (In.TexUV.x * 2.f - 1.f)*fViewZ;
	vPosition.y = (In.TexUV.y *-2.f + 1.f)*fViewZ;
	vPosition.z = vDepthInfo.y*fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vector vLightDir = vPosition - g_vLightPos;

	float fDistance = length(vLightDir);

	float fAtt = max((g_fRange - fDistance)*1.5f / g_fRange, 0.f);

	Out.vShade = saturate((g_vLightDiffuse*g_vMaterialDiffuse)*max(dot(normalize(g_vLightDir)*-1.f, vNormal), 0.f) + (g_vLightAmbient*g_vMaterialAmbient))*fAtt;
	Out.vShade.a = 1.f;

	return Out;
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
technique Default
{
    pass Direction_Render
    {	
		AlphaBlendEnable = true;
		SrcBlend = one;
		DestBlend = one;

		ZWriteEnable = false;
		
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_MAIN_DIRECTION();
    }	

	pass Point_Render
	{
		AlphaBlendEnable = true;
		SrcBlend = one;
		DestBlend = one;

		ZWriteEnable = false;

		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN_POINT();
	}
}
/////////////////////////////////////////////////////////////////////////////////