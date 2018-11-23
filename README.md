# Solo-C-API
C level API for WOOKONG Solo

Supported OS list:

macOS Mavericks (10.9) and above

Windows 7/8/8.1/10 x64

for macOS, use the following commands to compile and run:
```
gcc -o EWalletTest -L. -lEWallet EWalletTest.c
cp libEWallet.dylib /usr/local/lib
./EWalletTest
```

for Windows, use the following commands to compile and run:
```
cl EWalletTest.cpp
EWalletTest
```

