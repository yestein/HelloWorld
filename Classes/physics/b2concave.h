/****************************************************************************
  Copyright (c) 2014 Yestein

  FileName    :   b2concave.h
  Version     :   1.0
  Creater     :   Yestein
  Date        :   2014-1-17 14:19:39
  Comment     :   create a concave b2body by slice a concave to many convex

  Thanks to Antoan Angelov who supply the algorithm.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __B2CONCAVE_H__
#define __B2CONCAVE_H__

#include "Box2D/Box2D.h"
#include <vector>

#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef FLOAT_EPS
#define FLOAT_EPS 0.001f
#endif

#define LOG_PROCESS_ERROR(Condition) \
    do  \
{   \
    if (!(Condition))       \
{                       \
    printf(        \
    "ERROR(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
    );                  \
    goto Exit0;         \
}                       \
} while (false)


#define PROCESS_ERROR(Condition) \
    do  \
{   \
    if (!(Condition))       \
{                       \
    goto Exit0;         \
}                       \
} while (false)

#define PROCESS_SUCCES(Condition) \
    do  \
{   \
    if ((Condition))       \
{                       \
    goto Exit1;         \
}                       \
} while (false)

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) if(p) {delete[] (p); (p) = NULL;}
#endif

class b2Concave {
    
public:
    struct SHAPE
    {
        b2Vec2 array_point[b2_maxPolygonVertices * 3];
        int count_point;
    };
    typedef vector<SHAPE> Shapes;
    
    b2Concave() {}        
    int Create(b2Body* pBody, b2FixtureDef* pFixtureDef, const b2Vec2* const_ptr_vetor_vertices, int count_vertices);
    int BuildShapes(const b2Vec2* const_ptr_vetor_vertices, int count_vertices);

    const Shapes* GetShapes() {return &m_shapes;};

private:
    
    int SlicePolygon(const b2Vec2* const_ptr_vetor_vertices, int count_vertices, float scale, SHAPE* ptr_shape, int* ptr_start_index, int* ptr_end_index);
    int SearchIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, b2Vec2* ptr_point_result);
    int IsPointEqual(float x1, float y1, float x2,float y2);
    int IsOnSegment(float point_x, float point_y, float x1, float y1, float x2, float y2);
    int IsInSquare(float point_x, float point_y, float x1, float y1, float x2, float y2);
    int IsOnLine(float point_x, float point_y, float x1, float y1, float x2, float y2);
    float det(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        // 单位小的时候会有误差！！！
        return x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1;
    }
    float det(const b2Vec2 &vec1, const b2Vec2 &vec2)
    {
        return vec1.x * vec2.y - vec2.x * vec1.y;
    }
private:    
    Shapes m_shapes;
};

#endif