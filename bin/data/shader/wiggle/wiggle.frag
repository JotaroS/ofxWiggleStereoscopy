uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2DRect src;
uniform sampler2DRect displacementMap;

uniform vec2 offset;
uniform vec2 mapDimensions;
uniform vec4 dimensions;

uniform float focus;
uniform float scale;
uniform float alpha;
void main(){
    vec2 pos = gl_TexCoord[0].st;
    
    float r = texture2DRect(src, pos).r;
    float g = texture2DRect(src, pos).g;
    float b = texture2DRect(src, pos).b;
    float a = texture2DRect(src, pos).a;

    float gr = (r + g + b) / 3.0; //set intencity
    
    vec4 color = vec4(r,g,b,a);     //set src color
    float aspect = u_resolution.x/u_resolution.y;
    vec2 scale2 = vec2(scale * min(1.0, 1.0 / aspect), scale * min(1.0, aspect)) * vec2(1, -1) * vec2(1);
    vec2 mapCords = gl_TexCoord[0].st;
    float map = texture2DRect(displacementMap, mapCords).r;
    map = map * -1.0 + focus;
    vec2 disCords = gl_TexCoord[0].st;
    disCords += offset * map * scale2;      //deform coordinate based on offset and scale
    gl_FragColor = texture2DRect(src, disCords); //maybe this should be deleted??

    // wiggle light color
    float _r = texture2DRect(src, disCords).r;  
    float _g = texture2DRect(src, disCords).g;
    float _b = texture2DRect(src, disCords).b;
    float _a = texture2DRect(src, disCords).a;

    vec4 dstcolor = vec4 (_r, _g, _b, alpha); // set alpha level

    gl_FragColor = dstcolor;
}
