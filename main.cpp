#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_3次元ベクトルの表示";

//表示幅:横
static const int kColumnWidth = 60;

//表示幅:縦
static const int kRowHeight = 20;

//3次元ベクトル
struct Vector3 {
	float x, y, z;
};

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);

//長さ(ノルム)
float Length(const Vector3& v);

//正規化
Vector3 Normalize(const Vector3& v);

//3次元ベクトルの各値の表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//1つ目のベクトル
	Vector3 v1{ 1.0f,3.0f,-5.0f };

	//2つ目のベクトル
	Vector3 v2{ 4.0f,-1.0f,2.0f };

	//スカラー倍
	float k = { 4.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		//加算結果
		Vector3 resultAdd = Add(v1, v2);

		//減算結果
		Vector3 resultSubtract = Subtract(v1, v2);

		//スカラー倍計算結果
		Vector3 resultMultiply = Multiply(k, v1);

		//内積計算結果
		float resultDot = Dot(v1, v2);

		//長さ計算結果
		float resultLength = Length(v1);

		//正規化結果
		Vector3 resultNormalize = Normalize(v2);



		//加算結果の表示
		VectorScreenPrintf(0, 0, resultAdd, " : Add");

		//減算結果の表示
		VectorScreenPrintf(0, kRowHeight, resultSubtract, " : Subtract");
		
		//スカラー倍計算結果の表示
		VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, " : Multiply");
		
		//内積計算結果の表示
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		
		//長さ計算結果の表示
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		
		//正規化結果の表示
		VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}


//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;

}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;

}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {

	float result = 0.0f;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;

}

//長さ(ノルム)
float Length(const Vector3& v) {
	
	float result = 0.0f;

	result = sqrtf(Dot(v,v));

	return result;

}


//正規化
Vector3 Normalize(const Vector3& v) {
	
	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;

}

//3次元ベクトルの各値の表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}
