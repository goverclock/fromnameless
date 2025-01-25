int strlen(const char *s) {
  int ret = 0;
  while (s[ret])
    ret++;
  return ret;
}
