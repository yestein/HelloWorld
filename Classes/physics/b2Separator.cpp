//
//  b2Separator.cpp
//
//  Algorithm Created by Antoan Angelov
//  CPP Version Created by Jarad Delorenzo on 1/7/13.
//  Modifyed by yestein(Lei Yu) on 1/16/2014
//

#include "b2Separator.h"
#define MAX_VALUE 2147483647

int b2Separator::Separate(b2Body* pBody, b2FixtureDef* pFixtureDef,const vector<b2Vec2>* const_ptr_vetor_vertices, int scale) 
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    int num_vertices_count = const_ptr_vetor_vertices->size();
    int num_figures_count = 0;
    vector<b2Vec2> vector_vertices;
    vector<vector<b2Vec2>> vector_figures;  
    b2Vec2 array_b2vec2_vertices[b2_maxPolygonVertices];

    num_ret_code = calcShapes(const_ptr_vetor_vertices, vector_figures);
    LOG_PROCESS_ERROR(num_ret_code);

    num_figures_count = vector_figures.size();    
    for (int i = 0;i < num_figures_count;i++)
    {
        b2PolygonShape b2polygonshape;
        vector<b2Vec2>& ref_figure_vertices = vector_figures[i];
        int num_figure_vertices = ref_figure_vertices.size();
        for (int j = 0; j < num_figure_vertices; j++) 
        {
            array_b2vec2_vertices[j] = b2Vec2(ref_figure_vertices[j].x/scale,ref_figure_vertices[j].y/scale);
        }
        assert(num_figure_vertices >= 3);

        b2polygonshape.Set(array_b2vec2_vertices, num_figure_vertices);
        pFixtureDef->shape = &b2polygonshape;
        pBody->CreateFixture(pFixtureDef); 
    }

	num_result = TRUE;
Exit0:
	return num_result;
   
}
/**
* Checks whether the ptr_array_vertices in can be properly distributed into the new fixtures (more specifically, it makes sure there are no overlapping segments and the ptr_array_vertices are in clockwise order). 
* It is recommended that you use this method for debugging only, because it may cost more CPU usage.
* @param vector_vertices The ptr_array_vertices to be validated.
* @return An integer which can have the following values:
* 0 if the ptr_array_vertices can be properly processed.
* 1 If there are overlapping lines.
* 2 if the points are <b>not</b> in clockwise order.
* 3 if there are overlapping lines and the points are not in clockwise order.
* */        
int b2Separator::Validate(const vector<b2Vec2> &vector_vertices) 
{
	int num_result = 0;
	int num_ret_code = FALSE;

    int num_vertices = vector_vertices.size();

    int fl2 = FALSE;

    for (int index_point = 0; index_point < num_vertices; index_point++) 
    {
        int index_next = (index_point < num_vertices - 1) ? index_point + 1 : 0; 
        int index_previous = (index_point > 0) ? index_point - 1 : num_vertices - 1;

        b2Vec2 point = vector_vertices.at(index_point);
        b2Vec2 point_next = vector_vertices.at(index_next);
        b2Vec2 point_previous = vector_vertices.at(index_previous);

        b2Vec2 vec2next = point_next - point;

        int bool_anti_clockwise = FALSE;
        for (int i = 0;i < num_vertices;i++) 
        {
            if ((i != index_point)&&(i != index_next)) 
            {
                if (!bool_anti_clockwise) 
                {
                    b2Vec2 vec_check = vector_vertices[i] - point_next;
                    float d = det(vec2next, vec_check);
                    if ((d > 0.0f)) 
                    {
                        bool_anti_clockwise = TRUE;
                    }
                }

                if ((i != index_previous)) 
                {
                    int j2= (i <num_vertices - 1) ? i + 1 : 0;
                    if ( hitSegment (
                        vector_vertices[index_point].x,vector_vertices[index_point].y,vector_vertices[index_next].x,vector_vertices[index_next].y,
                        vector_vertices[i].x,vector_vertices[i].y,vector_vertices[j2].x,vector_vertices[j2].y)) {
                        num_result=1; // TODO: This may be wrong!!!
                    }
                }
            }
        }

        if (!bool_anti_clockwise) {
            fl2 = TRUE;
        }
    }

    if (fl2) {
        if (num_result==1) {
            num_result=3;
        }
        else {
            num_result=2;
        }

    }
Exit0:
	return num_result;
    
}
        
