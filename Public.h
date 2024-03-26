/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_securebootuefi,
    0xb94987a1,0x83a1,0x4e8c,0x83,0x3c,0x14,0x39,0x83,0x0b,0xf6,0x09);
// {b94987a1-83a1-4e8c-833c-1439830bf609}
