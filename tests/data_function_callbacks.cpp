#include <cassert>
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include "data/DataFunction.h"

float sample(size_t i) { return 2.0f * i + 1.0f; }

#if GRAFICI_USE_STD_FUNCTION
struct Generator
{
    float offset = 3;
    float sample(size_t i) const { return float(i) + offset; }
    DataFunction source()
    {
        return DataFunction(3, [this](size_t i) { return sample(i); }, {0, 10});
    }
};

struct Capture
{
    int *copies;
    explicit Capture(int &count) : copies(&count) {}
    Capture(const Capture &other) : copies(other.copies) { ++*copies; }
    float operator()(size_t i) const { return float(i); }
};
#endif

int main()
{
#if GRAFICI_USE_STD_FUNCTION
    static_assert(std::is_same<DataFunction::Callback, std::function<float(size_t)>>::value,
                  "Capturing callbacks are enabled explicitly");
#else
    static_assert(std::is_same<DataFunction::Callback, float (*)(size_t)>::value,
                  "The default retains raw-pointer storage");
#endif
    DataFunction inferred(3, sample);
    assert(inferred.size() == 3);
    assert(inferred.range().low == 1 && inferred.range().high == 5);
    assert(inferred[0].norm() == 0 && inferred[1].norm() == 0.5f && inferred[2].norm() == 1);
    DataFunction explicit_range(3, sample, {0, 10});
    assert(explicit_range[2].raw() == 5 && explicit_range[2].norm() == 0.5f);
    DataFunction no_capture(3, [](size_t i) { return float(i); });
    assert(no_capture[1].norm() == 0.5f);
    DataFunction::Callback empty{};
    DataFunction missing(3, empty), missing_range(3, empty, {0, 10});
    assert(missing.size() == 0 && missing_range.size() == 0);
    assert(missing[0].raw() == 0 && missing_range[0].raw() == 0);
    size_t calls = 0;
#if GRAFICI_USE_STD_FUNCTION
    DataFunction zero(0, [&calls](size_t i) { ++calls; return float(i); });
    assert(zero.size() == 0 && calls == 0);
    const float offset = 2;
    DataFunction captured(3, [offset](size_t i) { return float(i) + offset; });
    assert(captured.range().low == 2 && captured.range().high == 4);
    assert(captured[1].raw() == 3);
    Generator generator;
    auto member = generator.source();
    assert(member[1].raw() == 4);
    generator.offset = 5;
    assert(member[1].raw() == 6);
    auto copied = member;
    assert(copied[2].raw() == 7);
    int copies = 0;
    DataFunction::Callback callback = Capture(copies);
    const int before = copies;
    DataFunction moved(3, static_cast<DataFunction::Callback &&>(callback), {0, 10});
    assert(copies == before && moved[2].raw() == 2);
#else
    (void)calls;
    DataFunction zero(0, sample);
    assert(zero.size() == 0);
#endif
    std::puts(GRAFICI_USE_STD_FUNCTION ? "Captured and pointer callbacks passed." : "Default pointer callbacks passed.");
}
