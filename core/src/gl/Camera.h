#pragma once

#include "gl/Matrix.h"
#include "math/Ray.h"

namespace chr
{
  namespace gl
  {
    class Camera
    {
    public:
      Camera& setFov(float fovY); // IN DEGREES
      Camera& setClip(float nearZ, float farZ);
      Camera& setWindowSize(const glm::vec2 &size);

      Camera& setPan2D(const glm::vec2 &pan);
      Camera& setZoom2D(float zoom);

      Matrix& getModelViewMatrix();
      glm::mat4 getProjectionMatrix();
      glm::mat4 getModelViewProjectionMatrix();
      glm::mat3 getNormalMatrix();

      inline Matrix& getMVMatrix() { return getModelViewMatrix(); }
      inline glm::mat4 getMVPMatrix() { return getModelViewProjectionMatrix(); }

      glm::vec3 getEyePosition();
      math::Ray getRay(const glm::vec2 &windowPosition);

      inline Camera& setPan2D(float x, float y) { return setPan2D(glm::vec2(x, y)); }

    protected:
      bool updateRequired = false;

      float fovY = 60;
      float nearZ = 0.1f;
      float farZ = 1000.0f;
      glm::vec2 windowSize = { 1, 1 };

      glm::vec2 pan2D;
      float zoom2D = 1;
      glm::vec2 frustumSize;

      glm::mat4 projectionMatrix;
      Matrix modelViewMatrix;

      void update();
    };
  }
}
