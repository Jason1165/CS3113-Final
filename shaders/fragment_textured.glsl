
uniform sampler2D diffuse;
varying vec2 texCoordVar;

// new stuff
uniform vec2 lightPosition;
varying vec2 varPosition;

uniform float alpha;


// modify a for how far to brightness
float attenuate(float dist, float a, float b)
{
    return 1.0 / (1.0 + (a * dist) + (b * dist * dist));
}

void main() {
    float brightness = attenuate(distance(lightPosition, varPosition), alpha, 0.0);
    vec4 color = texture2D(diffuse, texCoordVar);
    gl_FragColor = vec4(color.rgb * brightness, color.a);
}
