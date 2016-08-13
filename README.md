src from https://github.com/mjosaarinen/kuznechik
```
make
insmod kuznechik.ko
dd if=/dev/urandom of=crypt_test bs=4K count=100000
losetup /dev/loop0 crypt_test
cryptsetup -y luksFormat -c kuznechik -s 256 /dev/loop0
cryptsetup luksOpen /dev/loop0 crypt_test
mkfs.ext4 /dev/mapper/crypt_test -L test
mkdir crypt_test_mnt
mount /dev/mapper/crypt_test crypt_test_mnt
....
umount crypt_test_mnt
cryptsetup luksClose crypt_test
losetup -d /dev/loop0
file crypt_test
```
