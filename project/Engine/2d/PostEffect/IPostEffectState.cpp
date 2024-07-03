#include "IPostEffectState.h"

// タイトルシーンで初期化
int IPostEffectState::effectNo = kOutline;

// 仮想デストラクタの定義
// 純粋仮想関数化していないので、ここで定義できる
IPostEffectState::~IPostEffectState() {}

// エフェクト番号のゲッター
int IPostEffectState::GetEffectNo(){ return effectNo;}

// エフェクト番号のセッター
void IPostEffectState::SetEffectNo(int effectNo) { effectNo = effectNo;}
