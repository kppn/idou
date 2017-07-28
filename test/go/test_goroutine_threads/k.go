package main
import "fmt"

func make_ch_threads(last_ch chan int, n int) chan int {
  var to_ch chan int
  own_ch := make(chan int)

  if (n-1) == 0 {
    to_ch = last_ch
  } else {
    to_ch = make_ch_threads(last_ch, n-1)
  }

  go func(to chan int, from chan int) {
    x := <-from
    to <- (x+1)
  }(to_ch, own_ch)

  return own_ch
}

func make_threads(n int) (chan int, chan int) {
  main_ch  := make(chan int)
  start_ch := make_ch_threads(main_ch, n)
  return main_ch, start_ch
}

func exec_ch(start_ch chan int, main_ch chan int) int {
  start_ch <- 0
  return (<-main_ch)
}

func muladd(a int, b int, c int) int {
  return a * b + c
}

func main() {
  main_ch, start_ch := make_threads(100000)
  result := exec_ch(start_ch, main_ch)

  fmt.Println(result)
}
