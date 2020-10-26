package main

import "fmt"

func main() {
	// verified using https://www.boxentriq.com/code-breaking/modular-exponentiation
	fmt.Println(sqmul(11, 13, 52))
	fmt.Println(sqmul(22, 1024, 31))
}

func sqmul(x, e, m int) int {
	r := 1
	expBinStr := fmt.Sprintf("%b", e)
	for i := 0; i < len(expBinStr); i++ {
		r = r * r % m
		if expBinStr[i] == '1' {
			r = r * x % m
		}
	}
	return r
}