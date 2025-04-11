#ifdef GL_ES
    precision mediump float;
#endif


uniform sampler2D texture;


float s_curve(float x) {
    x = x * 2.0 - 1.0;
    return -x * abs(x) * 0.5 + x + 0.5;
}

vec4 blur_h(sampler2D source, vec2 size, vec2 uv, float radius) {
    if (radius >= 1.0) {
        vec4 A = vec4(0.0);
        vec4 C = vec4(0.0);

        float width = 1.0 / size.x;
        float divisor = 0.0;
        float weight = 0.0;

        float radiusMultiplier = 1.0 / radius;

        for (float x = -radius; x <= radius; x++) {
            A = texture2D(source, uv + vec2(x * width, 0.0));
            weight = s_curve(1.0 - (abs(x) * radiusMultiplier));
            C += A * weight;
            divisor += weight;
        }

        return vec4(C.r / divisor, C.g / divisor, C.b / divisor, 1.0);
    }

    return texture2D(source, uv);
}

vec4 blur_v(vec4 source, vec2 size, vec2 uv, float radius) {
    if (radius >= 1.0) {
        vec4 A = vec4(0.0);
        vec4 C = vec4(0.0);

        float width = 1.0 / size.x;
        float divisor = 0.0;
        float weight = 0.0;

        float radiusMultiplier = 1.0 / radius;

        for (float x = -radius; x <= radius; x++) {
            A = texture2D(source, uv + vec2(x * width, 0.0));
            weight = s_curve(1.0 - (abs(x) * radiusMultiplier));
            C += A * weight;
            divisor += weight;
        }

        return vec4(C.r / divisor, C.g / divisor, C.b / divisor, 1.0);
    }

    return texture2D(source, uv);
}


void main() {
    vec2 res = vec2(800, 800);
    vec4 col = blur_h(texture, res, gl_TexCoord[0].xy, 20.0);
    gl_FragColor = blur_v();
}

