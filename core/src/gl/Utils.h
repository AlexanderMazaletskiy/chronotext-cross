#pragma once

#include "gl.h"
#include "gl/Quad.h"
#include "gl/Texture.h"
#include "gl/ShaderHelper.h"
#include "math/Utils.h"
#include "image/Utils.h"

namespace chr
{
  namespace gl
  {
    Texture::Response loadAndUploadTexture(const Texture::Request &request);
    Texture::Response uploadTexture(const image::ImageBuffer &image, bool useMipmap = true, bool useAnisotropy = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    Texture::Response loadAndUploadMaskedTexture(const Texture::MaskedRequest &request);
    Texture::Response uploadMaskedTexture(const image::ImageBuffer &image, const image::ImageBuffer &mask, bool useMipmap = true, bool useAnisotropy = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    void uploadTexture(GLenum format, GLsizei width, GLsizei height, const GLvoid *data, bool useMipmap = true, bool useAnisotropy = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);

    const glm::mat4 getPerspectiveMatrix(float fovY, float nearZ, float farZ, float width, float height, float panX = 0, float panY = 0, float zoom = 1);

    bool clip(Quad<XYZ.UV> &quad, const math::Rectf &clipRect, const glm::vec2 &textureFactor);
  }
}
