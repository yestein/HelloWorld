/****************************************************************************
  Copyright (c) 2014 Yestein

  FileName    :   b2concave.cpp
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

#include "b2concave.h"

int b2Concave::Create(b2Body* pBody, b2FixtureDef* pFixtureDef, const b2Vec2* const_ptr_vetor_vertices, int count_vertices)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;


    LOG_PROCESS_ERROR(pBody);
    LOG_PROCESS_ERROR(pFixtureDef);
    LOG_PROCESS_ERROR(const_ptr_vetor_vertices);
    LOG_PROCESS_ERROR(count_vertices > 0);
	
    num_ret_code = BuildShapes(const_ptr_vetor_vertices, count_vertices);
    LOG_PROCESS_ERROR(num_ret_code);
    
    // All Success! begin to create fixtures
    {
        Shapes::iterator it = m_shapes.begin();
        for (NULL; it != m_shapes.end(); ++it)
        {
            b2PolygonShape b2polygonshape;
            b2polygonshape.Set(it->array_point, it->count_point);
            pFixtureDef->shape = &b2polygonshape;
            pBody->CreateFixture(pFixtureDef); 
        }
    }
	num_result = TRUE;
Exit0:
	return num_result;
}

int b2Concave::BuildShapes(const b2Vec2* const_ptr_vetor_vertices, int count_vertices)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;
    b2Vec2* ptr_clone_vertices = NULL;
    b2Vec2* ptr_clone_vertices_backup = NULL;
    b2Vec2* ptr_vertices_cur_used = NULL;
    int num_rest_vertice = 0;

    LOG_PROCESS_ERROR(const_ptr_vetor_vertices);
    LOG_PROCESS_ERROR(count_vertices > 0);
    
    if(!m_shapes.empty())
    {
        m_shapes.clear();
    }

    // 创建2个缓冲区用于切换，互相拷贝顶点信息
    ptr_clone_vertices = new b2Vec2[count_vertices];
    LOG_PROCESS_ERROR(ptr_clone_vertices);

    ptr_clone_vertices_backup = new b2Vec2[count_vertices];
    LOG_PROCESS_ERROR(ptr_clone_vertices_backup);

    num_rest_vertice = count_vertices;
    for(int i = 0; i < count_vertices; i++)
    {
        ptr_clone_vertices[i].Set(
            const_ptr_vetor_vertices[i].x,
            const_ptr_vetor_vertices[i].y
            );
    }
    ptr_vertices_cur_used = ptr_clone_vertices;
    while(num_rest_vertice > 2)
    {
        SHAPE shape;
        memset(&shape, 0, sizeof(shape));
        int ret_start_index = -1;
        int ret_end_index = -1;
        num_ret_code = SlicePolygon(ptr_vertices_cur_used, num_rest_vertice, &shape, &ret_start_index, &ret_end_index);
        LOG_PROCESS_ERROR(num_ret_code && "Slice Failed");
        LOG_PROCESS_ERROR(shape.count_point >= 3);
        LOG_PROCESS_ERROR(ret_start_index >= 0);
        LOG_PROCESS_ERROR(ret_end_index >= 0);

        // 超过Box2D的边数限制，需要进行切分
        if (shape.count_point > b2_maxPolygonVertices)
        {
            SHAPE shape_sub;
            for(int i = 0; i < b2_maxPolygonVertices; i++)
            {
                shape_sub.array_point[i] = shape.array_point[i];
                shape_sub.count_point = b2_maxPolygonVertices;
            }
            m_shapes.push_back(shape_sub);

            for(int i = b2_maxPolygonVertices - 1; i < shape.count_point; i++)
            {
                shape.array_point[i - b2_maxPolygonVertices + 2] = shape.array_point[i];
            }
            shape.count_point -= b2_maxPolygonVertices - 2;
        }
        m_shapes.push_back(shape);

        // 切换主副缓冲区，开始准备拷贝
        b2Vec2* ptr_vertices_old = ptr_vertices_cur_used;
        if (ptr_vertices_cur_used == ptr_clone_vertices)
        {
            ptr_vertices_cur_used = ptr_clone_vertices_backup;
        }
        else
        {
            ptr_vertices_cur_used = ptr_clone_vertices;
        }

        // 第一个顶点一定是扫描多边形的开始顶点
        int num_sort_index = 0;
        ptr_vertices_cur_used[num_sort_index++] = ptr_vertices_old[ret_start_index];
        num_ret_code = IsPointEqual(
            ptr_clone_vertices[ret_start_index].x,
            ptr_clone_vertices[ret_start_index].y,
            shape.array_point[0].x,
            shape.array_point[0].y
        );
        if(!num_ret_code)
        {
            // 如果是切割多边形，第二个顶点就是这个交点
            ptr_vertices_cur_used[num_sort_index++] = shape.array_point[0];            
        }

        // 跳过剔除的顶点
        int i = ret_end_index;
        while (i != ret_start_index)
        {
            ptr_vertices_cur_used[num_sort_index++] = ptr_vertices_old[i];
            i++;
            if (i >= num_rest_vertice)
            {
                i -= num_rest_vertice;
            }
        }

        num_rest_vertice = num_sort_index;
    }
    num_result = TRUE;
Exit0:
    SAFE_DELETE_ARRAY(ptr_clone_vertices);
    SAFE_DELETE_ARRAY(ptr_clone_vertices_backup);
    return num_result;
}

int b2Concave::IsOnLine(float point_x, float point_y, float x1, float y1, float x2, float y2)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    float float_diff_x_1_2 = x2 - x1;
    float float_diff_y_1_2 = y2 - y1;

    float float_diff_point_x1 = point_x - x1;
    if(abs(float_diff_x_1_2) < FLOAT_EPS) 
    {
        float float_diff = point_x - x1;
        PROCESS_SUCCES(abs(float_diff) < FLOAT_EPS);
    }

    float float_tan = float_diff_y_1_2 / float_diff_x_1_2;
    float respect_y= float_tan * float_diff_point_x1 + y1;
    float float_diff_respect = point_y - respect_y;

    PROCESS_ERROR(abs(float_diff_respect) < FLOAT_EPS);

Exit1:
	num_result = TRUE;
Exit0:
	return num_result;
}

int b2Concave::IsInSquare(float point_x, float point_y, float x1, float y1, float x2, float y2)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    float small_x = x1;
    float big_x = x2;
    if (x1 > x2)
    {
        big_x = x1;
        small_x = x2;
    }

    float small_y = y1;
    float big_y = y2;
    if (y1 > y2)
    {
        big_y = y1;
        small_y = y2;
    }

    PROCESS_ERROR((point_x < big_x + FLOAT_EPS && point_x > small_x - FLOAT_EPS));
    PROCESS_ERROR((point_y < big_y + FLOAT_EPS && point_y > small_y - FLOAT_EPS));

	num_result = TRUE;
Exit0:
	return num_result;
}

int b2Concave::IsOnSegment(float point_x, float point_y, float x1, float y1, float x2, float y2)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    num_ret_code = IsInSquare(point_x, point_y, x1, y1, x2, y2);
	PROCESS_ERROR(num_ret_code);

    num_ret_code = IsOnLine(point_x, point_y, x1, y1, x2, y2);
    PROCESS_ERROR(num_ret_code);

	num_result = TRUE;
Exit0:
	return num_result;
}

int b2Concave::IsPointEqual(float x1, float y1, float x2,float y2)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

	float diff_x = abs(x2 - x1);
    float diff_y = abs(y2 - y1);

    PROCESS_ERROR((diff_x < FLOAT_EPS) && (diff_y < FLOAT_EPS));

	num_result = TRUE;
Exit0:
	return num_result;
}

int b2Concave::SearchIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, b2Vec2* ptr_point_result)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;
    int num_ret_code_2 = FALSE;

    LOG_PROCESS_ERROR(ptr_point_result);

    {
        b2Vec2 vec_a(x2 - x1, y2 - y1);
        b2Vec2 vec_b(x4 - x3, y4 - y3);
        b2Vec2 vec_s(x3 - x1, y3 - y1);
        float cross_s_b = 0.0f;
        float cross_a_b = b2Cross(vec_a, vec_b);

        PROCESS_ERROR(cross_a_b - 0.0f > 0.0001f || cross_a_b - 0.0f < -0.0001f);

        cross_s_b = b2Cross(vec_s, vec_b);

        ptr_point_result->x = x1 + vec_a.x * cross_s_b / cross_a_b;
        ptr_point_result->y = y1 + vec_a.y * cross_s_b / cross_a_b;
    }


    num_result = TRUE;
Exit0:
    return num_result;   
}

int b2Concave::SlicePolygon(const b2Vec2* const_ptr_vetor_vertices, int count_vertices, SHAPE* ptr_shape, int* ptr_start_index, int* ptr_end_index)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    // 起点不可以从“凹”处开始
    int index_start_valid = -1;
    for (int index_cur = 0; index_cur < count_vertices; index_cur++)
    {
        int index_previous = (index_cur > 0) ? index_cur - 1 : count_vertices - 1;
        int index_next = (index_cur < count_vertices - 1)? index_cur + 1 : index_cur + 1 - count_vertices;
        const b2Vec2* ptr_point_previous = &const_ptr_vetor_vertices[index_previous];
        const b2Vec2* ptr_point_cur = &const_ptr_vetor_vertices[index_cur];
        const b2Vec2* ptr_point_next = &const_ptr_vetor_vertices[index_next];
        float det_vector = det(
            ptr_point_previous->x, ptr_point_previous->y,
            ptr_point_cur->x, ptr_point_cur->y,
            ptr_point_next->x, ptr_point_next->y
        );
        if (det_vector >0.0f)
        {        
            index_start_valid = index_cur;
            break;
        }
    }
    LOG_PROCESS_ERROR(index_start_valid >= 0);
    for (int index_cur = index_start_valid; index_cur < count_vertices; index_cur++)
    {
        
        int index_next = (index_cur < count_vertices - 1)? index_cur + 1 : index_cur + 1 - count_vertices;
        int index_next_next = (index_cur < count_vertices - 2)? index_cur + 2 : index_cur + 2 - count_vertices; //如果是最后，循环到头

        const b2Vec2* ptr_point_cur = &const_ptr_vetor_vertices[index_cur];
        const b2Vec2* ptr_point_next = &const_ptr_vetor_vertices[index_next];
        const b2Vec2* ptr_point_next_next = &const_ptr_vetor_vertices[index_next_next];

        float det_vector = det(
            ptr_point_cur->x, ptr_point_cur->y,
            ptr_point_next->x, ptr_point_next->y,
            ptr_point_next_next->x, ptr_point_next_next->y
        );
        if (det_vector > 0.0f) 
        {
            continue;
        }

        for (int index_check = 0; index_check < count_vertices; index_check++) 
        {
            if ((index_check == index_cur) || (index_check == index_next))
            {
                continue;
            }
            int index_check_next = (index_check < count_vertices - 1) ? index_check + 1 : 0;
            if ((index_check_next == index_cur) || (index_check_next == index_next))
            {
                continue;
            }

            const b2Vec2* ptr_point_check = &const_ptr_vetor_vertices[index_check];
            const b2Vec2* ptr_point_check_next = &const_ptr_vetor_vertices[index_check_next];

            b2Vec2 point_result;
            num_ret_code = SearchIntersection(
                ptr_point_cur->x, ptr_point_cur->y,
                ptr_point_next->x, ptr_point_next->y,
                ptr_point_check->x, ptr_point_check->y,
                ptr_point_check_next->x, ptr_point_check_next->y,
                &point_result
            );
            if (!num_ret_code) 
            {
                continue;
            }
            num_ret_code = IsOnSegment(
                point_result.x, point_result.y,
                ptr_point_check->x, ptr_point_check->y,
                ptr_point_check_next->x, ptr_point_check_next->y
            );
            if (!num_ret_code)
            {
                continue;
            }
            
            *ptr_start_index = index_check;
            *ptr_end_index = index_next;

            ptr_shape->array_point[ptr_shape->count_point++] = point_result;
            int i = index_check_next;
            while(i != index_next)
            {
                ptr_shape->array_point[ptr_shape->count_point++] = const_ptr_vetor_vertices[i];
                i++;
                if (i >= count_vertices)
                {
                    i -= count_vertices;
                }
            }
            PROCESS_SUCCES(TRUE);
        }
        LOG_PROCESS_ERROR(FALSE && "Not Found Intersection");
    }
    *ptr_start_index = 0;
    *ptr_end_index = count_vertices - 1;
    for(int i = 0; i < count_vertices; i++)
    {
        ptr_shape->array_point[i] = const_ptr_vetor_vertices[i];
    }
    ptr_shape->count_point = count_vertices;

Exit1:
    num_result = TRUE;
Exit0:
    if (!num_result)
    {
        printf("Error!\n");
    }    
    return num_result;   
}
