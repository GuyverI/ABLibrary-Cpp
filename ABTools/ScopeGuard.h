#pragma once

#include <functional>

namespace ABTools
{
    class ScopeGuard
    {
    public:
        ScopeGuard(std::function<void()> beginFunc, std::function<void()> endFunc)
            : _endFunc(std::move(endFunc))
        {
            if (beginFunc) {
                beginFunc();
            }
        }

        ~ScopeGuard()
        {
            if (_endFunc) {
                _endFunc();
            }
        }

    private:
        std::function<void()> _endFunc;
    };
}

