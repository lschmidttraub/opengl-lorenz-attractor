#include "Attractor.h"
#include "maths/Geometry.h"
#include "maths/LinearAlgebra.h"
#include "graphics/Shader.h"
#include "graphics/CameraControls.h"
#include "ErrorHandling.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>

static const int WIDTH = 800, HEIGHT = 500;
static double lastTime = glfwGetTime();
static double currentTime = glfwGetTime();
static int nPoints = 0;


int main()
{
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(WIDTH, HEIGHT, "Lorenz Attractor", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); 
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 410";
  ImGui_ImplOpenGL3_Init(glsl_version);

  glfwSwapInterval(1);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cout << "GLEW could not initialise\n";
  }

  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(ErrorCallback, NULL);

  Attractor lorenz({ 1.0f, 1.0f, 1.0f }, 10.0f, 28.0f, 8.0f / 3, 1.0f);

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  int nSides = 5;
  BuildCone(vertices, indices, 0.02f, 0.1f, nSides);

  unsigned int point_VAO;
  glGenVertexArrays(1, &point_VAO);
  glBindVertexArray(point_VAO);

  unsigned int point_VBO;
  glGenBuffers(1, &point_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, point_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  unsigned int point_EBO;
  glGenBuffers(1, &point_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, point_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, coords));
  glEnableVertexArrayAttrib(point_VAO, 0);

  unsigned int path_VAO;
  glGenVertexArrays(1, &path_VAO);
  glBindVertexArray(path_VAO);

  unsigned int path_VBO;
  glGenBuffers(1, &path_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, path_VBO);
  static const int MAX_SIZE = 100000;
  glBufferData(GL_ARRAY_BUFFER, MAX_SIZE * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, coords));
  glEnableVertexArrayAttrib(path_VAO, 0);

  Shader pointShader("res/shaders/Point.vert", "res/shaders/Point.frag");
  Shader pathShader("res/shaders/Point.vert", "res/shaders/Path.frag");


  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glm::vec4 color(1.0f);

  glm::mat4 scale = lin::scale(glm::vec3(1.f / 20, 1.f / 30, 1.f / 50));
  glm::mat4 lookAt = lin::lookAt({ 0.0f, 0.0f, -1.0f }, glm::vec3(0.0f), { 0.0f, 1.0f, 0.0f });
  glm::mat4 proj = lin::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 15.0f);

  while (!glfwWindowShouldClose(window))
  {
    currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    lorenz.Update(deltaTime);
    ++nPoints;

    glm::vec3 offset = scale * glm::vec4(lorenz.getPosition(), 1.0f);
    glm::mat4 pointModel = lin::translate(offset) * lin::orient(lorenz.getGrad(), { 0.f,1.f,0.f });
    glm::mat4 view = lookAt * lin::scale(glm::vec3(exp(zoom))) * worldRotation;
    glm::mat4 pointMVP = proj * view * pointModel;
    glm::mat4 pathMVP = proj * view * scale;

    glClear(GL_COLOR_BUFFER_BIT);

    pointShader.Bind();
    glBindVertexArray(point_VAO);
    pointShader.setUniform4f("u_Color", color);
    pointShader.setUniformMat4f("u_MVP", pointMVP);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


    pathShader.Bind();
    glBindVertexArray(path_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, path_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, (nPoints % MAX_SIZE) * sizeof(Vertex), sizeof(Vertex), &(lorenz.getPath().back()));
    pathShader.setUniformMat4f("u_MVP", pathMVP);
    glDrawArrays(GL_LINE_STRIP, 0, nPoints % MAX_SIZE);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
      ImGui::Begin("Controls");
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
      ImGui::SliderFloat("Speed", &lorenz.speed, -0.1f, 1.7f);
      ImGui::ColorEdit4("Point", &color[0]);
      if (ImGui::Button("Reset")) {
        lorenz.reset({ 1.0,1.0,1.0 });
        nPoints = 0;
        color = glm::vec4(1.0f);
      }
      ImGui::End();
      ImGui::Render();
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}