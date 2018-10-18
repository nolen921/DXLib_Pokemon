#include <WICTextureLoader.h>
#include "texture.h"

// メンバ変数の実体を宣言
//int Texture::num_;

ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context )
{
    // num_ = 100;
    
    ID3D11ShaderResourceView* texture_;

    if( FAILED( CreateWICTextureFromFileEx(
        Device,                     // D3Dデバイスインターフェイス
        Context,                    // デバイスコンテキストインターフェイス
        FileName,                   // ファイル名（ワイド文字で指定）
        0,                          // ミニマップレベル
        D3D11_USAGE_DEFAULT,        // 使用方法
        D3D11_BIND_SHADER_RESOURCE, // バインドの種類
        0,                          // CPUアクセス方法
        0,                          // フラグオプション
        WIC_LOADER_DEFAULT,         // SRGBフラグ
        NULL,                       // リソースデータ受取先ポインタ
        &texture_ ) ) )             // シェーダーリソースビュー
    {
        // エラー
        return NULL;
    }

    return texture_;
}