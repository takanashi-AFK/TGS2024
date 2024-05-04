//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture: register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	g_matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matNormalTrans;	// 法線の変換行列（回転行列と拡大の逆行列）
	float4x4	g_matWorld;			// ワールド変換行列
	float4		g_vecLightDir;		// ライトの方向ベクトル
	float4		g_vecDiffuse;		// ディフューズカラー（マテリアルの色）
	float4		g_vecAmbient;		// アンビエントカラー（影の色）
	float4		g_vecSpeculer;		// スペキュラーカラー（ハイライトの色）
	float4		g_vecCameraPosition;// 視点（カメラの位置）
	float		g_shuniness;		// ハイライトの強さ（テカリ具合）
	bool		g_isTexture;		// テクスチャ貼ってあるかどうか

};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float4 normal : TEXCOORD2;		//法線
	float2 uv	  : TEXCOORD0;		//UV座標
	float4 eye	  : TEXCOORD1;		//視線
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, g_matWVP);		

	//法線の変形
	Normal.w = 0;					//4次元目は使わないので0
	Normal = mul(Normal, g_matNormalTrans);		//オブジェクトが変形すれば法線も変形
	outData.normal = Normal;		//これをピクセルシェーダーへ

	//視線ベクトル（ハイライトの計算に必要
	float4 worldPos = mul(pos, g_matWorld);					//ローカル座標にワールド行列をかけてワールド座標へ
	outData.eye = normalize(g_vecCameraPosition - worldPos);	//視点から頂点位置を引き算し視線を求めてピクセルシェーダーへ

	//UV「座標
	outData.uv = Uv;	//そのままピクセルシェーダーへ


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 diffuse;
	//テクスチャ有無
	if (g_isTexture == true)
	{
		//テクスチャの色
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		//マテリアルの色
		diffuse = g_vecDiffuse;
	}
	
	//最終的な色
	return diffuse;
}