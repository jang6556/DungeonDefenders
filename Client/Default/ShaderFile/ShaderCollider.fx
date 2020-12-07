matrix g_matWorld, g_matView, g_matProj;
bool   g_IsCollision;

struct VS_IN
{
    float3 Position : POSITION;	
};

struct VS_OUT
{
    float4 Position : POSITION;	
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    matrix matWV, matWVP;

    matWV = mul(g_matWorld, g_matView);
    matWVP = mul(matWV, g_matProj);

    Out.Position = mul(float4(In.Position, 1.f), matWVP);   
    return Out;
}


struct PS_IN
{
    float4 Position : POSITION;
    
};

struct PS_OUT
{
    float4 Color : COLOR;
};

PS_OUT PS_MAIN(PS_IN In)
{
    PS_OUT Out = (PS_OUT) 0;
   
	Out.Color = vector( g_IsCollision ,1 - g_IsCollision ,0.f,1.f );

    return Out;
}

technique Default
{
    pass Default_Render
    {	        
		fillmode = wireframe;
		
        VertexShader = compile vs_3_0 VS_MAIN();
        PixelShader = compile ps_3_0 PS_MAIN();
    }

    
}