int b2Separator::calcShapes(const vector<b2Vec2>* const_ptr_vetor_vertices, vector<vector<b2Vec2> > &result)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    vector<b2Vec2> vec;
    int i, n, j,minLen;
    float det_vector, t, dx, dy;
    int i1, i2, i3;
    b2Vec2 p1, p2, p3;
    int j1, j2;
    b2Vec2 v1, v2;
    int k=0, h=0;
    vector<b2Vec2> *vec1, *vec2;
    b2Vec2 *pV, hitV(0,0);
    bool isConvex;
    vector<vector<b2Vec2> > vector_figures;
    queue<vector<b2Vec2> > queue;

    queue.push(*const_ptr_vetor_vertices);

    while (!queue.empty()) {
        vec = queue.front();
        n = vec.size();
        isConvex = true;

        for ( i = 0; i < n; i++) 
        {
            i1 = i;
            i2 = (i < n - 1)? i + 1 : i + 1 - n;
            i3 = (i < n - 2)? i + 2 : i + 2 - n; //如果是最后，循环到头

            p1 = vec[i1];
            p2 = vec[i2];
            p3 = vec[i3];

            b2Vec2 vec_12 = p2 - p1;
            b2Vec2 vec_23 = p3 - p2;

            det_vector = det(vec_12, vec_23); // 向量叉积，用于判断凹凸
            if ((det_vector<0)) 
            {
                isConvex=false;
                minLen = MAX_VALUE;

                for (j = 0; j < n; j++) {
                    if ((j != i1)&&(j != i2)) {
                        j1 = j;
                        j2 = (j < n - 1) ? j + 1 : 0;

                        v1 = vec[j1];
                        v2 = vec[j2];

                        pV = hitRay(p1.x,p1.y,p2.x,p2.y,v1.x,v1.y,v2.x,v2.y);

                        if (pV) {
                            b2Vec2 v = *pV;
                            dx = p2.x - v.x;
                            dy = p2.y - v.y;
                            t = dx * dx + dy * dy;

                            if ((t<minLen)) {
                                h = j1;
                                k = j2;
                                hitV=v;
                                minLen=t;
                            }
                        }
                    }
                }

                LOG_PROCESS_ERROR(minLen < MAX_VALUE);

                vec1 = new vector<b2Vec2>();
                vec2 = new vector<b2Vec2>();

                j1=h;
                j2=k;
                v1=vec[j1];
                v2=vec[j2];

                if (!pointsMatch(hitV.x,hitV.y,v2.x,v2.y)) {
                    vec1->push_back(hitV);
                }
                if (!pointsMatch(hitV.x,hitV.y,v1.x,v1.y)) {
                    vec2->push_back(hitV);
                }

                h = -1;
                k = i1;
                while (true) {
                    if ((k!=j2)) {
                        vec1->push_back(vec[k]);
                    }
                    else {
                        LOG_PROCESS_ERROR(h >= 0);
                        LOG_PROCESS_ERROR(h < n);
                        if (! isOnSegment(v2.x,v2.y,vec[h].x,vec[h].y,p1.x,p1.y)) {
                            vec1->push_back(vec[k]);
                        }
                        break;
                    }

                    h=k;
                    if (((k-1)<0)) {
                        k=n-1;
                    }
                    else {
                        k--;
                    }
                }

                reverse(vec1->begin(), vec1->end());

                h=-1;
                k=i2;
                while (true) {
                    if ((k!=j1)) {
                        vec2->push_back(vec[k]);
                    }
                    else {
                        LOG_PROCESS_ERROR(h >= 0);
                        LOG_PROCESS_ERROR(h < n);
                        if (((k==j1)&&! isOnSegment(v1.x,v1.y,vec[h].x,vec[h].y,p2.x,p2.y))) {
                            vec2->push_back(vec[k]);
                        }
                        break;
                    }

                    h=k;
                    if (((k+1)>n-1)) {
                        k=0;
                    }
                    else {
                        k++;
                    }
                }

                queue.push(*vec1);
                queue.push(*vec2);
                queue.pop();

                break;
            }
        }

        if (isConvex) {
            vector_figures.push_back(queue.front());
            queue.pop();
        }
    }
    result = vector_figures;
	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        printf("Error!\n");
    }    
	return num_result;   
}
        
