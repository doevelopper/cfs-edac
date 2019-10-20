

#ifndef CFS_FSM_ERROR_SM_HPP
#define CFS_FSM_ERROR_SM_HPP

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace cfs::fsm
{
    namespace sml = boost::sml;

    class Error_SM
    {
    public:

        auto opeartor()()
        {
            return make_transition_table(
                *("idle"_s) + "event1"_e / []
                {
                    throw std::runtime_error{"error"};
                }
                , "idle"_s  + "event2"_e / []
                {
                    throw 0;
                }
                , *("exceptions handling"_s) + exception<std::runtime_error> / []
                {
                    std::cout << "exception caught" << std::endl;
                }
                , "exceptions handling"_s  + exception<_> / []
                {
                    std::cout << "generic exception caught" << std::endl;
                } = X
                , *("unexpected events handling"_s) + unexpected_event<some_event> / []
                {
                    std::cout << "unexpected event 'some_event'" << std::endl;
                }
                , "unexpected events handling"_s  + unexpected_event<_> / []
                {
                    std::cout << "generic unexpected event" << std::endl;
                } = X );
        }
    };
}

#endif

