@VertexShader
layout(location = 0) in vec3 vsPos;

uniform mat4 gProjMat, gViewMat, gWorldMat;

void main() {
    gl_Position = gProjMat*gViewMat*gWorldMat*vec4(vsPos.x, vsPos.y, vsPos.z, 1.0);
}

@PixelShader

out vec4 fragColor;

void main() {
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}