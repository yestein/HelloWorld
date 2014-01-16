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

#ifndef GB2_SHAPE_CACHE_X_H
#define GB2_SHAPE_CACHE_X_H

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class b2Body;
struct b2FixtureDef;

class GB2FixtureDef {
public:
    GB2FixtureDef()
        : next(NULL) {}

    ~GB2FixtureDef();
    GB2FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class GB2BodyDef {
public:
    GB2BodyDef()
        : fixtures(NULL) {}

    ~GB2BodyDef();
    GB2FixtureDef *fixtures;
    cocos2d::Point anchorPoint;
};

namespace cocos2d {
    /**
     * Internal class to hold the fixtures
     */

	class GB2ShapeCache {
	public:
		// Static interface
		static GB2ShapeCache* sharedGB2ShapeCache(void);
		
	public:
		bool init();			
		void addShapesWithFile(const std::string &plist);
		void addFixturesToBody(b2Body *body, const std::string &shape);
        GB2FixtureDef* GetFixtures(const std::string &shape);
		cocos2d::Point anchorPointForShape(const std::string &shape);
		void reset();
		float getPtmRatio() { return ptmRatio; }
		~GB2ShapeCache() {}
		
	private:
		std::map<std::string, GB2BodyDef *> shapeObjects;
		GB2ShapeCache(void) {}
		float ptmRatio;
	};
};

#endif
