#pragma once

#include<Windows.h>
#include<cstdio>

class Error
{
public:
    static void showDialog( const char* Message )
    {
        MessageBox(
            NULL,                           // �E�B���h�E�n���h��
            Message,   // ���b�Z�[�W
            "Error",                        // �^�C�g��
            MB_OK | MB_ICONERROR );         // �t���O
    }
};