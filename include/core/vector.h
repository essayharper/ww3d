#ifndef WW3D_VECTOR_H
#define WW3D_VECTOR_H

class vec2 {
    public:
    float x;
    float y;

    vec2() : x(0), y(0) {};

    vec2(float x, float y) {
        this->x = x;
        this->y = y;
    };
    
    inline vec2 operator + (vec2 &other) {
        vec2 ret;
        ret.x = this->x + other.x;
        ret.y = this->y + other.y;
        return ret;
    };

    inline vec2 operator - (vec2 &other) {
        vec2 ret;
        ret.x = this->x - other.x;
        ret.y = this->y - other.y;
        return ret;
    };

    inline vec2 operator * (const float amount) {
        vec2 ret;
        ret.x = this->x * amount;
        ret.y = this->y * amount;
        return ret;
    };

    inline vec2 operator / (const float amount) {
        vec2 ret;
        ret.x = this->x / amount;
        ret.y = this->y / amount;
        return ret;
    };

    inline void operator += (vec2 &other) {
        this->x += other.x;
        this->y += other.y;
    };

    inline void operator -= (vec2 &other) {
        this->x -= other.x;
        this->y -= other.y;
    };

    inline void operator *= (const float amount) {
        this->x *= amount;
        this->y *= amount;
    };

    inline void operator /= (const float amount) {
        this->x /= amount;
        this->y /= amount;
    };
};

class vec3 {
    public:
    float x;
    float y;
    float z;

    vec3() : x(0), y(0), z(0) {};

    vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    inline vec3 operator + (vec3 &other) {
        vec3 ret;
        ret.x = this->x + other.x;
        ret.y = this->y + other.y;
        ret.z = this->z + other.z;
        return ret;
    };

    inline vec3 operator - (vec3 &other) {
        vec3 ret;
        ret.x = this->x - other.x;
        ret.y = this->y - other.y;
        ret.z = this->z - other.z;
        return ret;
    };

    inline vec3 operator * (const float amount) {
        vec3 ret;
        ret.x = this->x * amount;
        ret.y = this->y * amount;
        ret.z = this->z * amount;
        return ret;
    };

    inline vec3 operator / (const float amount) {
        vec3 ret;
        ret.x = this->x / amount;
        ret.y = this->y / amount;
        ret.z = this->z / amount;
        return ret;
    };

    inline void operator += (vec3 &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    };

    inline void operator -= (vec3 &other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

    };

    inline void operator *= (const float amount) {
        this->x *= amount;
        this->y *= amount;
        this->z *= amount;
    };

    inline void operator /= (const float amount) {
        this->x /= amount;
        this->y /= amount;
        this->z /= amount;
    };
};
#endif //WW3D_VECTOR_H