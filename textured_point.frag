uniform float iGlobalTime;
uniform vec2 iResolution;
uniform sampler2D pointTexture;

void main() {
	//"Alpha test" :D
	vec4 color = texture2D(pointTexture, vec2(gl_PointCoord.x, 1.0-gl_PointCoord.y));
	if (color.a < 0.1)
		discard;
    gl_FragColor = color;
}