b2Vec2* b2Separator::hitRay(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float t1 = x3-x1;
    float t2 = y3-y1;
    float t3 = x2-x1;
    float t4 = y2-y1;
    float t5 = x4-x3;
    float t6 = y4-y3;
    float t7 = t4*t5-t3*t6;

    //DBZ Error. Undefined hit segment.
    if(t7 == 0) return NULL;
    
    float  a = (((t5*t2) - t6*t1) / t7);
    float px = x1+a*t3;
    float py = y1+a*t4;
    bool b1 = isOnSegment(x2,y2,x1,y1,px,py);
    bool b2 = isOnSegment(px,py,x3,y3,x4,y4);
    
    if(b1 && b2) {
        return new b2Vec2(px,py);
    }
    return NULL;
}

b2Vec2* b2Separator::hitSegment(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float t1 = x3-x1;
    float t2 = y3-y1;
    float t3 = x2-x1;
    float t4 = y2-y1;
    float t5 = x4-x3;
    float t6 = y4-y3;
    float t7 = t4*t5 - t3*t6;
    
    //DBZ Error. Undefined hit segment.
    if(t7 == 0) return NULL;
    
    float  a = (((t5*t2) - t6*t1) / t7);
    float px = x1+a*t3;
    float py = y1+a*t4;
    bool b1 = isOnSegment(px,py,x1,y1,x2,y2);
    bool b2 = isOnSegment(px,py,x3,y3,x4,y4);
    
    if(b1 && b2) {
        return new b2Vec2(px,py);
    }
    return NULL;
}

bool b2Separator::isOnSegment(float point_x, float point_y, float x1, float y1, float x2, float y2) {
    bool b1 = ((x1 + 0.1 >= point_x && point_x >= x2 - 0.1)||(x1 - 0.1 <= point_x && point_x <= x2 + 0.1));
    bool b2 = ((y1 + 0.1 >= point_y && point_y >= y2 - 0.1)||(y1 - 0.1 <= point_y && point_y <= y2 + 0.1));
    return (b1 && b2 && isOnLine(point_x, point_y, x1, y1, x2, y2));
}
        
bool b2Separator::pointsMatch(float x1 ,float y1 ,float x2 ,float y2) {
    float dx = (x2>=x1) ? x2-x1 : x1-x2;
    float dy = (y2>=y1) ? y2-y1 : y1-y2;
    return ((dx<0.1f) && dy<0.1f);
}
        
bool b2Separator::isOnLine(float px ,float py ,float x1 ,float y1 ,float x2 ,float y2) {
    if(x2 - x1 > 0.1f || x1 - x2 > 0.1f) 
    {
        float float_tan = (y2 - y1) / (x2 - x1);
		float possibleY= float_tan * (px - x1) + y1;
		float diff = (possibleY > py ? possibleY - py : py - possibleY);
        return (diff < 0.1f);
    }
    return (x1 - 0.1f < px || px < x1 +  0.1f);
}
        
float b2Separator::det(float x1, float y1, float x2, float y2, float x3, float y3) 
{
	return x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1;
}

float b2Separator::det(b2Vec2 &vec1, b2Vec2 &vec2)
{
    return vec1.x * vec2.y - vec2.x * vec1.y;
}
        
//		private function err():void {
//			throw new Error("A problem has occurred. Use the Validate() method to see where the problem is.");
//		}