matrix g_matWorld, g_matView, g_matProj;
float g_fCool = 0.f;
float g_fHP = 0.f, g_fMP = 0.f;
texture g_Texture;

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
  //  Out.LocalPos.y += 0.5f;

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
    
	if (In.LocalPos.y <= g_fCool)
    {       
        Out.Color.rbg *= 0.5f;
    }
        return Out;
}

PS_OUT PS_MAIN_INT(PS_IN In)
{
	PS_OUT Out = (PS_OUT)0;

	Out.Color = (tex2D(BaseSampler, In.TexUV));

    if(g_fCool<0)
        return Out;

    float fDegreeCool = g_fCool * 360.f;

    if (In.LocalPos.x>0)
    {
        if (In.LocalPos.y > 0) //1
        {
            float fRadian = atan2(abs(In.LocalPos.x), abs(In.LocalPos.y));
            float fDegree = degrees(fRadian);

            if (fDegree >= fDegreeCool)
                Out.Color.rbg *= 0.5f;

        }
        else//2
        {
            float fRadian = atan2(abs(In.LocalPos.y), abs(In.LocalPos.x));
            float fDegree = degrees(fRadian) +90.f;

            if (fDegree >= fDegreeCool)
                Out.Color.rbg *= 0.5f;
        }

    }
    else
    {
        if (In.LocalPos.y > 0) //4
        {
            float fRadian = atan2(abs(In.LocalPos.y), abs(In.LocalPos.x));
            float fDegree = degrees(fRadian) + 270.f;

            if (fDegree >= fDegreeCool)
                Out.Color.rbg *= 0.5f;
        }
        else//3
        {
            float fRadian = atan2(abs(In.LocalPos.x), abs(In.LocalPos.y));
            float fDegree = degrees(fRadian) + 180.f;

            if (fDegree >= fDegreeCool)
                Out.Color.rbg *= 0.5f;
        }
    }

   
	return Out;
}

technique Default
{
    pass Default_Render
    {	
		CullMode = NONE;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;		
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
	}

	pass Default_Render_INT
	{
		CullMode = NONE;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN_INT();
	}
}
