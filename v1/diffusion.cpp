#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include "diffusion.h"
using namespace std;
VecLong first_kind(const VecLong &f0, long double p){
	VecLong f1;
	f1.push_back(0);
	CommonMethods::Instance().clear_corrent_x();
	int xN=f0.size();
	for (int i=1; i<xN-1; i++){
		long double dx = CommonMethods::Instance().get_next_dx();
		long double dt = CommonMethods::Instance().get_next_dt();

		long double df=f0[i-1]+f0[i+1]-2*f0[i];
		df *=p/(dx*dx);
		f1.push_back(df*dt+f0[i]);		
	}
	f1.push_back(0);
	return f1;
}

VecLong second_kind(const VecLong &f0, long double p){
	VecLong f1;
	int xN=f0.size();
	f1.push_back(0);
	CommonMethods::Instance().clear_corrent_x();
	for (int i=1; i<xN-1; i++){
		long double df=f0[i-1]+f0[i+1]-2*f0[i];
		long double dx = CommonMethods::Instance().get_next_dx();
		df *=p/(dx*dx);
		long double dt = CommonMethods::Instance().get_next_dt();
		f1.push_back(df*dt+f0[i]);		
	}
	long double dx = CommonMethods::Instance().get_next_dx();
	f1[0]=10*dx+f1[1];
	f1.push_back(f1[f1.size()-2]);
	return f1;
}
VecLong first_kind_nonclear(const VecLong &f0, long double p){
	/**
[A C B]
	*/
	VecLong A;
	VecLong B;
	VecLong C;
	int xN=f0.size();
	long double dt = CommonMethods::Instance().get_next_dt();
	CommonMethods::Instance().clear_corrent_x();
	for (int i = 0; i < xN; ++i){
		long double dx = CommonMethods::Instance().get_next_dx();
		A.push_back(-p*p*dt/(dx*dx));
		C.push_back(+2*p*p*dt/(dx*dx)+1);
		B.push_back(-p*p*dt/(dx*dx));
	}
	A[0]=0;
	B[B.size()-1]=0;
	return CommonMethods::matrixSolver(A,B,C,f0);
}

VecLong init1(){
	VecLong f0;
	int xN=CommonMethods::Instance().get_x_numbers();
	for (int i=0; i<xN/2; i++){
		f0.push_back(i*0.5);
	}
	for (int i=xN/2; i<xN; i++){
		f0.push_back(f0[xN/2-1]-(i-xN/2)*0.5);
	}
	return f0;

}

