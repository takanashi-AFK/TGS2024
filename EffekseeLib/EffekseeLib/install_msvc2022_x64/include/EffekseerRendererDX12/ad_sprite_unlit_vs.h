#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tvs_4_0 /Emain /Fh ShaderHeader/ad_sprite_unlit_vs.h
//    Shader/ad_sprite_unlit_vs.fx
//
//
// Buffer Definitions: 
//
// cbuffer VS_ConstantBuffer
// {
//
//   float4x4 _263_mCamera;             // Offset:    0 Size:    64 [unused]
//   float4x4 _263_mCameraProj;         // Offset:   64 Size:    64
//   float4 _263_mUVInversed;           // Offset:  128 Size:    16
//   float4 _263_flipbookParameter1;    // Offset:  144 Size:    16
//   float4 _263_flipbookParameter2;    // Offset:  160 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// VS_ConstantBuffer                 cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xyz         0     NONE  float   xyz 
// TEXCOORD                 1   xyzw        1     NONE  float   xyzw
// TEXCOORD                 2   xy          2     NONE  float   xy  
// TEXCOORD                 3   xyzw        3     NONE  float   xyzw
// TEXCOORD                 4   xy          4     NONE  float   xy  
// TEXCOORD                 5   xyzw        5     NONE  float   xyzw
// TEXCOORD                 6   x           6     NONE  float   x   
// TEXCOORD                 7   x           7     NONE  float   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xyzw        0     NONE  float   xyzw
// TEXCOORD                 1   xyzw        1     NONE  float   xyzw
// TEXCOORD                 2   xyz         2     NONE  float   xyz 
// TEXCOORD                 3   xyzw        3     NONE  float   xyzw
// TEXCOORD                 4   xyzw        4     NONE  float   xyzw
// TEXCOORD                 5   xyzw        5     NONE  float   xyzw
// TEXCOORD                 6   xyzw        6     NONE  float   xyzw
// SV_Position              0   xyzw        7      POS  float   xyzw
//
vs_4_0
dcl_constantbuffer cb0[11], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyzw
dcl_input v2.xy
dcl_input v3.xyzw
dcl_input v4.xy
dcl_input v5.xyzw
dcl_input v6.x
dcl_input v7.x
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_output o2.xyz
dcl_output o3.xyzw
dcl_output o4.xyzw
dcl_output o5.xyzw
dcl_output o6.xyzw
dcl_output_siv o7.xyzw, position
dcl_temps 8
mad r0.x, cb0[8].y, v2.y, cb0[8].x
mul r1.xyzw, v0.yyyy, cb0[5].xyzw
mad r1.xyzw, cb0[4].xyzw, v0.xxxx, r1.xyzw
mad r1.xyzw, cb0[6].xyzw, v0.zzzz, r1.xyzw
add r1.xyzw, r1.xyzw, cb0[7].xyzw
mad o3.yw, cb0[8].yyyy, v3.yyyw, cb0[8].xxxx
mad r2.x, cb0[8].y, v4.y, cb0[8].x
mad o4.yw, cb0[8].yyyy, v5.yyyw, cb0[8].xxxx
lt r3.x, l(0.000000), cb0[9].x
if_nz r3.x
  frc r0.y, v6.x
  round_ni r3.x, v6.x
  add r3.w, r3.x, l(1.000000)
  mul r4.x, cb0[9].w, cb0[9].z
  eq r4.y, cb0[9].y, l(0.000000)
  if_nz r4.y
    ge r4.y, r3.w, r4.x
    mad r4.z, cb0[9].z, cb0[9].w, l(-1.000000)
    add r3.y, r3.x, l(1.000000)
    movc r4.yz, r4.yyyy, r4.zzzz, r3.xxyx
  else 
    div r3.y, r3.x, r4.x
    round_ni r3.y, r3.y
    mad r5.x, -r4.x, r3.y, r3.x
    div r4.w, r3.w, r4.x
    round_ni r4.w, r4.w
    mad r5.y, -r4.x, r4.w, r3.w
    eq r5.zw, cb0[9].yyyy, l(0.000000, 0.000000, 1.000000, 2.000000)
    mul r3.w, r3.y, l(0.500000)
    round_ni r3.w, r3.w
    mad r3.y, -r3.w, l(2.000000), r3.y
    eq r3.y, r3.y, l(1.000000)
    mad r3.w, cb0[9].z, cb0[9].w, l(-1.000000)
    round_ni r6.xy, r5.xyxx
    add r6.xy, r3.wwww, -r6.xyxx
    movc r7.x, r3.y, r6.x, r5.x
    mul r3.y, r4.w, l(0.500000)
    round_ni r3.y, r3.y
    mad r3.y, -r3.y, l(2.000000), r4.w
    eq r3.y, r3.y, l(1.000000)
    movc r7.y, r3.y, r6.y, r5.y
    add r3.z, r3.x, l(1.000000)
    movc r3.xy, r5.wwww, r7.xyxx, r3.xzxx
    movc r4.yz, r5.zzzz, r5.xxyx, r3.xxyx
  endif 
  mad r3.y, cb0[8].y, r0.x, cb0[8].x
  ftoi r3.zw, r4.yyyz
  ftoi r4.x, cb0[9].z
  and r4.yz, r3.zzwz, l(0, 0x80000000, 0x80000000, 0)
  imax r5.xy, r3.zwzz, -r3.zwzz
  imax r4.w, r4.x, -r4.x
  udiv r5.x, r6.x, r5.x, r4.w
  ineg r5.z, r6.x
  movc r4.y, r4.y, r5.z, r6.x
  itof r6.x, r4.y
  xor r3.zw, r3.zzzw, r4.xxxx
  ineg r4.x, r5.x
  and r3.zw, r3.zzzw, l(0, 0, 0x80000000, 0x80000000)
  movc r3.z, r3.z, r4.x, r5.x
  itof r6.y, r3.z
  mad r4.xy, r6.xyxx, cb0[10].xyxx, cb0[10].zwzz
  mov r3.x, v2.x
  add r3.xy, r3.xyxx, -r4.xyxx
  udiv r4.x, r5.x, r5.y, r4.w
  ineg r3.z, r5.x
  movc r3.z, r4.z, r3.z, r5.x
  itof r5.x, r3.z
  ineg r3.z, r4.x
  movc r3.z, r3.w, r3.z, r4.x
  itof r5.y, r3.z
  mad r3.xy, r5.xyxx, cb0[10].xyxx, r3.xyxx
  add r3.xy, r3.xyxx, cb0[10].zwzz
  mad r3.z, cb0[8].y, r3.y, cb0[8].x
  mov r2.yz, r3.xxzx
