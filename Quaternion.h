/*
 * Quaternion.h
 *
 *  Created on: Feb 11, 2023
 *      Author: OHYA Satoshi
 */

#ifndef QUATERNION_QUATERNION_H_
#define QUATERNION_QUATERNION_H_

#include <array>

class Quaternion {
public:
	Quaternion(){}
	Quaternion(std::array<float, 3> vector3){
		for(uint8_t n=0; n<3; n++){
			value[n] = vector3[n];
		}
		value[3] = 0;
	}
	Quaternion(float val0, float val1, float val2, float val3){
		value[0] = val0;
		value[1] = val1;
		value[2] = val2;
		value[3] = val3;
	}

	Quaternion operator + (Quaternion obj){
		Quaternion tmp;
		for(uint8_t n=0; n<4; n++){
			tmp[n] = value[n] + obj[n];
		}
		return tmp;
	}

	Quaternion operator*(Quaternion obj){
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

	float & operator [](int n) { return value[n]; }
private:
	std::array<float, 4> value;
};

#endif /* QUATERNION_QUATERNION_H_ */
