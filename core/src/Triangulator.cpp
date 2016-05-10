#include "Triangulator.h"

#include "Log.h"

using namespace std;
using namespace chr::gl;
using namespace chr::math;

namespace chr
{
  static void* stdAlloc(void* userData, unsigned int size)
  {
    int* allocated = (int*)userData;
    *allocated += (int)size;
    return malloc(size);
  }

  static void stdFree(void* userData, void* ptr)
  {
    free(ptr);
  }

  Triangulator::Triangulator()
  {
    TESSalloc ma;
    memset(&ma, 0, sizeof(ma));
    ma.memalloc = stdAlloc;
    ma.memfree = stdFree;
    ma.userData = (void*)&allocated;
    ma.extraVertices = 256; // realloc not provided, allow 256 extra vertices.

    tess = tessNewTess(&ma);
  }

  Triangulator::~Triangulator()
  {
    tessDeleteTess(tess);
  }

  Triangulator& Triangulator::setWindingRule(int windingRule)
  {
    this->windingRule = windingRule;
    return *this;
  }

  Triangulator& Triangulator::setColor(const glm::vec4 &color)
  {
    this->color = color;
    return *this;
  }

  Triangulator& Triangulator::setColor(float r, float g, float b, float a)
  {
    color = { r, g, b, a };
    return *this;
  }

  template <>
  Triangulator& Triangulator::add<GL_CCW>(const Rectf &rect)
  {
    vector<glm::vec2> polygon;
    polygon.emplace_back(rect.x1y1());
    polygon.emplace_back(rect.x1y2());
    polygon.emplace_back(rect.x2y2());
    polygon.emplace_back(rect.x2y1());

    add(polygon);
    return *this;
  }

  template <>
  Triangulator& Triangulator::add<GL_CW>(const Rectf &rect)
  {
    vector<glm::vec2> polygon;
    polygon.emplace_back(rect.x1y1());
    polygon.emplace_back(rect.x2y1());
    polygon.emplace_back(rect.x2y2());
    polygon.emplace_back(rect.x1y2());

    add(polygon);
    return *this;
  }

  Triangulator& Triangulator::add(const vector<vector<glm::vec2>> &polygons)
  {
    for (auto &polygon : polygons)
    {
      add(polygon);
    }

    return *this;
  }

  Triangulator& Triangulator::add(const vector<glm::vec2> &polygon)
  {
    tessAddContour(tess, 2, polygon.data(), sizeof(glm::vec2), polygon.size());
    return *this;
  }

  template <>
  void Triangulator::process(IndexedVertexBatch<XYZ> &batch, Matrix &matrix)
  {
    process(batch, matrix);
  }

  template <>
  void Triangulator::process(IndexedVertexBatch<XYZ.N> &batch, Matrix &matrix)
  {
    auto normal = matrix.transformNormal(0, 0, 1);
    process(batch, matrix, normal);
  }

  template <>
  void Triangulator::process(IndexedVertexBatch<XYZ.RGBA> &batch, Matrix &matrix)
  {
    process(batch, matrix, color);
  }

  template <>
  void Triangulator::process(IndexedVertexBatch<XYZ.N.RGBA> &batch, Matrix &matrix)
  {
    auto normal = matrix.transformNormal(0, 0, 1);
    process(batch, matrix, normal, color);
  }

  vector<vector<Triangulator::Segment>> Triangulator::getContourSegments() const
  {
    vector<vector<Segment>> contours;

    tessTesselate(tess, windingRule, TESS_BOUNDARY_CONTOURS, 0, 0, 0);

    const auto vertices = (glm::vec2*)tessGetVertices(tess);
    const auto elements = tessGetElements(tess);
    auto elementCount = tessGetElementCount(tess);

    for (auto i = 0; i < elementCount; i++)
    {
      const auto base = elements[i << 1];
      const auto count = elements[(i << 1) + 1];

      contours.emplace_back();

      for (int j = 0; j < count; j++)
      {
        auto &p0 = vertices[base + j];
        auto &p1 = vertices[base + (j + 1) % count];
        auto tangeant = glm::normalize(p1 - p0).yx() * glm::vec2(-1, +1);

        contours.back().emplace_back(p0, p1, tangeant);
      }

      /*
       * NECESSARY TO ADD THE CONTOURS BACK FOR FURTHER tessTesselate OPERATIONS
       */
      tessAddContour(tess, 2, &vertices[base], sizeof(glm::vec2), count);
    }

    return contours;
  }
}
