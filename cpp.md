Use more often:
non-compiler bit functions:
std::has_single_bit()
std::popcount
1 << std::bit_width = std::bit_ceil
std::bit_floor(n) <= bit_ceil(n)

std::partial_sum -> normal prefix/suffix in-place, std::inclusive_scan, std::exclusive_scan a bit more powerful and verbose
You can use if(cmx(x, y)) { cout << ... } to debug more easily!

Fun cpp things I learned through my template in addition to basic concepts:

std::conditional_t, std::monostate for conditional storage / return types among template instantiations
