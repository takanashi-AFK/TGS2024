//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D g_texture : register(t0); // テクスチャ
SamplerState g_sampler : register(s0); // サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
    float4x4 g_matWVP; // ワールド・ビュー・プロジェクションの合成行列
    float4 colorMultiplier; // 色の乗数
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
    float4 pos : SV_POSITION; // 位置
    float2 uv : TEXCOORD0; // UV座標
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float2 Uv : TEXCOORD)
{
    VS_OUT outData;

    // ローカル座標に、ワールド・ビュー・プロジェクション行列をかけてスクリーン座標に変換し、ピクセルシェーダーへ
    outData.pos = mul(pos, g_matWVP);

    // UV座標をそのままピクセルシェーダーへ
    outData.uv = Uv;

    return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
    // テクスチャの色をサンプル
    float4 color = g_texture.Sample(g_sampler, inData.uv);

    // 色を乗数で変更
    color *= colorMultiplier;

    // 最終的な色
    return color;
}
