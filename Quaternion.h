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



template<typename T=float>
class Quaternion {
public:
	Quaternion(){}
	Quaternion(std::array<T, 3> vector3){
		for(uint8_t n=1; n<4; n++){
			value[n] = vector3[n];
		}
		value[0] = 0;
	}
	Quaternion(std::array<T, 4> vector4){
		for(uint8_t n=1; n<4; n++){
			value[n] = vector4[n];
		}
		value[0] = 0;
	}
	Quaternion(T val0, T val1, T val2, T val3){
		value[0] = val0;
		value[1] = val1;
		value[2] = val2;
		value[3] = val3;
	}

	std::array<std::array<T, 3>, 3> rotationMat(){
		std::array<std::array<T, 3>, 3> tmp;
		tmp[0][0] = 2*std::pow(value[0],2)+2*std::pow(value[1],2)-1;
		tmp[0][1] = 2*(value[1]*value[2]-value[3]*value[0]);
		tmp[0][2] = 2*(value[1]*value[3]+value[2]*value[0]);
		tmp[1][0] = 2*(value[1]*value[2]+value[3]*value[0]);
		tmp[1][1] = 2*std::pow(value[0],2)+2*std::pow(value[2],2)-1;
		tmp[1][2] = 2*(value[2]*value[3]-value[1]*value[0]);
		tmp[2][0] = 2*(value[1]*value[3]-value[2]*value[0]);
		tmp[2][1] = 2*(value[2]*value[3]+value[2]*value[0]);
		tmp[2][2] = 2*std::pow(value[0],2)+2*std::pow(value[3],2)-1;

		return tmp;
	}

	std::array<T, 3> rotateVector(std::array<T, 3> arg){
		const std::array<std::array<T, 3>, 3> rotationMat = this->rotationMat();
		std::array<T, 3> tmp;
		tmp[0] = rotationMat[0][0]*arg[0] + rotationMat[0][1]*arg[1] + rotationMat[0][2]*arg[2];
		tmp[1] = rotationMat[1][0]*arg[0] + rotationMat[1][1]*arg[1] + rotationMat[1][2]*arg[2];
		tmp[2] = rotationMat[2][0]*arg[0] + rotationMat[2][1]*arg[1] + rotationMat[2][2]*arg[2];
		return tmp;
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

	Quaternion invers(){
		return Quaternion(value[0],value[1],value[2],value[3]);
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

	Quaternion operator*=(T val){
		for(auto &it:value){
			it *= val;
		}
		return *this;
	}

	Quaternion operator*=(Quaternion obj){
		Quaternion tmp(
			value[0]*obj[0]-value[1]*obj[1]-value[2]*obj[2]-value[3]*obj[3],
			value[0]*obj[1]-value[1]* obj[0]+value[2]*obj[3]-value[3]*obj[2],
			value[0]*obj[2]-value[1]*obj[3]+value[2]*obj[0]+value[3]*obj[1],
			value[0]*obj[3]+value[1]*obj[2]-value[2]*obj[1]+value[3]*obj[0]);

		return *this = tmp;
	}

	T & operator [](int n) { return value[n]; }
private:
	std::array<T, 4> value;
};

#endif /* QUATERNION_QUATERNION_H_ */
