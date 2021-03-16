// RUN: %dxc -T lib_6_3 -auto-binding-space 11 %s | FileCheck %s

// CHECK: error: ray payload parameter must be inout
// CHECK: error: intersection attributes parameter must be in

struct MyPayload {
  float4 color;
  uint2 pos;
};

struct MyAttributes {
  float2 bary;
  uint id;
};

[shader("anyhit")]
void anyhit_out( out MyPayload payload, out MyAttributes attr ) {}
