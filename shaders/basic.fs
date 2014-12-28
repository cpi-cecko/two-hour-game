#version 120

uniform sampler2D uSampler;

varying vec2 vUV;

void main(void)
{
	gl_FragColor = texture2D(uSampler, vUV);
}
