/*
 * Quaternion.h
 *
 *  Created on: Feb 11, 2023
 *      Author: OHYA Satoshi
 */

#ifndef QUATERNION_QUATERNION_H_
#define QUATERNION_QUATERNION_H_

#include <array>
#include <cmath>

class Quaternion {
public:
	Quaternion(){}
	Quaternion(std::array<float, 3> vector3){
		for(uint8_t n=1; n<4; n++){
			value[n] = vector3[n];
		}
		value[0] = 0;
	}
	Quaternion(float val0, float val1, float val2, float val3){
		value[0] = val0;
		value[1] = val1;
		value[2] = val2;
		value[3] = val3;
	}

	Quaternion normalize(){
		float size = 0;
		for(auto &it:value){
			size += std::pow(it,2);
		}
		size = std::sqrt(size);

		if(size == 0){
			return Quaternion();
		}

		for(auto &it:value){
			it /= size;
		}
		return *this;
	}

	Quaternion operator + (Quaternion &obj){
		for(uint8_t n=0; n<4; n++){
			this->value[n] += obj[n];
		}
		return *this;
	}

	Quaternion operator*(Quaternion &obj){
		return Quaternion(
				value[0]*obj[0]-value[1]*obj[1]-value[2]*obj[2]-value[3]*obj[3],
				value[0]*obj[1]-value[1]* obj[0]+value[2]*obj[3]-value[3]*obj[2],
				value[0]*obj[2]-value[1]*obj[3]+value[2]*obj[0]+value[3]*obj[1],
				value[0]*obj[3]+value[1]*obj[2]-value[2]*obj[1]+value[3]*obj[0]);
	}

	Quaternion &operator*(float val){
		for(auto &it:value){
			it *= val;
		}
		return *this;
	}

	Quaternion &operator-(Quaternion &obj){
		for(uint8_t n=0; n<4; n++){
			this->value[n] -= obj[n];
		}
		return *this;
	}

	Quaternion &operator/(float val){
		for(uint8_t n=0; n<4; n++){
			this->value[n] /= val;
		}
		return *this;
	}

	void operator*=(float val){
		for(auto &it:value){
			it *= val;
		}
	}

	float & operator [](int n) { return value[n]; }
private:
	std::array<float, 4> value;
};

#endif /* QUATERNION_QUATERNION_H_ */
