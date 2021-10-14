#version 150

uniform mat4 mvp_matrix;

in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;

uniform sampler2D heightMap;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    vec4 color  = texture2D(heightMap, a_texcoord);
    gl_Position = mvp_matrix * vec4(a_position.xy, a_position.z - color.z,1.0f);

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
//! [0]
