package main
import "testing"

func BenchmarkMakeThreads(b *testing.B) {
  make_threads(100000)
}

func BenchmarkCh(b *testing.B) {
  main_ch, start_ch := make_threads(100000)

  b.ResetTimer()
  exec_ch(start_ch, main_ch)
}
