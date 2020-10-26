package main

import "fmt"

type LFSR struct {
	value, length int
}

var (
	X, Y, Z = &LFSR{
		value: 0b1111101010101010101,
		length: 19,
	}, &LFSR{
		value: 0b1100110011001100110011,
		length: 22,
	}, &LFSR{
		value: 0b11100001111000011110000,
		length: 23,
	}
)

func main() {
	fmt.Print("N = ")
	var length int
	fmt.Scanf("%d", &length)
	genA51KeyStreamToStdout(length)
	fmt.Println()
}

func genA51KeyStreamToStdout(n int) {
	fmt.Print("Key stream: ")
	for i := 0; i < n; i++ {
		fmt.Print(genStreamBit())
		decideRegsToStep()
	}
}

func genStreamBit() int {
	return (X.value & 1) ^ (Y.value & 1) ^ (Z.value & 1)
}

func decideRegsToStep() {
	major := getMajorBit()
	if getBit(X, 8) == major {
		step(X)
	}
	if getBit(Y, 10) == major {
		step(Y)
	}
	if getBit(Z, 10) == major {
		step(Z)
	}
}

func getMajorBit() int {
	sum := getBit(X, 8) + getBit(Y, 10) + getBit(Z, 10)
	if sum <= 1 {
		return 0
	}
	return 1
}

func getBit(reg *LFSR, bitPos int) int {
	return (reg.value >> (reg.length - 1 - bitPos)) & 1
}

func step(reg *LFSR) {
	var msb int
	switch reg.length {
		case 19:
			msb = getBit(reg, 13) ^ getBit(reg, 16) ^ getBit(reg, 17) ^ getBit(reg, 18)
		case 22:
			msb = getBit(reg, 20) ^ getBit(reg, 21)
		case 23:
			msb = getBit(reg, 20) ^ getBit(reg, 21) ^ getBit(reg, 22)
	}
	reg.value = (reg.value >> 1) | (msb << (reg.length - 1))
}