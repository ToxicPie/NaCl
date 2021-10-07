struct scanner {
  static constexpr size_t LEN = 32 << 20;
  char *buf, *buf_ptr, *buf_end;
  scanner()
      : buf(new char[LEN]), buf_ptr(buf + LEN),
        buf_end(buf + LEN) {}
  ~scanner() { delete[] buf; }
  char getc() {
    if (buf_ptr == buf_end) [[unlikely]]
      buf_end = buf + fread_unlocked(buf, 1, LEN, stdin),
      buf_ptr = buf;
    return *(buf_ptr++);
  }
  char seek(char del) {
    char c;
    while ((c = getc()) < del) {}
    return c;
  }
  void read(int &t) {
    bool neg = false;
    char c = seek('-');
    if (c == '-') neg = true, t = 0;
    else t = c ^ '0';
    while ((c = getc()) >= '0') t = t * 10 + (c ^ '0');
    if (neg) t = -t;
  }
};
struct printer {
  static constexpr size_t CPI = 21, LEN = 32 << 20;
  char *buf, *buf_ptr, *buf_end, *tbuf;
  char *int_buf, *int_buf_end;
  printer()
      : buf(new char[LEN]), buf_ptr(buf),
        buf_end(buf + LEN), int_buf(new char[CPI + 1]()),
        int_buf_end(int_buf + CPI - 1) {}
  ~printer() {
    flush();
    delete[] buf, delete[] int_buf;
  }
  void flush() {
    fwrite_unlocked(buf, 1, buf_ptr - buf, stdout);
    buf_ptr = buf;
  }
  void write_(const char &c) {
    *buf_ptr = c;
    if (++buf_ptr == buf_end) [[unlikely]]
      flush();
  }
  void write_(const char *s) {
    for (; *s != '\0'; ++s) write_(*s);
  }
  void write(int x) {
    if (x < 0) write_('-'), x = -x;
    if (x == 0) [[unlikely]]
      return write_('0');
    for (tbuf = int_buf_end; x != 0; --tbuf, x /= 10)
      *tbuf = '0' + char(x % 10);
    write_(++tbuf);
  }
};
