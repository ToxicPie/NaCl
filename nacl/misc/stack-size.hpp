constexpr size_t size = 200 << 20; // 200MiB
int main() {
  register long rsp asm("rsp");
  char *buf = new char[size];
  asm("movq %0, %%rsp\n" ::"r"(buf + size));
  // do stuff
  asm("movq %0, %%rsp\n" ::"r"(rsp));
  delete[] buf;
}
