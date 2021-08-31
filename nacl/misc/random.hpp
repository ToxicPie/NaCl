#ifdef __unix__
random_device rd;
mt19937_64 RNG(rd());
#else
const auto SEED = chrono::high_resolution_clock::now()
                  .time_since_epoch()
                  .count();
mt19937_64 RNG(SEED);
#endif
// random long long: RNG();
// uniformly random type T (int, double, ...) in [l, r]:
// uniform_int_distribution<T> dist(l, r); dist(RNG);
