#include "LinearAlgebra.h"

namespace lin {

  glm::mat4 translate(glm::vec3 shift)
  {
    return {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      shift.x, shift.y, shift.z,1
    };
  }

  glm::mat4 rotate(float pitch, float roll, float yaw)
  {
    return rotateX(pitch) * rotateY(roll) * rotateZ(yaw);
  }

  glm::mat4 rotateX(float angle)
  {
    float a = angle;
    return {
      1,0,0,0,
      0,cos(a),sin(a),0,
      0,-sin(a),cos(a),0,
      0,0,0,1
    };
  }

  glm::mat4 rotateY(float angle)
  {
    float a = angle;
    return {
      cos(a),0,-sin(a),0,
      0,1,0,0,
      sin(a),0,cos(a),0,
      0,0,0,1
    };
  }

  glm::mat4 rotateZ(float angle)
  {
    float a = angle;
    return {
      cos(a),sin(a),0,0,
      -sin(a),cos(a),0,0,
      0,0,1,0,
      0,0,0,1
    };
  }

  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 obj, glm::vec3 up)
  {
    glm::vec3 shift = obj - eye;
    // 1. move camera to origin
    // 2. orient world in the opposite direction of the camera direction
    return orient(-shift, up) * translate(-eye);
  }

  glm::mat4 perspective(float yFov, float aspect, float zNear, float zFar)
  {
    float n = zNear, f = zFar, a = aspect;
    float h = tan(yFov / 2)*n;
    float w = h * aspect;


    return {
      n / w,0,0,0,
      0,n / h,0,0,
      0,0,(n + f) / (n - f),-1,
      0,0,2 * n * f / (n - f),0
    };
  }

  glm::mat4 scale(glm::vec3 factors)
  {
    return {
      factors.x,0,0,0,
      0,factors.y,0,0,
      0,0,factors.z,0,
      0,0,0,1
    };
  }
  glm::mat4 orient(glm::vec3 front, glm::vec3 up)
  {
    // Calculate new unit vectors (orthonormal basis)
    glm::vec3 k = glm::normalize(front);
    glm::vec3 i = glm::normalize(glm::cross(up, k));
    glm::vec3 j = glm::normalize(glm::cross(k, i));

    // Map original basis to new basis
    return {
      i.x,i.y,i.z,0,
      j.x,j.y,j.z,0,
      k.x,k.y,k.z,0,
      0,0,0,1
    };
  }
}