int main(int argc, char *argv[]) {
  /* initialize randomizer */
  struct timeval tp;
  gettimeofday(&tp, NULL);
  srand(tp.tv_sec * 1000000 + tp.tv_usec);
  gen();
  return 0;
}
