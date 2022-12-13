#include <iostream>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <SDL2/SDL.h>



// define the gravity
b2Vec2 gravity(0.0f, -9.8f);

// create the world
b2World world(gravity);


// define the ball's body
b2BodyDef ballBodyDef;
ballBodyDef.type = b2_dynamicBody;
ballBodyDef.position.Set(0.0f, 10.0f);
b2Body* ballBody = world.CreateBody(&ballBodyDef);

// define the ball's shape
b2CircleShape ballShape;
ballShape.m_radius = 1.0f;

// define the ball's fixture
b2FixtureDef ballFixtureDef;
ballFixtureDef.shape = &ballShape;
ballFixtureDef.density = 1.0f;
ballFixtureDef.friction = 0.0f;
ballFixtureDef.restitution = 1.0f;
ballFixtureDef.filter.groupIndex = -1;
ballBody->CreateFixture(&ballFixtureDef);

b2Vec2 velocity(1.0f, 0.0f); // 設定水平速度為 1，垂直速度為 0
circle->SetLinearVelocity(velocity);

float timeStep = 1.0f / 60.0f; // 每秒更新 60 次
int32 velocityIterations = 6;
int32 positionIterations = 2;
world->Step(timeStep, velocityIterations, positionIterations);



//m_p可以獲得圓心
//m_radius可以獲得半徑

class MyContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) {
        // 碰撞開始時執行的操作

        // 獲取碰撞的兩個形狀
        b2Shape* shapeA = contact->GetFixtureA()->GetShape();
        b2Shape* shapeB = contact->GetFixtureB()->GetShape();

        // 判斷兩個形狀是否為圓形
        if (shapeA->GetType() == b2Shape::e_circle && shapeB->GetType() == b2Shape::e_circle) {
            // 獲取兩個圓形的半徑
            float radiusA = shapeA->m_radius;
            float radiusB = shapeB->m_radius;

            // 判斷兩個圓形的半徑是否相等
            if (radiusA == radiusB) {
                // 兩個圓形的半徑相等，碰到了
                world->DestroyBody();
            }
        }
    }
    void EndContact(b2Contact* contact) {


    }
};
//如果相同球體碰到合成下一個球體
//還沒放圖片
//算分數
//超過那條線幾秒鐘失敗
