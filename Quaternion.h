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

template<typename T>
class Quaternion {
public:
	Quaternion(){}
	Quaternion(std::array<T, 3> vector3){
		for(uint8_t n=1; n<4; n++){
			value[n] = vector3[n];
		}
		value[0] = 0;
	}
	Quaternion(T val0, T val1, T val2, T val3){
		value[0] = val0;
		value[1] = val1;
		value[2] = val2;
		value[3] = val3;
	}

	Quaternion normalize(){
		T size = 0;
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
        Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] + obj[n];
		}
		return tmp;
	}

	Quaternion operator + (Quaternion obj){
		Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] + obj[n];
		}
		return tmp;
	}

	Quaternion operator*(Quaternion &obj){
		return Quaternion(
				value[0]*obj[0]-value[1]*obj[1]-value[2]*obj[2]-value[3]*obj[3],
				value[0]*obj[1]-value[1]* obj[0]+value[2]*obj[3]-value[3]*obj[2],
				value[0]*obj[2]-value[1]*obj[3]+value[2]*obj[0]+value[3]*obj[1],
				value[0]*obj[3]+value[1]*obj[2]-value[2]*obj[1]+value[3]*obj[0]);
	}

	Quaternion operator*(T val){
        Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] * val;
		}
		return tmp;
	}

	Quaternion operator-(Quaternion &obj){
        Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] - obj[n];
		}
		return tmp;
	}

	Quaternion operator-(Quaternion obj){
        Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] - obj[n];
		}
		return tmp;
	}

	Quaternion operator/(T val){
        Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] / val;
		}
		return tmp;
	}

	void operator*=(T val){
		for(auto &it:value){
			it *= val;
		}
	}

	T & operator [](int n) { return value[n]; }
private:
	std::array<T, 4> value;
};

#endif /* QUATERNION_QUATERNION_H_ */
