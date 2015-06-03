#version 120

uniform vec3 u_Position;
uniform mat3 u_Rotation;
uniform mat4 u_ViewProjection;

attribute vec3 a_Vertex;
attribute vec3 a_Normal;
attribute vec3 a_Color;

varying vec3 v_Color;

void main() {
  gl_Position = u_ViewProjection * vec4(u_Position + u_Rotation * a_Vertex, 1.0);
  v_Color = a_Color * -(u_Rotation * a_Normal).z;
}
