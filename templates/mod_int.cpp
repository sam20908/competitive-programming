template <int MOD>
struct mod_int
{
    T v{};
    constexpr mod_int() = default;
    constexpr mod_int(T vx) : v((vx % M + M) % M) {}
    constexpr mod_int &operator=(T vx)
    {
        v = (vx % M + M) % M;
        return *this;
    }
#define OP(op)                                                               \
    constexpr friend mod_int operator op(const mod_int &a, const mod_int &b) \
    {                                                                        \
        return ((a.v op b.v) % M + M) % M;                                   \
    }                                                                        \
    constexpr friend mod_int operator op(T a, const mod_int &b)              \
    {                                                                        \
        return (((a % M + M) % M op b.v) % M + M) % M;                       \
    }                                                                        \
    constexpr mod_int &operator op##=(const mod_int & other)                 \
    {                                                                        \
        v = ((v op other.v) % M + M) % M;                                    \
        return *this;                                                        \
    }
    OP(+)
    OP(-)
    OP(*)
#undef OP
    constexpr friend bool operator==(const mod_int &a, const mod_int &b) { return a.v == b.v; }
    constexpr friend bool operator!=(const mod_int &a, const mod_int &b) { return a.v != b.v; }
};