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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Material__460 {
 0.588000;0.588000;0.588000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "ColosseumWall01_Dif.tga";
 }
}

Frame ColliderWall10 {
 

 FrameTransformMatrix {
  1.461000,0.000000,0.000000,0.000000,0.000000,0.500000,0.000000,0.000000,0.000000,0.000000,1.245000,0.000000,0.000000,-59.963008,836.46598,1.000000;;
 }

 Mesh ColliderWall10 {
  4;
  124.060019;353.335629;-443.51642;,
  270.052045;359.661722;-371.694771;,
  124.060019;80.456986;-443.51642;,
  270.052045;86.783072;-371.694771;;
  2;
  3;0,1,2;,
  3;1,3,2;;

  MeshMaterialList {
   1;
   2;
   0,
   0;
   { Material__460 }
  }

  DeclData {
   6;
   2;0;3;0;,
   2;0;6;0;,
   2;0;7;0;,
   3;0;10;0;,
   1;0;5;0;,
   1;0;5;1;;
   68;
   1054999330,
   0,
   3211113770,
   1063618756,
   1025450817,
   1054988147,
   1024379688,
   3212824197,
   1015840530,
   1065353216,
   1065353216,
   1065353216,
   1065353216,
   1046413312,
   1058447360,
   1038901248,
   1061855232,
   1054999328,
   0,
   3211113771,
   1063618757,
   1025450820,
   1054988145,
   1024379690,
   3212824197,
   1015840531,
   1065353216,
   1065353216,
   1065353216,
   1065353216,
   1053941760,
   1058447360,
   1045889024,
   1061855232,
   1054999328,
   0,
   3211113771,
   1063618757,
   1025450806,
   1054988145,
   1024379678,
   3212824197,
   1015840518,
   1065353216,
   1065353216,
   1065353216,
   1065353216,
   1046413312,
   1065287680,
   1038901248,
   1065222144,
   1054999328,
   0,
   3211113771,
   1063618757,
   1025450828,
   1054988145,
   1024379697,
   3212824197,
   1015840538,
   1065353216,
   1065353216,
   1065353216,
   1065353216,
   1053941760,
   1065287680,
   1045889024,
   1065222144;
  }
 }
}