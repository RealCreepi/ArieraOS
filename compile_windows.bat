md debug
nasm -felf32 src/boot.asm -o debug/boot.o
i686-elf-gcc -c src/kernel.c -o debug/kernel.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -c src/common.c -o debug/common.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -c src/Drivers/keyboard.c -o debug/keyboard.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -c src/Drivers/VGA.c -o debug/VGA.o -std=gnu99 -ffreestanding -masm=intel -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o debug/mountainos.bin -ffreestanding -O2 -nostdlib debug/boot.o debug/kernel.o debug/common.o debug/keyboard.o debug/VGA.o -lgcc
set /p run="Run? (requires QEMU) (y/n) "
if %run% EQU y qemu-system-i386 -kernel debug/mountainos.bin -machine type=pc-i440fx-3.1 -serial file:serial.log
pause