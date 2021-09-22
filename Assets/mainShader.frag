#version 330
out vec4 color;
in vec3 out_pos_model;
uniform int isMirror;
uniform sampler2D mirror;
void main(){
  if(isMirror==0){
    color=vec4(1,1,1,1);
  }else{
    vec2 uv=out_pos_model.xy;
    uv=(uv+vec2(1,1))/2;
    color=texture(mirror,uv);
  }
}