else 
  mov r2.yz, l(0,0,0,0)
  mov r0.y, l(0)
endif 
mov o0.xyzw, v1.xyzw
mov r0.z, v2.x
mov r0.w, v7.x
mov o1.xyzw, r0.zxyw
mov o3.xz, v3.xxzx
mov o4.xz, v5.xxzx
mov r2.w, v4.x
mov o5.xyzw, r2.wxyz
mov o6.xyzw, r1.xyzw
mov o7.xyzw, r1.xyzw
mov o2.xyz, l(0,0,0,0)
ret 
// Approximately 90 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67, 108, 192, 
    223,  40, 214, 172, 169,  26, 
    160, 184,  55, 128, 195, 202, 
    111,  67,   1,   0,   0,   0, 
    236,  14,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    212,   1,   0,   0, 176,   2, 
      0,   0, 152,   3,   0,   0, 
    112,  14,   0,   0,  82,  68, 
     69,  70, 152,   1,   0,   0, 
      1,   0,   0,   0,  80,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,  16,   1,   0,   0, 
    100,   1,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     86,  83,  95,  67, 111, 110, 
    115, 116,  97, 110, 116,  66, 
    117, 102, 102, 101, 114,   0, 
    171, 171,  60,   0,   0,   0, 
      5,   0,   0,   0, 104,   0, 
      0,   0, 176,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 224,   0,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   0,   0,   0,   0, 
    240,   0,   0,   0,   0,   0, 
      0,   0,   0,   1,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    240,   0,   0,   0,   0,   0, 
      0,   0,  17,   1,   0,   0, 
    128,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,  52,   1,   0,   0, 
    144,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,  76,   1,   0,   0, 
    160,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,  95,  50,  54,  51, 
     95, 109,  67,  97, 109, 101, 
    114,  97,   0, 171, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  95,  50, 
     54,  51,  95, 109,  67,  97, 
    109, 101, 114,  97,  80, 114, 
    111, 106,   0,  95,  50,  54, 
     51,  95, 109,  85,  86,  73, 
    110, 118, 101, 114, 115, 101, 
    100,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  95,  50,  54,  51, 
     95, 102, 108, 105, 112,  98, 
    111, 111, 107,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
     49,   0,  95,  50,  54,  51, 
     95, 102, 108, 105, 112,  98, 
    111, 111, 107,  80,  97, 114, 
     97, 109, 101, 116, 101, 114, 
     50,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  50,  57,  46, 
     57,  53,  50,  46,  51,  49, 
     49,  49,   0, 171, 171, 171, 
     73,  83,  71,  78, 212,   0, 
      0,   0,   8,   0,   0,   0, 
      8,   0,   0,   0, 200,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   7,   0,   0, 200,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,  15,   0,   0, 200,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   3,   0,   0, 200,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,  15,   0,   0, 200,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
      3,   3,   0,   0, 200,   0, 
      0,   0,   5,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,  15,   0,   0, 200,   0, 
      0,   0,   6,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   1,   0,   0, 200,   0, 
      0,   0,   7,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   7,   0,   0,   0, 
      1,   1,   0,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0, 171, 171, 171,  79,  83, 
     71,  78, 224,   0,   0,   0, 
      8,   0,   0,   0,   8,   0, 
      0,   0, 200,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 200,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0, 200,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   8, 
      0,   0, 200,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,  15,   0, 
      0,   0, 200,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,   0, 
      0,   0, 200,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,  15,   0, 
      0,   0, 200,   0,   0,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      6,   0,   0,   0,  15,   0, 
      0,   0, 209,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0,  15,   0, 
      0,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  83, 
     86,  95,  80, 111, 115, 105, 
    116, 105, 111, 110,   0, 171, 
    171, 171,  83,  72,  68,  82, 
    208,  10,   0,   0,  64,   0, 
      1,   0, 180,   2,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     11,   0,   0,   0,  95,   0, 
      0,   3, 114,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      1,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      2,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      3,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      4,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      5,   0,   0,   0,  95,   0, 
      0,   3,  18,  16,  16,   0, 
      6,   0,   0,   0,  95,   0, 
      0,   3,  18,  16,  16,   0, 
      7,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      3,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      4,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      5,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      6,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      7,   0,   0,   0,   1,   0, 
      0,   0, 104,   0,   0,   2, 
      8,   0,   0,   0,  50,   0, 
      0,  11,  18,   0,  16,   0, 
      0,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  26,  16, 
     16,   0,   2,   0,   0,   0, 
     10, 128,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  21,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   6,  16,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
    166,  26,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   7,   0,   0,   0, 
     50,   0,   0,  11, 162,  32, 
     16,   0,   3,   0,   0,   0, 
     86, 133,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     86,  29,  16,   0,   3,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  50,   0,   0,  11, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  26, 128,  32,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  26,  16,  16,   0, 
      4,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  50,   0, 
      0,  11, 162,  32,  16,   0, 
      4,   0,   0,   0,  86, 133, 
     32,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,  86,  29, 
     16,   0,   5,   0,   0,   0, 
      6, 128,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     49,   0,   0,   8,  18,   0, 
     16,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  31,   0,   4,   3, 
     10,   0,  16,   0,   3,   0, 
      0,   0,  26,   0,   0,   5, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  10,  16,  16,   0, 
      6,   0,   0,   0,  65,   0, 
      0,   5,  18,   0,  16,   0, 
      3,   0,   0,   0,  10,  16, 
     16,   0,   6,   0,   0,   0, 
      0,   0,   0,   7, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  56,   0, 
      0,   9,  18,   0,  16,   0, 
      4,   0,   0,   0,  58, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,  24,   0, 
      0,   8,  34,   0,  16,   0, 
      4,   0,   0,   0,  26, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   4,   3,  26,   0, 
     16,   0,   4,   0,   0,   0, 
     29,   0,   0,   7,  34,   0, 
     16,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  50,   0, 
      0,  11,  66,   0,  16,   0, 
      4,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,  58, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128, 191, 
      0,   0,   0,   7,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  55,   0, 
      0,   9,  98,   0,  16,   0, 
      4,   0,   0,   0,  86,   5, 
     16,   0,   4,   0,   0,   0, 
    166,  10,  16,   0,   4,   0, 
      0,   0,   6,   1,  16,   0, 
      3,   0,   0,   0,  18,   0, 
      0,   1,  14,   0,   0,   7, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
     65,   0,   0,   5,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  10, 
     18,   0,  16,   0,   5,   0, 
      0,   0,  10,   0,  16, 128, 
     65,   0,   0,   0,   4,   0, 
      0,   0,  26,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   3,   0,   0,   0, 
     14,   0,   0,   7, 130,   0, 
     16,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  65,   0, 
      0,   5, 130,   0,  16,   0, 
      4,   0,   0,   0,  58,   0, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,  10,  34,   0, 
     16,   0,   5,   0,   0,   0, 
     10,   0,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   4,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  24,   0, 
      0,  11, 194,   0,  16,   0, 
      5,   0,   0,   0,  86, 133, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    128,  63,   0,   0,   0,  64, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  65,   0, 
      0,   5, 130,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,  64,  26,   0,  16,   0, 
      3,   0,   0,   0,  24,   0, 
      0,   7,  34,   0,  16,   0, 
      3,   0,   0,   0,  26,   0, 
     16,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,  11, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  58, 128,  32,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128, 191,  65,   0, 
      0,   5,  50,   0,  16,   0, 
      6,   0,   0,   0,  70,   0, 
     16,   0,   5,   0,   0,   0, 
      0,   0,   0,   8,  50,   0, 
     16,   0,   6,   0,   0,   0, 
    246,  15,  16,   0,   3,   0, 
      0,   0,  70,   0,  16, 128, 
     65,   0,   0,   0,   6,   0, 
      0,   0,  55,   0,   0,   9, 
     18,   0,  16,   0,   7,   0, 
      0,   0,  26,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  56,   0,   0,   7, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     65,   0,   0,   5,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  10, 
     34,   0,  16,   0,   3,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  64,  58,   0, 
     16,   0,   4,   0,   0,   0, 
     24,   0,   0,   7,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   3,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  55,   0, 
      0,   9,  34,   0,  16,   0, 
      7,   0,   0,   0,  26,   0, 
     16,   0,   3,   0,   0,   0, 
     26,   0,  16,   0,   6,   0, 
      0,   0,  26,   0,  16,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   7,  66,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   3,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  55,   0,   0,   9, 
     50,   0,  16,   0,   3,   0, 
      0,   0, 246,  15,  16,   0, 
      5,   0,   0,   0,  70,   0, 
     16,   0,   7,   0,   0,   0, 
    134,   0,  16,   0,   3,   0, 
      0,   0,  55,   0,   0,   9, 
     98,   0,  16,   0,   4,   0, 
      0,   0, 166,  10,  16,   0, 
      5,   0,   0,   0,   6,   1, 
     16,   0,   5,   0,   0,   0, 
      6,   1,  16,   0,   3,   0, 
      0,   0,  21,   0,   0,   1, 
     50,   0,   0,  11,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     26, 128,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  27,   0,   0,   5, 
    194,   0,  16,   0,   3,   0, 
      0,   0,  86,   9,  16,   0, 
      4,   0,   0,   0,  27,   0, 
      0,   6,  18,   0,  16,   0, 
      4,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,   1,   0, 
      0,  10,  98,   0,  16,   0, 
      4,   0,   0,   0, 166,  11, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0, 128, 
      0,   0,   0, 128,   0,   0, 
      0,   0,  36,   0,   0,   8, 
     50,   0,  16,   0,   5,   0, 
      0,   0, 230,  10,  16,   0, 
      3,   0,   0,   0, 230,  10, 
     16, 128,  65,   0,   0,   0, 
      3,   0,   0,   0,  36,   0, 
      0,   8, 130,   0,  16,   0, 
      4,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
     10,   0,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     78,   0,   0,   9,  18,   0, 
     16,   0,   5,   0,   0,   0, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  10,   0,  16,   0, 
      5,   0,   0,   0,  58,   0, 
     16,   0,   4,   0,   0,   0, 
     40,   0,   0,   5,  66,   0, 
     16,   0,   5,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,  55,   0,   0,   9, 
     34,   0,  16,   0,   4,   0, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,  42,   0, 
     16,   0,   5,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,  43,   0,   0,   5, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  26,   0,  16,   0, 
      4,   0,   0,   0,  87,   0, 
      0,   7, 194,   0,  16,   0, 
      3,   0,   0,   0, 166,  14, 
     16,   0,   3,   0,   0,   0, 
      6,   0,  16,   0,   4,   0, 
      0,   0,  40,   0,   0,   5, 
     18,   0,  16,   0,   4,   0, 
      0,   0,  10,   0,  16,   0, 
      5,   0,   0,   0,   1,   0, 
      0,  10, 194,   0,  16,   0, 
      3,   0,   0,   0, 166,  14, 
     16,   0,   3,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0, 128,   0,   0, 
      0, 128,  55,   0,   0,   9, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  42,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   5,   0, 
      0,   0,  43,   0,   0,   5, 
     34,   0,  16,   0,   6,   0, 
      0,   0,  42,   0,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  11,  50,   0,  16,   0, 
      4,   0,   0,   0,  70,   0, 
     16,   0,   6,   0,   0,   0, 
     70, 128,  32,   0,   0,   0, 
      0,   0,  10,   0,   0,   0, 
    230, 138,  32,   0,   0,   0, 
      0,   0,  10,   0,   0,   0, 
     54,   0,   0,   5,  18,   0, 
     16,   0,   3,   0,   0,   0, 
     10,  16,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,   8, 
     50,   0,  16,   0,   3,   0, 
      0,   0,  70,   0,  16,   0, 
      3,   0,   0,   0,  70,   0, 
     16, 128,  65,   0,   0,   0, 
      4,   0,   0,   0,  78,   0, 
      0,   9,  18,   0,  16,   0, 
      4,   0,   0,   0,  18,   0, 
     16,   0,   5,   0,   0,   0, 
     26,   0,  16,   0,   5,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,  40,   0, 
      0,   5,  66,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     55,   0,   0,   9,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   4,   0, 
      0,   0,  42,   0,  16,   0, 
      3,   0,   0,   0,  10,   0, 
     16,   0,   5,   0,   0,   0, 
     43,   0,   0,   5,  18,   0, 
     16,   0,   5,   0,   0,   0, 
     42,   0,  16,   0,   3,   0, 
      0,   0,  40,   0,   0,   5, 
     66,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  55,   0, 
      0,   9,  66,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      4,   0,   0,   0,  43,   0, 
      0,   5,  34,   0,  16,   0, 
      5,   0,   0,   0,  42,   0, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10,  50,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   0,  16,   0,   5,   0, 
      0,   0,  70, 128,  32,   0, 
      0,   0,   0,   0,  10,   0, 
      0,   0,  70,   0,  16,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   8,  50,   0,  16,   0, 
      3,   0,   0,   0,  70,   0, 
     16,   0,   3,   0,   0,   0, 
    230, 138,  32,   0,   0,   0, 
      0,   0,  10,   0,   0,   0, 
     50,   0,   0,  11,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     26, 128,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     26,   0,  16,   0,   3,   0, 
      0,   0,  10, 128,  32,   0, 
      0,   0,   0,   0,   8,   0, 
      0,   0,  54,   0,   0,   5, 
     98,   0,  16,   0,   2,   0, 
      0,   0,   6,   2,  16,   0, 
      3,   0,   0,   0,  18,   0, 
      0,   1,  54,   0,   0,   8, 
     98,   0,  16,   0,   2,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  34,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     21,   0,   0,   1,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  30, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   0,   0,   0,   0, 
     10,  16,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  10,  16,  16,   0, 
      7,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      1,   0,   0,   0,  38,  13, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  82,  32, 
     16,   0,   3,   0,   0,   0, 
      6,  18,  16,   0,   3,   0, 
      0,   0,  54,   0,   0,   5, 
     82,  32,  16,   0,   4,   0, 
      0,   0,   6,  18,  16,   0, 
      5,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      2,   0,   0,   0,  10,  16, 
     16,   0,   4,   0,   0,   0, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   5,   0,   0,   0, 
     54,   9,  16,   0,   2,   0, 
      0,   0,  54,   0,   0,   5, 
    242,  32,  16,   0,   6,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      7,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   8, 114,  32, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  90,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
     26,   0,   0,   0,   6,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     24,   0,   0,   0,   9,   0, 
      0,   0,  13,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
