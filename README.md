# Big Systems OS


--------- Prerequisites ---------
A text editor such as VS Code.
Docker for creating our build-environment.
Qemu for emulating our operating system.
Remember to add Qemu to the path so that you can access it from your command-line. (Windows instructions here)

--------- How to Build ---------
Enter build environment:
(Type this in one of the command lines below to enter the Docker build enviroment command line)
Linux or MacOS: docker run --rm -it -v "$pwd":/root/env bsos-buildenv
Windows (CMD): docker run --rm -it -v "%cd%":/root/env bsos-buildenv
Windows (PowerShell): docker run --rm -it -v "${pwd}:/root/env" bsos-buildenv

NOTE: If you are having trouble with an unshared drive, ensure your docker daemon has access to the drive you're development environment is in. For Docker Desktop, this is in "Settings > Shared Drives" or "Settings > Resources > File Sharing".

Build for x86 (other architectures may come in the future):
(Type this in the Docker build enviroment command line)
make build-x86_64


To leave the Docker build environment, enter exit.

--------- Emulate ---------
You can emulate your operating system using Qemu: (Don't forget to add qemu to your path!)
(For windows type this in cmd)
qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso

If the path doesn't work you can manually type the path here is an example:
(For windows type this in cmd)
"C:\Program Files\qemu\qemu-system-x86_64" -cdrom dist/x86_64/kernel.iso

NOTE: When building your operating system, if changes to your code fail to compile, ensure your QEMU emulator has been closed, as this will block writing to kernel.iso.
Alternatively, you should be able to load the operating system on a USB drive and boot into it when you turn on your computer. (I haven't actually tested this yet.)