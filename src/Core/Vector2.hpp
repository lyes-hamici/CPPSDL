#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER
class Vector2{
	public:
		float x;
		float y;
        Vector2();
        Vector2(float value);
        Vector2(float x,float y);
        ~Vector2();
		float& operator[](int index);
		bool operator==(Vector2 other);
		Vector2 operator+(Vector2 other);
		Vector2 operator+(float value);
		Vector2 operator-(Vector2 other);
		Vector2 operator-(float value);
		Vector2 operator*(Vector2 other);
		Vector2 operator*(float scale);
		Vector2 operator/(Vector2 other);
		Vector2 operator/(float divider);
        void Set(float x,float y);
        void Set(float value);
		Vector2 MoveTowards(Vector2 other,float amount);
};
#endif