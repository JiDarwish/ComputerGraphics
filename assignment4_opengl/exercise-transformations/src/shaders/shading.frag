#version 430

// output fragment color
out vec4 out_Color;

uniform vec4 default_color;

void main(void)
{    
    // assign the default color without illumination
    vec4 color = default_color;

	// output color for this fragment
    out_Color = color;
}
