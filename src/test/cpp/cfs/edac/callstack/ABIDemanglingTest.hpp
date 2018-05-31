
#ifndef CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP
#define CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP

namespace cfs::edac::callstack

{
    class ABIDemanglingTest
    {

    public:

        ABIDemanglingTest();
        ~ABIDemanglingTest();

    protected:

        void Setup() override ;
        void TearDOwn() override;

    private:
    };
}
#endif
