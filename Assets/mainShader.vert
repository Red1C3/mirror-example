#version 330
layout(location=0) in vec3 pos_model;
uniform mat4 MVP;
out vec3 out_pos_model;
void main(){
  out_pos_model=pos_model;
  gl_Position=MVP*vec4(pos_model,1);
}
