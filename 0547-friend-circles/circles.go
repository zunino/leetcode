package main

import (
	"fmt"
)

func uniqueIndex(dim, i, j int) int {
	return i*dim + j - (i*i+i)/2
}

func visit(m [][]int, i int, j int, visited []bool) {
	dim := len(m)
	index := uniqueIndex(dim, i, j)
	if visited[index] {
		return
	}
	visited[index] = true
	// row
	for col := i; col < dim; col++ {
		if m[i][col] == 1 {
			visit(m, i, col, visited)
		}
	}
	// column
	for row := 0; row <= j; row++ {
		if m[row][j] == 1 {
			visit(m, row, j, visited)
		}
	}
}

func findCircleNum(m [][]int) int {
	dim := len(m)
	if dim != len(m[0]) {
		panic("Matrix should be square")
	}
	visited := make([]bool, (dim*dim+dim)/2)
	circles := 0
	for i := 0; i < dim; i++ {
		for j := i; j < dim; j++ {
			if visited[uniqueIndex(dim, i, j)] || m[i][j] == 0 {
				continue
			}
			visit(m, i, j, visited)
			circles++
		}
	}
	return circles
}

func main() {
	m1 := [][]int{
		{1, 1, 0},
		{1, 1, 0},
		{0, 0, 1},
	}
	m2 := [][]int{
		{1, 1, 0},
		{1, 1, 1},
		{0, 1, 1},
	}
	m3 := [][]int{
		{1, 1, 0, 1},
		{1, 1, 1, 0},
		{0, 1, 1, 1},
		{1, 0, 1, 1},
	}
	m4 := [][]int{
		{1, 0, 0, 1},
		{0, 1, 1, 0},
		{0, 1, 1, 1},
		{1, 0, 1, 1},
	}
	m5 := [][]int{
		{1, 1, 0, 0, 1},
		{1, 1, 0, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 1, 1, 0},
		{1, 0, 0, 0, 1},
	}
	fmt.Println("Circles in m1:", findCircleNum(m1))
	fmt.Println("Circles in m2:", findCircleNum(m2))
	fmt.Println("Circles in m3:", findCircleNum(m3))
	fmt.Println("Circles in m4:", findCircleNum(m4))
	fmt.Println("Circles in m5:", findCircleNum(m5))
}
