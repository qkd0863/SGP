#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_UV;

uniform float u_Time;

const int DROP_COUNT = 8;    // 여러 위치
const int MAX_RINGS  = 4;    // 동심원 최대 개수

float hash(float n) {
    return fract(sin(n) * 43758.5453);
}

void main()
{
    vec2 uv = v_UV;

    vec3 col = vec3(0.05, 0.06, 0.08);

    float rippleAccum = 0.0;

    float period    = 4.0;    // 한 위치의 전체 사이클
    float waveSpeed = 0.35;   // 퍼지는 속도
    float ringGap   = 0.35;   // 링 시작 시점 간격
    float thickness = 0.015;  // 링 두께
    float maxRadius = 0.25;   // 이 반지름을 넘으면 사라짐

    for (int i = 0; i < DROP_COUNT; ++i) {
        float fi = float(i);

        // 위치별 시간 어긋나게
        float t = u_Time + fi * 0.71;
        float localT = mod(t, period);

        // 랜덤 위치
        float rx = hash(fi * 13.57);
        float ry = hash(fi * 91.37);
        vec2 center = vec2(rx, mix(0.15, 0.85, ry));

        float distToCenter = distance(uv, center);

        for (int r = 0; r < MAX_RINGS; ++r) {
            float fr = float(r);

            float ringStart = fr * ringGap;
            if (localT < ringStart) {
                continue;
            }

            float ringT = localT - ringStart;

            // 현재 링의 반지름
            float radius = ringT * waveSpeed;

            // 여기서 최대 반지름 넘어가면 그 링은 그리지 않음
            if (radius > maxRadius) {
                continue;
            }

            // 두께로 링 모양 만들기
            float d = abs(distToCenter - radius);
            float ring = smoothstep(thickness, 0.0, d);

            // 시간에 따른 감쇠 (사이클 끝으로 갈수록 약해짐)
            float life = 1.0 - (ringT / (period - ringStart));
            ring *= life;

            // 반지름 끝으로 갈 때도 살짝 줄여주면 부드러움
            float edgeFade = 1.0 - (radius / maxRadius);
            ring *= edgeFade;

            rippleAccum = max(rippleAccum, ring);
        }
    }

    vec3 rippleColor = vec3(0.2, 0.4, 0.8) * rippleAccum;
    col += rippleColor;

    FragColor = vec4(col, 1.0);
}
