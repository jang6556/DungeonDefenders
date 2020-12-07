xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material material_9_ {
 1.000000;1.000000;1.000000;1.000000;;
 32.000000;
 0.100000;0.100000;0.100000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Stage_1th_impc_i.dds";
 }
}

Frame mesh23 {
 

 FrameTransformMatrix {
  -1.000000,0.000000,-0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,-309.622579,-28.452272,567.98483,1.000000;;
 }

 Mesh mesh23 {
  16;
  -68.250726;149.495168;-1.080204;,
  -51.971142;164.567846;-1.575399;,
  -52.413014;165.045594;-0.424381;,
  -67.802650;148.940582;-2.430530;,
  -53.309101;166.001254;-0.424381;,
  -69.153069;150.604365;-1.080204;,
  -53.757171;166.479002;-1.575399;,
  -69.607347;151.158963;-2.430530;,
  -49.444598;162.964864;-7.632528;,
  -69.502630;153.483994;-8.127722;,
  -49.722390;163.553357;-8.783546;,
  -69.242042;152.820339;-6.777397;,
  -50.289699;164.734208;-8.783546;,
  -70.029709;154.813158;-8.127722;,
  -50.573440;165.324570;-7.632528;,
  -70.296256;155.478682;-6.777397;;
  16;
  3;0,1,2;,
  3;3,1,0;,
  3;4,0,2;,
  3;5,0,4;,
  3;6,5,4;,
  3;7,5,6;,
  3;1,7,6;,
  3;3,7,1;,
  3;8,9,10;,
  3;11,9,8;,
  3;9,12,10;,
  3;13,12,9;,
  3;13,14,12;,
  3;15,14,13;,
  3;15,8,14;,
  3;11,8,15;;

  MeshNormals {
   16;
   0.361315;-0.405018;0.839888;,
   0.626073;-0.604029;-0.493134;,
   0.327240;-0.369956;0.869509;,
   0.619135;-0.599470;-0.507255;,
   -0.368956;0.342981;0.863850;,
   -0.367890;0.340256;0.865380;,
   -0.593538;0.644012;-0.482661;,
   -0.563967;0.613895;-0.552335;,
   0.415507;-0.764315;0.493129;,
   0.222833;-0.494916;-0.839883;,
   0.200873;-0.451225;-0.869509;,
   0.410259;-0.757877;0.507258;,
   -0.248765;0.438031;-0.863855;,
   -0.248569;0.435115;-0.865383;,
   -0.372459;0.792670;0.482648;,
   -0.353305;0.755046;0.552342;;
   16;
   3;0,1,2;,
   3;3,1,0;,
   3;4,0,2;,
   3;5,0,4;,
   3;6,5,4;,
   3;7,5,6;,
   3;1,7,6;,
   3;3,7,1;,
   3;8,9,10;,
   3;11,9,8;,
   3;9,12,10;,
   3;13,12,9;,
   3;13,14,12;,
   3;15,14,13;,
   3;15,8,14;,
   3;11,8,15;;
  }

  MeshMaterialList {
   1;
   16;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { material_9_ }
  }

  MeshTextureCoords c1 {
   16;
   0.683879;-0.390587;,
   1.000000;1.132694;,
   0.683879;1.132696;,
   1.000000;-0.390588;,
   0.310032;1.132700;,
   0.310032;-0.390586;,
   0.000000;1.132702;,
   0.000000;-0.390586;,
   1.000000;1.132694;,
   0.683879;-0.390587;,
   0.683879;1.132696;,
   1.000000;-0.390588;,
   0.310032;1.132700;,
   0.310032;-0.390586;,
   0.000000;1.132702;,
   0.000000;-0.390586;;
  }
 }
}