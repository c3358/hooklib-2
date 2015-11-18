#ifndef __IPC_NAMED_PIPE_H
#define __IPC_NAMED_PIPE_H

#include <Windows.h>
#include "../defines.h"
#include "../security/security_utils.h"

#define IPC_NAMED_PIPE_NAME_LENGTH 0x100

typedef struct _NAMED_PIPE
{
    WCHAR ObjectName[IPC_NAMED_PIPE_NAME_LENGTH];
    HANDLE ObjectHandle;
    HANDLE EventHandle;
} NAMED_PIPE, *PNAMED_PIPE;

typedef
BOOL
(*NAMED_PIPE_LEAVE_PROC)(
    LPVOID Context
);

BOOL
IpcCreateNamedPipe(
    IN LPCWSTR ObjectName,
    IN BOOL FirstInstance,
    IN DWORD OutBufferSize,
    IN DWORD InBufferSize,
    IN DWORD DefaultTimeout,
    OUT PNAMED_PIPE NamedPipe
);

BOOL
IpcDestroyNamedPipe(
    IN PNAMED_PIPE NamedPiped
);

BOOL
IpcOpenNamedPipe(
    IN LPCWSTR ObjectName,
    IN BOOL WaitIfNotAvailable,
    OUT PNAMED_PIPE NamedPipe
);

BOOL
IpcCloseNamedPipe(
    IN PNAMED_PIPE NamedPipe
);

BOOL
IpcWaitConnectClient(
    IN PNAMED_PIPE NamedPipe,
    IN DWORD Timeout,
    IN LPVOID Context,
    IN NAMED_PIPE_LEAVE_PROC LeaveProc
);

BOOL
IpcDisconnectClient(
    IN PNAMED_PIPE NamedPipe
);

BOOL
IpcReadFromNamedPipe(
    IN PNAMED_PIPE NamedPipe,
    IN LPVOID Buffer,
    IN DWORD BufferSize,
    IN BOOL IsServerSide,
    IN LPVOID Context,
    IN NAMED_PIPE_LEAVE_PROC LeaveProc
);

BOOL
IpcWriteToNamedPipe(
    IN PNAMED_PIPE NamedPipe,
    IN LPVOID Buffer,
    IN DWORD BufferSize,
    IN BOOL IsServerSide,
    IN LPVOID Context,
    IN NAMED_PIPE_LEAVE_PROC LeaveProc
);

BOOL
IpcFlushNamedPipe(
    IN PNAMED_PIPE NamedPipe
);

#endif