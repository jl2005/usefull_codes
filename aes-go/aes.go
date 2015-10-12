package aes

import (
    "errors"
	"bytes"
	"crypto/aes"
	"crypto/cipher"
)

func AesEcbEncrypt(origData, key []byte) ([]byte, error) {
	return aesEncrypt(origData, key, "ecb")
}

func AesEcbDecrypt(crypted, key []byte) ([]byte, error) {
	return aesDecrypt(crypted, key, "ecb")
}

func AesCbcEncrypt(origData, key []byte) ([]byte, error) {
	return aesEncrypt(origData, key, "cbc")
}

func AesCbcDecrypt(crypted, key []byte) ([]byte, error) {
	return aesDecrypt(crypted, key, "cbc")
}

func aesEncrypt(origData, key []byte, mode string) ([]byte, error) {
    if len(origData) == 0 {
        return make([]byte, 0), nil
    }
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	blockSize := block.BlockSize()
	origData = PKCS5Padding(origData, blockSize)
	crypted := make([]byte, len(origData))
	switch mode {
	case "ecb":
		ecb := NewECBEncrypter(block)
		ecb.CryptBlocks(crypted, origData)
	case "cbc":
		blockMode := cipher.NewCBCEncrypter(block, key[:blockSize])
		blockMode.CryptBlocks(crypted, origData)
	default:
		return nil, errors.New("aseEncrypt mode error. mode=" + mode)
	}
	return crypted, nil
}

func aesDecrypt(crypted, key []byte, mode string) ([]byte, error) {
    if len(crypted) == 0 {
        return make([]byte, 0), nil
    }
	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}
	origData := make([]byte, len(crypted))
	switch mode {
	case "ecb":
		ecb := NewECBDecrypter(block)
		ecb.CryptBlocks(origData, crypted)
	case "cbc":
        blockSize := block.BlockSize()
		blockMode := cipher.NewCBCDecrypter(block, key[:blockSize])
		blockMode.CryptBlocks(origData, crypted)
	default:
		return nil, errors.New("aseEncrypt mode error. mode=" + mode)
	}
	origData = PKCS5UnPadding(origData)
	return origData, nil
}

func ZeroPadding(ciphertext []byte, blockSize int) []byte {
	padding := blockSize - len(ciphertext)%blockSize
	padtext := bytes.Repeat([]byte{0}, padding)
	return append(ciphertext, padtext...)
}

func ZeroUnPadding(origData []byte) []byte {
	length := len(origData)
	unpadding := int(origData[length-1])
	return origData[:(length - unpadding)]
}

func PKCS5Padding(ciphertext []byte, blockSize int) []byte {
	padding := blockSize - len(ciphertext)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(ciphertext, padtext...)
}

func PKCS5UnPadding(origData []byte) []byte {
	length := len(origData)
	// 去掉最后一个字节 unpadding 次
	unpadding := int(origData[length-1])
    if unpadding >= length {
        return make([]byte, 0)
    }
	return origData[:(length - unpadding)]
}
