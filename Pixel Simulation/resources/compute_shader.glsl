#version 430

layout (local_size_x = 16, local_size_y = 16) in; // Workgroup size: 16x16

layout (rgba32f, binding = 0) uniform image2D img_output; // Image buffer

uniform float time;  // Uniform for passing time to the shader

void main() {
    ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy); // Pixel coordinates

    // Simple pixel color update based on time and pixel position
    vec4 color = vec4(sin(float(pixel_coords.x) * 0.01 + time), 
                      cos(float(pixel_coords.y) * 0.01 + time), 
                      sin(time), 1.0);

    imageStore(img_output, pixel_coords, color); // Store the color in the image
}