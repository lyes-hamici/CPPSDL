#include <string>
#include <stdexcept>
#include <cmath>
#include "Vector2.hpp"
Vector2::Vector2(){}
Vector2::Vector2(float value){
	this->x = value;
	this->y = value;
}
Vector2::Vector2(float x,float y){
	this->x = x;
	this->y = y;
}
Vector2::~Vector2(){}
float& Vector2::operator[](int index){
	if(index < 0 || index > 1){throw std::out_of_range("[Vector2] Index '"+std::to_string(index)+"' out of range (0-1).");}
	return index == 0 ? this->x : this->y;
}
bool Vector2::operator==(Vector2 other){
	return this->x == other.x && this->y == other.y;
}
Vector2 Vector2::operator+(Vector2 other){
	return Vector2(this->x + other.x,this->y + other.y);
}
Vector2 Vector2::operator+(float value){
	return Vector2(this->x + value,this->y + value);
}
Vector2 Vector2::operator-(Vector2 other){
	return Vector2(this->x - other.x,this->y - other.y);
}
Vector2 Vector2::operator-(float value){
	return Vector2(this->x - value,this->y - value);
}
Vector2 Vector2::operator*(Vector2 other){
	return Vector2(this->x * other.x,this->y * other.y);
}
Vector2 Vector2::operator*(float scale){
	return Vector2(this->x * scale,this->y * scale);
}
Vector2 Vector2::operator/(Vector2 other){
	return Vector2(this->x / other.x,this->y / other.y);
}
Vector2 Vector2::operator/(float divider){
	return Vector2(this->x / divider,this->y / divider);
}
void Vector2::Set(float value){
	this->x = value;
	this->y = value;
}
void Vector2::Set(float x,float y){
	this->x = x;
	this->y = y;
}
Vector2 Vector2::MoveTowards(Vector2 other,float amount){
	auto vector = Vector2();
	if(this->x < other.x){
		vector.x = std::min(this->x + amount,other.x);
	}
	else if(this->x > other.x){
		vector.x = std::max(this->x - amount,other.x);
	}
	if(this->y < other.y){
		vector.y = std::min(this->y + amount,other.y);
	}
	else if(this->y > other.y){
		vector.y = std::max(this->y - amount,other.y);
	}
	return vector;
}