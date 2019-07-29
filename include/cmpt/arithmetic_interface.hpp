#pragma once


namespace cmpt {

	/// <summary>
	/// 使える演算子を制限した型を生成するクラステンプレートを定義する
	/// CRTP を使ってインターフェースを作る
	/// 
	/// 現在
	/// インクリメント、デクリメント
	/// 加算、減算
	/// 乗算、除算
	/// 比較演算子
	/// をサポートしている
	/// 
	/// 将来的には
	/// ビット演算、シフト演算
	/// をサポートしたい
	/// </summary>
	namespace arithmetic {

		/// <summary>
		/// CRTP を使いやすくするための関数やタイプエイリアス定義
		/// これを継承していく
		/// </summary>
		template <class Derived_>
		class CRTPBase {
		public:
			using Derived = Derived_;

			Derived& derived() {
				return *static_cast<Derived*>(this);
			}

			const Derived& derived() const {
				return *static_cast<const Derived*>(this);
			}
		};


		/// <summary>
		/// 型 StackType を内部に持つクラス定義
		/// 本クラステンプレートを継承してインターフェースを追加していくが、
		/// 各インターフェースで使う関数、演算子を StackType_ が持っている必要がある
		/// 
		/// 現在 get set ref をもたせているが分離可能
		/// </summary>
		template <class Derived_, class StackType_>
		class StackBase : public CRTPBase<Derived_> {
		public:
			using Derived=Derived_;
			using StackType = StackType_;

		protected:
			StackType data_;

		public:
			const StackType& get() const {
				return this->data_;
			}

			Derived& set(const StackType& data_x) {
				this->data_ = data_x;
				return this->derived();
			}

			StackType& ref() { 
				return this->data_; 
			}

			const StackType& ref()const {
				return this->data_;
			}
		};


		/// <summary>
		/// インクリメント ++ とデクリメント -- を定義
		/// テンプレート引数 StackBase_ は StackBase かそれを継承したものを指定する
		/// </summary>
		template <class StackBase_>
		class Incrementable : public StackBase_ {

		public:
			using StackType=typename StackBase_::StackType;
			using Derived = typename StackBase_::Derived;
			

			Derived& operator++() {
				++this->data_;
				return this->derived();
			}
			Derived operator++(int) {
				Derived x;
				x.data_ = this->data_;
				operator++();
				return x;
			}
			Derived& operator--() {
				--this->data_;
				return this->derived();
			}
			Derived operator--(int) {
				Derived x;
				x.data_ = this->data_;
				operator--();
				return x;
			}
		};


		/// <summary>
		/// 加算 + - += -= + - を定義
		/// テンプレート引数 StackBase_ は StackBase かそれを継承したものを指定する
		/// </summary>
		template <class StackBase_>
		class Addable : public StackBase_ {
		public:
			using Derived = typename StackBase_::Derived;
			using StackType = typename StackBase_::StackType;

			Derived operator+() {
				return this->derived();
			}
			Derived operator-() {
				Derived x;
				x.data_ = -this->data_;
				return x;
			}
			Derived& operator+=(const Derived& other) {
				this->data_ += other.data_;
				return this->derived();
			}
			Derived& operator-=(const Derived& other) {
				this->data_ += -other.data_;
				return this->derived();
			}
			Derived operator+(const Derived& rhs) {
				Derived x(this->derived());
				x += rhs;
				return x;
			}
			Derived operator-(const Derived& rhs) {
				Derived x(this->derived());
				x -= rhs;
				return x;
			}
		};



		/// <summary>
		/// 乗算 * / *= /= を定義
		/// テンプレート引数 StackBase_ は StackBase かそれを継承したものを指定する
		/// </summary>
		template <class StackBase_>
		class Productable : public StackBase_{
		public:
			using Derived = typename StackBase_::Derived;
			using StackType = typename StackBase_::StackType;

			Derived& operator*=(const Derived& other) {
				this->data_ *= other.data_;
				return this->derived();
			}
			Derived& operator/=(const Derived& other) {
				this->data_ /= -other.data_;
				return this->derived();
			}
			Derived operator*(const Derived& rhs) const {
				Derived x(this->derived());
				x *= rhs;
				return x;
			}
			Derived operator/(const Derived& rhs) const {
				Derived x(this->derived());
				x /= rhs;
				return x;
			}
		};


		/// <summary>
		/// 比較演算子 { } == != を定義
		/// less than を表すオペレータ { から他の演算子は類推するようになっている
		/// テンプレート引数 StackBase_ は StackBase かそれを継承したものを指定する
		/// </summary>
		template <class StackBase_>
		class Comparable : public StackBase_ {
		public:
			using Derived = typename StackBase_::Derived;
			using StackType = typename StackBase_::StackType;

			bool operator<(const Derived& rhs) const {
				return this->data_ < rhs.data_;
			}
			bool operator>(const Derived& rhs) const {
				return rhs.operator<(this->derived());
			}
			bool operator!=(const Derived& rhs) const {
				return operator<(rhs) || operator>(rhs);
			}
			bool operator==(const Derived& rhs) const {
				return !operator!=(rhs);
			}
		};

	}
}


