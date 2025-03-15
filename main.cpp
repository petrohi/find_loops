#include <iostream>
#include <vector>

struct Loop
{
    size_t start;
    size_t length;
    size_t count;
};

void find_loop(Loop& loop, std::vector<uint32_t>::const_iterator start, std::vector<uint32_t>::const_iterator end) {
    if (end - start >= loop.length * 2) {
        auto next_start = start + loop.length;

        auto i = start;
        auto j = next_start;
        while (i != next_start) {
            if (*i != *j) {
                return;
            }
            i++;
            j++;
        }
        loop.count++;
        find_loop(loop, next_start, end);
    }
}

std::vector<Loop> find_loops_of_length(const std::vector<uint32_t> &trace, size_t length)
{
    std::vector<Loop> loops;

    for (auto i = trace.begin(); i != trace.end(); i++)
    {
        Loop loop{static_cast<size_t>(i - trace.begin()), length, 1};

        find_loop(loop, i, trace.end());

        if (loop.count > 1)
        {
            loops.push_back(loop);
        }
    }

    return loops;
}

std::vector<Loop> find_loops(const std::vector<uint32_t> &trace)
{
    std::vector<Loop> loops;

    for (size_t i = 1; i < trace.size() / 2 + 1; i++)
    {
        auto loops_of_length = find_loops_of_length(trace, i);
        loops.insert(loops.end(), loops_of_length.begin(), loops_of_length.end());
    }

    return loops;
}

int main()
{
    std::string line;
    std::vector<uint32_t> trace;

    while (std::getline(std::cin, line))
    {
        trace.push_back(std::stoi(line));
    }

    std::vector<Loop> loops = find_loops(trace);

    for (const auto &loop : loops)
    {

        std::cout << "Loop{start=" << loop.start << ",length=" << loop.length << ",count=" << loop.count << "}" << std::endl;
    }

    return 0;
}