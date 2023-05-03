import java.io.*
import java.util.*

@JvmField val cin = System.`in`.bufferedReader()
@JvmField val cout = PrintWriter(System.out, false)
@JvmField var tokenizer: StringTokenizer
                       = StringTokenizer("")
fun nextLine() = cin.readLine()!!
fun read(): String {
  while(!tokenizer.hasMoreTokens())
    tokenizer = StringTokenizer(nextLine())
  return tokenizer.nextToken()
}

// example
fun main() {
  val n = read().toInt()
  val a = DoubleArray(n) { read().toDouble() }
  cout.println("omg hi")
  cout.flush()
}
