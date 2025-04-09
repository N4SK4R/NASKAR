# 🛠️ i386 Toolchain + OS Build Environment

Use the Bash script to set up a cross-compilation environment for building a 32-bit i386 operating system. It includes:

- A GCC cross-compiler targeting `i386-elf`
- `nasm` for assembling low-level x86 code
- `qemu-system-x86_64` for running the compiled OS in a virtual machine

---



Run the script to build and install `binutils` and `gcc` for the `i386-elf` target:

```bash
chmod +x build-i386-toolchain.sh
sudo ./build-i386-toolchain.sh


echo '' >> ~/.bashrc
echo '# Destination folder for gcc-i386 and binutil-i386' >> ~/.bashrc
echo 'export PATH="/usr/local/i386-elf/bin:$PATH"' >> ~/.bashrc


sudo apt install -y nasm
sudo apt install -y qemu-system-x86
```


![OS](docs/os.gif) 


`make vbox` to run the .vdi file on vbox