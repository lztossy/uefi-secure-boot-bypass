# uefi secure boot bypass
code snippet is an example of a UEFI driver that implements a hook for the `GetVariable` UEFI runtime service. 
The hook is to simulate the enablement of the SB (secureboot) bios function, without it being enabled
this code is unfinished, and will most likely not be completed, maybe in the future when im free. 
Please feel free to use this as an example to fix ur shitty perm spoofer paste and actually add a functional sb bypass 😆

# code breakdown (for dumb amidewin spoof pasters)
- `EFI_GET_VARIABLE OriginalGetVariable` is a pointer used to store the original `GetVariable` function provided by the UEFI runtime service, before it gets called to hook
- `HookedGetVariable` replaces `GetVariable` which checks if the request var is secureboot, if it is, the function simulates it being enabled with a corresponding value and attritubte. for anything else, it calls the original getvariable function
- `UefiMain` is the entry point of the UEFI driver, it saves the original `GetVariable` function into `OriginalGetVariable` and sets `HookedGetVariable` to replace the original `GetVariable`
- the code also recalculates the CRC32 checksum for the uefi runtime service table, which is neccecary to maintain the integrity of the table after modifications
- `InitializeSecureBootHook` is the second entry point that calls `UefiMain`

# understanding the code (for pasters)
- this driver demonstrates how to intercept calls to a uefi runtime service in order to alter the behaviour for certain variables, while delegating all the other variable requests to the original service function.
- to implement, finish, and structure this code to work with your spoofer you need to have a bit of intelligence, creating a new file under 'sb bypass' and pasting this will not work and only give u 10 more errors

# how do i build this?
- Install https://github.com/tianocore/edk2 (EDK II) following the TianoCore documentation, which involves cloning the EDK II repository and setting up necessary tools like the compiler (GCC or CLANG for Linux, or MSVC for Windows).
- Within the EDK II workspace, create a new package directory for your driver if it doesn't exist already.
Inside this directory, create a .inf file that describes your driver and its sources. This file contains metadata and a list of the source files, include directories, library classes used, etc.
- Set up the environment variables needed by EDK II. This is typically done by running the edksetup.bat script on Windows or edksetup.sh script on Linux.
Configure the target architecture, build target (DEBUG or RELEASE), and toolchain in the Conf/target.txt file within the EDK II workspace.
- Open a command line or terminal window.
- Navigate to your EDK II workspace.
- Run the build command. The exact command depends on your environment, but it will typically look something like this:
  `build -p YourPackage/YourDriver.dsc -a X64 -b DEBUG -t GCC5`
  - In this command, replace YourPackage/YourDriver.dsc with the path to your .dsc file, X64 with your target architecture (it could also be IA32, ARM, AARCH64, etc.), DEBUG with your build target (it could also be RELEASE), and GCC5 with your toolchain tag (it could also be VS2017, VS2019, CLANG38, etc.).

# testing & debugging
- Once built, the driver will be an .efi executable located in the build output directory within the EDK II workspace.
You can then test this driver in a UEFI environment, such as using the UEFI shell, or by adding it to your system's firmware as an option ROM if appropriate.
