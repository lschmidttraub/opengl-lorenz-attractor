# OpenGL Lorenz Attractor
This is a simulation of a Lorenz Attractor using the GLFW and GLEW graphics libraries.

Features:
- 3D simulation
- Matrix scaling rotation, translation, perspective projection implemented
- Camera and mouse controls
- ImGui controls
- Shader class
- Error handling

Missing features:
- Multiple concurrent simulations
- Dynamically sized vertex buffer (OpenGL VBOs need to have a fixed size. This can be worked around with shader storage buffer objects)
- VBO and VAO classes
- Still relies on GLM for basic vector and matrix operations (addition, multiplication, cross-product)
