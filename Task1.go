package main

import (
	"fmt"
	"math"
)

func main() {
	xStart := -7.5
	xEnd := 5.0
	dx := 0.5

	fmt.Printf("%10s | %10s\n", "x", "y")
	fmt.Println("---------------------------")

	for x := xStart; x <= xEnd; x += dx {
		var y float64

		if x <= -6 {
			y = -2*x - 14
		} else if x > -6 && x <= -2 {
			y = -2 + math.Sqrt(4-math.Pow(x+4, 2))
		} else if x > -2 && x <= 2 {
			y = math.Log2(x + 2)
		} else if x > 2 && x <= 4 {
			y = math.Sqrt(1 - math.Pow(x-3, 2))
		} else {
			y = 0
		}

		fmt.Printf("%10.2f | %10.2f\n", x, y)
	}
}
