#pragma once
#include <GLFW/glfw3.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>

static double lastx, lasty;
static bool pressed = false;
static float zoom = 0.0f;
static float zoomSensitivity = 0.1f;
static glm::mat4 worldRotation(1.0f);
static float rotationSensitivity = 0.01f;

void mouse_callback(GLFWwindow* window, double x, double y)
{
  ImGui_ImplGlfw_CursorPosCallback(window, x, y);
  ImGuiIO& io = ImGui::GetIO();
  if (io.WantCaptureMouse)
    return;
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!pressed) {
      pressed = true;
    }
    else {
      //we take the negative offset so that the cursor moves in the opposite direction as the camera
      float xoffset = (float)(lastx - x);
      float yoffset = (float)(lasty - y);
      worldRotation = lin::rotate(rotationSensitivity * yoffset, rotationSensitivity * xoffset, 0.0f) * worldRotation;
    }
  }
  else {
    pressed = false;
  }
  lastx = x;
  lasty = y;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  zoom += (float)yoffset * zoomSensitivity;
}


