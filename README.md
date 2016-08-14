- Кузнечик https://github.com/mjosaarinen/kuznechik
- Стрибог https://www.streebog.net/

```
$ dd if=/dev/urandom of=crypt_test bs=4K count=100000
$ make
$ make clean
$ sudo -i
# insmod kuznechik.ko
# insmod stribog.ko
# losetup /dev/loop0 crypt_test
# echo -n "123" | cryptsetup luksFormat --cipher kuznechik --hash stribog256 --key-size 256 /dev/loop0
# echo -n "123" | cryptsetup luksOpen /dev/loop0 crypt_test
# mkfs.ext4 /dev/mapper/crypt_test -L test
# mkdir crypt_test_mnt
# mount /dev/mapper/crypt_test crypt_test_mnt
....
# umount crypt_test_mnt
# cryptsetup luksClose crypt_test
# losetup -d /dev/loop0
# rmmod kuznechik.ko
# rmmod stribog.ko
# exit
$ file crypt_test
```
