package aes

import (
	"bytes"
	"testing"
)

func TestAesEcb(t *testing.T) {
	// AES-128。key长度：16, 24, 32 bytes 对应 AES-128, AES-192, AES-256
	key := []byte("sfe023f_9fd&fwfl")
	data := []byte("polaris@studygolang")
	result, err := AesEcbEncrypt(data, key)
	if err != nil {
		t.Error(err)
	}
	origData, err := AesEcbDecrypt(result, key)
	if err != nil {
		t.Error(err)
	}
	if bytes.Compare(origData, data) != 0 {
		t.Error("Ecb crypt failed. Decrypt data is '%s'\n", origData)
	}
	t.Log("Test aes/ecb past")
}

func TestAesCbc(t *testing.T) {
	// AES-128。key长度：16, 24, 32 bytes 对应 AES-128, AES-192, AES-256
	key := []byte("sfe023f_9fd&fwfl")
	data := []byte("polaris@studygolang")
	result, err := AesCbcEncrypt(data, key)
	if err != nil {
		t.Error(err)
	}
	origData, err := AesCbcDecrypt(result, key)
	if err != nil {
		t.Error(err)
	}
	if bytes.Compare(origData, data) != 0 {
		t.Error("Ecb crypt failed. Decrypt data is ", origData)
	}
	t.Log("Test aes/cbc past")
}
