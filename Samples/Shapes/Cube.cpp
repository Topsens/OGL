#include "Cube.h"
#include "Square.h"

Cube::Cube()
{
    for (int i = 0; i < 6; i++)
    {
        this->AddChild(std::make_shared<Square>());
    }

    this->children[0]->Position.Z =  .5f;  // front
    this->children[1]->Position.Z = -.5f;  // back
    this->children[2]->Position.X = -.5f;  // left
    this->children[3]->Position.X =  .5f;  // right
    this->children[4]->Position.Y =  .5f;  // top
    this->children[5]->Position.Y = -.5f;  // bottom

    this->children[1]->Rotation = Quaternion<>::FromAxisAngle(Vertex::YAxis, ToRadian(180.f)).ToRotation();    // back
    this->children[2]->Rotation = Quaternion<>::FromAxisAngle(Vertex::YAxis, ToRadian(-90.f)).ToRotation();    // left
    this->children[3]->Rotation = Quaternion<>::FromAxisAngle(Vertex::YAxis, ToRadian( 90.f)).ToRotation();    // right
    this->children[4]->Rotation = Quaternion<>::FromAxisAngle(Vertex::XAxis, ToRadian(-90.f)).ToRotation();    // top
    this->children[5]->Rotation = Quaternion<>::FromAxisAngle(Vertex::XAxis, ToRadian( 90.f)).ToRotation();    // bottom
}