// Include
#include "adx.h"

// ���̂̐錾
CriAtomExVoicePoolHn Adx::voice_pool_;
CriAtomExAcbHn Adx::acb_;
CriAtomExPlayerHn Adx::player_;

// �v���g�^�C�v�錾
void* user_alloc_func( void* obj, CriUint32 size );
void  user_free_func( void* obj, void* ptr );

// ������
bool Adx::init( const CriChar8* acfFilePath )
{
    // �G���[�R�[���o�b�N�֐��̓o�^
    criErr_SetCallback( userErrorCallback );

    // �������A���P�[�^�֐��̓o�^
    criAtomEx_SetUserAllocator( user_alloc_func, user_free_func, NULL );

    // ���C�u����������
    criAtomEx_Initialize_WASAPI( NULL, NULL, 0 );

    // �X�g���[�~���O�p�o�b�t�@�̍쐬
    CriAtomDbasId dbas = criAtomDbas_Create( NULL, NULL, 0 );

    // �S�̐ݒ�t�@�C���̓o�^
    if( !criAtomEx_RegisterAcfFile( NULL, "Game.acf", NULL, 0 ) )
    {
        // �G���[
        return false;
    }

    // DSP�o�X�ݒ�̓o�^
    criAtomEx_AttachDspBusSetting( "DspBusSetting_0", NULL, 0 );

    // �{�C�X�v�[���\���̂̍쐬
    CriAtomExStandardVoicePoolConfig vpconfig;

    // �f�t�H���g�l��ݒ�
    criAtomExVoicePool_SetDefaultConfigForStandardVoicePool( &vpconfig );

    // �X�g���[�~���O�Đ��L��
    vpconfig.player_config.streaming_flag = CRI_TRUE;

    // �{�C�X�v�[���̍쐬
    voice_pool_ = criAtomExVoicePool_AllocateStandardVoicePool(
        &vpconfig, NULL, 0 );

    // �v���C���[�n���h�����쐬
    player_ = criAtomExPlayer_Create( NULL, NULL, 0 );

    return true;
}

// �ǂݍ���
bool Adx::load( const CriChar8* acbFilePath, CriChar8* awbFilePath )
{
    // acb�t�@�C���̓ǂݍ���
    acb_ = criAtomExAcb_LoadAcbFile(
        NULL, acbFilePath, NULL, awbFilePath, NULL, 0 );

    return true;
}

// �Đ�
void Adx::play( CriAtomExCueId id )
{
    // ACB�n���h����ݒ�
    criAtomExPlayer_SetCueId( player_, acb_, id );

    // �L���[�̍Đ�
    criAtomExPlayer_Start( player_ );
}

// �j��
void Adx::destroy()
{
    criAtomExPlayer_Destroy( player_ );
    criAtomExAcb_Release( acb_ );
    criAtomExVoicePool_Free( voice_pool_ );
    criAtomEx_UnregisterAcf();
    criAtomEx_Finalize_WASAPI();
}


// �R�[���o�b�N�֐�
void Adx::userErrorCallback( const CriChar8* ErrorId, CriUint32 P1, CriUint32 P2, CriUint32* pArray )
{
    const CriChar8* msg;
    msg = criErr_ConvertIdToMessage( ErrorId, P1, P2 );
    OutputDebugString( msg );
}



// �������m�ۊ֐��̎���
void* user_alloc_func( void* obj, CriUint32 size )
{
    void* ptr = static_cast<void*>(new char[ size ]);
    return ptr;
}

// ����������֐��̎���
void user_free_func( void* obj, void* ptr )
{
    SAFE_DELETE_ARRAY( ptr );
}