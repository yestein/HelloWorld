//
//  GB2ShapeCache-x.cpp
//  
//  Loads physics sprites created with http://www.PhysicsEditor.de
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//      http://www.PhysicsEditor.de
//      http://texturepacker.com
//      http://www.code-and-web.de
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include "gb2_shape_cache_x.h"
#include "CCNS.h"

using namespace cocos2d;

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2FixtureDef::~GB2FixtureDef() {
    delete next;
    delete fixture.shape;
}

GB2BodyDef::~GB2BodyDef() {
    if (fixtures)
        delete fixtures;
}

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}
	
	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, GB2BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape) {
	std::map<std::string, GB2BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	GB2BodyDef *so = (*pos).second;

	GB2FixtureDef *fix = so->fixtures;
    while (fix) {
        body->CreateFixture(&fix->fixture);
        fix = fix->next;
    }
}

GB2FixtureDef* GB2ShapeCache::GetFixtures(const std::string &shape)
{
    GB2FixtureDef* ptr_ret_fixturedef = NULL;
    GB2BodyDef *ptr_body_def = NULL;
    std::map<std::string, GB2BodyDef *>::iterator pos = shapeObjects.find(shape);
    assert(pos != shapeObjects.end());
    ptr_body_def = pos->second;

    ptr_ret_fixturedef = ptr_body_def->fixtures;
    assert(ptr_ret_fixturedef);
    return ptr_ret_fixturedef;
}

cocos2d::CCPoint GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, GB2BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
	
	GB2BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
	std::string fullPath = CCFileUtils::getInstance()->fullPathForFilename(plist);
	Dictionary *dict = Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
	CCAssert(dict != NULL, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict->count() != 0, "plist file empty or not existing");
	
	Dictionary* metadataDict = static_cast<Dictionary*>(dict->objectForKey("metadata") );

	int format = metadataDict->valueForKey("format")->intValue();
    ptmRatio = metadataDict->valueForKey("ptm_ratio")->floatValue();
	CCAssert(format == 1, "Format not supported");

	Dictionary *bodyDict = static_cast<Dictionary*>(dict->objectForKey("bodies"));

    b2Vec2 vertices[b2_maxPolygonVertices];
	std::string bodyName;
	DictElement* element = NULL;
	CCDICT_FOREACH(bodyDict, element)
	{
		bodyName = element->getStrKey();
		GB2BodyDef *bodyDef = new GB2BodyDef();
		Dictionary* bodyData = static_cast<Dictionary*>(element->getObject());
		bodyDef->anchorPoint = PointFromString(bodyData->valueForKey("anchorpoint")->getCString());
		
		Array* fixtureList = static_cast<Array*>(bodyData->objectForKey("fixtures"));
		
        GB2FixtureDef **nextFixtureDef = &(bodyDef->fixtures);

		Object* pObj = NULL;
		CCARRAY_FOREACH(fixtureList, pObj)
		{

            b2FixtureDef basicData;
			Dictionary *fixtureData = static_cast<Dictionary*>(pObj);
			
            basicData.filter.categoryBits = fixtureData->valueForKey("filter_categoryBits")->intValue();
            basicData.filter.maskBits = fixtureData->valueForKey("filter_maskBits")->intValue();
            basicData.filter.groupIndex = fixtureData->valueForKey("filter_groupIndex")->intValue();
            basicData.friction = fixtureData->valueForKey("friction")->floatValue();
            basicData.density = fixtureData->valueForKey("density")->floatValue();
            basicData.restitution = fixtureData->valueForKey("restitution")->floatValue();
            basicData.isSensor = fixtureData->valueForKey("isSensor")->boolValue();

			const String *cb = fixtureData->valueForKey("userdataCbValue");
			
            int callbackData = 0;
			
			if (cb)
				callbackData = cb->intValue();
            
			const String* fixtureType = fixtureData->valueForKey("fixture_type");
			
			if (fixtureType->compare("POLYGON") == 0) {
				Array* polygonsArray = static_cast<Array*>(fixtureData->objectForKey("polygons"));
				Object* pPolygon = NULL;
				CCARRAY_FOREACH(polygonsArray, pPolygon)
				{
                    GB2FixtureDef *fix = new GB2FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
					
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
					Array* polygonArray = static_cast<Array*>(pPolygon);
                    assert(polygonArray->count() <= b2_maxPolygonVertices);

					Object* pSinglePolygon = NULL;
					CCARRAY_FOREACH(polygonArray, pSinglePolygon)
					{
						String* pStr = dynamic_cast<String*>(pSinglePolygon);
                        Point offset = PointFromString(pStr->getCString());
                        vertices[vindex].x = (offset.x / ptmRatio) ; 
                        vertices[vindex].y = (offset.y / ptmRatio) ; 
                        vindex++;
                    }
                    
                    polyshape->Set(vertices, vindex);
                    fix->fixture.shape = polyshape;
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);
				}
				
			} else if (fixtureType->compare("CIRCLE") == 0) {
				GB2FixtureDef *fix = new GB2FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
				Dictionary *circleData = static_cast<Dictionary*>(fixtureData->objectForKey("circle"));
                
                b2CircleShape *circleShape = new b2CircleShape();
				
                circleShape->m_radius = circleData->valueForKey("radius")->floatValue() / ptmRatio;
				Point p = PointFromString(circleData->valueForKey("position")->getCString());
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
				
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);

			} else {
				CCAssert(0, "Unknown fixtureType");
			}
			
			// add the body element to the hash
			shapeObjects[bodyName] = bodyDef;
		}
	}
}