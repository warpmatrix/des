# DES (Data Encryption Standard)

DES 是一种典型的块加密方法：它以64位为分组长度，明文被分割成64位一组作为算法的输入，经过一系列计算过程，输出同样64位长度的密文。

DES 使用加密密钥定义变换过程，因此被认为只有持有加密密钥的用户才能解密密文。

原始明文消息按 PKCS#5 (RFC 8018) 规范进行字节填充：

- 原始明文消息最后的分组不够8个字节 (64位) 时，在末尾以字节填满，填入的字节取值相同，都是填充的字节数目；
- 原始明文消息刚好分组完全时，在明文末尾额外填充8个字节 (即增加一个完整分组)，每个字节取值都是08。

> 这里的 des 使用小端模式，并且一个字节中最高位作为第 8 位，与网上的大多数代码不同。（若使用 ascii 码输入密钥，每个字节的第 8 位正好可以作为奇偶校验位）

## Quick Start

Use the follow commands to run demo：

```shell
git clone git@github.com:warpmatrix/des.git
cd des
make
./bin/des
```
