#pragma once
//シーン名を列挙型(Enum)で定義
enum POSTEFFECTMODE { FULLSCREEN, GRAYSCALE, VIGNETTING, SMOOTHING,GAUSSIANFILTER,OUTLINE,DISSOLVE,RANDOM,BLOOM,EFFECTNUM };


// シーン内での処理を行う基底クラス
class IPostEffectState {
protected:
	// シーン番号を管理する変数
	static int effectNo;
public:
	// 継承先で実装される関数
	/// 抽象クラスなので純粋仮想関数とする
	virtual void CommandBuffer() = 0;

	virtual void CommandBuffer() = 0;

	// 仮想デストラクタを用意しないと警告される
	virtual ~IPostEffectState();

	// シーン番号のゲッター
	static int GetEffectNo();
	static void SetEffectNo(int effectNo);


};