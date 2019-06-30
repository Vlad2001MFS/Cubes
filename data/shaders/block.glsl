@VertexShader
layout(location = 0) in vec3 vsPos;
layout(location = 1) in vec3 vsNormal;
layout(location = 2) in vec3 vsTexCoord;

out vec3 psNormal;
out vec3 psTexCoord;

uniform mat4 gProjMat, gViewMat;

void main() {
    gl_Position = gProjMat*gViewMat*vec4(vsPos.x, vsPos.y, vsPos.z, 1.0);
    psNormal = vsNormal;
    psTexCoord = vsTexCoord;
}

@PixelShader
in vec3 psNormal;
in vec3 psTexCoord;

out vec4 fragColor;

layout(binding = 0) uniform sampler2DArray gTexture;

void main() {
    fragColor = texture(gTexture, psTexCoord);
}