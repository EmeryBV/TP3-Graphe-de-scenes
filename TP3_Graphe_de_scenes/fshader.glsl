#version 150

uniform sampler2D heightMap;
uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;

in vec2 v_texcoord;
in vec3 v_position;


//! [0]
void main()
{
    // Set fragment color from texture
    vec4 heightMapVec  = texture2D(heightMap, v_texcoord);

    if(heightMapVec.z > 0.80)  gl_FragColor = texture2D(textureSnow, v_texcoord);
     else if(heightMapVec.z > 0.65)  gl_FragColor = texture2D(textureRock, v_texcoord);
    else  gl_FragColor = texture2D(textureGrass, v_texcoord);


//    gl_FragColor = texture2D(textureRock, v_texcoord);
}
//! [0]

