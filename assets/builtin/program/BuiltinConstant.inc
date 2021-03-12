cbuffer cbPerObject : register(b0)
{
    float4x4 TINY3D_MATRIX_M;
    float4x4 TINY3D_MATRIX_I_M;
    float4x4 TINY3D_MATRIX_T_M;
    float4x4 TINY3D_MATRIX_IT_M;
    
    float4x4 TINY3D_MATRIX_MV;
    float4x4 TINY3D_MATRIX_I_MV;
    float4x4 TINY3D_MATRIX_T_MV;
    float4x4 TINY3D_MATRIX_IT_MV;
    
    float4x4 TINY3D_MATRIX_MVP;
    float4x4 TINY3D_MATRIX_I_MVP;
    float4x4 TINY3D_MATRIX_T_MVP;
    float4x4 TINY3D_MATRIX_IT_MVP;
};

cbuffer cbPerFrame : register(b1)
{
    float4x4 TINY3D_MATRIX_V;
    float4x4 TINY3D_MATRIX_I_V;
    float4x4 TINY3D_MATRIX_T_V;
    float4x4 TINY3D_MATRIX_IT_V;
    
    float4x4 TINY3D_MATRIX_VP;
    float4x4 TINY3D_MATRIX_I_VP;
    float4x4 TINY3D_MATRIX_T_VP;
    float4x4 TINY3D_MATRIX_IT_VP;
};

cbuffer cbRarely : register(b2)
{
    float4x4 TINY3D_MATRIX_P;
    float4x4 TINY3D_MATRIX_I_P;
    float4x4 TINY3D_MATRIX_T_P;
    float4x4 TINY3D_MATRIX_IT_P;
};