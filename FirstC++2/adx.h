#pragma once

// Include
#include <cri_adx2le.h>
#include "release.h"

// Class
class Adx
{
private:
    static CriAtomExVoicePoolHn voice_pool_; // ボイスプール
    static CriAtomExAcbHn acb_;              // ACBハンドル
    static CriAtomExPlayerHn player_;        // プレイヤーハンドル

public:
    static bool init( const CriChar8* acfFilePath ); // 初期化Path );
    static bool load( const CriChar8* acbFilePath, CriChar8* awbFile ); // サウンドの読み込み
    static void destroy(); // 破棄
    static void play( CriAtomExCueId id = 0 ); // 再生

    // 停止
    static void stop() { criAtomExPlayer_Stop( player_ ); }
    static void stop( CriAtomExCueId id ) { criAtomExPlayback_Stop( id ); }
   
    // ADXライブラリ更新処理
    static void update() { criAtomEx_ExecuteMain(); }

    // エラー処理関数
    static void userErrorCallback(
        const CriChar8* ErrorId,
        CriUint32 P1,
        CriUint32 P2,
        CriUint32* pArray );
};