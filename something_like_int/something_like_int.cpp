// something_like_int.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "cmpt/arithmetic_interface.hpp"

int main(){
	using namespace cmpt::arithmetic;
	
	if (1) {
		// int のような型でインクリメント、デクリメントのみが可能な型を定義
		class SomethingIncrementable : public Incrementable<StackBase<SomethingIncrementable, int>> {};

		auto i2 = SomethingIncrementable().set(2);
		++i2;	// インクリメント可能
		i2--;	// デクリメント可能
		SomethingIncrementable i2_copy = i2;	// コピー可能

		// i2 = i2 + i2;					// エラー 加算は定義されていない 
		// SomethingIncrementable i3{3};	// エラー オリジナルの型からの暗黙変換不可
		// int i = i2;						// エラー オリジナルの型への暗黙変換不可
	}

	if (1) {
		// int のような型でインクリメント、デクリメント、加算、乗算、比較 が可能なものを定義
		class SomethingLikeInt : public Comparable<Productable<Addable<Incrementable<StackBase<SomethingLikeInt, int>>>>> {};

		auto i2 = SomethingLikeInt().set(2);
		auto i3 = i2;
		i3++;
		auto i5 = i2 + i3;
		std::cout << i5.get() << std::endl;
		auto i6 = i2 * i3;
		std::cout << i6.get() << std::endl;
		std::cout << (i2 < i3) << std::endl;
		std::cout << (i2 == i3) << std::endl;
	}
	
	if (1) {

		class Double : public Comparable<Productable<Addable<StackBase<Double, double>>>> {};
		
		auto pi = Double().set(3.14);
		auto r = Double().set(5.0);
		auto circ = Double().set(2.0) * pi * r;
		auto area = pi * r * r;
		


	}

	return 0;
}
