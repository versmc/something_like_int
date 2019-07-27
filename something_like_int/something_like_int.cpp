// something_like_int.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include "cmpt/arithmetic_interface.hpp"

int main()
{

	if (1) {
		using namespace cmpt::arithmetic;

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

	}
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
